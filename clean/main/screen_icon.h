/* An animated icon drawn as an OBJ over the screen (the object at data_0213ffb0, class vtable
 * 0x020d72cc); func_0208af44, func_0208af60, func_0208af7c and func_0208af98 draw, update, rewind
 * and reset it together with the game's other screen indicators.
 *
 * The icon has graphics in several variants (`mode`, loaded with func_02011f1c); a new one is
 * asked for in `next_mode` and loaded once the icon is out of view. Variants 0, 3 and 4 sit at a
 * fixed place; the others slide in from the left over four steps while the icon is shown and
 * back out when it is not, the animation running only while fully in. The icon is shown while
 * `timer` runs, `enabled` is set and the delay after state flag 4 changed is over; it moves
 * down by 0x8c pixels while state flag 4 is set. */
#ifndef CLEAN_MAIN_SCREEN_ICON_H
#define CLEAN_MAIN_SCREEN_ICON_H

#include "types.h"

#define SCREEN_ICON_MODE_NONE 5
#define SCREEN_ICON_STEPS 4

struct ScreenIcon;

typedef struct ScreenIconVtable {
    const void *unk_00[2];
    void (*draw)(struct ScreenIcon *icon);   /* 0x08 */
    void (*update)(struct ScreenIcon *icon); /* 0x0c */
} ScreenIconVtable;

/* A cell animation (func_0208a0c8 advances it): the cells with how long each shows. */
typedef struct CellAnim {
    const void *data;
    int frame;
    fx32 time;
    fx32 speed;
    int hold; /* nonzero: stop on the last frame instead of looping */
} CellAnim;

typedef struct ScreenIcon {
    const ScreenIconVtable *vtable;
    int x; /* 0x04: the indicator's place, (0x80, 0x60) */
    int y;
    CellAnim anim;   /* 0x0c */
    int slide_x;     /* 0x20: from the slide table, by `step` */
    u32 step;        /* 0x24: 0 out of view to 4 fully in */
    fx32 flag_value; /* 0x28: StateFlags_ValueOrOne in the frame before */
    int delay;       /* 0x2c: frames before the icon may show again */
    u8 flag4;        /* 0x30: state flag 4 in the frame before */
    u8 enabled;      /* 0x31 */
    u8 fixed_place;  /* 0x32: the variant does not slide */
    u8 restart_anim; /* 0x33: start the animation again on the next update */
    u32 mode;        /* 0x34: the variant loaded */
    u32 next_mode;   /* 0x38: the variant asked for, SCREEN_ICON_MODE_NONE for none */
    int timer;       /* 0x3c: frames the icon stays shown */
} ScreenIcon;

void ScreenIcon_ApplyMode(ScreenIcon *icon);
void ScreenIcon_Slide(ScreenIcon *icon);
void ScreenIcon_TrackFlag(ScreenIcon *icon);
int ScreenIcon_IsShown(ScreenIcon *icon);
void ScreenIcon_SetAnim(ScreenIcon *icon, int still);
void ScreenIcon_CallDraw(ScreenIcon *icon);
void ScreenIcon_CallUpdate(ScreenIcon *icon);
void ScreenIcon_RestartAnim(ScreenIcon *icon);
void ScreenIcon_Reset(ScreenIcon *icon);
void ScreenIcons_DrawIcon(void);
void ScreenIcons_UpdateIcon(void);
void ScreenIcons_RestartIconAnim(void);
void ScreenIcons_ResetIcon(void);
void ScreenIcon_Update(ScreenIcon *icon);
void ScreenIcon_Draw(ScreenIcon *icon);

#endif
