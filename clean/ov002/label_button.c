/* The menu scenes' label button (label_button.h). */
#include "label_button.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/label_sprite.h"
#include "main/screen_sprite.h"
#include "main/text_label.h"

static_assert(offsetof(LabelButton, anim_id) == 0x44 && offsetof(LabelButton, kind) == 0x72, "label button");
static_assert(sizeof(LabelButton) == 0x78, "label button");

extern const u8 data_ov002_0220bd58[]; /* LabelButton1's vtable */
extern const u8 data_ov002_0220bd74[]; /* LabelButton0's */

extern const u8 data_ov002_0220bd90[]; /* the base class's vtable */

extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c60; /* the touch's x, as a byte (as main's func_020a806c gives it) */
extern u8 data_021f6c5c; /* the touch's y */

/* The touch area from the place, both ends included. */
#define TOUCH_WIDTH 0x40
#define TOUCH_HEIGHT 0x18

/* The animation LabelButton_ShowAt starts, and the one whose frames move the button. */
#define ANIM_SHOWN 1
#define ANIM_PRESSED 2

/* The screen's centre, (0, 0) of main's places. */
#define CENTER_X 0x80
#define CENTER_Y 0x60

/* The vtable's entries called here. */
#define SLOT_STEP 3
#define SLOT_SET_PLACE 4

typedef void ButtonMethod(LabelButton *button);
typedef void ButtonPlaceMethod(LabelButton *button, int x, int y);

/* The function in vtable slot `slot` of the button. */
static uintptr_t virtual_slot(const LabelButton *button, int slot)
{
    return ((const u32 *) button->vtable)[slot];
}

static void step(LabelButton *button)
{
    ((ButtonMethod *) virtual_slot(button, SLOT_STEP))(button);
}

/* func_ov002_0220b3f0 (vtable entry 1): destructs and frees the button. */
LabelButton *LabelButton1_Delete(LabelButton *button)
{
    button->vtable = data_ov002_0220bd58;
    LabelButtonBase_Destruct(button);
    Heap_OperatorDeleteB(button);
    return button;
}
CLEAN_AS(func_ov002_0220b3f0, LabelButton1_Delete)

/* func_ov002_0220b410 (vtable entry 0) */
LabelButton *LabelButton1_Destroy(LabelButton *button)
{
    button->vtable = data_ov002_0220bd58;
    LabelButtonBase_Destruct(button);
    return button;
}
CLEAN_AS(func_ov002_0220b410, LabelButton1_Destroy)

/* func_ov002_0220b428 */
LabelButton *LabelButton1_Construct(LabelButton *button)
{
    LabelButtonBase_Construct(button, 1, 0);
    button->vtable = data_ov002_0220bd58;
    return button;
}
CLEAN_AS(func_ov002_0220b428, LabelButton1_Construct)

/* func_ov002_0220b444 (vtable entry 1) */
LabelButton *LabelButton0_Delete(LabelButton *button)
{
    button->vtable = data_ov002_0220bd74;
    LabelButtonBase_Destruct(button);
    Heap_OperatorDeleteB(button);
    return button;
}
CLEAN_AS(func_ov002_0220b444, LabelButton0_Delete)

/* func_ov002_0220b464 (vtable entry 0) */
LabelButton *LabelButton0_Destroy(LabelButton *button)
{
    button->vtable = data_ov002_0220bd74;
    LabelButtonBase_Destruct(button);
    return button;
}
CLEAN_AS(func_ov002_0220b464, LabelButton0_Destroy)

/* func_ov002_0220b47c */
LabelButton *LabelButton0_Construct(LabelButton *button)
{
    LabelButtonBase_Construct(button, 0, 0);
    button->vtable = data_ov002_0220bd74;
    return button;
}
CLEAN_AS(func_ov002_0220b47c, LabelButton0_Construct)

/* func_ov002_0220b498: whether the pen went down this frame within TOUCH_WIDTH by
 * TOUCH_HEIGHT pixels right of and below the button's place. */
int LabelButton_IsTouched(LabelButton *button)
{
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return 0;
    }
    int dx = data_021f6c60 - ScreenSprite_X((ScreenSprite *) (void *) button);
    int dy = data_021f6c5c - ScreenSprite_Y((ScreenSprite *) (void *) button);
    return dx >= 0 && dx <= TOUCH_WIDTH && dy >= 0 && dy <= TOUCH_HEIGHT;
}
CLEAN_AS(func_ov002_0220b498, LabelButton_IsTouched)

/* func_ov002_0220b4fc: shows message `message` of "2d_menu" with the button placed at (x, y)
 * on the screen, without offset, and starts animation 1 with one step. */
void LabelButton_ShowAt(LabelButton *button, int message, int x, int y)
{
    LabelButton_SetMessage(button, message);
    ((ButtonPlaceMethod *) virtual_slot(button, SLOT_SET_PLACE))(button, x, y);
    LabelSprite_SetOffset((LabelSprite *) (void *) button, 0, 0);
    LabelSprite_ShowSecond((LabelSprite *) (void *) button);
    LabelSprite_SetState((LabelSprite *) (void *) button, ANIM_SHOWN);
    step(button);
}
CLEAN_AS(func_ov002_0220b4fc, LabelButton_ShowAt)

/* func_ov002_0220b53c: as LabelButton_ShowAt, at (0x98, 0xac). */
void LabelButton_ShowLowerRight(LabelButton *button, int message)
{
    LabelButton_ShowAt(button, message, 0x98, 0xac);
}
CLEAN_AS(func_ov002_0220b53c, LabelButton_ShowLowerRight)

/* func_ov002_0220b550: gives the button the text of message `message` of "2d_menu".
 * QUIRK: returns what the destructor of its temporary label returns, the label's address on the
 * stack; the callers ignore it. */
int LabelButton_SetMessage(LabelButton *button, int message)
{
    TextLabel label;

    TextLabel_Construct(&label);
    TextLabel_LoadMenuMessage(&label, (char) message);
    LabelSprite_SetText((LabelSprite *) (void *) button, (TextBase *) (void *) &label);
    return (int) (uintptr_t) TextLabel_Destruct(&label);
}
CLEAN_AS(func_ov002_0220b550, LabelButton_SetMessage)

/* func_ov002_0220b57c: steps the animation while it plays; returns 1 when it stepped, 0 once
 * both layers have ended. */
int LabelButton_StepAnimation(LabelButton *button)
{
    if (LabelSprite_IsDone((LabelSprite *) (void *) button) == 0) {
        step(button);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_0220b57c, LabelButton_StepAnimation)

/* func_ov002_0220b59c: the y of anchor point `anchor` of the button: its place, moved as far
 * as the pressed animation has moved its frame from the first, plus 8 for anchors 0, 1 and 3
 * (and nothing for 2 or any other). LabelButton_AnchorX gives the x. */
int LabelButton_AnchorY(LabelButton *button, int anchor)
{
    int y = ScreenSprite_Y((ScreenSprite *) (void *) button);
    if (LabelSprite_State((LabelSprite *) (void *) button) == ANIM_PRESSED) {
        int dx;
        int dy;
        LabelSprite_Travel((LabelSprite *) (void *) button, &dx, &dy);
        y += dy;
    }
    switch (anchor) {
        case 0:
        case 1:
        case 3:
            y += 8;
            break;
        default:
            break;
    }
    return y;
}
CLEAN_AS(func_ov002_0220b59c, LabelButton_AnchorY)

/* func_ov002_0220b5ec: the x of anchor point `anchor` of the button: its place, moved as far
 * as the pressed animation has moved its frame from the first, plus 0x10 for anchors 0 and 2,
 * 0x20 for 1 and 3 (and nothing for any other). */
int LabelButton_AnchorX(LabelButton *button, int anchor)
{
    int x = ScreenSprite_X((ScreenSprite *) (void *) button);
    if (LabelSprite_State((LabelSprite *) (void *) button) == ANIM_PRESSED) {
        int dx;
        int dy;
        LabelSprite_Travel((LabelSprite *) (void *) button, &dx, &dy);
        x += dx;
    }
    switch (anchor) {
        case 0:
        case 2:
            x += 0x10;
            break;
        case 1:
        case 3:
            x += 0x20;
            break;
        default:
            break;
    }
    return x;
}
CLEAN_AS(func_ov002_0220b5ec, LabelButton_AnchorX)

/* func_ov002_0220b63c (vtable slot 4 of all three classes): places the button at (x, y) on
 * the screen. */
void LabelButton_SetPlace(LabelButton *button, int x, int y)
{
    ScreenSprite_SetPlace((ScreenSprite *) (void *) button, x - CENTER_X, y - CENTER_Y);
}
CLEAN_AS(func_ov002_0220b63c, LabelButton_SetPlace)

/* func_ov002_0220b648: the base class's destructor, as the derived classes' destructors call
 * it. */
LabelButton *LabelButtonBase_Destruct(LabelButton *button)
{
    button->vtable = data_ov002_0220bd90;
    LabelSprite_DestructCopy((LabelSprite *) (void *) button);
    return button;
}
CLEAN_AS(func_ov002_0220b648, LabelButtonBase_Destruct)

/* func_ov002_0220b660 (vtable entry 1): destructs and frees a base class button. */
LabelButton *LabelButtonBase_Delete(LabelButton *button)
{
    button->vtable = data_ov002_0220bd90;
    LabelSprite_DestructCopy((LabelSprite *) (void *) button);
    Heap_OperatorDeleteB(button);
    return button;
}
CLEAN_AS(func_ov002_0220b660, LabelButtonBase_Delete)

/* func_ov002_0220b680 (vtable entry 0).
 * QUIRK: the same code as LabelButtonBase_Destruct, a second copy in the ROM. */
LabelButton *LabelButtonBase_Destroy(LabelButton *button)
{
    button->vtable = data_ov002_0220bd90;
    LabelSprite_DestructCopy((LabelSprite *) (void *) button);
    return button;
}
CLEAN_AS(func_ov002_0220b680, LabelButtonBase_Destroy)

/* func_ov002_0220b698: constructs main's labelled sprite with `kind` and `param`, then makes
 * it a base class button. */
LabelButton *LabelButtonBase_Construct(LabelButton *button, char kind, int param)
{
    LabelSprite_ConstructCopy((LabelSprite *) (void *) button, kind, param);
    button->vtable = data_ov002_0220bd90;
    return button;
}
CLEAN_AS(func_ov002_0220b698, LabelButtonBase_Construct)
