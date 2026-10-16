/* main's labelled sprite (vtable data_020e23a0, 0x78 bytes, derived from main's screen sprite
 * base, screen_sprite.h): two cell animations played together with a short text drawn over
 * them in a box of OBJ tiles. The menu scenes' label buttons (ov002/label_button.h) build on
 * it, and main's func_020ac0ac keeps one.
 *
 * Its kind (0 or 1) picks its animations (from the entry of data_020d0b74 on), the VRAM tiles of
 * its text box (data_020d0b7c) and the OBJ colour its text is drawn in (data_020d0b78: colour 14
 * or 15 of OBJ palette 0). That colour is loaded into both engines' OBJ palettes from the
 * sprite's own `colour` whenever it differs from the one last loaded for the kind
 * (data_021d361c), so the text turns another colour while the sprite is pressed.
 *
 * Its state picks the pair of animations of the table data_020d6fcc (the kind's entry plus
 * data_020d0b94's, the second the next entry), both held on their last frame: state 0 is not
 * drawn and not animated and has no text box, state 1 is shown still, states 2 and 3 play.
 * Vtable slot 2 draws it, slot 3 animates it. It is drawn at the base class's place plus
 * `offset`, on the main screen or the sub screen, and when `window` is set drawn again as OBJ
 * window.
 *
 * The text is an 8-bit text of up to 16 characters (LabelSpriteText, vtable data_020e2388,
 * derived from main's 8-bit text base, text_base.h). */
#ifndef CLEAN_MAIN_LABEL_SPRITE_H
#define CLEAN_MAIN_LABEL_SPRITE_H

#include "label_box.h"   /* LabelBox */
#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "text_base.h"  /* TextBase */
#include "text_label.h" /* TextVtable */
#include "types.h"

enum LabelSpriteState {
    LABEL_SPRITE_HIDDEN = 0,
    LABEL_SPRITE_STILL = 1,
    LABEL_SPRITE_PRESSED = 2, /* the text in the pressed colour; LabelSprite_Travel measures it
                               * from the first frame */
    LABEL_SPRITE_PLAY_B = 3,  /* and this one back to the first frame */
};

#define LABEL_SPRITE_TEXT_CAPACITY 16

/* The text (0x24 bytes): the 8-bit text base's fields, then its characters. */
typedef struct LabelSpriteText {
    const TextVtable *vtable;                 /* data_020e2388 */
    u32 length;                               /* 0x04: the bytes set */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x08 */
    char chars[LABEL_SPRITE_TEXT_CAPACITY];   /* 0x12 */
    u8 pad_22[2];
} LabelSpriteText;

typedef struct LabelSprite {
    ScreenSprite base;    /* vtable data_020e23a0, or a derived class's */
    int offset_x;         /* 0x0c: added to the base class's place */
    int offset_y;         /* 0x10 */
    int palette;          /* 0x14: the first animation's OBJ palette, -1 for the cells' own */
    int kind;             /* 0x18: 0 or 1 */
    CellAnim first;       /* 0x1c */
    CellAnim second;      /* 0x30 */
    int state;            /* 0x44: LabelSpriteState */
    LabelBox *box;        /* 0x48: the text's box, or NULL */
    LabelSpriteText text; /* 0x4c */
    u16 colour;           /* 0x70: the text's colour (BGR555) */
    u8 on_main;           /* 0x72: drawn on the main screen, else on the sub screen */
    u8 window;            /* 0x73: also drawn as OBJ window */
    u8 hide_second;       /* 0x74: the second animation not drawn */
    u8 colour_dirty;      /* 0x75: `colour` to be loaded at the next draw */
    u8 pad_76[2];
} LabelSprite;

void LabelSprite_UploadColour(LabelSprite *sprite);
void LabelSprite_FreeBox(LabelSprite *sprite);
void LabelSprite_OpenBox(LabelSprite *sprite);
int LabelSprite_IsDone(LabelSprite *sprite);
int LabelSprite_State(LabelSprite *sprite);
void LabelSprite_SetState(LabelSprite *sprite, int state);
void LabelSprite_Travel(LabelSprite *sprite, int *dx, int *dy);
void LabelSprite_SetOffset(LabelSprite *sprite, int x, int y);
void LabelSprite_SetText(LabelSprite *sprite, TextBase *text);
void LabelSprite_ShowSecond(LabelSprite *sprite);
void LabelSprite_HideSecond(LabelSprite *sprite);
void LabelSprite_SetWindow(LabelSprite *sprite);
void LabelSprite_Update(LabelSprite *sprite);
void LabelSprite_Draw(LabelSprite *sprite);
LabelSprite *LabelSprite_DestructCopy(LabelSprite *sprite);
LabelSprite *LabelSprite_Delete(LabelSprite *sprite);
LabelSprite *LabelSprite_Destruct(LabelSprite *sprite);
LabelSprite *LabelSprite_Construct(LabelSprite *sprite, int on_main, int kind);
LabelSprite *LabelSprite_ConstructCopy(LabelSprite *sprite, char on_main, int kind);
int LabelSprite_TextChars(LabelSpriteText *text);
int LabelSprite_TextCapacity(void);
LabelSpriteText *LabelSprite_TextDelete(LabelSpriteText *text);
LabelSpriteText *LabelSprite_TextDestruct(LabelSpriteText *text);
LabelSpriteText *LabelSprite_TextConstruct(LabelSpriteText *text);

#endif
