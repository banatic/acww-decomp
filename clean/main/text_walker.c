/* The text walkers, the text copier and the box walker (text_walker.h). */
#include "text_walker.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "label_box.h"
#include "message_tag.h"
#include "text_codes.h"
#include "message_walker.h"
#include "talk_object.h"

static_assert(offsetof(TextWalker, handler) == 0x24, "text walker handler");
static_assert(offsetof(TextWalker, stop_at_newline) == 0x28, "text walker flag");
static_assert(sizeof(TextWalker) == 0x2c, "text walker");
static_assert(offsetof(TextCopier, target) == 0x2c, "copier target");
static_assert(offsetof(TextCopier, fitted) == 0x38, "copier result");
static_assert(sizeof(TextCopier) == 0x3c, "copier");
static_assert(offsetof(BoxWalker, return_at) == 0x2c, "box walker return");
static_assert(sizeof(BoxWalker) == 0x30, "box walker");

/* The walkers' vtable slots called here. */
#define TEXT_WALKER_SLOT_ON_END 3
#define TEXT_WALKER_SLOT_WANTS_MORE 6

/* The tags the box walker acts on (group, and kind within it). */
#define TEXT_WALKER_GROUP_CODE 0
#define TEXT_WALKER_GROUP_TEXTS 2
#define TEXT_WALKER_GROUP_FORMAT 0xff
#define TEXT_WALKER_KIND_REPLACE 2

extern const u8 data_020e3de4[]; /* the text walker's vtable */
extern const u8 data_020e3e04[]; /* the text copier's */
extern const u8 data_020e3dc4[]; /* the box walker's */

typedef void TextWalkerOnEnd(void *walker);
typedef int TextWalkerWantsMore(void *walker);

/* The address of a walker's vtable slot. */
static uintptr_t text_walker_slot(const MessageWalker *walker, int slot)
{
    return (uintptr_t) ((const u32 *) walker->vtable)[slot];
}

/* ---- The text copier */

/* func_020a8cd4 (vtable slot 3): at the end of the walk, the bytes walked set or appended
 * into the target. */
void TextCopier_OnEnd(TextCopier *copier)
{
    if (copier->target == NULL) {
        return;
    }
    if (copier->mode == TEXT_COPIER_SET) {
        copier->fitted = TextBase_SetRange(copier->target, copier->source, copier->walker.base.position);
    } else if (copier->mode == TEXT_COPIER_APPEND) {
        copier->fitted = (u8) TextBase_AppendRange(copier->target, (int) copier->source, (int) copier->walker.base.position);
    }
}
CLEAN_AS(func_020a8cd4, TextCopier_OnEnd)

/* func_020a8d08 */
unsigned char TextCopier_Fitted(TextCopier *copier)
{
    return copier->fitted;
}
CLEAN_AS(func_020a8d08, TextCopier_Fitted)

/* func_020a8d10 */
void TextCopier_Reset(TextCopier *copier)
{
    copier->target = NULL;
    copier->source = 0;
    copier->mode = 0;
    copier->fitted = 0;
}
CLEAN_AS(func_020a8d10, TextCopier_Reset)

/* func_020a8d20: a copy of the message text at `source` into `target` set up, and its walk
 * started (the caller runs it). */
void TextCopier_Start(TextCopier *copier, TextBase *target, int source, int mode, unsigned char stop_at_newline)
{
    copier->target = target;
    copier->source = (u32) source;
    copier->mode = mode;
    copier->fitted = 0;
    if (stop_at_newline) {
        TextWalker_StopAtNewlineOn(&copier->walker);
    } else {
        TextWalker_StopAtNewlineOff(&copier->walker);
    }
    MessageWalker_Start((MessageWalker *) copier, source);
}
CLEAN_AS(func_020a8d20, TextCopier_Start)

/* func_020a8d58 (vtable slot 1) */
void *TextCopier_Delete(TextCopier *copier)
{
    copier->walker.base.vtable = data_020e3e04;
    TextWalker_Destruct(copier);
    Heap_OperatorDeleteB(copier);
    return copier;
}
CLEAN_AS(func_020a8d58, TextCopier_Delete)

/* func_020a8d78 (vtable slot 0) */
void *TextCopier_Destruct(void *copier)
{
    ((TextCopier *) copier)->walker.base.vtable = data_020e3e04;
    TextWalker_Destruct(copier);
    return copier;
}
CLEAN_AS(func_020a8d78, TextCopier_Destruct)

/* func_020a8d90: a copier stopping at newlines, with nothing to do. */
TextCopier *TextCopier_Construct(TextCopier *copier)
{
    TextWalker_Construct(&copier->walker, 1);
    copier->walker.base.vtable = data_020e3e04;
    copier->target = NULL;
    copier->source = 0;
    copier->mode = 0;
    copier->fitted = 0;
    return copier;
}
CLEAN_AS(func_020a8d90, TextCopier_Construct)

/* ---- The box walker */

/* The address of the fixed text a 0/`kind` tag stands for, or 0. */
static int box_walker_code_text(int kind)
{
    switch (kind) {
        case 0:
            return TextCodes_Asterisk();
        case 1:
            return TextCodes_Slash();
        case 6:
            return TextCodes_Ampersand();
        case 7:
            return TextCodes_Percent();
        case 8:
            return TextCodes_LeftBrace();
        case 9:
            return TextCodes_LeftParen();
        case 10:
            return TextCodes_RightParen();
        default:
            return 0;
    }
}

/* func_020a9080 (vtable slot 5): the tag at `position` (the walk is already past it).
 * - 2/x: the texts it carries skipped;
 * - 0xff/2: when func_02068114 says 0, the number of characters its first parameter byte
 *   gives are skipped and the rest of its parameters walked in their place. QUIRK: the walk
 *   comes back once the position is that text's start plus its size with the lowest bit
 *   flipped: a whole number of characters when the size is odd (a padding byte), else a
 *   position never reached, so the walk comes back only at the nested text's 0;
 * - 0/x: the fixed text of TextCodes standing for it walked in its place (none for the kinds
 *   2-5 and above 10).
 * Then the box is handed the tag. */
void BoxWalker_OnTag(BoxWalker *walker, int position)
{
    MessageTag tag;

    MessageTag_Construct(&tag);
    MessageTag_Read(&tag, position);
    if (tag.group == TEXT_WALKER_GROUP_TEXTS) {
        MessageWalker_Skip((MessageWalker *) walker, (int) MessageTag_TextsSize(&tag));
    } else if (tag.group == TEXT_WALKER_GROUP_FORMAT) {
        if (tag.kind == TEXT_WALKER_KIND_REPLACE) {
            u32 skip;
            s32 end;
            const s8 *rest;
            MessageTag_SplitParams(&tag, &skip, &end, &rest);
            if (TalkObject_OptionFlagOff() == 0) {
                u32 text = (u32) (uintptr_t) rest;
                MessageWalker_Skip((MessageWalker *) walker, (int) (skip * 2));
                MessageWalker_Enter((MessageWalker *) walker, (int) text);
                walker->return_at = text + (((u32) end - text) ^ 1);
            }
        }
    } else if (tag.group == TEXT_WALKER_GROUP_CODE) {
        int text = box_walker_code_text((int) tag.kind);
        if (text != 0) {
            MessageWalker_Enter((MessageWalker *) walker, text);
        }
    }
    if (walker->walker.handler != NULL) {
        LabelBox_OnTag(walker->walker.handler, position);
    }
}
CLEAN_AS(func_020a9080, BoxWalker_OnTag)

/* func_020a9164 (vtable slot 4): the character handed to the box; at the end of a 0xff/2
 * tag's text, the walk goes back to where it was. */
void BoxWalker_OnCharacter(BoxWalker *walker, int character)
{
    if (walker->walker.handler != NULL) {
        LabelBox_OnCharacter(walker->walker.handler, character);
    }
    if (walker->return_at != 0 && walker->walker.base.position == walker->return_at) {
        walker->return_at = 0;
        MessageWalker_Return((MessageWalker *) walker);
    }
}
CLEAN_AS(func_020a9164, BoxWalker_OnCharacter)

/* func_020a9190 (vtable slot 3) */
void BoxWalker_OnEnd(void *walker)
{
    void *handler = ((BoxWalker *) walker)->walker.handler;
    if (handler != NULL) {
        LabelBox_OnEnd(handler);
    }
}
CLEAN_AS(func_020a9190, BoxWalker_OnEnd)

/* func_020a91a4 (vtable slot 2) */
void BoxWalker_OnText(void *walker)
{
    void *handler = ((BoxWalker *) walker)->walker.handler;
    if (handler != NULL) {
        LabelBox_OnText(handler);
    }
}
CLEAN_AS(func_020a91a4, BoxWalker_OnText)

/* func_020a91b8 (vtable slot 1) */
void *BoxWalker_Delete(void *walker)
{
    ((BoxWalker *) walker)->walker.base.vtable = data_020e3dc4;
    TextWalker_Destruct(walker);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020a91b8, BoxWalker_Delete)

/* func_020a91d8 (vtable slot 0) */
void *BoxWalker_Destruct(void *walker)
{
    ((BoxWalker *) walker)->walker.base.vtable = data_020e3dc4;
    TextWalker_Destruct(walker);
    return walker;
}
CLEAN_AS(func_020a91d8, BoxWalker_Destruct)

/* func_020a91f0: a box walker stopping at newlines. */
BoxWalker *BoxWalker_Construct(BoxWalker *walker)
{
    TextWalker_Construct(&walker->walker, 1);
    walker->walker.base.vtable = data_020e3dc4;
    walker->return_at = 0;
    return walker;
}
CLEAN_AS(func_020a91f0, BoxWalker_Construct)

/* ---- The text walker */

/* func_020a9210 */
void TextWalker_StopAtNewlineOff(TextWalker *walker)
{
    walker->stop_at_newline = 0;
}
CLEAN_AS(func_020a9210, TextWalker_StopAtNewlineOff)

/* func_020a9218 */
void TextWalker_StopAtNewlineOn(TextWalker *walker)
{
    walker->stop_at_newline = 1;
}
CLEAN_AS(func_020a9218, TextWalker_StopAtNewlineOn)

/* func_020a9220 */
void TextWalker_ClearHandler(TextWalker *walker)
{
    walker->handler = NULL;
}
CLEAN_AS(func_020a9220, TextWalker_ClearHandler)

/* func_020a9228 */
void TextWalker_SetHandler(TextWalker *walker, void *handler)
{
    walker->handler = handler;
}
CLEAN_AS(func_020a9228, TextWalker_SetHandler)

/* func_020a922c: the walk run until its position is `end` (then slot 3 is called) or the text
 * ends; 0. */
int TextWalker_RunTo(TextWalker *walker, int end)
{
    for (;;) {
        if (walker->base.position == (u32) end) {
            ((TextWalkerOnEnd *) text_walker_slot(&walker->base, TEXT_WALKER_SLOT_ON_END))(walker);
            break;
        }
        if (!MessageWalker_Step((MessageWalker *) walker, walker->stop_at_newline)) {
            break;
        }
    }
    return 0;
}
CLEAN_AS(func_020a922c, TextWalker_RunTo)

/* func_020a9260: the destructor the derived classes call. */
void *TextWalker_Destruct(void *walker)
{
    ((TextWalker *) walker)->base.vtable = data_020e3de4;
    MessageWalker_BaseDestruct(walker);
    return walker;
}
CLEAN_AS(func_020a9260, TextWalker_Destruct)

/* func_020a9278 (vtable slot 1) */
void *TextWalker_Delete(void *walker)
{
    ((TextWalker *) walker)->base.vtable = data_020e3de4;
    MessageWalker_BaseDestruct(walker);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020a9278, TextWalker_Delete)

/* func_020a9298 (vtable slot 0): the destructor, the same as TextWalker_Destruct. */
TextWalker *TextWalker_DestructSlot(TextWalker *walker)
{
    walker->base.vtable = data_020e3de4;
    MessageWalker_BaseDestruct(walker);
    return walker;
}
CLEAN_AS(func_020a9298, TextWalker_DestructSlot)

/* func_020a92b0: a walker with no handler. */
TextWalker *TextWalker_Construct(TextWalker *walker, char stop_at_newline)
{
    MessageWalker_Construct((MessageWalker *) walker);
    walker->base.vtable = data_020e3de4;
    walker->handler = NULL;
    walker->stop_at_newline = (u8) stop_at_newline;
    return walker;
}
CLEAN_AS(func_020a92b0, TextWalker_Construct)

/* func_020a92d8: any walker (one with a slot 6) run until its position is `end` (then slot 3
 * is called; 0), the text ends (0), or slot 6 says to stop (the position then).
 * QUIRK: newlines never end the text here (each step is told 0). */
int TextWalker_Run(MessageWalker *walker, int end)
{
    do {
        if (walker->position == (u32) end) {
            ((TextWalkerOnEnd *) text_walker_slot(walker, TEXT_WALKER_SLOT_ON_END))(walker);
            return 0;
        }
        if (((TextWalkerWantsMore *) text_walker_slot(walker, TEXT_WALKER_SLOT_WANTS_MORE))(walker) == 0) {
            return (int) walker->position;
        }
    } while (MessageWalker_Step(walker, 0) != 0);
    return 0;
}
CLEAN_AS(func_020a92d8, TextWalker_Run)
