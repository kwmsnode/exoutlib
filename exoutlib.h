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

#ifndef EXOUTLIB_H
#define EXOUTLIB_H

void exoutlib_initcontents(void);

void exoutlib_show(void);
void exoutlib_showmini(void);
void exoutlib_showminimal(void);
void exoutlib_exitautoshow(void);

void exoutlib_print(const char *content);
void exoutlib_printint(int intcontent);

#endif