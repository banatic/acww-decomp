/* The animated screen icon (screen_icon.h). */
#include "screen_icon.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "state_flags.h"

static_assert(offsetof(ScreenIcon, anim) == 0x0c, "ScreenIcon layout");
static_assert(offsetof(ScreenIcon, slide_x) == 0x20, "ScreenIcon layout");
static_assert(offsetof(ScreenIcon, flag4) == 0x30, "ScreenIcon layout");
static_assert(offsetof(ScreenIcon, restart_anim) == 0x33, "ScreenIcon layout");
static_assert(offsetof(ScreenIcon, timer) == 0x3c, "ScreenIcon layout");

/* How far left of its place the icon is drawn at each step: -18, -12, -2, -1, 0. */
extern const s8 data_020c7588[SCREEN_ICON_STEPS + 1];
/* The icon's animation. */
extern const u8 data_020d5c64[];
extern ScreenIcon data_0213ffb0;

/* The delays before the icon may show after state flag 4 was set, and after its value left 1.0
 * while it stayed set. */
#define DELAY_FLAG_SET 0xe
#define DELAY_VALUE_LEFT_ONE 0x17
/* The fixed place, from the indicator's (x, y); the drop while state flag 4 is set. */
#define FIXED_DX 0x78
#define FIXED_DY 0x48
#define FLAG4_DY 0x8c

/* Load the graphics of a variant. */
extern void func_02011f1c(int mode);
extern void func_0208a0c8(CellAnim *anim);                   /* advance */
extern void func_0208a1f0(CellAnim *anim, const void *data); /* set the animation */
extern void func_0208a1ec(CellAnim *anim, int hold);
extern void *func_0208a1e0(CellAnim *anim, int frame, fx32 time);
extern void func_0208a158(CellAnim *anim);           /* speed 0 */
extern void *func_0208a144(CellAnim *anim);          /* speed 1.0 from the first frame */
extern int func_0208a1d0(CellAnim *anim);            /* the frame's cell */
extern s16 func_0208a1b0(CellAnim *anim, int frame); /* a frame's x, the current one for -1 */
extern s16 func_0208a198(CellAnim *anim, int frame); /* a frame's y, the current one for -1 */
extern int func_0208aef0(ScreenIcon *icon);          /* the indicator's x */
extern int func_0208aeec(ScreenIcon *icon);          /* the indicator's y */
extern void func_02088df8(int a, int cell, int x, int y, int b, int c, fx32 scale_x, fx32 scale_y, int d, int e, int f, int g);

static void set_step(ScreenIcon *icon, u32 step)
{
    icon->step = step;
    icon->slide_x = data_020c7588[step];
}

/* func_020037c8: load the variant asked for, once the icon is out of view. */
void ScreenIcon_ApplyMode(ScreenIcon *icon)
{
    if (icon->step != 0 || icon->next_mode == SCREEN_ICON_MODE_NONE || icon->next_mode == icon->mode) {
        return;
    }
    func_02011f1c((int) icon->next_mode);
    icon->mode = icon->next_mode;
    icon->next_mode = SCREEN_ICON_MODE_NONE;
    icon->fixed_place = icon->mode == 0 || icon->mode == 3 || icon->mode == 4;
    icon->restart_anim = 1;
}
CLEAN_AS(func_020037c8, ScreenIcon_ApplyMode)

/* func_02003814: one step of sliding in or out, then the timer and the animation. A variant at
 * the fixed place jumps straight in or out. */
void ScreenIcon_Slide(ScreenIcon *icon)
{
    if (icon->restart_anim) {
        ScreenIcon_SetAnim(icon, 0);
    }

    if (icon->fixed_place) {
        set_step(icon, ScreenIcon_IsShown(icon) ? SCREEN_ICON_STEPS : 0);
    } else if (ScreenIcon_IsShown(icon)) {
        if (icon->step < SCREEN_ICON_STEPS) {
            set_step(icon, icon->step + 1);
            if (icon->step == SCREEN_ICON_STEPS) {
                ScreenIcon_SetAnim(icon, 0);
            }
        }
    } else if (icon->step != 0) {
        if (icon->step == SCREEN_ICON_STEPS) {
            ScreenIcon_SetAnim(icon, 1);
        }
        set_step(icon, icon->step - 1);
    }

    if (icon->timer > 0) {
        icon->timer--;
    }
    func_0208a0c8(&icon->anim);
}
CLEAN_AS(func_02003814, ScreenIcon_Slide)

/* func_020038bc: follow state flag 4. When it is set the icon goes out of view at once, still,
 * and may show again after a delay; while it stays set, its value leaving 1.0 starts a longer
 * delay. At the end of a delay the animation starts again. */
void ScreenIcon_TrackFlag(ScreenIcon *icon)
{
    u8 flag4 = StateFlags_Test4() != 0;
    fx32 value = StateFlags_ValueOrOne();

    if (icon->delay > 0) {
        icon->delay--;
        if (icon->delay == 0) {
            icon->restart_anim = 1;
        }
    }

    if (icon->flag4) {
        if (icon->flag_value == 0x1000 && value < 0x1000) {
            icon->delay = DELAY_VALUE_LEFT_ONE;
        }
    } else if (flag4) {
        set_step(icon, 0);
        ScreenIcon_SetAnim(icon, 1);
        icon->delay = DELAY_FLAG_SET;
    }

    icon->flag4 = flag4;
    icon->flag_value = value;
}
CLEAN_AS(func_020038bc, ScreenIcon_TrackFlag)

/* func_02003938: enabled, no delay and the timer running; and no other variant waiting. */
int ScreenIcon_IsShown(ScreenIcon *icon)
{
    if (!icon->enabled || icon->delay != 0 || icon->timer <= 0) {
        return 0;
    }
    if (icon->next_mode != SCREEN_ICON_MODE_NONE && icon->next_mode != icon->mode) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_02003938, ScreenIcon_IsShown)

/* func_0200396c: the icon's animation from its start, either running in a loop or held on its
 * second frame. */
void ScreenIcon_SetAnim(ScreenIcon *icon, int still)
{
    func_0208a1f0(&icon->anim, data_020d5c64);
    if (still) {
        func_0208a1ec(&icon->anim, 1);
        func_0208a1e0(&icon->anim, 1, 0);
        func_0208a158(&icon->anim);
    } else {
        func_0208a1ec(&icon->anim, 0);
        func_0208a144(&icon->anim);
    }
    icon->restart_anim = 0;
}
CLEAN_AS(func_0200396c, ScreenIcon_SetAnim)

/* func_020039c4: the draw function of the icon's class. */
void ScreenIcon_CallDraw(ScreenIcon *icon)
{
    icon->vtable->draw(icon);
}
CLEAN_AS(func_020039c4, ScreenIcon_CallDraw)

/* func_020039d4: the update function of the icon's class. */
void ScreenIcon_CallUpdate(ScreenIcon *icon)
{
    icon->vtable->update(icon);
}
CLEAN_AS(func_020039d4, ScreenIcon_CallUpdate)

/* func_020039e4: the animation running from its first frame. */
void ScreenIcon_RestartAnim(ScreenIcon *icon)
{
    func_0208a144(&icon->anim);
}
CLEAN_AS(func_020039e4, ScreenIcon_RestartAnim)

/* func_020039f0: out of view, disabled, with variant 0 at the fixed place and no variant asked
 * for. */
void ScreenIcon_Reset(ScreenIcon *icon)
{
    icon->enabled = 0;
    icon->slide_x = data_020c7588[0];
    icon->step = 0;
    icon->flag_value = 0;
    icon->delay = 0;
    icon->flag4 = 0;
    icon->fixed_place = 1;
    ScreenIcon_SetAnim(icon, 0);
    icon->restart_anim = 0;
    icon->mode = 0;
    icon->next_mode = SCREEN_ICON_MODE_NONE;
    icon->timer = 0;
}
CLEAN_AS(func_020039f0, ScreenIcon_Reset)

/* func_02003a34 */
void ScreenIcons_DrawIcon(void)
{
    ScreenIcon_CallDraw(&data_0213ffb0);
}
CLEAN_AS(func_02003a34, ScreenIcons_DrawIcon)

/* func_02003a44 */
void ScreenIcons_UpdateIcon(void)
{
    ScreenIcon_CallUpdate(&data_0213ffb0);
}
CLEAN_AS(func_02003a44, ScreenIcons_UpdateIcon)

/* func_02003a54 */
void ScreenIcons_RestartIconAnim(void)
{
    ScreenIcon_RestartAnim(&data_0213ffb0);
}
CLEAN_AS(func_02003a54, ScreenIcons_RestartIconAnim)

/* func_02003a64 */
void ScreenIcons_ResetIcon(void)
{
    ScreenIcon_Reset(&data_0213ffb0);
}
CLEAN_AS(func_02003a64, ScreenIcons_ResetIcon)

/* func_02003a74: vtable slot 0x0c. */
void ScreenIcon_Update(ScreenIcon *icon)
{
    ScreenIcon_TrackFlag(icon);
    ScreenIcon_Slide(icon);
    ScreenIcon_ApplyMode(icon);
}
CLEAN_AS(func_02003a74, ScreenIcon_Update)

/* func_02003a90: vtable slot 0x08; draws the animation's cell unless the icon is out of view. */
void ScreenIcon_Draw(ScreenIcon *icon)
{
    if (icon->step == 0) {
        return;
    }
    int cell = func_0208a1d0(&icon->anim);
    if (cell == 0) {
        return;
    }
    int x = func_0208aef0(icon);
    x += func_0208a1b0(&icon->anim, -1);
    int y = func_0208aeec(icon);
    y += func_0208a198(&icon->anim, -1);
    if (icon->fixed_place) {
        x += FIXED_DX;
        y += FIXED_DY;
    } else {
        x += icon->slide_x;
        y += icon->flag4 ? FLAG4_DY : 0;
    }
    func_02088df8(0, cell, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_02003a90, ScreenIcon_Draw)

/* The icon's class (vtable 0x020d72cc); its base is the screen indicator (vtable 0x020e20c8). */
extern const ScreenIconVtable data_020d72cc;
extern void func_0208af30(ScreenIcon *icon); /* indicator constructor: at (0x80, 0x60) */
extern void func_0208af00(ScreenIcon *icon); /* indicator destructor */
extern void func_0208a1f8(CellAnim *anim);   /* no animation, speed 1.0 */
extern void func_0208a1f4(CellAnim *anim);   /* animation destructor (does nothing) */
extern void func_020edb3c(void *block);      /* operator delete */

/* func_02003b24: the deleting destructor. */
ScreenIcon *ScreenIcon_DestructFree(ScreenIcon *icon)
{
    ScreenIcon_Destruct(icon);
    func_020edb3c(icon);
    return icon;
}
CLEAN_AS(func_02003b24, ScreenIcon_DestructFree)

/* func_02003b50: the destructor, run at exit for data_0213ffb0. QUIRK: it starts the animation
 * again from its first frame before going back to the base class. */
ScreenIcon *ScreenIcon_Destruct(ScreenIcon *icon)
{
    icon->vtable = &data_020d72cc;
    ScreenIcon_RestartAnim(icon);
    func_0208a1f4(&icon->anim);
    func_0208af00(icon);
    return icon;
}
CLEAN_AS(func_02003b50, ScreenIcon_Destruct)

/* func_02003b78: the constructor, run at start for data_0213ffb0: out of view and disabled,
 * with variant 0 at the fixed place and no variant asked for. */
ScreenIcon *ScreenIcon_Construct(ScreenIcon *icon)
{
    func_0208af30(icon);
    icon->vtable = &data_020d72cc;
    func_0208a1f8(&icon->anim);
    icon->slide_x = 0;
    icon->step = 0;
    icon->flag_value = 0;
    icon->delay = 0;
    icon->flag4 = 0;
    icon->enabled = 0;
    icon->fixed_place = 1;
    icon->restart_anim = 0;
    icon->mode = 0;
    icon->next_mode = SCREEN_ICON_MODE_NONE;
    icon->timer = 0;
    return icon;
}
CLEAN_AS(func_02003b78, ScreenIcon_Construct)
