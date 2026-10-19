/* Questions about a message text (message_query.h). */
#include "message_query.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "message_tag.h"
#include "message_walker.h"
#include "ov004/member_pointer.h"
#include "text_walker.h"

static_assert(offsetof(MessageQuery, mode) == 0x24, "mode");
static_assert(offsetof(MessageQuery, tag) == 0x28, "tag");
static_assert(offsetof(MessageQuery, character) == 0x3c, "character");
static_assert(offsetof(MessageQuery, want_group) == 0x40, "want group");
static_assert(offsetof(MessageQuery, index) == 0x48, "index");
static_assert(offsetof(MessageQuery, line) == 0x50, "line");
static_assert(offsetof(MessageQuery, done) == 0x58, "done");
static_assert(sizeof(MessageQuery) == 0x5c, "query");

/* The end of a line. */
#define MESSAGE_QUERY_NEWLINE 10

extern const u8 data_020e3e68[]; /* the walkers' base class's vtable */
extern const u8 data_020e3e44[]; /* the query's */

/* The game's one query object. */
extern MessageQuery data_021f4548;

/* The actions func_020a7aa8 and func_020a7b34 pick by the mode: function-local statics the
 * game fills from constants on its first call (ov004/member_pointer.h). data_020e3cf4[1] is
 * func_020a7a14's member pointer. */
extern u32 data_021f4400, data_021f43fc;
extern MemberPointer data_021f44b4[5], data_021f448c[5];
extern const MemberPointer data_020e3cf4[2], data_020e3d04, data_020e3ce4, __ptmf_null;

/* func_020a7a14: done when the tag met is the one looked for. */
void MessageQuery_CheckTag(MessageQuery *query)
{
    if (query->tag.group == query->want_group && query->tag.kind == query->want_kind) {
        query->done = 1;
    }
}
CLEAN_AS(func_020a7a14, MessageQuery_CheckTag)

/* func_020a7a2c: a newline counted; done when it ends the line before the one looked for. */
void MessageQuery_CountLine(MessageQuery *query)
{
    if (query->character == MESSAGE_QUERY_NEWLINE) {
        query->lines++;
        if (query->lines == query->line) {
            query->done = 1;
        }
    }
}
CLEAN_AS(func_020a7a2c, MessageQuery_CountLine)

/* func_020a7a48 */
void MessageQuery_CountCharacter(MessageQuery *query)
{
    query->count++;
}
CLEAN_AS(func_020a7a48, MessageQuery_CountCharacter)

/* func_020a7a50: a character counted; done when it is the one at the index looked for. */
void MessageQuery_CountToIndex(MessageQuery *query)
{
    s32 index = query->count++;
    if (index == query->index) {
        query->done = 1;
    }
}
CLEAN_AS(func_020a7a50, MessageQuery_CountToIndex)

/* func_020a7a64: the query cleared (nothing looked for) and its walk back to the start. */
void MessageQuery_Reset(MessageQuery *query)
{
    query->mode = MESSAGE_QUERY_TAG;
    MessageTag_Construct(&query->tag);
    query->character = 0;
    query->want_group = (u32) -1;
    query->want_kind = (u32) -1;
    query->index = 0;
    query->count = 0;
    query->line = 0;
    query->lines = 0;
    query->done = 0;
    MessageWalker_Reset((MessageWalker *) query);
}
CLEAN_AS(func_020a7a64, MessageQuery_Reset)

/* func_020a7a98 (slot 6): the walk goes on until the answer is found. */
int MessageQuery_WantsMore(const MessageQuery *query)
{
    return query->done == 0;
}
CLEAN_AS(func_020a7a98, MessageQuery_WantsMore)

/* func_020a7aa8 (slot 5): the tag at `position` read; a tag query checks it.
 * REQUIRES: mode 0 to 4 (the ROM picks the action from a 5-entry table by the mode). */
void MessageQuery_OnTag(MessageQuery *query, int position)
{
    static const MemberPointer *const actions[5] = {
        &data_020e3cf4[1], &__ptmf_null, &__ptmf_null, &__ptmf_null, &__ptmf_null,
    };
    MessageTag_Read(&query->tag, position);
    MemberTable_InitOnce(&data_021f4400, data_021f44b4, actions, 5);
    if (query->mode == MESSAGE_QUERY_TAG) {
        MessageQuery_CheckTag(query);
    }
}
CLEAN_AS(func_020a7aa8, MessageQuery_OnTag)

/* func_020a7b34 (slot 4): the character kept, and counted as the mode asks.
 * REQUIRES: mode 0 to 4 (the ROM picks the action from a 5-entry table by the mode). */
void MessageQuery_OnCharacter(MessageQuery *query, unsigned int character)
{
    static const MemberPointer *const actions[5] = {
        &__ptmf_null, &data_020e3cf4[0], &__ptmf_null, &data_020e3d04, &data_020e3ce4,
    };
    query->character = character;
    MemberTable_InitOnce(&data_021f43fc, data_021f448c, actions, 5);
    switch (query->mode) {
        case MESSAGE_QUERY_CHARACTER:
            MessageQuery_CountToIndex(query);
            break;
        case MESSAGE_QUERY_LENGTH:
            MessageQuery_CountCharacter(query);
            break;
        case MESSAGE_QUERY_LINE:
            MessageQuery_CountLine(query);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020a7b34, MessageQuery_OnCharacter)

/* func_020a7bd0 (slot 3): a length query is answered at the end. */
void MessageQuery_OnEnd(MessageQuery *query)
{
    if (query->mode == MESSAGE_QUERY_LENGTH) {
        query->done = 1;
    }
}
CLEAN_AS(func_020a7bd0, MessageQuery_OnEnd)

/* func_020a7be0 (slot 2): line 0 starts where the text does. */
void MessageQuery_OnText(MessageQuery *query)
{
    if (query->mode == MESSAGE_QUERY_LINE && query->line == 0) {
        query->done = 1;
    }
}
CLEAN_AS(func_020a7be0, MessageQuery_OnText)

/* Walks `text` with the game's query, set up by the caller after a reset. */
static void message_query_walk(int text)
{
    MessageWalker_Start((MessageWalker *) &data_021f4548, text);
    TextWalker_Run((MessageWalker *) &data_021f4548, 0);
}

/* func_020a7bf4: the address where line `line` of `text` starts, or 0 when the text has fewer
 * lines. */
int MessageQuery_Line(int text, int line)
{
    MessageQuery_Reset(&data_021f4548);
    data_021f4548.mode = MESSAGE_QUERY_LINE;
    data_021f4548.line = line;
    message_query_walk(text);
    if (data_021f4548.done != 0) {
        return (int) data_021f4548.base.position;
    }
    return 0;
}
CLEAN_AS(func_020a7bf4, MessageQuery_Line)

/* func_020a7c38: the number of characters of `text` (newlines included, tags not). */
int MessageQuery_Length(int text)
{
    MessageQuery_Reset(&data_021f4548);
    data_021f4548.mode = MESSAGE_QUERY_LENGTH;
    message_query_walk(text);
    if (data_021f4548.done != 0) {
        return data_021f4548.count;
    }
    return 0;
}
CLEAN_AS(func_020a7c38, MessageQuery_Length)

/* func_020a7c74: the character `index` places before the last of `text` (0 the last one), or
 * 0 when the text is shorter. */
int MessageQuery_CharacterFromEnd(const void *text, int index)
{
    int address = (int) (uintptr_t) text;
    int at = MessageQuery_Length(address) - index - 1;

    if (at >= 0) {
        return MessageQuery_CharacterAt(address, at);
    }
    return 0;
}
CLEAN_AS(func_020a7c74, MessageQuery_CharacterFromEnd)

/* func_020a7c98: the character at `index` of `text`, or 0 when the text is shorter. */
int MessageQuery_CharacterAt(int text, int index)
{
    MessageQuery_Reset(&data_021f4548);
    data_021f4548.mode = MESSAGE_QUERY_CHARACTER;
    data_021f4548.index = index;
    message_query_walk(text);
    if (data_021f4548.done != 0) {
        return (int) data_021f4548.character;
    }
    return 0;
}
CLEAN_AS(func_020a7c98, MessageQuery_CharacterAt)

/* func_020a7cdc: the address of the first tag of `text` with this group and kind, or 0. */
int MessageQuery_FindTag(int text, int group, int kind)
{
    MessageQuery_Reset(&data_021f4548);
    data_021f4548.mode = MESSAGE_QUERY_TAG;
    data_021f4548.want_group = (u32) group;
    data_021f4548.want_kind = (u32) kind;
    message_query_walk(text);
    if (data_021f4548.done != 0) {
        return (int) (uintptr_t) data_021f4548.tag.start;
    }
    return 0;
}
CLEAN_AS(func_020a7cdc, MessageQuery_FindTag)

/* func_020a7d20 (slot 1): the query destroyed (MessageQuery_Destruct) and freed. */
MessageQuery *MessageQuery_Delete(MessageQuery *query)
{
    query->base.vtable = data_020e3e44;
    query->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(query);
    Heap_OperatorDeleteB(query);
    return query;
}
CLEAN_AS(func_020a7d20, MessageQuery_Delete)

/* func_020a7d48 (slot 0): the destructor: its vtable, the base class's, then the walkers'
 * base destructor. */
MessageQuery *MessageQuery_Destruct(MessageQuery *query)
{
    query->base.vtable = data_020e3e44;
    query->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(query);
    return query;
}
CLEAN_AS(func_020a7d48, MessageQuery_Destruct)

/* func_020a7d68: the constructor: the walkers' base, then every field cleared as by
 * MessageQuery_Reset (the walk is not moved). */
MessageQuery *MessageQuery_Construct(MessageQuery *query)
{
    MessageWalker_Construct((MessageWalker *) query);
    query->base.vtable = data_020e3e68;
    query->base.vtable = data_020e3e44;
    query->mode = MESSAGE_QUERY_TAG;
    MessageTag_Construct(&query->tag);
    query->character = 0;
    query->want_group = (u32) -1;
    query->want_kind = (u32) -1;
    query->index = 0;
    query->count = 0;
    query->line = 0;
    query->lines = 0;
    query->done = 0;
    return query;
}
CLEAN_AS(func_020a7d68, MessageQuery_Construct)
