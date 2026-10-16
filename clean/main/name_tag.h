/* A name tag (vtable data_020e22f8, 0x80 bytes, derived from main's screen sprite base,
 * screen_sprite.h): a cell drawn on the main screen with a text box over it that shows a name.
 * Overlay 004 keeps five (func_ov004_02245f70 builds them as an array): kinds 0-3 placed at the
 * screen positions of the town's players and given their names, kind 4 at a fixed place.
 *
 * Its kind picks the cell's animation (an entry of data_020d5b3c, from data_020d0ac8) and the
 * VRAM tiles of its text box; the animation's frames are widths of the tag, and the tag takes
 * the frame that fits the text (NameTag_LayOut).
 *
 * Its states (NameTagState), stepped by its update (NameTag_Update): hidden, until asked to show
 * (the box is then made, the text drawn and laid out); appearing, in which the tag pops (drawn
 * 5 pixels lower, then 1 higher, 1 lower, then in place); shown, until no longer asked; hiding,
 * in which it drops 11 pixels a frame for two frames, after which its box is freed. */
#ifndef CLEAN_MAIN_NAME_TAG_H
#define CLEAN_MAIN_NAME_TAG_H

#include "label_box.h"   /* LabelBox */
#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "text_base.h"  /* TextBase */
#include "text_label.h" /* TextVtable */
#include "types.h"

enum NameTagState {
    NAME_TAG_HIDDEN = 0,
    NAME_TAG_APPEARING = 1,
    NAME_TAG_SHOWN = 2,
    NAME_TAG_HIDING = 3,
};

/* The kind with the fixed place, its own palette colour and VRAM tiles. */
#define NAME_TAG_KIND_FIXED 4

/* The name: a message label of the quick messages (quick_message.c, vtable data_020da640). */
typedef struct NameTagText {
    const TextVtable *vtable;
    u32 words[12];
} NameTagText;

typedef struct NameTag {
    ScreenSprite base; /* vtable data_020e22f8 */
    int kind;          /* 0x0c: 0-4 */
    int anim_entry;    /* 0x10: the entry of data_020d5b3c the cell's animation is */
    CellAnim anim;     /* 0x14: still; its frame is the tag's width */
    int x;             /* 0x28: the place, added to the base class's */
    int y;             /* 0x2c */
    int bounce;        /* 0x30: pixels lower, while appearing and hiding */
    int shift_x;       /* 0x34: pixels to the right, for the width's frame */
    NameTagText text;  /* 0x38 */
    LabelBox *box;     /* 0x6c: or NULL */
    int state;         /* 0x70: NameTagState */
    int wanted;        /* 0x74: nonzero while the tag is asked to show */
    int timer;         /* 0x78: frames left of appearing or hiding */
    u8 visible;        /* 0x7c: drawn */
    u8 pad_7d[3];
} NameTag;

void NameTag_FreeBox(NameTag *tag);
void NameTag_OpenBox(NameTag *tag);
void NameTag_LayOut(NameTag *tag);
void NameTag_SetAnim(NameTag *tag);
void NameTag_StepHiding(NameTag *tag);
void NameTag_EnterHiding(NameTag *tag);
void NameTag_StepShown(NameTag *tag);
void NameTag_EnterShown(NameTag *tag);
void NameTag_StepAppearing(NameTag *tag);
void NameTag_EnterAppearing(NameTag *tag);
void NameTag_StepHidden(NameTag *tag);
void NameTag_EnterHidden(NameTag *tag);
void NameTag_LoadFixedColour(void);
void *NameTag_Hide(NameTag *tag);
int NameTag_Show(NameTag *tag);
void *NameTag_SetText(NameTag *tag, TextBase *text);
void NameTag_SetPlace(NameTag *tag, int x, int y);
void NameTag_Rewind(NameTag *tag);
void NameTag_SetKind(NameTag *tag, int kind);
void NameTag_Update(NameTag *tag);
void NameTag_Draw(NameTag *tag);
NameTag *NameTag_Delete(NameTag *tag);
NameTag *NameTag_Destruct(NameTag *tag);
NameTag *NameTag_Construct(NameTag *tag);

#endif
