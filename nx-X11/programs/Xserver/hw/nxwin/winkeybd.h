/*
 *Copyright (C) 1994-2000 The XFree86 Project, Inc. All Rights Reserved.
 *
 *Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 *"Software"), to deal in the Software without restriction, including
 *without limitation the rights to use, copy, modify, merge, publish,
 *distribute, sublicense, and/or sell copies of the Software, and to
 *permit persons to whom the Software is furnished to do so, subject to
 *the following conditions:
 *
 *The above copyright notice and this permission notice shall be
 *included in all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *NONINFRINGEMENT. IN NO EVENT SHALL THE XFREE86 PROJECT BE LIABLE FOR
 *ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 *CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *Except as contained in this notice, the name of the XFree86 Project
 *shall not be used in advertising or otherwise to promote the sale, use
 *or other dealings in this Software without prior written authorization
 *from the XFree86 Project.
 *
 * Authors:	Harold L Hunt II
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/winkeybd.h,v 1.3 2002/07/05 09:19:26 alanh Exp $ */

/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2001,2006 NoMachine, http://www.nomachine.com.           */
/*                                                                        */
/* NXWIN, NX protocol compression and NX extensions to this software      */
/* are copyright of NoMachine. Redistribution and use of the present      */
/* software is allowed according to terms specified in the file LICENSE   */
/* which comes in the source distribution.                                */
/*                                                                        */
/* Check http://www.nomachine.com/licensing.html for applicability.       */
/*                                                                        */
/* NX and NoMachine are trademarks of Medialogic S.p.A.                   */
/*                                                                        */
/* All rights reserved.                                                   */
/*                                                                        */
/**************************************************************************/

/*
 * We need symbols for the scan codes of keys.
 */
#include "../xfree86/common/atKeynames.h"


/*
 * Include the standard XFree86 ASCII keymap.
 *
 * This header declares a static KeySym array called 'map'.
 */
#include "../xfree86/common/xf86Keymap.h"


#if WIN_NEW_KEYBOARD_SUPPORT

/* Define the keymap structure */
typedef struct
{
  DWORD		dwVirtualKey;
  DWORD		dwXKey;
} winKeymappingRec, *winKeymappingPtr;

static const winKeymappingRec 
winKeymap[] = {
	{VK_BACK,		XK_BackSpace},
	{VK_TAB,		XK_Tab},
	{VK_CLEAR,		XK_Clear},
	{VK_RETURN,		XK_Return},
	{VK_LSHIFT,		XK_Shift_L},
	{VK_RSHIFT,		XK_Shift_R},
	{VK_SHIFT,		XK_Shift_L},
	{VK_LCONTROL,		XK_Control_L},
	{VK_RCONTROL,		XK_Control_R},
	{VK_CONTROL,		XK_Control_L},
	{VK_LMENU,		XK_Alt_L},
	{VK_RMENU,		XK_Alt_R},
	{VK_MENU,		XK_Alt_L},
	{VK_PAUSE,		XK_Pause},
	{VK_CAPITAL,		XK_Caps_Lock},
	{VK_ESCAPE,		XK_Escape},
	{VK_SPACE,		XK_space},
	{VK_PRIOR,		XK_Page_Up},
	{VK_NEXT,		XK_Page_Down},
	{VK_END,		XK_End},
	{VK_HOME,		XK_Home},
	{VK_LEFT,		XK_Left},
	{VK_UP,			XK_Up},
	{VK_RIGHT,		XK_Right},
	{VK_DOWN,		XK_Down},
	{VK_SELECT,		XK_Select},
	{VK_EXECUTE,		XK_Execute},
	{VK_SNAPSHOT,		XK_Print},
	{VK_INSERT,		XK_Insert},
	{VK_DELETE,		XK_Delete},
	{VK_HELP,		XK_Help},
	{VK_NUMPAD0,		XK_KP_0},
	{VK_NUMPAD1,		XK_KP_1},
	{VK_NUMPAD2,		XK_KP_2},
	{VK_NUMPAD3,		XK_KP_3},
	{VK_NUMPAD4,		XK_KP_4},
	{VK_NUMPAD5,		XK_KP_5},
	{VK_NUMPAD6,		XK_KP_6},
	{VK_NUMPAD7,		XK_KP_7},
	{VK_NUMPAD8,		XK_KP_8},
	{VK_NUMPAD9,		XK_KP_9},
	{VK_MULTIPLY,		XK_KP_Multiply},
	{VK_ADD,		XK_KP_Add},
	{VK_SEPARATOR,		XK_KP_Separator},   // often comma
	{VK_SUBTRACT,		XK_KP_Subtract},
	{VK_DECIMAL,		XK_KP_Decimal},
	{VK_DIVIDE,		XK_KP_Divide},
	{VK_F1,			XK_F1},
	{VK_F2,			XK_F2},
	{VK_F3,			XK_F3},
	{VK_F4,			XK_F4},
	{VK_F5,			XK_F5},
	{VK_F6,			XK_F6},
	{VK_F7,			XK_F7},
	{VK_F8,			XK_F8},
	{VK_F9,			XK_F9},
	{VK_F10,		XK_F10},
	{VK_F11,		XK_F11},
	{VK_F12,		XK_F12},
	{VK_F13,		XK_F13},
	{VK_F14,		XK_F14},
	{VK_F15,		XK_F15},
	{VK_F16,		XK_F16},
	{VK_F17,		XK_F17},
	{VK_F18,		XK_F18},
	{VK_F19,		XK_F19},
	{VK_F20,		XK_F20},
	{VK_F21,		XK_F21},
	{VK_F22,		XK_F22},
	{VK_F23,		XK_F23},
	{VK_F24,		XK_F24},
	{VK_NUMLOCK,		XK_Num_Lock},
	{VK_SCROLL,		XK_Scroll_Lock}
};

static int g_winKeymapEntries = sizeof (winKeymap) / sizeof (winKeymappingRec);

#else /* WIN_NEW_KEYBOARD_SUPPORT */

#define		WIN_KEYMAP_COLS		3

const int
g_iKeyMap [] = {
  /* count	Windows VK,	ASCII,		ASCII when extended VK */
  /* 0 */	0,		0,		0,
  /* 1 */	0,		0,		0,
  /* 2 */	0,		0,		0,
  /* 3 */	VK_CANCEL,	0,		KEY_Break,
  /* 4 */	0,		0,		0,
  /* 5 */	0,		0,		0,
  /* 6 */	0,		0,		0,
  /* 7 */	0,		0,		0,
  /* 8 */	0,		0,		0,
  /* 9 */	0,		0,		0,
  /* 10 */	0,		0,		0,
  /* 11 */	0,		0,		0,
  /* 12 */	0,		0,		0,
  /* 13 */	VK_RETURN,	0,		KEY_KP_Enter,
  /* 14 */	0,		0,		0,
  /* 15 */	0,		0,		0,
  /* 16 */	VK_SHIFT,	KEY_ShiftL,	KEY_ShiftR,
  /* 17 */	VK_CONTROL,	0,		KEY_RCtrl,
  /* 18 */	VK_MENU,	0,		KEY_AltLang,
  /* 19 */	VK_PAUSE,	KEY_Pause,	0,
  /* 20 */	0,		0,		0,
  /* 21 */	0,		0,		0,
  /* 22 */	0,		0,		0,
  /* 23 */	0,		0,		0,
  /* 24 */	0,		0,		0,
  /* 25 */	0,		0,		0,
  /* 26 */	0,		0,		0,
  /* 27 */	0,		0,		0,
  /* 28 */	0,		0,		0,
  /* 29 */	0,		0,		0,
  /* 30 */	0,		0,		0,
  /* 31 */	0,		0,		0,
  /* 32 */	0,		0,		0,
  /* 33 */	VK_PRIOR,	0,		KEY_PgUp,
  /* 34 */	VK_NEXT,	0,		KEY_PgDown,
  /* 35 */	VK_END,		0,		KEY_End,
  /* 36 */	VK_HOME,	0,		KEY_Home,
  /* 37 */	VK_LEFT,	0,		KEY_Left,
  /* 38 */	VK_UP,		0,		KEY_Up,
  /* 39 */	VK_RIGHT,	0,		KEY_Right,
  /* 40 */	VK_DOWN,	0,		KEY_Down,
  /* 41 */	0,		0,		0,
  /* 42 */	0,		0,		0,
  /* 43 */	0,		0,		0,
  /* 44 */	VK_SNAPSHOT,	0,		KEY_Print,  
  /* 45 */	VK_INSERT,	0,		KEY_Insert,
  /* 46 */	VK_DELETE,	0,		KEY_Delete,
  /* 47 */	0,		0,		0,
  /* 48 */	0,		0,		0,
  /* 49 */	0,		0,		0,
  /* 50 */	0,		0,		0,
  /* 51 */	0,		0,		0,
  /* 52 */	0,		0,		0,
  /* 53 */	0,		0,		0,
  /* 54 */	0,		0,		0,
  /* 55 */	0,		0,		0,
  /* 56 */	0,		0,		0,
  /* 57 */	0,		0,		0,
  /* 58 */	0,		0,		0,
  /* 59 */	0,		0,		0,
  /* 60 */	0,		0,		0,
  /* 61 */	0,		0,		0,
  /* 62 */	0,		0,		0,
  /* 63 */	0,		0,		0,
  /* 64 */	0,		0,		0,
  /* 65 */	0,		0,		0,
  /* 66 */	0,		0,		0,
  /* 67 */	0,		0,		0,
  /* 68 */	0,		0,		0,
  /* 69 */	0,		0,		0,
  /* 70 */	0,		0,		0,
  /* 71 */	0,		0,		0,
  /* 72 */	0,		0,		0,
  /* 73 */	0,		0,		0,
  /* 74 */	0,		0,		0,
  /* 75 */	0,		0,		0,
  /* 76 */	0,		0,		0,
  /* 77 */	0,		0,		0,
  /* 78 */	0,		0,		0,
  /* 79 */	0,		0,		0,
  /* 80 */	0,		0,		0,
  /* 81 */	0,		0,		0,
  /* 82 */	0,		0,		0,
  /* 83 */	0,		0,		0,
  /* 84 */	0,		0,		0,
  /* 85 */	0,		0,		0,
  /* 86 */	0,		0,		0,
  /* 87 */	0,		0,		0,
  /* 88 */	0,		0,		0,
  /* 89 */	0,		0,		0,
  /* 90 */	0,		0,		0,
  /* 91 */	0,		0,		0,
  /* 92 */	0,		0,		0,
  /* 93 */	0,		0,		0,
  /* 94 */	0,		0,		0,
  /* 95 */	0,		0,		0,
  /* 96 */	0,		0,		0,
  /* 97 */	0,		0,		0,
  /* 98 */	0,		0,		0,
  /* 99 */	0,		0,		0,
  /* 100 */	0,		0,		0,
  /* 101 */	0,		0,		0,
  /* 102 */	0,		0,		0,
  /* 103 */	0,		0,		0,
  /* 104 */	0,		0,		0,
  /* 105 */	0,		0,		0,
  /* 106 */	0,		0,		0,
  /* 107 */	0,		0,		0,
  /* 108 */	0,		0,		0,
  /* 109 */	0,		0,		0,
  /* 110 */	0,		0,		0,
  /* 111 */	VK_DIVIDE,	0,		KEY_KP_Divide,
  /* 112 */	0,		0,		0,
  /* 113 */	0,		0,		0,
  /* 114 */	0,		0,		0,
  /* 115 */	0,		0,		0,
  /* 116 */	0,		0,		0,
  /* 117 */	0,		0,		0,
  /* 118 */	0,		0,		0,
  /* 119 */	0,		0,		0,
  /* 120 */	0,		0,		0,
  /* 121 */	0,		0,		0,
  /* 122 */	0,		0,		0,
  /* 123 */	0,		0,		0,
  /* 124 */	0,		0,		0,
  /* 125 */	0,		0,		0,
  /* 126 */	0,		0,		0,
  /* 127 */	0,		0,		0,
  /* 128 */	0,		0,		0,
  /* 129 */	0,		0,		0,
  /* 130 */	0,		0,		0,
  /* 131 */	0,		0,		0,
  /* 132 */	0,		0,		0,
  /* 133 */	0,		0,		0,
  /* 134 */	0,		0,		0,
  /* 135 */	0,		0,		0,
  /* 136 */	0,		0,		0,
  /* 137 */	0,		0,		0,
  /* 138 */	0,		0,		0,
  /* 139 */	0,		0,		0,
  /* 140 */	0,		0,		0,
  /* 141 */	0,		0,		0,
  /* 142 */	0,		0,		0,
  /* 143 */	0,		0,		0,
  /* 144 */	0,		0,		0,
  /* 145 */	0,		0,		0,
  /* 146 */	0,		0,		0,
  /* 147 */	0,		0,		0,
  /* 148 */	0,		0,		0,
  /* 149 */	0,		0,		0,
  /* 150 */	0,		0,		0,
  /* 151 */	0,		0,		0,
  /* 152 */	0,		0,		0,
  /* 153 */	0,		0,		0,
  /* 154 */	0,		0,		0,
  /* 155 */	0,		0,		0,
  /* 156 */	0,		0,		0,
  /* 157 */	0,		0,		0,
  /* 158 */	0,		0,		0,
  /* 159 */	0,		0,		0,
  /* 160 */	0,		0,		0,
  /* 161 */	0,		0,		0,
  /* 162 */	0,		0,		0,
  /* 163 */	0,		0,		0,
  /* 164 */	0,		0,		0,
  /* 165 */	0,		0,		0,
  /* 166 */	0,		0,		0,
  /* 167 */	0,		0,		0,
  /* 168 */	0,		0,		0,
  /* 169 */	0,		0,		0,
  /* 170 */	0,		0,		0,
  /* 171 */	0,		0,		0,
  /* 172 */	0,		0,		0,
  /* 173 */	0,		0,		0,
  /* 174 */	0,		0,		0,
  /* 175 */	0,		0,		0,
  /* 176 */	0,		0,		0,
  /* 177 */	0,		0,		0,
  /* 178 */	0,		0,		0,
  /* 179 */	0,		0,		0,
  /* 180 */	0,		0,		0,
  /* 181 */	0,		0,		0,
  /* 182 */	0,		0,		0,
  /* 183 */	0,		0,		0,
  /* 184 */	0,		0,		0,
  /* 185 */	0,		0,		0,
  /* 186 */	0,		0,		0,
  /* 187 */	0,		0,		0,
  /* 188 */	0,		0,		0,
  /* 189 */	0,		0,		0,
  /* 190 */	0,		0,		0,
  /* 191 */	0,		0,		0,
  /* 192 */	0,		0,		0,
  /* 193 */	0,		0,		0,
  /* 194 */	0,		0,		0,
  /* 195 */	0,		0,		0,
  /* 196 */	0,		0,		0,
  /* 197 */	0,		0,		0,
  /* 198 */	0,		0,		0,
  /* 199 */	0,		0,		0,
  /* 200 */	0,		0,		0,
  /* 201 */	0,		0,		0,
  /* 202 */	0,		0,		0,
  /* 203 */	0,		0,		0,
  /* 204 */	0,		0,		0,
  /* 205 */	0,		0,		0,
  /* 206 */	0,		0,		0,
  /* 207 */	0,		0,		0,
  /* 208 */	0,		0,		0,
  /* 209 */	0,		0,		0,
  /* 210 */	0,		0,		0,
  /* 211 */	0,		0,		0,
  /* 212 */	0,		0,		0,
  /* 213 */	0,		0,		0,
  /* 214 */	0,		0,		0,
  /* 215 */	0,		0,		0,
  /* 216 */	0,		0,		0,
  /* 217 */	0,		0,		0,
  /* 218 */	0,		0,		0,
  /* 219 */	0,		0,		0,
  /* 220 */	0,		0,		0,
  /* 221 */	0,		0,		0,
  /* 222 */	0,		0,		0,
  /* 223 */	0,		0,		0,
  /* 224 */	0,		0,		0,
  /* 225 */	0,		0,		0,
  /* 226 */	0,		0,		0,
  /* 227 */	0,		0,		0,
  /* 228 */	0,		0,		0,
  /* 229 */	0,		0,		0,
  /* 230 */	0,		0,		0,
  /* 231 */	0,		0,		0,
  /* 232 */	0,		0,		0,
  /* 233 */	0,		0,		0,
  /* 234 */	0,		0,		0,
  /* 235 */	0,		0,		0,
  /* 236 */	0,		0,		0,
  /* 237 */	0,		0,		0,
  /* 238 */	0,		0,		0,
  /* 239 */	0,		0,		0,
  /* 240 */	0,		0,		0,
  /* 241 */	0,		0,		0,
  /* 242 */	0,		0,		0,
  /* 243 */	0,		0,		0,
  /* 244 */	0,		0,		0,
  /* 245 */	0,		0,		0,
  /* 246 */	0,		0,		0,
  /* 247 */	0,		0,		0,
  /* 248 */	0,		0,		0,
  /* 249 */	0,		0,		0,
  /* 250 */	0,		0,		0,
  /* 251 */	0,		0,		0,
  /* 252 */	0,		0,		0,
  /* 253 */	0,		0,		0,
  /* 254 */	0,		0,		0,
  /* 255 */	0,		0,		0
};
#endif /* WIN_NEW_KEYBOARD_SUPPORT */
