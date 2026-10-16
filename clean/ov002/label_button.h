/* A sprite with a text of "2d_menu" on it that the menu scenes use as a button (at 0x3bc in
 * ov091's scene; overlays 091 and 096-106 keep one, and the paged choice one as its page
 * label): an object of main's labelled sprite class (vtable 0x020e23a0, constructor
 * func_0208f58c, destructor func_0208f46c) under ov002's class (vtable 0x0220bd90, constructor
 * func_ov002_0220b698, destructor func_ov002_0220b648), whose own vtable slot 4 places it by
 * screen coordinates (func_ov002_0220b63c). Slot 2 is main's draw (func_0208f288), slot 3
 * main's step of its two animation layers (func_0208f268).
 *
 * Two classes derive from it, differing only in the byte func_0208f58c is given: LabelButton1
 * (vtable 0x0220bd58, 1) and LabelButton0 (vtable 0x0220bd74, 0).
 *
 * The animations (func_0208f0c4 starts one, func_0208f0c0 reads it): LabelButton_ShowAt starts
 * 1; ov091 starts 2 when the button is touched. */
#ifndef CLEAN_OV002_LABEL_BUTTON_H
#define CLEAN_OV002_LABEL_BUTTON_H

#include "types.h"

typedef struct LabelButton {
    const void *vtable; /* data_ov002_0220bd58 or data_ov002_0220bd74 */
    /* main's labelled sprite */
    s32 x;           /* 0x04: its place (func_0208aef0) */
    s32 y;           /* 0x08: (func_0208aeec) */
    s32 offset_x;    /* 0x0c: (func_0208f210 sets both) */
    s32 offset_y;    /* 0x10 */
    u8 unk_14[0x30]; /* 0x14: the two animation layers at 0x1c and 0x30 */
    u32 anim_id;     /* 0x44 */
    void *box;       /* 0x48: the text's box */
    u8 text[0x24];   /* 0x4c: the text */
    u16 unk_70;      /* 0x70 */
    u8 kind;         /* 0x72: the byte given to func_0208f58c */
    u8 unk_73;       /* 0x73 */
    u8 unk_74;       /* 0x74: cleared by LabelButton_ShowAt (func_0208f250) */
    u8 unk_75;       /* 0x75 */
    u8 pad_76[2];
} LabelButton;

LabelButton *LabelButton1_Delete(LabelButton *button);
LabelButton *LabelButton1_Destroy(LabelButton *button);
LabelButton *LabelButton1_Construct(LabelButton *button);
LabelButton *LabelButton0_Delete(LabelButton *button);
LabelButton *LabelButton0_Destroy(LabelButton *button);
LabelButton *LabelButton0_Construct(LabelButton *button);
int LabelButton_IsTouched(LabelButton *button);
void LabelButton_ShowAt(LabelButton *button, int message, int x, int y);
void LabelButton_ShowLowerRight(LabelButton *button, int message);
int LabelButton_SetMessage(LabelButton *button, int message);
int LabelButton_StepAnimation(LabelButton *button);
int LabelButton_AnchorY(LabelButton *button, int anchor);

#endif
