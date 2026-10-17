/* Overlay 134's entry picker, as the screens of overlays 136 (time_screen.h) and 137
 * (birthday_screen.h) keep and drive it; its functions are called by symbol.
 *
 * The picker (constructor func_ov134_0229bed4, destructor func_ov134_0229beb0, 0x28b0 bytes) is
 * set up for a kind (func_ov134_0229bd38's second argument: 1 for a time, 2 for a month and day)
 * and shows fields numbered 0-4: by the evidence 0 the year, 1 the month, 2 the day, 3 the hour
 * and 4 the minute (func_ov134_0229b034 counts field 4 plus 60 times field 3 in a 720-minute
 * circle; func_ov134_0229a5c8 gives field 2 as many values as the month has days). A field's
 * values open as a scrolling list, picked by the d-pad or the pen; 6 stands for no field. For a
 * time it also draws a clock whose hands the pen can drag. The value entered comes back as a
 * DateTime (func_ov134_0229bbdc). */
#ifndef CLEAN_OV136_ENTRY_PICKER_H
#define CLEAN_OV136_ENTRY_PICKER_H

#include "main/calendar.h"
#include "types.h"

/* The field number that stands for none (also the panel's OK button). */
#define ENTRY_PICKER_NO_FIELD 6

/* The picker's kinds the two screens set up. */
#define ENTRY_PICKER_KIND_TIME 1
#define ENTRY_PICKER_KIND_MONTH_DAY 2

/* Construction, destruction, setup (kind and three display arguments). */
extern void *func_ov134_0229bed4(void *picker);
extern char *func_ov134_0229beb0(char *picker);
extern void func_ov134_0229bd38(void *picker, int kind, int a, int b, u8 c);

/* Its graphics: the characters (func_ov134_0229b954) and the texts with a prompt message
 * (func_ov134_0229baec, then func_ov134_0229ba10). */
extern int func_ov134_0229b954(void *picker);
extern int func_ov134_0229baec(void *picker);
extern void func_ov134_0229ba10(void *picker, unsigned int message);

/* Each frame: its start (its sprite updated), its end, its draw at a wipe offset; its teardown. */
extern void func_ov134_0229bcac(void *picker);
extern void func_ov134_0229bbe8(void *picker);
extern void func_ov134_0229b220(void *picker, int x, int y);
extern void func_ov134_0229bcf0(void *picker);

/* The value entered. */
extern void func_ov134_0229bbdc(void *picker, DateTime *when);

/* The list's cursor sprite: its x (func_ov134_022999e0) and y (func_ov134_022999ac), and its
 * row put at a y (func_ov134_02299980). */
extern int func_ov134_022999e0(void *picker);
extern int func_ov134_022999ac(void *picker);
extern void func_ov134_02299980(void *picker, int y);

/* A field's list opened (func_ov134_0229a5c8) and its opening stepped, nonzero once done
 * (func_ov134_0229a4e4); the list closed keeping the value under the cursor
 * (func_ov134_0229a3e4) or not (func_ov134_0229a398), the closing stepped, nonzero once done
 * (func_ov134_0229a24c); the field the picker is at afterwards (func_ov134_0229a8a0). */
extern void func_ov134_0229a5c8(void *picker, int field);
extern int func_ov134_0229a4e4(void *picker);
extern void func_ov134_0229a3e4(void *picker);
extern void func_ov134_0229a398(void *picker);
extern int func_ov134_0229a24c(void *picker);
extern unsigned char func_ov134_0229a8a0(void *picker);

/* The list by the keys: a frame of the d-pad (func_ov134_022997dc; EntryPickerKeys); whether the
 * cursor is on the list's scroll bar, then taken there (func_ov134_02299b70); the value under
 * the cursor taken when it may be, nonzero then (func_ov134_022997b0); the scroll bar moved by
 * up and down while A is held (func_ov134_02299a90), let go (func_ov134_02299a84), and its
 * return to the list stepped, nonzero once done (func_ov134_02299a60). */
extern int func_ov134_022997dc(void *picker, void *keys);
extern int func_ov134_02299b70(void *picker);
extern int func_ov134_022997b0(void *picker);
extern void func_ov134_02299a90(void *picker);
extern int func_ov134_02299a84(void *picker);
extern int func_ov134_02299a60(void *picker);

/* The list by the pen: what a touch at (x, y) hit (func_ov134_0229a1f0; EntryPickerTouch); the
 * list dragged by its scroll bar to a pen's y (func_ov134_02299b18) or along it
 * (func_ov134_02299af0). */
extern int func_ov134_0229a1f0(void *picker, int x, int y);
extern void func_ov134_02299b18(void *picker, int y);
extern void func_ov134_02299af0(void *picker, int y);

/* The fields under a touch at (x, y), 6 for none: the hour or minute (func_ov134_0229aad8), the
 * month or day (func_ov134_0229ab2c). */
extern int func_ov134_0229aad8(void *picker, int x, int y);
extern int func_ov134_0229ab2c(void *picker, int x, int y);

/* The clock's hands: grabbed by a touch at (x, y), nonzero then (func_ov134_0229b168); dragged
 * to (x, y) (func_ov134_0229b108); let go, nonzero when they move on to their place
 * (func_ov134_0229b034); that move stepped, nonzero once done (func_ov134_0229b014). */
extern int func_ov134_0229b168(void *picker, int x, int y);
extern void func_ov134_0229b108(void *picker, int x, int y);
extern int func_ov134_0229b034(void *picker);
extern int func_ov134_0229b014(void *picker);

/* What func_ov134_022997dc answers. */
enum EntryPickerKeys {
    ENTRY_PICKER_KEYS_NONE = 0,    /* nothing moved */
    ENTRY_PICKER_KEYS_MOVED = 1,   /* the cursor moved (onto or off the scroll bar) */
    ENTRY_PICKER_KEYS_STEPPED = 2, /* the cursor stepped up or down a row */
    ENTRY_PICKER_KEYS_SCROLLED = 3 /* the list scrolled under a held key */
};

/* What func_ov134_0229a1f0 answers. */
enum EntryPickerTouch {
    ENTRY_PICKER_TOUCH_VALUE = 0,   /* a value of the list */
    ENTRY_PICKER_TOUCH_OUTSIDE = 1, /* nothing of the list */
    ENTRY_PICKER_TOUCH_COLUMN = 2,  /* the list's column, elsewhere */
    ENTRY_PICKER_TOUCH_BAR = 3,     /* the scroll bar */
    ENTRY_PICKER_TOUCH_OTHER = 4    /* something the screens ignore */
};

#endif
