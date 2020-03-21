#include "devices/vga.h"
#include <round.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "threads/io.h"
#include "threads/interrupt.h"
#include "threads/vaddr.h"

/* VGA text screen support.  See [FREEVGA] for more information. */

/* Number of columns and rows on the text display. */
#define COL_CNT 80
#define ROW_CNT 25

/* Current cursor position.  (0,0) is in the upper left corner of
   the display. */
static size_t cx, cy;

/* Attribute value for gray text on a black background. */
#define GRAY_ON_BLACK 0x07

/* Framebuffer.  See [FREEVGA] under "VGA Text Mode Operation".
   The character at (x,y) is fb[y][x][0].
   The attribute at (x,y) is fb[y][x][1]. */
static uint8_t (*fb)[COL_CNT][2];

static void clear_row (size_t y);
static void cls (void);
static void newline (void);
static void move_cursor (void);
static void find_cursor (size_t *x, size_t *y);

/* Initializes the VGA text display. */
static void
init (void) {
	/* Already initialized? */
	static bool inited;
	if (!inited) {
		fb = ptov (0xb8000);
		find_cursor (&cx, &cy);
		inited = true;
	}
}

/* Writes C to the VGA text display, interpreting control
   characters in the conventional ways.  */
void
vga_putc (int c) {
	/* Disable interrupts to lock out interrupt handlers
	   that might write to the console. */
	enum intr_level old_level = intr_disable ();

	init ();

	switch (c) {
		case '\n':
			newline ();
			break;

		case '\f':
			cls ();
			break;

		case '\b':
			if (cx > 0)
				cx--;
			break;

		case '\r':
			cx = 0;
			break;

		case '\t':
			cx = ROUND_UP (cx + 1, 8);
			if (cx >= COL_CNT)
				newline ();
			break;

		default:
			fb[cy][cx][0] = c;
			fb[cy][cx][1] = GRAY_ON_BLACK;
			if (++cx >= COL_CNT)
				newline ();
			break;
	}

	/* Update cursor position. */
	move_cursor ();

	intr_set_level (old_level);
}

/* Clears the screen and moves the cursor to the upper left. */
static void
cls (void) {
	size_t y;

	for (y = 0; y < ROW_CNT; y++)
		clear_row (y);

	cx = cy = 0;
	move_cursor ();
}

/* Clears row Y to spaces. */
static void
clear_row (size_t y) {
	size_t x;

	for (x = 0; x < COL_CNT; x++)
	{
		fb[y][x][0] = ' ';
		fb[y][x][1] = GRAY_ON_BLACK;
	}
}

/* Advances the cursor to the first column in the next line on
   the screen.  If the cursor is already on the last line on the
   screen, scrolls the screen upward one line. */
static void
newline (void) {
	cx = 0;
	cy++;
	if (cy >= ROW_CNT)
	{
		cy = ROW_CNT - 1;
		memmove (&fb[0], &fb[1], sizeof fb[0] * (ROW_CNT - 1));
		clear_row (ROW_CNT - 1);
	}
}

/* Moves the hardware cursor to (cx,cy). */
static void
move_cursor (void) {
	/* See [FREEVGA] under "Manipulating the Text-mode Cursor". */
	uint16_t cp = cx + COL_CNT * cy;
	outw (0x3d4, 0x0e | (cp & 0xff00));
	outw (0x3d4, 0x0f | (cp << 8));
}

/* Reads the current hardware cursor position into (*X,*Y). */
static void
find_cursor (size_t *x, size_t *y) {
	/* See [FREEVGA] under "Manipulating the Text-mode Cursor". */
	uint16_t cp;

	outb (0x3d4, 0x0e);
	cp = inb (0x3d5) << 8;

	outb (0x3d4, 0x0f);
	cp |= inb (0x3d5);

	*x = cp % COL_CNT;
	*y = cp / COL_CNT;
}
