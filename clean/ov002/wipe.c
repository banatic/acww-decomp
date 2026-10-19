/* The screen wipe of the menu scenes (wipe.h). */
#include "wipe.h"

#include <stddef.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"

static_assert(offsetof(Wipe, position) == 0x0c && offsetof(Wipe, direction) == 0x18, "wipe fields");
static_assert(offsetof(Progress, left) == 0x08 && sizeof(Wipe) == 0x1c, "progress fields");

extern const u8 data_ov002_0220bb04[]; /* the progress's vtable */
extern const u8 data_ov002_0220baf4[]; /* the wipe's vtable */

/* The parts of the display copy (display_shadow.h) that have no Clean version yet. */
extern s32 FX_MulFunc(s32 a, s32 b);

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int neg32(int a)
{
    return (int) (0u - (u32) a);
}

/* An arithmetic shift right, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_ov002_02208344 */
void Wipe_SetExtent(Wipe *wipe, int extent)
{
    wipe->extent = extent;
}
CLEAN_AS(func_ov002_02208344, Wipe_SetExtent)

/* func_ov002_02208348: sets window `window` to the whole screen with the wipe's edge at its
 * position. A direction other than the four gives the whole screen. */
void Wipe_ApplyWindow(Wipe *wipe, int window)
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0xff;
    int y2 = SCREEN_HEIGHT;

    switch (wipe->direction) {
        case WIPE_TOP:
            y1 = wipe->position - wipe->margin;
            if (y1 < 0) {
                y1 = 0;
            }
            break;
        case WIPE_BOTTOM:
            y2 = wipe->margin + SCREEN_HEIGHT - wipe->position;
            if (y2 > SCREEN_HEIGHT - 1) {
                y2 = SCREEN_HEIGHT - 1;
            }
            break;
        case WIPE_RIGHT:
            x2 = 0xff - wipe->position;
            if (x2 < 1) {
                x2 = 1;
            }
            break;
        case WIPE_LEFT:
            x1 = wipe->position;
            if (x1 > 0xfe) {
                x1 = 0xfe;
            }
            break;
    }

    DisplayShadow_SetWindow((unsigned int) window, x1, y1, x2, y2);
}
CLEAN_AS(func_ov002_02208348, Wipe_ApplyWindow)

/* func_ov002_022083b8: sets background `layer` to the offset (x, y) moved by the wipe's
 * position along its direction (both negated, as the hardware scrolls the other way). */
void Wipe_ApplyScroll(Wipe *wipe, int layer, int x, int y)
{
    switch (wipe->direction) {
        case WIPE_TOP:
            DisplayLayer_SetScroll((unsigned int) layer, -x, -(wipe->position + y));
            break;
        case WIPE_BOTTOM:
            DisplayLayer_SetScroll((unsigned int) layer, -x, wipe->position - y);
            break;
        case WIPE_RIGHT:
            DisplayLayer_SetScroll((unsigned int) layer, wipe->position - x, -y);
            break;
        case WIPE_LEFT:
            DisplayLayer_SetScroll((unsigned int) layer, -(wipe->position + x), -y);
            break;
    }
}
CLEAN_AS(func_ov002_022083b8, Wipe_ApplyScroll)

/* The height or width a direction runs over; 0 for none of the four. */
static int extent_of(u8 direction)
{
    switch (direction) {
        case WIPE_TOP:
        case WIPE_BOTTOM:
            return SCREEN_HEIGHT;
        case WIPE_RIGHT:
        case WIPE_LEFT:
            return SCREEN_WIDTH;
    }
    return 0;
}

/* func_ov002_02208418: a wipe over `frames` frames from position 0.
 * QUIRK: with a direction other than the four the extent is left as it was. */
void Wipe_Start(Wipe *wipe, int frames, u8 direction, int margin)
{
    wipe->direction = direction;
    wipe->margin = margin;
    Progress_Start(&wipe->progress, (unsigned int) frames);
    wipe->position = 0;
    if (extent_of(wipe->direction) != 0) {
        wipe->extent = extent_of(wipe->direction);
    }
}
CLEAN_AS(func_ov002_02208418, Wipe_Start)

/* func_ov002_02208458: a wipe over `frames` frames from the far end (position = extent).
 * QUIRK: with a direction other than the four the position and the extent are left as they
 * were. */
void Wipe_StartCovered(Wipe *wipe, int frames, u8 direction, u32 margin)
{
    wipe->direction = direction;
    wipe->margin = (s32) margin;
    Progress_Start(&wipe->progress, (unsigned int) frames);
    if (extent_of(wipe->direction) != 0) {
        wipe->position = extent_of(wipe->direction);
        wipe->extent = extent_of(wipe->direction);
    }
}
CLEAN_AS(func_ov002_02208458, Wipe_StartCovered)

/* func_ov002_02208498: Wipe_Start, then the main engine's window 0 set up for it: enabled,
 * showing all planes inside, and `layers` (a plane mask) taken from the planes outside the
 * windows when window 1 is on, else the planes outside set to all but `layers`. */
void Wipe_StartOnWindow0(Wipe *wipe, int layers, int frames, int direction, int margin)
{
    Wipe_Start(wipe, frames, (u8) direction, margin);
    DisplayShadow_EnableMainWindows(WINDOW_0);
    DisplayShadow_SetMainWindow0Planes(0x1f);
    if (DisplayShadow_GetMainWindows() & WINDOW_1) {
        DisplayShadow_HideMainOutsidePlanes((u8) layers);
    } else {
        DisplayShadow_SetMainOutsidePlanes((u8) (~layers & 0x1f));
    }
    Wipe_ApplyWindow(wipe, 0);
}
CLEAN_AS(func_ov002_02208498, Wipe_StartOnWindow0)

/* func_ov002_022084e4: Wipe_StartCovered, then the main engine's window 0 set up for it:
 * enabled, showing all planes inside and all but `layers` outside. */
void Wipe_StartCoveredOnWindow0(Wipe *wipe, int layers, int frames, int direction, int margin)
{
    Wipe_StartCovered(wipe, frames, (u8) direction, (u32) margin);
    DisplayShadow_EnableMainWindows(WINDOW_0);
    DisplayShadow_SetMainWindow0Planes(0x1f);
    DisplayShadow_SetMainOutsidePlanes((u8) (~layers & 0x1f));
    Wipe_ApplyWindow(wipe, 0);
}
CLEAN_AS(func_ov002_022084e4, Wipe_StartCoveredOnWindow0)

/* func_ov002_0220851c: Wipe_Start, then the sub engine's window 0 set up for it: enabled,
 * showing all planes inside and all but `layers` outside. */
void Wipe_StartOnWindow2(Wipe *wipe, int layers, int frames, int direction, int margin)
{
    Wipe_Start(wipe, frames, (u8) direction, margin);
    DisplayShadow_EnableSubWindows(WINDOW_0);
    DisplayShadow_SetSubWindow0Planes(0x1f, 1);
    DisplayShadow_SetSubOutsidePlanes((u8) (~layers & 0x1f));
    Wipe_ApplyWindow(wipe, 2);
}
CLEAN_AS(func_ov002_0220851c, Wipe_StartOnWindow2)

/* func_ov002_02208558: Wipe_StartCovered, then the sub engine's window 0 set up as by
 * Wipe_StartOnWindow2. */
void Wipe_StartCoveredOnWindow2(Wipe *wipe, int layers, int frames, int direction, int margin)
{
    Wipe_StartCovered(wipe, frames, (u8) direction, (u32) margin);
    DisplayShadow_EnableSubWindows(WINDOW_0);
    DisplayShadow_SetSubWindow0Planes(0x1f, 1);
    DisplayShadow_SetSubOutsidePlanes((u8) (~layers & 0x1f));
    Wipe_ApplyWindow(wipe, 2);
}
CLEAN_AS(func_ov002_02208558, Wipe_StartCoveredOnWindow2)

/* func_ov002_02208594: a frame of the wipe forward on `screen` (WipeScreen). Returns 1, with
 * the screen's windows turned off, on the frame after the one that brought the position to
 * the extent; else 0. */
int Wipe_Step(Wipe *wipe, int screen)
{
    if (Progress_Step(&wipe->progress)) {
        switch (screen) {
            case WIPE_ON_SUB:
                DisplayShadow_DisableSubWindows(WINDOW_0);
                break;
            case WIPE_ON_MAIN:
                DisplayShadow_DisableMainWindows(WINDOW_0);
                break;
        }
        return 1;
    }

    switch (wipe->direction) {
        case WIPE_TOP:
        case WIPE_BOTTOM:
            Wipe_StepVertical(wipe, screen);
            break;
        default:
            Wipe_StepHorizontal(wipe, screen);
            break;
    }
    return 0;
}
CLEAN_AS(func_ov002_02208594, Wipe_Step)

/* func_ov002_022085e8: moves the position on (linearly) and sets the screen's window. */
void Wipe_StepHorizontal(Wipe *wipe, int screen)
{
    wipe->position = sub32(wipe->extent, Progress_ScaleRemaining(&wipe->progress, wipe->extent));
    switch (screen) {
        case WIPE_ON_SUB:
            Wipe_ApplyWindow(wipe, 2);
            break;
        case WIPE_ON_MAIN:
            Wipe_ApplyWindow(wipe, 0);
            break;
    }
}
CLEAN_AS(func_ov002_022085e8, Wipe_StepHorizontal)

/* func_ov002_02208620: moves the position on (linearly); once it is past the margin, turns the
 * screen's window 0 on and sets it. */
void Wipe_StepVertical(Wipe *wipe, int screen)
{
    wipe->position = sub32(wipe->extent, Progress_ScaleRemaining(&wipe->progress, wipe->extent));
    if (wipe->position > wipe->margin) {
        switch (screen) {
            case WIPE_ON_SUB:
                DisplayShadow_EnableSubWindows(WINDOW_0);
                Wipe_ApplyWindow(wipe, 2);
                break;
            case WIPE_ON_MAIN:
                DisplayShadow_EnableMainWindows(WINDOW_0);
                Wipe_ApplyWindow(wipe, 0);
                break;
        }
    }
}
CLEAN_AS(func_ov002_02208620, Wipe_StepVertical)

/* Turns the screen's window 0 off and shows all planes outside the windows. */
static void close_window(int screen)
{
    switch (screen) {
        case WIPE_ON_SUB:
            DisplayShadow_DisableSubWindows(WINDOW_0);
            DisplayShadow_SetSubOutsidePlanes(0x1f);
            break;
        case WIPE_ON_MAIN:
            DisplayShadow_DisableMainWindows(WINDOW_0);
            DisplayShadow_SetMainOutsidePlanes(0x1f);
            break;
    }
}

/* func_ov002_0220866c: a frame of the wipe back on `screen`: the position runs from the extent
 * down to 0. Returns 1, with the position at 0 and the screen's window closed, on the frame
 * after the last step; else 0. */
int Wipe_StepBack(Wipe *wipe, int screen)
{
    if (Progress_Step(&wipe->progress)) {
        wipe->position = 0;
        close_window(screen);
        return 1;
    }

    switch (wipe->direction) {
        case WIPE_TOP:
        case WIPE_BOTTOM:
            Wipe_StepBackVertical(wipe, screen);
            break;
        default:
            Wipe_StepBackHorizontal(wipe, screen);
            break;
    }
    return 0;
}
CLEAN_AS(func_ov002_0220866c, Wipe_StepBack)

/* func_ov002_022086d0: moves the position back (by the square of the progress left) and sets
 * the screen's window. */
void Wipe_StepBackHorizontal(Wipe *wipe, int screen)
{
    wipe->position = Progress_ScaleRemainingSquared(&wipe->progress, wipe->extent);
    switch (screen) {
        case WIPE_ON_SUB:
            Wipe_ApplyWindow(wipe, 2);
            break;
        case WIPE_ON_MAIN:
            Wipe_ApplyWindow(wipe, 0);
            break;
    }
}
CLEAN_AS(func_ov002_022086d0, Wipe_StepBackHorizontal)

/* func_ov002_02208704: moves the position back (by the square of the progress left); while it
 * is past the margin sets the screen's window, else closes it. */
void Wipe_StepBackVertical(Wipe *wipe, int screen)
{
    wipe->position = Progress_ScaleRemainingSquared(&wipe->progress, wipe->extent);
    switch (screen) {
        case WIPE_ON_SUB:
        case WIPE_ON_MAIN:
            if (wipe->position > wipe->margin) {
                Wipe_ApplyWindow(wipe, screen == WIPE_ON_SUB ? 2 : 0);
            } else {
                close_window(screen);
            }
            break;
    }
}
CLEAN_AS(func_ov002_02208704, Wipe_StepBackVertical)

/* func_ov002_02208764: the horizontal displacement of a horizontal wipe (0 for a vertical
 * one). */
int Wipe_OffsetX(Wipe *wipe)
{
    switch (wipe->direction) {
        case WIPE_RIGHT:
            return neg32(wipe->position);
        case WIPE_LEFT:
            return wipe->position;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov002_02208764, Wipe_OffsetX)

/* func_ov002_02208780: the vertical displacement of a vertical wipe (0 for a horizontal
 * one). */
int Wipe_OffsetY(Wipe *wipe)
{
    switch (wipe->direction) {
        case WIPE_TOP:
            return wipe->position;
        case WIPE_BOTTOM:
            return neg32(wipe->position);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov002_02208780, Wipe_OffsetY)

/* func_ov002_0220879c: the deleting destructor. */
Wipe *Wipe_Delete(Wipe *wipe)
{
    wipe->progress.vtable = data_ov002_0220baf4;
    Progress_Destroy(&wipe->progress);
    Heap_OperatorDeleteB(wipe);
    return wipe;
}
CLEAN_AS(func_ov002_0220879c, Wipe_Delete)

/* func_ov002_022087bc */
Wipe *Wipe_Destroy(Wipe *wipe)
{
    wipe->progress.vtable = data_ov002_0220baf4;
    Progress_Destroy(&wipe->progress);
    return wipe;
}
CLEAN_AS(func_ov002_022087bc, Wipe_Destroy)

/* func_ov002_022087d4 */
Wipe *Wipe_Construct(Wipe *wipe)
{
    Progress_Construct(&wipe->progress);
    wipe->progress.vtable = data_ov002_0220baf4;
    return wipe;
}
CLEAN_AS(func_ov002_022087d4, Wipe_Construct)

/* func_ov002_022087ec: `value` times the progress still to run (20.12, rounded toward minus
 * infinity, the product kept to 32 bits). */
int Progress_ScaleRemaining(Progress *progress, int value)
{
    return shift_right((int) ((u32) value * (u32) progress->left), 12);
}
CLEAN_AS(func_ov002_022087ec, Progress_ScaleRemaining)

/* func_ov002_022087f4: `value` times the square of the progress still to run. */
int Progress_ScaleRemainingSquared(Progress *progress, int value)
{
    s32 squared = FX_MulFunc(progress->left, progress->left);
    return shift_right((int) ((u32) value * (u32) squared), 12);
}
CLEAN_AS(func_ov002_022087f4, Progress_ScaleRemainingSquared)

/* func_ov002_0220880c: a frame: the progress left goes down by the rate, stopping at 0.
 * Returns 1 when it was already 0 (the frame after the last), else 0. */
int Progress_Step(Progress *progress)
{
    if (progress->left == 0) {
        return 1;
    }
    if (progress->left > progress->rate) {
        progress->left = sub32(progress->left, progress->rate);
    } else {
        progress->left = 0;
    }
    return 0;
}
CLEAN_AS(func_ov002_0220880c, Progress_Step)

/* func_ov002_0220882c: a run over `frames` frames.
 * QUIRK: 0 frames gives a rate of 1.0 (one frame): the ROM's unsigned division returns the
 * numerator for a zero divisor. */
void Progress_Start(Progress *progress, unsigned int frames)
{
    progress->left = PROGRESS_ONE;
    progress->rate = (s32) (frames != 0 ? PROGRESS_ONE / frames : PROGRESS_ONE);
}
CLEAN_AS(func_ov002_0220882c, Progress_Start)

/* func_ov002_02208844 */
void Progress_Destroy(Progress *progress)
{
    progress->vtable = data_ov002_0220bb04;
}
CLEAN_AS(func_ov002_02208844, Progress_Destroy)

/* func_ov002_02208850: the deleting destructor. */
Progress *Progress_Delete(Progress *progress)
{
    progress->vtable = data_ov002_0220bb04;
    Heap_OperatorDeleteB(progress);
    return progress;
}
CLEAN_AS(func_ov002_02208850, Progress_Delete)

/* func_ov002_02208868: the destructor as one of the base's pair (it does what
 * Progress_Destroy does). */
void Progress_DestroyBase(Progress *progress)
{
    progress->vtable = data_ov002_0220bb04;
}
CLEAN_AS(func_ov002_02208868, Progress_DestroyBase)

/* func_ov002_02208874 */
void Progress_Construct(Progress *progress)
{
    progress->vtable = data_ov002_0220bb04;
}
CLEAN_AS(func_ov002_02208874, Progress_Construct)
