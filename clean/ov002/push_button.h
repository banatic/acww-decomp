/* A button the menu scenes of overlays such as 112, 122 and 134-146 keep (at 0x1fb4 in
 * ov146's scene): an object of main's second sprite class (vtable 0x020e2330, constructor
 * func_0208ec88, destructor func_0208ebb8) with this class's vtable 0x0220bcec over it. The
 * scene presses it when it is touched (PushButton_Contains): the pressed animation, then the
 * release, which PushButton_SettleRelease turns back into the button at rest once it has
 * played. */
#ifndef CLEAN_OV002_PUSH_BUTTON_H
#define CLEAN_OV002_PUSH_BUTTON_H

#include "main/screen_icon.h"
#include "types.h"

/* The animations (func_0208e95c starts one, func_0208e958 reads it). */
enum PushButtonAnim {
    PUSH_BUTTON_ANIM_NONE = 0,     /* as constructed */
    PUSH_BUTTON_ANIM_UP = 1,       /* at rest */
    PUSH_BUTTON_ANIM_PRESSED = 2,  /* held down */
    PUSH_BUTTON_ANIM_RELEASING = 3 /* coming back up */
};

typedef struct PushButton {
    const void *vtable; /* data_ov002_0220bcec */
    s32 x;              /* 0x04: main's place (func_0208aef0) */
    s32 y;              /* 0x08: (func_0208aeec) */
    s32 offset_x;       /* 0x0c: drawn at the place plus the offset */
    s32 offset_y;       /* 0x10 */
    CellAnim anim;      /* 0x14 */
    CellAnim anim2;     /* 0x28: played with the first */
    u32 anim_id;        /* 0x3c: PushButtonAnim */
    u8 kind;            /* 0x40: the value given to func_0208ec88 */
    u8 pad_41[3];
    s32 unk_44; /* 0x44 */
} PushButton;

void PushButton_PressCue(PushButton *button);
void PushButton_ScrollCue(PushButton *button);
int PushButton_FaceY(PushButton *button);
int PushButton_FaceX(PushButton *button);
int PushButton_ScreenY(PushButton *button);
int PushButton_ScreenX(PushButton *button);
void PushButton_SettleRelease(PushButton *button);
int PushButton_Release(PushButton *button);
void PushButton_Press(PushButton *button);
void PushButton_ShowUp(PushButton *button);
int PushButton_Contains(PushButton *button, int x, int y);
PushButton *PushButton_Delete(PushButton *button);
PushButton *PushButton_Destroy(PushButton *button);
PushButton *PushButton_Construct(PushButton *button);

#endif
