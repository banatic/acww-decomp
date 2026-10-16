/* The walkers' base class (message_walker.h). */
#include "message_walker.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "text_walker.h" /* TextWalker_Run */

extern const u8 data_020e3e68[]; /* the walkers' base class's vtable */

/* The walkers' base destructor. */
extern void *func_020a941c(void *walker);

/* func_020a794c (slot 0): the destructor: its vtable, then the base destructor. */
MessageWalker *MessageWalker_Destruct(MessageWalker *walker)
{
    walker->vtable = data_020e3e68;
    func_020a941c(walker);
    return walker;
}
CLEAN_AS(func_020a794c, MessageWalker_Destruct)

/* func_020a7964 (slot 1): the walker destroyed (as MessageWalker_Destruct) and freed. */
MessageWalker *MessageWalker_Delete(MessageWalker *walker)
{
    walker->vtable = data_020e3e68;
    func_020a941c(walker);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020a7964, MessageWalker_Delete)

/* ---- The class data_020e3e68 derives from */

static_assert(sizeof(MessageWalkerStack) == sizeof(((MessageWalker *) 0)->stack), "walker stack");
static_assert(sizeof(MessageWalkRun) == 0x0c, "walk run");

/* The character that starts a tag, the byte of a tag that gives its size, a newline. */
#define MESSAGE_WALKER_TAG_START 0x1a
#define MESSAGE_WALKER_TAG_SIZE_BYTE 2
#define MESSAGE_WALKER_NEWLINE 0x0a

/* The vtable slots called here. */
#define MESSAGE_WALKER_SLOT_ON_TEXT 2
#define MESSAGE_WALKER_SLOT_ON_END 3
#define MESSAGE_WALKER_SLOT_ON_CHARACTER 4
#define MESSAGE_WALKER_SLOT_ON_TAG 5

extern const u8 data_020e3e24[]; /* the class's vtable */

/* The stack's top position, and its top dropped (when it has one). */
extern u32 *func_020a9cc0(MessageWalkerStack *stack);
extern void func_020a9ccc(MessageWalkerStack *stack);

typedef void MessageWalkerSlot(MessageWalker *walker);
typedef void MessageWalkerSlotArg(MessageWalker *walker, int value);

/* The address of a walker's vtable slot. */
static uintptr_t message_walker_slot(const MessageWalker *walker, int slot)
{
    return (uintptr_t) ((const u32 *) walker->vtable)[slot];
}

static MessageWalkerStack *message_walker_stack(MessageWalker *walker)
{
    return (MessageWalkerStack *) (void *) walker->stack;
}

/* func_020a9314 (slot 6 of data_020e3e68): go on. */
int MessageWalker_WantsMoreDefault(void)
{
    return 1;
}
CLEAN_AS(func_020a9314, MessageWalker_WantsMoreDefault)

/* func_020a9318: back from a nested text, to the position on top of the stack.
 * REQUIRES: a nested text was entered (the stack is not empty); its callers check. */
void MessageWalker_Return(MessageWalker *walker)
{
    walker->position = *func_020a9cc0(message_walker_stack(walker));
    func_020a9ccc(message_walker_stack(walker));
}
CLEAN_AS(func_020a9318, MessageWalker_Return)

/* func_020a9334: the text at `text` walked from here on, the walk coming back here at its end
 * (nothing for 0). QUIRK: with the stack full the position is not kept, so the walk goes on
 * past the nested text's end to an older position. */
void MessageWalker_Enter(MessageWalker *walker, int text)
{
    if (text != 0) {
        MessageWalkerStack_Push(message_walker_stack(walker), &walker->position);
        walker->position = (u32) text;
    }
}
CLEAN_AS(func_020a9334, MessageWalker_Enter)

/* func_020a9354: the walk started at `text`; slot 2 is told. */
void MessageWalker_Start(MessageWalker *walker, int text)
{
    walker->position = (u32) text;
    ((MessageWalkerSlot *) message_walker_slot(walker, MESSAGE_WALKER_SLOT_ON_TEXT))(walker);
}
CLEAN_AS(func_020a9354, MessageWalker_Start)

/* func_020a9368: one step; 0 once the outermost text ended (slot 3 was called), else 1. With
 * `stop_at_newline` a newline ends a text like its 0. The characters are read a byte at a
 * time, so a text may sit at any address. */
int MessageWalker_Step(MessageWalker *walker, int stop_at_newline)
{
    const u8 *at = (const u8 *) (uintptr_t) walker->position;
    int character = at[0] | (at[1] << 8);

    if (character == 0 || (stop_at_newline != 0 && character == MESSAGE_WALKER_NEWLINE)) {
        if (MessageWalkerStack_IsEmpty(message_walker_stack(walker))) {
            ((MessageWalkerSlot *) message_walker_slot(walker, MESSAGE_WALKER_SLOT_ON_END))(walker);
            return 0;
        }
        MessageWalker_Return(walker);
    } else if (character == MESSAGE_WALKER_TAG_START) {
        MessageWalker_PassTag(walker);
    } else {
        walker->position += 2;
        ((MessageWalkerSlotArg *) message_walker_slot(walker, MESSAGE_WALKER_SLOT_ON_CHARACTER))(walker, character);
    }
    return 1;
}
CLEAN_AS(func_020a9368, MessageWalker_Step)

/* func_020a93dc: the position taken back by the size of `tag` (the tag just passed). */
void MessageWalker_BackOverTag(MessageWalker *walker, const u8 *tag)
{
    walker->position -= tag[MESSAGE_WALKER_TAG_SIZE_BYTE];
}
CLEAN_AS(func_020a93dc, MessageWalker_BackOverTag)

/* func_020a93e8: the position moved on by `bytes`, unless the text has ended (0). */
void MessageWalker_Skip(MessageWalker *walker, int bytes)
{
    if (walker->position != 0) {
        walker->position += (u32) bytes;
    }
}
CLEAN_AS(func_020a93e8, MessageWalker_Skip)

/* func_020a93f4: the walk past the tag at the position; slot 5 is handed the tag's address. */
void MessageWalker_PassTag(MessageWalker *walker)
{
    u32 tag = walker->position;
    walker->position = tag + ((const u8 *) (uintptr_t) tag)[MESSAGE_WALKER_TAG_SIZE_BYTE];
    ((MessageWalkerSlotArg *) message_walker_slot(walker, MESSAGE_WALKER_SLOT_ON_TAG))(walker, (int) tag);
}
CLEAN_AS(func_020a93f4, MessageWalker_PassTag)

/* func_020a940c (slot 5): a tag; nothing. */
void MessageWalker_OnTag(void) {}
CLEAN_AS(func_020a940c, MessageWalker_OnTag)

/* func_020a9410 (slot 4): a character; nothing. */
void MessageWalker_OnCharacter(void) {}
CLEAN_AS(func_020a9410, MessageWalker_OnCharacter)

/* func_020a9414 (slot 3): the end; nothing. */
void MessageWalker_OnEnd(void) {}
CLEAN_AS(func_020a9414, MessageWalker_OnEnd)

/* func_020a9418 (slot 2): the text set; nothing. */
void MessageWalker_OnText(void) {}
CLEAN_AS(func_020a9418, MessageWalker_OnText)

/* func_020a941c: the destructor the derived classes call: the walk reset. */
void *MessageWalker_BaseDestruct(void *walker)
{
    MessageWalker *self = walker;
    self->vtable = data_020e3e24;
    MessageWalker_Reset(self);
    MessageWalkerStack_Destruct(self->stack);
    return walker;
}
CLEAN_AS(func_020a941c, MessageWalker_BaseDestruct)

/* func_020a943c (slot 1): the walker destroyed (as MessageWalker_BaseDestruct) and freed. */
MessageWalker *MessageWalker_BaseDelete(MessageWalker *walker)
{
    walker->vtable = data_020e3e24;
    MessageWalker_Reset(walker);
    MessageWalkerStack_Destruct(walker->stack);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020a943c, MessageWalker_BaseDelete)

/* func_020a9464 (slot 0): the destructor, the same as MessageWalker_BaseDestruct. */
MessageWalker *MessageWalker_BaseDestructSlot(MessageWalker *walker)
{
    walker->vtable = data_020e3e24;
    MessageWalker_Reset(walker);
    MessageWalkerStack_Destruct(walker->stack);
    return walker;
}
CLEAN_AS(func_020a9464, MessageWalker_BaseDestructSlot)

/* func_020a9484: a walker with no text, of this class (vtable data_020e3e24); the derived
 * classes then put their own vtable in. */
MessageWalker *MessageWalker_Construct(MessageWalker *walker)
{
    walker->vtable = data_020e3e24;
    walker->position = 0;
    MessageWalkerStack_Construct(message_walker_stack(walker));
    return walker;
}
CLEAN_AS(func_020a9484, MessageWalker_Construct)

/* func_020a94a4: no text, and the nested texts dropped one by one. */
void MessageWalker_Reset(MessageWalker *walker)
{
    walker->position = 0;
    while (!MessageWalkerStack_IsEmpty(message_walker_stack(walker))) {
        func_020a9ccc(message_walker_stack(walker));
    }
}
CLEAN_AS(func_020a94a4, MessageWalker_Reset)

/* ---- The walk run a little at a time */

/* func_020a94c8: the walk started at `text`. */
void MessageWalkRun_Start(MessageWalkRun *run, int text)
{
    run->text = text;
    run->stopped_at = text;
    MessageWalker_Start(run->walker, text);
}
CLEAN_AS(func_020a94c8, MessageWalkRun_Start)

/* func_020a94d8: the walk run on until the walker's slot 6 says to stop (1) or the text ends
 * (0, and the run is over); 0 when there is no walk. */
int MessageWalkRun_Step(MessageWalkRun *run)
{
    if (run->text == 0) {
        return 0;
    }
    run->stopped_at = TextWalker_Run(run->walker, 0);
    if (run->stopped_at != 0) {
        return 1;
    }
    run->text = 0;
    return 0;
}
CLEAN_AS(func_020a94d8, MessageWalkRun_Step)

/* func_020a9508: the walker reset, and no walk. */
void MessageWalkRun_Reset(MessageWalkRun *run)
{
    MessageWalker_Reset(run->walker);
    run->text = 0;
    run->stopped_at = 0;
}
CLEAN_AS(func_020a9508, MessageWalkRun_Reset)

/* func_020a9520: the destructor; nothing. */
void MessageWalkRun_Destruct(void *run)
{
    (void) run;
}
CLEAN_AS(func_020a9520, MessageWalkRun_Destruct)

/* func_020a9524: a run of `walker`, with no walk. */
void MessageWalkRun_Construct(MessageWalkRun *run, MessageWalker *walker)
{
    run->walker = walker;
    run->text = 0;
    run->stopped_at = 0;
}
CLEAN_AS(func_020a9524, MessageWalkRun_Construct)

/* ---- The stack of positions */

/* func_020a9c84: empty, its positions 0. */
void MessageWalkerStack_Construct(MessageWalkerStack *stack)
{
    stack->count = 0;
    for (int i = 0; i < MESSAGE_WALKER_STACK_DEPTH; i++) {
        stack->positions[i] = 0;
    }
}
CLEAN_AS(func_020a9c84, MessageWalkerStack_Construct)

/* func_020a9c98: the destructor; nothing. */
void MessageWalkerStack_Destruct(void *stack)
{
    (void) stack;
}
CLEAN_AS(func_020a9c98, MessageWalkerStack_Destruct)

/* func_020a9c9c: 1 when it holds no position. */
int MessageWalkerStack_IsEmpty(void *stack)
{
    return ((MessageWalkerStack *) stack)->count == 0;
}
CLEAN_AS(func_020a9c9c, MessageWalkerStack_IsEmpty)

/* func_020a9cac: `*position` pushed; nothing when the stack is full. */
void MessageWalkerStack_Push(MessageWalkerStack *stack, const u32 *position)
{
    u32 count = stack->count;
    if (count >= MESSAGE_WALKER_STACK_DEPTH) {
        return;
    }
    stack->count = count + 1;
    stack->positions[count] = *position;
}
CLEAN_AS(func_020a9cac, MessageWalkerStack_Push)
