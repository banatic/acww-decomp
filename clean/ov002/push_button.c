/* The menu scenes' push button (push_button.h). */
#include "push_button.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(PushButton, anim) == 0x14 && offsetof(PushButton, anim2) == 0x28, "push button");
static_assert(offsetof(PushButton, anim_id) == 0x3c && offsetof(PushButton, unk_44) == 0x44, "push button");

extern const u8 data_ov002_0220bcec[];  /* the button's vtable */
extern void func_020edb3c(void *block); /* operator delete */

/* Main's second sprite class. */
extern void *func_0208ec88(PushButton *button, int kind);        /* constructor */
extern void *func_0208ebb8(PushButton *button);                  /* destructor */
extern void *func_0208e95c(PushButton *button, int anim);        /* start an animation */
extern int func_0208e958(PushButton *button);                    /* the animation, anim_id */
extern int func_0208e930(PushButton *button);                    /* whether both layers ended */
extern void func_0208e9e0(PushButton *button, int *dx, int *dy); /* see PushButton_FaceY */
extern int func_0208aef0(PushButton *button);                    /* x */
extern int func_0208aeec(PushButton *button);                    /* y */
extern void RtcSendPxiCommand(int command);                      /* func_020f1fb4(&data_021fd1bc, command) */

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
    func_0208e9e0(button, &dx, &dy);
    return add32(add32(dy, PushButton_ScreenY(button)), FACE_INSET);
}
CLEAN_AS(func_ov002_0220a4d4, PushButton_FaceY)

/* func_ov002_0220a4f8 */
int PushButton_FaceX(PushButton *button)
{
    int dx;
    int dy;
    func_0208e9e0(button, &dx, &dy);
    return add32(add32(dx, PushButton_ScreenX(button)), FACE_INSET);
}
CLEAN_AS(func_ov002_0220a4f8, PushButton_FaceX)

/* func_ov002_0220a51c: y on the screen, the place plus the offset. */
int PushButton_ScreenY(PushButton *button)
{
    int y = func_0208aeec(button);
    return add32(button->offset_y, y);
}
CLEAN_AS(func_ov002_0220a51c, PushButton_ScreenY)

/* func_ov002_0220a530 */
int PushButton_ScreenX(PushButton *button)
{
    int x = func_0208aef0(button);
    return add32(button->offset_x, x);
}
CLEAN_AS(func_ov002_0220a530, PushButton_ScreenX)

/* func_ov002_0220a544: a release that has played out leaves the button at rest. */
void PushButton_SettleRelease(PushButton *button)
{
    if (func_0208e958(button) == PUSH_BUTTON_ANIM_RELEASING && func_0208e930(button) != 0) {
        PushButton_ShowUp(button);
    }
}
CLEAN_AS(func_ov002_0220a544, PushButton_SettleRelease)

/* func_ov002_0220a568: returns what func_0208e95c returns. */
int PushButton_Release(PushButton *button)
{
    return (int) (intptr_t) func_0208e95c(button, PUSH_BUTTON_ANIM_RELEASING);
}
CLEAN_AS(func_ov002_0220a568, PushButton_Release)

/* func_ov002_0220a574 */
void PushButton_Press(PushButton *button)
{
    func_0208e95c(button, PUSH_BUTTON_ANIM_PRESSED);
}
CLEAN_AS(func_ov002_0220a574, PushButton_Press)

/* func_ov002_0220a580 */
void PushButton_ShowUp(PushButton *button)
{
    func_0208e95c(button, PUSH_BUTTON_ANIM_UP);
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
    func_0208ebb8(button);
    func_020edb3c(button);
    return button;
}
CLEAN_AS(func_ov002_0220a5c4, PushButton_Delete)

/* func_ov002_0220a5e4 (vtable entry 0) */
PushButton *PushButton_Destroy(PushButton *button)
{
    button->vtable = data_ov002_0220bcec;
    func_0208ebb8(button);
    return button;
}
CLEAN_AS(func_ov002_0220a5e4, PushButton_Destroy)

/* func_ov002_0220a5fc: main's sprite of kind 0, without an animation. */
PushButton *PushButton_Construct(PushButton *button)
{
    func_0208ec88(button, 0);
    button->vtable = data_ov002_0220bcec;
    func_0208e95c(button, PUSH_BUTTON_ANIM_NONE);
    return button;
}
CLEAN_AS(func_ov002_0220a5fc, PushButton_Construct)
