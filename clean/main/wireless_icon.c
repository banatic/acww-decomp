/* The wireless signal icon (wireless_icon.h). */
#include "wireless_icon.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "state_flags.h"

static_assert(offsetof(WirelessIcon, delay) == 0x10, "WirelessIcon layout");
static_assert(offsetof(WirelessIcon, wfc_graphics) == 0x15, "WirelessIcon layout");

/* How far left of its place the icon is drawn at each step: -18, -12, -2, -1, 0 (shared with
 * the animated screen icon). */
extern const s8 data_020c7588[WIRELESS_ICON_STEPS + 1];

/* A frame of a cell animation, starting with its cell. */
typedef struct AnimFrame {
    int cell;
    u8 unk_04[8];
} AnimFrame;

/* The game's cell animations: their frames and how many. */
typedef struct AnimEntry {
    const AnimFrame *frames;
    int count;
} AnimEntry;

extern const AnimEntry data_020d5b3c[];
extern WirelessIcon data_0213ff98;

#define SIGNAL_ANIM 1
#define DRAW_X 0x80
#define DRAW_Y 0x60

/* The delays before the icon may show after state flag 4 was set, and after its value left 1.0
 * while it stayed set. */
#define DELAY_FLAG_SET 0xe
#define DELAY_VALUE_LEFT_ONE 0x17

/* The wireless mode (data_021fbef8): 0 none, 1 and 2 the local wireless library, 3 and 4 the
 * Wi-Fi Connection. */
extern u8 func_020ec1e8(void);
/* The link level, 1 to 3, of the library in use; 0 for none. */
extern int func_020ec39c(void);
/* Load one of the icon's two sets of graphics (nonzero: the Wi-Fi Connection's). */
extern void func_02011f2c(int wfc);
extern void func_02088df8(int a, int cell, int x, int y, int b, int c, fx32 scale_x, fx32 scale_y, int d, int e, int f, int g);

static void set_step(WirelessIcon *icon, u32 step)
{
    icon->step = step;
    icon->slide_x = data_020c7588[step];
}

/* func_02003bc4: called at the end of each update; does nothing. */
void WirelessIcon_AfterUpdate(WirelessIcon *icon)
{
    (void) icon;
}
CLEAN_AS(func_02003bc4, WirelessIcon_AfterUpdate)

/* func_02003bc8: one step in while active with the right graphics loaded, else one step out.
 * Once out of view while active with the other graphics, those are loaded. */
void WirelessIcon_Slide(WirelessIcon *icon)
{
    int active = WirelessIcon_IsActive(icon);
    int match = WirelessIcon_GraphicsMatch(icon);

    if (active && match) {
        if (icon->step < WIRELESS_ICON_STEPS) {
            set_step(icon, icon->step + 1);
        }
    } else if (icon->step != 0) {
        set_step(icon, icon->step - 1);
    }

    if (active && !match && icon->step == 0) {
        icon->wfc_graphics = !icon->wfc_graphics;
        func_02011f2c(icon->wfc_graphics);
    }
}
CLEAN_AS(func_02003bc8, WirelessIcon_Slide)

/* func_02003c38: follow state flag 4. When it is set the icon goes out of view at once and may
 * show again after a delay; while it stays set, its value leaving 1.0 starts a longer delay. */
void WirelessIcon_TrackFlag(WirelessIcon *icon)
{
    u8 flag4 = StateFlags_Test4() != 0;
    fx32 value = StateFlags_ValueOrOne();

    if (icon->delay > 0) {
        icon->delay--;
    }

    if (icon->flag4) {
        if (icon->flag_value == 0x1000 && value < 0x1000) {
            icon->delay = DELAY_VALUE_LEFT_ONE;
        }
    } else if (flag4) {
        set_step(icon, 0);
        icon->delay = DELAY_FLAG_SET;
    }

    icon->flag4 = flag4;
    icon->flag_value = value;
}
CLEAN_AS(func_02003c38, WirelessIcon_TrackFlag)

/* func_02003c98: whether the graphics loaded are those of the library in use. */
int WirelessIcon_GraphicsMatch(WirelessIcon *icon)
{
    u8 mode = func_020ec1e8();
    return icon->wfc_graphics == (mode == 3 || mode == 4);
}
CLEAN_AS(func_02003c98, WirelessIcon_GraphicsMatch)

/* func_02003cc0: a wireless library in use (a mode other than 0 and 6) and no delay. */
int WirelessIcon_IsActive(WirelessIcon *icon)
{
    int in_use = func_020ec1e8() != 0 && func_020ec1e8() != 6;
    return in_use && icon->delay == 0;
}
CLEAN_AS(func_02003cc0, WirelessIcon_IsActive)

/* func_02003cf4: draws the frame's cell unless the icon is out of view. */
void WirelessIcon_Draw(WirelessIcon *icon)
{
    if (icon->step == 0) {
        return;
    }
    int cell = data_020d5b3c[SIGNAL_ANIM].frames[icon->frame].cell;
    func_02088df8(0, cell, icon->slide_x + DRAW_X, DRAW_Y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_02003cf4, WirelessIcon_Draw)

/* func_02003d3c: while active, the frame from the link level; then the flag and the slide. */
void WirelessIcon_Update(WirelessIcon *icon)
{
    if (WirelessIcon_IsActive(icon)) {
        switch (func_020ec39c()) {
            case 1:
                icon->frame = 2;
                break;
            case 2:
                icon->frame = 1;
                break;
            case 3:
                icon->frame = 0;
                break;
            default:
                icon->frame = 3;
                break;
        }
    }
    WirelessIcon_TrackFlag(icon);
    WirelessIcon_Slide(icon);
    WirelessIcon_AfterUpdate(icon);
}
CLEAN_AS(func_02003d3c, WirelessIcon_Update)

/* func_02003d88: the icon has no animation to rewind. */
void WirelessIcon_Rewind(WirelessIcon *icon)
{
    (void) icon;
}
CLEAN_AS(func_02003d88, WirelessIcon_Rewind)

/* func_02003d8c: out of view, no signal and no delay. The graphics are marked as the local
 * library's without being loaded. */
void WirelessIcon_Reset(WirelessIcon *icon)
{
    icon->frame = 3;
    set_step(icon, 0);
    icon->flag_value = 0;
    icon->delay = 0;
    icon->flag4 = 0;
    icon->wfc_graphics = 0;
}
CLEAN_AS(func_02003d8c, WirelessIcon_Reset)

/* func_02003da8: the destructor, run at exit for data_0213ff98; does nothing. */
void WirelessIcon_Destruct(WirelessIcon *icon)
{
    (void) icon;
}
CLEAN_AS(func_02003da8, WirelessIcon_Destruct)

/* func_02003dac: the constructor, run at start for data_0213ff98. QUIRK: unlike the reset, it
 * sets the slide to 0 instead of the table's first entry (-18). */
void WirelessIcon_Construct(WirelessIcon *icon)
{
    icon->frame = 3;
    icon->slide_x = 0;
    icon->step = 0;
    icon->flag_value = 0;
    icon->delay = 0;
    icon->flag4 = 0;
    icon->wfc_graphics = 0;
}
CLEAN_AS(func_02003dac, WirelessIcon_Construct)

/* func_02003dc0 */
void WirelessIcons_Draw(void)
{
    WirelessIcon_Draw(&data_0213ff98);
}
CLEAN_AS(func_02003dc0, WirelessIcons_Draw)

/* func_02003dd0 */
void WirelessIcons_Update(void)
{
    WirelessIcon_Update(&data_0213ff98);
}
CLEAN_AS(func_02003dd0, WirelessIcons_Update)

/* func_02003de0 */
void WirelessIcons_Rewind(void)
{
    WirelessIcon_Rewind(&data_0213ff98);
}
CLEAN_AS(func_02003de0, WirelessIcons_Rewind)

/* func_02003df0 */
void WirelessIcons_Reset(void)
{
    WirelessIcon_Reset(&data_0213ff98);
}
CLEAN_AS(func_02003df0, WirelessIcons_Reset)
