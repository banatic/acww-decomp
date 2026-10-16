/* The labels' text boxes (label_box.h). */
#include "label_box.h"

#include "autoload_2/heap.h" /* Heap_Alloc, Heap_Free, Heap_OperatorDeleteB */
#include "clean.h"
#include "message_tag.h"
#include "text_box.h"

static_assert(offsetof(LabelBox, mode) == 0x7c, "label box mode");
static_assert(offsetof(LabelBox, walker) == 0x80, "label box walker");
static_assert(sizeof(LabelBox) == 0x84, "label box");

/* The box's vtable slots called here. */
#define LABEL_BOX_SLOT_DESTRUCT 0
#define LABEL_BOX_SLOT_MEASURE 3

/* A colour tag: group 0xff, kind 0. */
#define LABEL_BOX_GROUP_FORMAT 0xff
#define LABEL_BOX_KIND_COLOUR 0

/* The box LabelBox_CharsWidth measures with: from VRAM tile 0, 1 tile wide, 2 high. */
#define LABEL_BOX_MEASURE_TILE 0
#define LABEL_BOX_MEASURE_CELLS 1
#define LABEL_BOX_MEASURE_ROWS 2

extern const u32 data_020e3dac[]; /* the label box's vtable */
extern BoxWalker data_021f44dc;   /* the box walker boxes use when they have none */
extern Heap *data_021c8194;       /* the text heap */
extern u8 data_021c81bc[];        /* the list of boxes (an NNSFndList) */

extern void NNS_FndAppendListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
/* The walkers' base (message_cursor.h): its nested texts dropped; its walk started at `text`. */
extern void func_020a94a4(void *walker);
extern void func_020a9354(void *walker, int text);
/* The colour a colour tag's value stands for: 9 is 3, any other the value plus one. */
extern unsigned char func_02068bc8(int colour);

typedef void *LabelBoxDestruct(void *box);
typedef int LabelBoxMeasure(void *box);
typedef void *TextBufferFunction(void *text);

static uintptr_t label_box_slot(const LabelBox *box, int slot)
{
    return (uintptr_t) box->base.vtable[slot];
}

/* The box's text walked by its walker (data_021f44dc when it has none) for `mode`. */
static void label_box_walk(LabelBox *box, int mode)
{
    TextWalker *walker = box->walker;
    if (walker == NULL) {
        walker = &data_021f44dc.walker;
    }
    box->mode = mode;
    TextWalker_SetHandler(walker, box);
    func_020a94a4(walker);
    func_020a9354(walker, (int) (uintptr_t) box->base.text);
    TextWalker_RunTo(walker, (int) box->base.unk_14);
    TextWalker_ClearHandler(walker);
    box->mode = LABEL_BOX_IDLE;
}

/* func_020a8db8 (vtable slot 3): the width of the box's text, in pixels. */
int LabelBox_Measure(LabelBox *box)
{
    label_box_walk(box, LABEL_BOX_MEASURE);
    return (int) box->base.pen;
}
CLEAN_AS(func_020a8db8, LabelBox_Measure)

/* func_020a8e04 (vtable slot 2): a strip of the box's text drawn. */
void LabelBox_Draw(LabelBox *box)
{
    label_box_walk(box, LABEL_BOX_DRAW);
}
CLEAN_AS(func_020a8e04, LabelBox_Draw)

/* func_020a8e4c: while drawing, a colour tag at `position` sets the text's colour. */
void LabelBox_OnTag(LabelBox *box, int position)
{
    if (box->mode != LABEL_BOX_DRAW) {
        return;
    }
    MessageTag tag;
    MessageTag_Construct(&tag);
    MessageTag_Read(&tag, position);
    if (tag.group == LABEL_BOX_GROUP_FORMAT && tag.kind == LABEL_BOX_KIND_COLOUR) {
        box->base.color = func_02068bc8(MessageTag_Colour(&tag));
    }
}
CLEAN_AS(func_020a8e4c, LabelBox_OnTag)

/* func_020a8e8c */
void LabelBox_OnCharacter(LabelBox *box, int character)
{
    if (box->mode == LABEL_BOX_DRAW) {
        TextDraw_DrawChar(&box->base, character);
    } else if (box->mode == LABEL_BOX_MEASURE) {
        TextDraw_MeasureChar(&box->base, character);
    }
}
CLEAN_AS(func_020a8e8c, LabelBox_OnCharacter)

/* func_020a8eac */
void LabelBox_OnEnd(LabelBox *box)
{
    if (box->mode == LABEL_BOX_DRAW) {
        TextDraw_UploadStrip(&box->base);
    } else if (box->mode == LABEL_BOX_MEASURE) {
        TextDraw_EndMeasureStrip();
    }
}
CLEAN_AS(func_020a8eac, LabelBox_OnEnd)

/* func_020a8ecc */
void LabelBox_OnText(LabelBox *box)
{
    if (box->mode == LABEL_BOX_DRAW) {
        TextDraw_BeginStrip(&box->base);
    } else if (box->mode == LABEL_BOX_MEASURE) {
        TextDraw_BeginMeasure(&box->base);
    }
}
CLEAN_AS(func_020a8ecc, LabelBox_OnText)

/* func_020a8eec: the walker the box's text is walked with (0 for the default). */
void LabelBox_SetWalker(LabelBox *box, u32 walker)
{
    box->walker = (TextWalker *) (uintptr_t) walker;
}
CLEAN_AS(func_020a8eec, LabelBox_SetWalker)

/* func_020a8ef4 (vtable slot 1) */
void *LabelBox_Delete(LabelBox *box)
{
    box->base.vtable = data_020e3dac;
    TextBoxBase_Destruct((unsigned int *) box);
    Heap_OperatorDeleteB(box);
    return box;
}
CLEAN_AS(func_020a8ef4, LabelBox_Delete)

/* func_020a8f14 (vtable slot 0) */
void *LabelBox_Destruct(void *box)
{
    ((LabelBox *) box)->base.vtable = data_020e3dac;
    TextBoxBase_Destruct(box);
    return box;
}
CLEAN_AS(func_020a8f14, LabelBox_Destruct)

/* func_020a8f2c: a box drawing into RAM at `ram`. */
LabelBox *LabelBox_Construct(LabelBox *box, int ram, int cells, int rows)
{
    TextBoxBase_Construct((TextBoxBase *) box, ram, cells, rows);
    box->base.vtable = data_020e3dac;
    box->mode = LABEL_BOX_IDLE;
    box->walker = NULL;
    return box;
}
CLEAN_AS(func_020a8f2c, LabelBox_Construct)

/* func_020a8f50: a box drawing into VRAM tiles from `first_tile`. */
LabelBox *LabelBox_ConstructInVram(LabelBox *box, unsigned int first_tile, unsigned int cells, unsigned int rows)
{
    TextBoxBase_ConstructInVram((TextBoxBase *) box, first_tile, cells, rows);
    box->base.vtable = data_020e3dac;
    box->mode = LABEL_BOX_IDLE;
    box->walker = NULL;
    return box;
}
CLEAN_AS(func_020a8f50, LabelBox_ConstructInVram)

/* func_020a8f74: the width of a text's characters, in pixels. */
int LabelBox_TextWidth(TextBase *text)
{
    void *chars = ((TextBufferFunction *) (uintptr_t) text->vtable->buffer)(text);
    return LabelBox_CharsWidth((int) (uintptr_t) chars);
}
CLEAN_AS(func_020a8f74, LabelBox_TextWidth)

/* func_020a8f88: the width of the characters at `chars`, in pixels, measured with a box of
 * its own (0 when none could be allocated). */
int LabelBox_CharsWidth(int chars)
{
    int width = 0;
    LabelBox *box = LabelBox_NewInVram(LABEL_BOX_MEASURE_TILE, LABEL_BOX_MEASURE_CELLS, LABEL_BOX_MEASURE_ROWS);
    if (box != NULL) {
        box->base.text = (const char *) (uintptr_t) chars;
        width = ((LabelBoxMeasure *) label_box_slot(box, LABEL_BOX_SLOT_MEASURE))(box);
    }
    LabelBox_Free(box);
    return width;
}
CLEAN_AS(func_020a8f88, LabelBox_CharsWidth)

/* func_020a8fb8: the box taken from the list, destructed and freed (nothing for NULL). */
void LabelBox_Free(LabelBox *box)
{
    if (box != NULL) {
        NNS_FndRemoveListObject(data_021c81bc, box);
        ((LabelBoxDestruct *) label_box_slot(box, LABEL_BOX_SLOT_DESTRUCT))(box);
        Heap_Free(data_021c8194, box);
    }
}
CLEAN_AS(func_020a8fb8, LabelBox_Free)

/* func_020a8fe8: a box drawing into RAM, allocated and put in the list; NULL when the heap
 * is full. */
LabelBox *LabelBox_New(int ram, int cells, int rows)
{
    LabelBox *box = Heap_Alloc(data_021c8194, sizeof(LabelBox));
    if (box != NULL) {
        LabelBox_Construct(box, ram, cells, rows);
        NNS_FndAppendListObject(data_021c81bc, box);
    }
    return box;
}
CLEAN_AS(func_020a8fe8, LabelBox_New)

/* func_020a9034: a box drawing into VRAM tiles, allocated and put in the list; NULL when the
 * heap is full. */
LabelBox *LabelBox_NewInVram(int first_tile, int cells, int rows)
{
    LabelBox *box = Heap_Alloc(data_021c8194, sizeof(LabelBox));
    if (box != NULL) {
        LabelBox_ConstructInVram(box, (unsigned int) first_tile, (unsigned int) cells, (unsigned int) rows);
        NNS_FndAppendListObject(data_021c81bc, box);
    }
    return box;
}
CLEAN_AS(func_020a9034, LabelBox_NewInVram)
