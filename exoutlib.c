// Copyright 2026 Kawamura Masato (kwmsnode)
// This file is part of EX Output Library(EX出力ライブラリ).
// EX Output Library(EX出力ライブラリ) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// EX Output Library(EX出力ライブラリ) is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with EX Output Library(EX出力ライブラリ). If not, see <https://www.gnu.org/licenses/>. 

// EX Output Library
// EX出力ライブラリ
// by kwmsnode (https://kwmsnode.f5.si/)(https://github.com/kwmsnode/)
// Ver. 1
// Provides output functionality for debugging on the device.
// This library depends on libdataplus, which is typically included with devkitSH4.
// 本体でのデバッグ用途の出力機能を提供します。
// このライブラリは、libdataplusに依存します。これは普通devkitSH4に付属しています。

// To accommodate multilingual use, the English comments provided here are primarily generated using Google Translate, though the original text is in Japanese. Please note this distinction.
// 多言語での利用を考慮し、Google 翻訳を用いた英文コメントを主として記載していますが、原文は日本語になります。ご注意ください。

#include "exoutlib.h"

#include <graphics/text.h>
#include <graphics/lcdc.h>
#include <graphics/color.h>
#include <graphics/drawing.h>
#include <string.h>
#include <stdio.h>

// exoutlib_printint cannot be used if MAX_CONTENT_MEMORY_SIZE is less than 32.
// MAX_CONTENT_MEMORY_SIZEが32より下になる場合、exoutlib_printintは利用できません。
#define MAX_CONTENT_MEMORY_SIZE 64
#define MAX_CONTENT_SIZE (MAX_CONTENT_MEMORY_SIZE - 1)

#if MAX_CONTENT_MEMORY_SIZE < 32
#error "MAX_CONTENT_MEMORY_SIZE must be at least 32"
#endif

#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 320

char contents[4][MAX_CONTENT_MEMORY_SIZE];
int8_t inited = 0;
int8_t shown = 0;

// ライブラリを初期化します。
// Initialize the library.
void exoutlib_initcontents() {
    contents[0][0] = '\0';
    contents[1][0] = '\0';
    contents[2][0] = '\0';
    contents[3][0] = '\0';
}

// 出力を1行繰ります。
// Advances the output by one line.
void exoutlib_shiftcontents() {
    // 0banana
    // 1ringo
    // 2orange
    // 3pale
    memcpy(&contents[3][0], &contents[2][0], MAX_CONTENT_MEMORY_SIZE);
    memcpy(&contents[2][0], &contents[1][0], MAX_CONTENT_MEMORY_SIZE);
    memcpy(&contents[1][0], &contents[0][0], MAX_CONTENT_MEMORY_SIZE);
    contents[0][0] = '\0';
}

// 出力を画面下部に表示して、自動表示を開始します。（4行）
// Display the output at the bottom of the screen and start automatic display. (4 lines)
void exoutlib_show() {
    if(inited == 0) { exoutlib_initcontents(); inited = 1; }
    set_pen(create_rgb16(0, 0, 0));
    draw_rect(14, SCREEN_HEIGHT - 70, SCREEN_WIDTH - 28, 56);
    set_pen(create_rgb16(255, 255, 255));
    render_text(14, SCREEN_HEIGHT - 70, &contents[0][0]);
    render_text(14, SCREEN_HEIGHT - 56, &contents[1][0]);
    render_text(14, SCREEN_HEIGHT - 42, &contents[2][0]);
    render_text(14, SCREEN_HEIGHT - 28, &contents[3][0]);
    lcdc_copy_vram();
    shown = 1;
}

// 出力を画面下部に表示して、自動表示を開始します。（2行）
// Display the output at the bottom of the screen and start automatic display. (2 lines)
void exoutlib_showmini() {
    if(inited == 0) { exoutlib_initcontents(); inited = 1; }
    set_pen(create_rgb16(0, 0, 0));
    draw_rect(14, SCREEN_HEIGHT - 42, SCREEN_WIDTH - 28, 28);
    set_pen(create_rgb16(255, 255, 255));
    render_text(14, SCREEN_HEIGHT - 42, &contents[0][0]);
    render_text(14, SCREEN_HEIGHT - 28, &contents[1][0]);
    lcdc_copy_vram();
    shown = 2;
}

// 出力を画面下部に表示して、自動表示を開始します。（1行）
// Display the output at the bottom of the screen and start automatic display. (1 line)
void exoutlib_showminimal() {
    if(inited == 0) { exoutlib_initcontents(); inited = 1; }
    set_pen(create_rgb16(0, 0, 0));
    draw_rect(14, SCREEN_HEIGHT - 28, SCREEN_WIDTH - 28, 14);
    set_pen(create_rgb16(255, 255, 255));
    render_text(14, SCREEN_HEIGHT - 28, &contents[0][0]);
    lcdc_copy_vram();
    shown = 3;
}

// 出力の自動表示を終了します。
// Stop automatic display of output.
void exoutlib_exitautoshow() {
    shown = 0;
}

// 出力を1行繰ってから、新たな行にコンテンツを書き込みます。
// Advance the output by one line, then write the content to the new line.
void exoutlib_print(const char *content) {
    if(inited == 0) { exoutlib_initcontents(); inited = 1; }
    if(content == NULL) { return; }
    exoutlib_shiftcontents();

    int copy_byte = 0;
    int contentsize = strlen(&content[0]);

    if(contentsize > MAX_CONTENT_SIZE) {
        copy_byte = MAX_CONTENT_SIZE;
    }else{
        copy_byte = contentsize;
    }

    memcpy(&contents[0][0], &content[0], copy_byte);
    contents[0][copy_byte] = '\0';
    if(shown == 1) { exoutlib_show(); }
    if(shown == 2) { exoutlib_showmini(); }
    if(shown == 3) { exoutlib_showminimal(); }
}

// 出力を1行繰ってから、新たな行にint型のコンテンツを書き込みます。MAX_CONTENT_MEMORY_SIZEが32より下になる場合、この関数は利用できません。
// Advances the output by one line and writes content of type int to the new line. This function cannot be used if MAX_CONTENT_MEMORY_SIZE is less than 32.
void exoutlib_printint(int intcontent) {
    if(inited == 0) { exoutlib_initcontents(); inited = 1; }
    exoutlib_shiftcontents();

    sprintf(&contents[0][0], "%d", intcontent);
    if(shown == 1) { exoutlib_show(); }
    if(shown == 2) { exoutlib_showmini(); }
    if(shown == 3) { exoutlib_showminimal(); }
}