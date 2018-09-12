/*
DOS interrupt-based keyboard driver.
Copyright (C) 2013  John Tsiombikas <nuclear@member.fsf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License  for more details.

You should have received a copy of the GNU General Public License
along with the program. If not, see <http://www.gnu.org/licenses/>
*/
#ifndef KEYB_H_
#define KEYB_H_

#define KB_ANY		(-1)
#define KB_ALT		(-2)
#define KB_CTRL		(-3)
#define KB_SHIFT	(-4)

/* special keys */
enum {
	KB_LALT, KB_RALT,
	KB_LCTRL, KB_RCTRL,
	KB_LSHIFT, KB_RSHIFT,
	KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, KB_F6,
	KB_F7, KB_F8, KB_F9, KB_F10, KB_F11, KB_F12,
	KB_CAPSLK, KB_NUMLK, KB_SCRLK, KB_SYSRQ,
	KB_ESC = 27,
	KB_INSERT, KB_DEL, KB_HOME, KB_END, KB_PGUP, KB_PGDN,
	KB_LEFT, KB_RIGHT, KB_UP, KB_DOWN,
	KB_NUM_DOT, KB_NUM_ENTER, KB_NUM_PLUS, KB_NUM_MINUS, KB_NUM_MUL, KB_NUM_DIV,
	KB_NUM_0, KB_NUM_1, KB_NUM_2, KB_NUM_3, KB_NUM_4,
	KB_NUM_5, KB_NUM_6, KB_NUM_7, KB_NUM_8, KB_NUM_9,
	KB_BACKSP = 127
};


#ifdef __cplusplus
extern "C" {
#endif

int kb_init(int bufsz);	/* bufsz can be 0 for no buffered keys */
void kb_shutdown(void); /* don't forget to call this at the end! */

/* Boolean predicate for testing the current state of a particular key.
 * You may also pass KB_ANY to test if any key is held down.
 */
int kb_isdown(int key);

/* waits for any keypress */
void kb_wait(void);

/* removes and returns a single key from the input buffer.
 * If buffering is disabled (initialized with kb_init(0)), then it always
 * returns the last key pressed.
 */
int kb_getkey(void);

void kb_putback(int key);

#ifdef __cplusplus
}
#endif

#endif	/* KEYB_H_ */
