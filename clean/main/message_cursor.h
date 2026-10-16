/* The walkers of 16-bit message texts that the forbidden-word filter uses (message_reader.h).
 *
 * A walker (class data_020e3e68, func_020a9484 builds it) steps through a text from a position
 * (func_020a9354 sets it, func_020a92d8 runs it) and calls its own virtual functions: slot 2
 * when its text is set, 3 when it reaches the end, 4 for each character, 5 for each tag, and
 * slot 6 before each step to ask whether to go on.
 *
 * - The line walker (class data_020e5230) hands the characters of one line of the forbidden
 *   words one at a time: asked for one (`want` 1), it stores the next in `character`.
 * - The cursor (class data_020e5254) walks the text being filtered and writes it out again:
 *   it reads a character (MessageCursor_Read), copies one (MessageCursor_Copy) or replaces a
 *   run of characters with ideographic spaces (MessageCursor_Mask); the last two move its
 *   mark on, where MessageCursor_Rewind takes it back. Newlines are copied and never count. */
#ifndef CLEAN_MAIN_MESSAGE_CURSOR_H
#define CLEAN_MAIN_MESSAGE_CURSOR_H

#include "types.h"

/* The walkers' base (0x24 bytes). */
typedef struct MessageWalker {
    const void *vtable; /* 0x00 */
    u32 position;       /* 0x04: the address of the next character, 0 at the end */
    u8 stack[0x1c];     /* 0x08: the positions to come back to after a nested text */
} MessageWalker;

/* The line walker (0x30 bytes). */
typedef struct MessageLineWalker {
    MessageWalker base;
    const char *line; /* 0x24: the line walked (set by its owner) */
    s32 want;         /* 0x28: how many characters are still to be handed */
    s32 character;    /* 0x2c: the last character handed */
} MessageLineWalker;

/* What a cursor's walk does with the characters it meets. */
enum MessageCursorMode {
    MESSAGE_CURSOR_IDLE = 0,
    MESSAGE_CURSOR_COPY = 1, /* copied to the output */
    MESSAGE_CURSOR_MASK = 2, /* written to the output as ideographic spaces */
    MESSAGE_CURSOR_READ = 3  /* only looked at */
};

/* The cursor (0x40 bytes). */
typedef struct MessageCursor {
    MessageWalker base;
    s32 mode;           /* 0x24: enum MessageCursorMode */
    const void *source; /* 0x28: the text walked (an object whose slot 3 gives its characters) */
    void *output;       /* 0x2c: the text written */
    u32 mark;           /* 0x30: where the walk starts again */
    u8 done;            /* 0x34: set when a copy or mask reached the end */
    u8 unk_35[3];
    s32 character; /* 0x38: the last character met */
    s32 count;     /* 0x3c: the characters still to walk */
} MessageCursor;

int MessageLineWalker_WantsMore(void *walker);
void MessageLineWalker_OnTag(void);
void MessageLineWalker_OnCharacter(MessageLineWalker *walker, int character);
void MessageLineWalker_OnEnd(void);
void MessageLineWalker_OnText(void);
MessageLineWalker *MessageLineWalker_Delete(MessageLineWalker *walker);
void *MessageLineWalker_Destruct(void *walker);
MessageLineWalker *MessageLineWalker_Construct(MessageLineWalker *walker);

void MessageCursor_Write(MessageCursor *cursor, int character);
int MessageCursor_WantsMore(void *cursor);
void MessageCursor_OnTag(void);
void MessageCursor_OnCharacter(MessageCursor *cursor, int character);
void MessageCursor_OnEnd(void *cursor);
void MessageCursor_OnText(void);
int MessageCursor_Read(MessageCursor *cursor);
void MessageCursor_Copy(MessageCursor *cursor);
void MessageCursor_Mask(MessageCursor *cursor, int count);
void MessageCursor_Rewind(void *cursor);
void MessageCursor_SetOutput(MessageCursor *cursor, int output);
void MessageCursor_SetSource(MessageCursor *cursor, const void *source);
void MessageCursor_Reset(void *cursor);
void *MessageCursor_Delete(void *cursor);
void *MessageCursor_Destruct(void *cursor);
MessageCursor *MessageCursor_Construct(MessageCursor *cursor);

#endif
