/* The walkers' base class (data_020e3e68; MessageWalker in message_cursor.h): its destructor
 * and its deleting destructor. */
#ifndef CLEAN_MAIN_MESSAGE_WALKER_H
#define CLEAN_MAIN_MESSAGE_WALKER_H

#include "message_cursor.h"

MessageWalker *MessageWalker_Destruct(MessageWalker *walker);
MessageWalker *MessageWalker_Delete(MessageWalker *walker);

/* The class data_020e3e68 derives from (vtable data_020e3e24, built by
 * MessageWalker_Construct): a walk through a 16-bit message text, one step at a time
 * (MessageWalker_Step).
 *
 * A step reads the character at `position`. A 0 ends the text, and so does a newline when the
 * step is told to (TextWalker_RunTo): at the end of a nested text the walk comes back to where
 * it entered it, at the end of the outermost one slot 3 is called and the walk stops. A 0x1a
 * starts a tag, whose byte 2 gives its size in bytes: the walk goes past it and slot 5 is
 * handed its address. Any other character is handed to slot 4.
 *
 * Its vtable: the destructor, the deleting destructor, then slots 2 (the text was set), 3 (the
 * end), 4 (a character) and 5 (a tag), which do nothing here. data_020e3e68 adds a slot 6
 * that asks whether to go on (MessageWalker_WantsMoreDefault: always).
 *
 * The nested texts entered (MessageWalker_Enter) are kept on a stack of six positions. */

/* The stack of positions to come back to (MessageWalker.stack). */
#define MESSAGE_WALKER_STACK_DEPTH 6
typedef struct MessageWalkerStack {
    u32 positions[MESSAGE_WALKER_STACK_DEPTH]; /* 0x00 */
    u32 count;                                 /* 0x18 */
} MessageWalkerStack;

/* A walk run a little at a time (a talk's at 0x149c): MessageWalkRun_Step runs the walker
 * until its slot 6 says to stop, and again on the next call, until the text ends. */
typedef struct MessageWalkRun {
    MessageWalker *walker; /* 0x00 */
    s32 text;              /* 0x04: the text walked, 0 once it ended */
    s32 stopped_at;        /* 0x08: where the last run stopped (0: the text ended) */
} MessageWalkRun;

int MessageWalker_WantsMoreDefault(void);
void MessageWalker_Return(MessageWalker *walker);
void MessageWalker_Enter(MessageWalker *walker, int text);
void MessageWalker_Start(MessageWalker *walker, int text);
int MessageWalker_Step(MessageWalker *walker, int stop_at_newline);
void MessageWalker_BackOverTag(MessageWalker *walker, const u8 *tag);
void MessageWalker_Skip(MessageWalker *walker, int bytes);
void MessageWalker_PassTag(MessageWalker *walker);
void MessageWalker_OnTag(void);
void MessageWalker_OnCharacter(void);
void MessageWalker_OnEnd(void);
void MessageWalker_OnText(void);
void *MessageWalker_BaseDestruct(void *walker);
MessageWalker *MessageWalker_BaseDelete(MessageWalker *walker);
MessageWalker *MessageWalker_BaseDestructSlot(MessageWalker *walker);
MessageWalker *MessageWalker_Construct(MessageWalker *walker);
void MessageWalker_Reset(MessageWalker *walker);

void MessageWalkRun_Start(MessageWalkRun *run, int text);
int MessageWalkRun_Step(MessageWalkRun *run);
void MessageWalkRun_Reset(MessageWalkRun *run);
void MessageWalkRun_Destruct(void *run);
void MessageWalkRun_Construct(MessageWalkRun *run, MessageWalker *walker);

void MessageWalkerStack_Construct(MessageWalkerStack *stack);
void MessageWalkerStack_Destruct(void *stack);
int MessageWalkerStack_IsEmpty(void *stack);
void MessageWalkerStack_Push(MessageWalkerStack *stack, const u32 *position);

#endif
