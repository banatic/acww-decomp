/* A message's INF1 entry as the talks keep it (message_entry.h). */
#include "message_entry.h"

#include "clean.h"

static_assert(offsetof(MessageEntry, kind) == 0x04, "kind");
static_assert(sizeof(MessageEntry) == 0x0c, "record");

#define MESSAGE_ENTRY_SIZE 0x0c

/* Per kind: 1 when the text is centred (TalkObject_BeginMessage). */
extern const s32 data_020d1d0c[];
/* Per kind: the writing speed, 0, 1 or 2 (TalkObject_BeginMessage, TalkTags_SetSpeed). */
extern void *const data_020d1ca8[];
/* Per kind: the window's kind, 0 to 6, rising with the kind (talk_flow.c). */
extern const s32 data_020d1c44[];

extern void MI_CpuFill8(void *dst, int value, unsigned int size);

/* func_020a8248 */
int MessageEntry_CentredOfKind(MessageEntry *record)
{
    return data_020d1d0c[MessageEntry_Kind(record)];
}
CLEAN_AS(func_020a8248, MessageEntry_CentredOfKind)

/* func_020a8260 */
void *MessageEntry_SpeedOfKind(MessageEntry *record)
{
    return data_020d1ca8[MessageEntry_Kind(record)];
}
CLEAN_AS(func_020a8260, MessageEntry_SpeedOfKind)

/* func_020a8278 */
int MessageEntry_WindowOfKind(MessageEntry *record)
{
    return data_020d1c44[MessageEntry_Kind(record)];
}
CLEAN_AS(func_020a8278, MessageEntry_WindowOfKind)

/* func_020a8290 */
void MessageEntry_GetNext(u8 *out, MessageEntry *record)
{
    *out = record->next;
}
CLEAN_AS(func_020a8290, MessageEntry_GetNext)

/* func_020a8298 */
int MessageEntry_Sound(MessageEntry *record)
{
    return record->sound;
}
CLEAN_AS(func_020a8298, MessageEntry_Sound)

/* func_020a829c */
int MessageEntry_EndValue(MessageEntry *record)
{
    return record->end_value;
}
CLEAN_AS(func_020a829c, MessageEntry_EndValue)

/* func_020a82a0 */
int MessageEntry_BeginValue(MessageEntry *record)
{
    return record->begin_value;
}
CLEAN_AS(func_020a82a0, MessageEntry_BeginValue)

/* func_020a82a4 */
int MessageEntry_Fondness(MessageEntry *record)
{
    return record->fondness;
}
CLEAN_AS(func_020a82a4, MessageEntry_Fondness)

/* func_020a82a8 */
int MessageEntry_Kind(MessageEntry *record)
{
    return record->kind;
}
CLEAN_AS(func_020a82a8, MessageEntry_Kind)

/* func_020a82ac: the record itself (a getter of an owner whose record is its start). */
void *MessageEntry_Self(void *record)
{
    return record;
}
CLEAN_AS(func_020a82ac, MessageEntry_Self)

/* func_020a82b0: every byte 0. */
void MessageEntry_Clear(MessageEntry *record)
{
    MI_CpuFill8(record, 0, MESSAGE_ENTRY_SIZE);
}
CLEAN_AS(func_020a82b0, MessageEntry_Clear)

/* func_020a82bc: `src` copied to `dst`: the word, then the bytes one by one in order (which
 * decides the result when the two overlap). */
void MessageEntry_Copy(void *dst, const void *src)
{
    MessageEntry *to = dst;
    const MessageEntry *from = src;
    to->text_offset = from->text_offset;
    to->kind = from->kind;
    to->fondness = from->fondness;
    to->begin_value = from->begin_value;
    to->end_value = from->end_value;
    to->next = from->next;
    to->sound = from->sound;
    to->unk_0a = from->unk_0a;
    to->unk_0b = from->unk_0b;
}
CLEAN_AS(func_020a82bc, MessageEntry_Copy)

/* func_020a82e4: the destructor; nothing to do. */
void MessageEntry_Destruct(void *record)
{
    (void) record;
}
CLEAN_AS(func_020a82e4, MessageEntry_Destruct)

/* func_020a82e8: the constructor; a cleared record. */
MessageEntry *MessageEntry_Construct(MessageEntry *record)
{
    MessageEntry_Clear(record);
    return record;
}
CLEAN_AS(func_020a82e8, MessageEntry_Construct)
