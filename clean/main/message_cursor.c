/* The forbidden-word filter's line walker and cursor (message_cursor.h). */
#include "message_cursor.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(MessageWalker) == 0x24, "walker");
static_assert(offsetof(MessageLineWalker, line) == 0x24, "line");
static_assert(offsetof(MessageLineWalker, character) == 0x2c, "line character");
static_assert(sizeof(MessageLineWalker) == 0x30, "line walker");
static_assert(offsetof(MessageCursor, mode) == 0x24, "mode");
static_assert(offsetof(MessageCursor, mark) == 0x30, "mark");
static_assert(offsetof(MessageCursor, done) == 0x34, "done");
static_assert(offsetof(MessageCursor, character) == 0x38, "character");
static_assert(offsetof(MessageCursor, count) == 0x3c, "count");
static_assert(sizeof(MessageCursor) == 0x40, "cursor");

/* The end of a line; it is copied as it is and does not count. */
#define MESSAGE_CURSOR_NEWLINE 10
/* What a masked character becomes: the ideographic space. */
#define MESSAGE_CURSOR_MASK_CHARACTER 0x3000

extern const u8 data_020e3e68[]; /* the walkers' base class's vtable */
extern const u8 data_020e5230[]; /* the line walker's */
extern const u8 data_020e5254[]; /* the cursor's */

/* The walkers' base: its constructor and destructor, back to the start, a text to walk, and a
 * walk up to the end or until slot 6 says to stop. */
extern void *func_020a9484(void *walker);
extern void *func_020a941c(void *walker);
extern void func_020a94a4(void *walker);
extern void func_020a9354(void *walker, int text);
extern int func_020a92d8(void *walker, int stop);
/* Clears `size` bytes; text: raw characters appended. */
extern void *func_02137550(void *dst, u32 size);
extern int func_020a89f8(void *text, const void *characters);

typedef int MessageCursorCharactersFunction(const void *object);

/* The characters of a text object, through its vtable (slot 3), as an address. */
static int message_cursor_characters(const void *object)
{
    const u32 *vtable = *(const u32 *const *) object;
    MessageCursorCharactersFunction *characters = (MessageCursorCharactersFunction *) (uintptr_t) vtable[3];
    return characters(object);
}

/* Whether the cursor copies or masks, the modes that move its mark. */
static int message_cursor_moves(const MessageCursor *cursor)
{
    return cursor->mode == MESSAGE_CURSOR_COPY || cursor->mode == MESSAGE_CURSOR_MASK;
}

/* func_020b4a64 (the line walker's slot 6): whether a character is still wanted. */
int MessageLineWalker_WantsMore(void *walker)
{
    return ((MessageLineWalker *) walker)->want > 0;
}
CLEAN_AS(func_020b4a64, MessageLineWalker_WantsMore)

/* func_020b4a74 (slot 5): tags are passed over. */
void MessageLineWalker_OnTag(void) {}
CLEAN_AS(func_020b4a74, MessageLineWalker_OnTag)

/* func_020b4a78 (slot 4): the character kept, one fewer wanted. */
void MessageLineWalker_OnCharacter(MessageLineWalker *walker, int character)
{
    walker->character = character;
    walker->want--;
}
CLEAN_AS(func_020b4a78, MessageLineWalker_OnCharacter)

/* func_020b4a84 (slot 3): nothing at the end. */
void MessageLineWalker_OnEnd(void) {}
CLEAN_AS(func_020b4a84, MessageLineWalker_OnEnd)

/* func_020b4a88 (slot 2): nothing when a text is set. */
void MessageLineWalker_OnText(void) {}
CLEAN_AS(func_020b4a88, MessageLineWalker_OnText)

/* func_020b4a8c (slot 1): the line walker destroyed (MessageLineWalker_Destruct) and freed. */
MessageLineWalker *MessageLineWalker_Delete(MessageLineWalker *walker)
{
    walker->base.vtable = data_020e5230;
    walker->base.vtable = data_020e3e68;
    func_020a941c(walker);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020b4a8c, MessageLineWalker_Delete)

/* func_020b4ab4 (slot 0): the line walker's destructor: its vtable, the base class's, then the
 * walkers' base destructor. */
void *MessageLineWalker_Destruct(void *walker)
{
    MessageWalker *self = walker;
    self->vtable = data_020e5230;
    self->vtable = data_020e3e68;
    func_020a941c(walker);
    return walker;
}
CLEAN_AS(func_020b4ab4, MessageLineWalker_Destruct)

/* func_020b4ad4: the line walker's constructor: no line, nothing wanted or handed. */
MessageLineWalker *MessageLineWalker_Construct(MessageLineWalker *walker)
{
    func_020a9484(walker);
    walker->base.vtable = data_020e3e68;
    walker->base.vtable = data_020e5230;
    walker->line = NULL;
    walker->want = 0;
    walker->character = 0;
    return walker;
}
CLEAN_AS(func_020b4ad4, MessageLineWalker_Construct)

/* func_020b4afc: the 16-bit character appended to the cursor's output. */
void MessageCursor_Write(MessageCursor *cursor, int character)
{
    u8 characters[4];

    func_02137550(characters, sizeof(characters));
    characters[0] = (u8) character;
    characters[1] = (u8) (character >> 8);
    func_020a89f8(cursor->output, characters);
}
CLEAN_AS(func_020b4afc, MessageCursor_Write)

/* func_020b4b24 (the cursor's slot 6): whether characters are left to walk; when a copy or a
 * mask has walked them all, the mark moves to where the walk stands. */
int MessageCursor_WantsMore(void *cursor)
{
    MessageCursor *self = cursor;
    int more = self->count > 0;

    if (message_cursor_moves(self) && !more) {
        self->mark = self->base.position;
    }
    return more;
}
CLEAN_AS(func_020b4b24, MessageCursor_WantsMore)

/* func_020b4b44 (slot 5): tags are passed over. */
void MessageCursor_OnTag(void) {}
CLEAN_AS(func_020b4b44, MessageCursor_OnTag)

/* func_020b4b48 (slot 4): the character kept, and copied or masked as the mode says; every
 * character but a newline counts. A masked newline is still written as a newline. */
void MessageCursor_OnCharacter(MessageCursor *cursor, int character)
{
    cursor->character = character;
    switch (cursor->mode) {
        case MESSAGE_CURSOR_COPY:
            MessageCursor_Write(cursor, character);
            if (character != MESSAGE_CURSOR_NEWLINE) {
                cursor->count--;
            }
            break;
        case MESSAGE_CURSOR_MASK:
            if (character == MESSAGE_CURSOR_NEWLINE) {
                MessageCursor_Write(cursor, MESSAGE_CURSOR_NEWLINE);
            } else {
                MessageCursor_Write(cursor, MESSAGE_CURSOR_MASK_CHARACTER);
                cursor->count--;
            }
            break;
        case MESSAGE_CURSOR_READ:
            if (character != MESSAGE_CURSOR_NEWLINE) {
                cursor->count--;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020b4b48, MessageCursor_OnCharacter)

/* func_020b4ba0 (slot 3): a copy or a mask that reaches the end marks the cursor done. */
void MessageCursor_OnEnd(void *cursor)
{
    MessageCursor *self = cursor;
    if (message_cursor_moves(self)) {
        self->done = 1;
    }
}
CLEAN_AS(func_020b4ba0, MessageCursor_OnEnd)

/* func_020b4bb0 (slot 2): nothing when a text is set. */
void MessageCursor_OnText(void) {}
CLEAN_AS(func_020b4bb0, MessageCursor_OnText)

/* func_020b4bb4: the next character from where the walk stands (0 at the end); the mark does
 * not move. */
int MessageCursor_Read(MessageCursor *cursor)
{
    cursor->mode = MESSAGE_CURSOR_READ;
    cursor->count = 1;
    cursor->character = 0;
    func_020a92d8(cursor, 0);
    cursor->mode = MESSAGE_CURSOR_IDLE;
    return cursor->character;
}
CLEAN_AS(func_020b4bb4, MessageCursor_Read)

/* func_020b4bd4: one character copied to the output (with any newlines before it). */
void MessageCursor_Copy(MessageCursor *cursor)
{
    cursor->mode = MESSAGE_CURSOR_COPY;
    cursor->count = 1;
    func_020a92d8(cursor, 0);
    cursor->mode = MESSAGE_CURSOR_IDLE;
}
CLEAN_AS(func_020b4bd4, MessageCursor_Copy)

/* func_020b4bf0: `count` characters written to the output as ideographic spaces. */
void MessageCursor_Mask(MessageCursor *cursor, int count)
{
    cursor->mode = MESSAGE_CURSOR_MASK;
    cursor->count = count;
    func_020a92d8(cursor, 0);
    cursor->mode = MESSAGE_CURSOR_IDLE;
}
CLEAN_AS(func_020b4bf0, MessageCursor_Mask)

/* func_020b4c0c: the walk started again from the mark. */
void MessageCursor_Rewind(void *cursor)
{
    func_020a94a4(cursor);
    func_020a9354(cursor, (int) ((MessageCursor *) cursor)->mark);
}
CLEAN_AS(func_020b4c0c, MessageCursor_Rewind)

/* func_020b4c24: the text the cursor writes. */
void MessageCursor_SetOutput(MessageCursor *cursor, int output)
{
    cursor->output = (void *) (uintptr_t) output;
}
CLEAN_AS(func_020b4c24, MessageCursor_SetOutput)

/* func_020b4c28: the text the cursor walks; the mark goes to its first character. */
void MessageCursor_SetSource(MessageCursor *cursor, const void *source)
{
    cursor->source = source;
    cursor->mark = (u32) message_cursor_characters(source);
}
CLEAN_AS(func_020b4c28, MessageCursor_SetSource)

/* func_020b4c40: the cursor's fields cleared and the walk back to its start. */
void MessageCursor_Reset(void *cursor)
{
    MessageCursor *self = cursor;
    self->mode = MESSAGE_CURSOR_IDLE;
    self->source = NULL;
    self->output = NULL;
    self->mark = 0;
    self->done = 0;
    self->character = 0;
    self->count = 0;
    func_020a94a4(cursor);
}
CLEAN_AS(func_020b4c40, MessageCursor_Reset)

/* func_020b4c5c (slot 1): the cursor destroyed (MessageCursor_Destruct) and freed. */
void *MessageCursor_Delete(void *cursor)
{
    MessageWalker *self = cursor;
    self->vtable = data_020e5254;
    self->vtable = data_020e3e68;
    func_020a941c(cursor);
    Heap_OperatorDeleteB(cursor);
    return cursor;
}
CLEAN_AS(func_020b4c5c, MessageCursor_Delete)

/* func_020b4c84 (slot 0): the cursor's destructor: its vtable, the base class's, then the
 * walkers' base destructor. */
void *MessageCursor_Destruct(void *cursor)
{
    MessageWalker *self = cursor;
    self->vtable = data_020e5254;
    self->vtable = data_020e3e68;
    func_020a941c(cursor);
    return cursor;
}
CLEAN_AS(func_020b4c84, MessageCursor_Destruct)

/* func_020b4ca4: the cursor's constructor, every field cleared. */
MessageCursor *MessageCursor_Construct(MessageCursor *cursor)
{
    func_020a9484(cursor);
    cursor->base.vtable = data_020e3e68;
    cursor->base.vtable = data_020e5254;
    cursor->mode = MESSAGE_CURSOR_IDLE;
    cursor->source = NULL;
    cursor->output = NULL;
    cursor->mark = 0;
    cursor->done = 0;
    cursor->character = 0;
    cursor->count = 0;
    return cursor;
}
CLEAN_AS(func_020b4ca4, MessageCursor_Construct)
