/* The menu scenes' push button (push_button.h). */
#include "push_button.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/dual_cell_sprite.h"
#include "main/screen_sprite.h"

static_assert(offsetof(PushButton, anim) == 0x14 && offsetof(PushButton, anim2) == 0x28, "push button");
static_assert(offsetof(PushButton, anim_id) == 0x3c && offsetof(PushButton, unk_44) == 0x44, "push button");

extern const u8 data_ov002_0220bcec[]; /* the button's vtable */

/* Main's second sprite class. */
extern void RtcSendPxiCommand(int command); /* func_020f1fb4(&data_021fd1bc, command) */

/* PushButton_Contains: the size of the touch area from the screen place, both ends included. */
#define BUTTON_SIZE 0x10
/* PushButton_FaceY/X: from the screen place to the face's. */
#define FACE_INSET 7

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* func_ov002_0220a4bc: sends command 0x33, which the scenes send as they press the button. */
void PushButton_PressCue(PushButton *button)
{
    (void) button;
    RtcSendPxiCommand(0x33);
}
CLEAN_AS(func_ov002_0220a4bc, PushButton_PressCue)

/* func_ov002_0220a4c8: sends command 0x19 (ov146 sends it when a scroll position it shows
 * moves 4 or more). */
void PushButton_ScrollCue(PushButton *button)
{
    (void) button;
    RtcSendPxiCommand(0x19);
}
CLEAN_AS(func_ov002_0220a4c8, PushButton_ScrollCue)

/* func_ov002_0220a4d4: y of the button's face: the screen place moved as far as the pressed
 * or releasing animation has moved its frame from the first (func_0208e9e0; 0 for the other
 * animations), plus FACE_INSET. */
int PushButton_FaceY(PushButton *button)
{
    int dx;
    int dy;
    DualCellSprite_Travel((DualCellSprite *) (void *) button, &dx, &dy);
    return add32(add32(dy, PushButton_ScreenY(button)), FACE_INSET);
}
CLEAN_AS(func_ov002_0220a4d4, PushButton_FaceY)

/* func_ov002_0220a4f8 */
int PushButton_FaceX(PushButton *button)
{
    int dx;
    int dy;
    DualCellSprite_Travel((DualCellSprite *) (void *) button, &dx, &dy);
    return add32(add32(dx, PushButton_ScreenX(button)), FACE_INSET);
}
CLEAN_AS(func_ov002_0220a4f8, PushButton_FaceX)

/* func_ov002_0220a51c: y on the screen, the place plus the offset. */
int PushButton_ScreenY(PushButton *button)
{
    int y = ScreenSprite_Y((ScreenSprite *) (void *) button);
    return add32(button->offset_y, y);
}
CLEAN_AS(func_ov002_0220a51c, PushButton_ScreenY)

/* func_ov002_0220a530 */
int PushButton_ScreenX(PushButton *button)
{
    int x = ScreenSprite_X((ScreenSprite *) (void *) button);
    return add32(button->offset_x, x);
}
CLEAN_AS(func_ov002_0220a530, PushButton_ScreenX)

/* func_ov002_0220a544: a release that has played out leaves the button at rest. */
void PushButton_SettleRelease(PushButton *button)
{
    if (DualCellSprite_State((DualCellSprite *) (void *) button) == PUSH_BUTTON_ANIM_RELEASING &&
        DualCellSprite_IsDone((DualCellSprite *) (void *) button) != 0) {
        PushButton_ShowUp(button);
    }
}
CLEAN_AS(func_ov002_0220a544, PushButton_SettleRelease)

/* func_ov002_0220a568: returns what func_0208e95c returns. */
int PushButton_Release(PushButton *button)
{
    return (int) (intptr_t) DualCellSprite_SetState((DualCellSprite *) (void *) button, PUSH_BUTTON_ANIM_RELEASING);
}
CLEAN_AS(func_ov002_0220a568, PushButton_Release)

/* func_ov002_0220a574 */
void PushButton_Press(PushButton *button)
{
    DualCellSprite_SetState((DualCellSprite *) (void *) button, PUSH_BUTTON_ANIM_PRESSED);
}
CLEAN_AS(func_ov002_0220a574, PushButton_Press)

/* func_ov002_0220a580 */
void PushButton_ShowUp(PushButton *button)
{
    DualCellSprite_SetState((DualCellSprite *) (void *) button, PUSH_BUTTON_ANIM_UP);
}
CLEAN_AS(func_ov002_0220a580, PushButton_ShowUp)

/* func_ov002_0220a58c: whether the point (x, y) is within BUTTON_SIZE pixels right of and
 * below the screen place, both ends included. */
int PushButton_Contains(PushButton *button, int x, int y)
{
    int dx = sub32(x, PushButton_ScreenX(button));
    int dy = sub32(y, PushButton_ScreenY(button));
    return dx >= 0 && dx <= BUTTON_SIZE && dy >= 0 && dy <= BUTTON_SIZE;
}
CLEAN_AS(func_ov002_0220a58c, PushButton_Contains)

/* func_ov002_0220a5c4 (vtable entry 1) */
PushButton *PushButton_Delete(PushButton *button)
{
    button->vtable = data_ov002_0220bcec;
    DualCellSprite_DestructCopy((DualCellSprite *) (void *) button);
    Heap_OperatorDeleteB(button);
    return button;
}
CLEAN_AS(func_ov002_0220a5c4, PushButton_Delete)

/* func_ov002_0220a5e4 (vtable entry 0) */
PushButton *PushButton_Destroy(PushButton *button)
{
    button->vtable = data_ov002_0220bcec;
    DualCellSprite_DestructCopy((DualCellSprite *) (void *) button);
    return button;
}
CLEAN_AS(func_ov002_0220a5e4, PushButton_Destroy)

/* func_ov002_0220a5fc: main's sprite of kind 0, without an animation. */
PushButton *PushButton_Construct(PushButton *button)
{
    DualCellSprite_ConstructCopy((DualCellSprite *) (void *) button, 0);
    button->vtable = data_ov002_0220bcec;
    DualCellSprite_SetState((DualCellSprite *) (void *) button, PUSH_BUTTON_ANIM_NONE);
    return button;
}
CLEAN_AS(func_ov002_0220a5fc, PushButton_Construct)
