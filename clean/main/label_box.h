/* The text box a label opens (class data_020e3dac, 0x84 bytes): a box of text_draw.h whose
 * text is laid out by a box walker (text_walker.h).
 *
 * Drawing a strip (vtable slot 2, LabelBox_Draw) or measuring the text (slot 3,
 * LabelBox_Measure) walks the box's text with its walker (data_021f44dc when it has none),
 * which hands the box each character, the start and the end of the text and each tag: drawn
 * (TextDraw_BeginStrip, TextDraw_DrawChar, TextDraw_UploadStrip) or measured
 * (TextDraw_BeginMeasure, TextDraw_MeasureChar), and while drawing a colour tag (0xff/0)
 * changes the text's colour.
 *
 * The boxes are allocated in the text heap (data_021c8194) and kept in its list
 * (data_021c81bc), drawing into RAM (LabelBox_New) or into VRAM tiles (LabelBox_NewInVram). */
#ifndef CLEAN_MAIN_LABEL_BOX_H
#define CLEAN_MAIN_LABEL_BOX_H

#include "text_base.h"
#include "text_draw.h"
#include "text_walker.h"
#include "types.h"

/* What a walk of the box's text is for. */
enum LabelBoxMode {
    LABEL_BOX_IDLE = 0,
    LABEL_BOX_DRAW = 1,
    LABEL_BOX_MEASURE = 2,
};

typedef struct LabelBox {
    TextDrawBox base;
    s32 mode;           /* 0x7c: enum LabelBoxMode */
    TextWalker *walker; /* 0x80: or NULL for data_021f44dc */
} LabelBox;

int LabelBox_Measure(LabelBox *box);
void LabelBox_Draw(LabelBox *box);
void LabelBox_OnTag(LabelBox *box, int position);
void LabelBox_OnCharacter(LabelBox *box, int character);
void LabelBox_OnEnd(LabelBox *box);
void LabelBox_OnText(LabelBox *box);
void LabelBox_SetWalker(LabelBox *box, u32 walker);
void *LabelBox_Delete(LabelBox *box);
void *LabelBox_Destruct(LabelBox *box);
LabelBox *LabelBox_Construct(LabelBox *box, int ram, int cells, int rows);
LabelBox *LabelBox_ConstructInVram(LabelBox *box, unsigned int first_tile, unsigned int cells, unsigned int rows);
int LabelBox_TextWidth(TextBase *text);
int LabelBox_CharsWidth(int chars);
void LabelBox_Free(LabelBox *box);
LabelBox *LabelBox_New(int ram, int cells, int rows);
LabelBox *LabelBox_NewInVram(int first_tile, int cells, int rows);

#endif
