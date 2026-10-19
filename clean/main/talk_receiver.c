/* The receiver a talk is for, and its speaker's name (talk_receiver.h). */
#include "talk_receiver.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "talk_flow.h"
#include "talk_object.h"
#include "talk_voice.h"

static_assert(offsetof(TalkReceiverName, style) == 0x0c, "name style");
static_assert(offsetof(TalkReceiverName, chars) == 0x12, "name chars");
static_assert(sizeof(TalkReceiverName) == 0x20, "name");
static_assert(offsetof(TalkReceiver, speaker) == 0x20, "receiver speaker");
static_assert(offsetof(TalkReceiver, talk) == 0x40, "receiver talk");
static_assert(offsetof(TalkReceiver, nameless) == 0x44, "receiver nameless");
static_assert(offsetof(TalkReceiver, base.message) == 0x1e, "receiver message");
static_assert(sizeof(TalkReceiver) == 0x48, "receiver");

/* The vtables: the receiver's and its speaker name's. */
extern const u8 data_020df008[];
extern const TextVtable data_020def4c;

/* The folder of the message files: "/script/KOR/message". */
extern const char data_020df080[];

/* --- The speaker's name --- */

/* func_02066a5c (vtable entry 3): the characters' address. */
int TalkReceiverName_Chars(int name)
{
    return name + (int) offsetof(TalkReceiverName, chars);
}
CLEAN_AS(func_02066a5c, TalkReceiverName_Chars)

/* func_02066a60 (vtable entry 2): the capacity, 14 bytes. */
int TalkReceiverName_Capacity(void)
{
    return TALK_RECEIVER_NAME_CAPACITY;
}
CLEAN_AS(func_02066a60, TalkReceiverName_Capacity)

/* func_02066a64 (vtable entry 1): the destructor, then the object freed. */
TalkReceiverName *TalkReceiverName_DestructDelete(TalkReceiverName *name)
{
    name->vtable = &data_020def4c;
    TextBase_Destruct((TextBase *) (void *) name);
    Heap_OperatorDeleteB(name);
    return name;
}
CLEAN_AS(func_02066a64, TalkReceiverName_DestructDelete)

/* func_02066a84 (vtable entry 0): the destructor: the text base's. */
void *TalkReceiverName_Destruct(void *name)
{
    ((TalkReceiverName *) name)->vtable = &data_020def4c;
    TextBase_Destruct((TextBase *) name);
    return name;
}
CLEAN_AS(func_02066a84, TalkReceiverName_Destruct)

/* func_02066a9c: the constructor: the text base built, then the text emptied. */
void *TalkReceiverName_Construct(void *name)
{
    TextBase_Construct(name);
    ((TalkReceiverName *) name)->vtable = &data_020def4c;
    TextBase_Clear(name);
    return name;
}
CLEAN_AS(func_02066a9c, TalkReceiverName_Construct)

/* --- The receiver --- */

/* func_0206684c: the receiver taken off its talk. */
void TalkReceiver_DropTalk(TalkReceiver *receiver)
{
    receiver->talk = NULL;
}
CLEAN_AS(func_0206684c, TalkReceiver_DropTalk)

/* func_02066854: the talk showing the receiver's message. */
void TalkReceiver_SetTalk(TalkReceiver *receiver, struct TalkObject *talk)
{
    receiver->talk = talk;
}
CLEAN_AS(func_02066854, TalkReceiver_SetTalk)

/* func_02066858 (slot 0x74): nothing. */
void TalkReceiver_Nothing74(void) {}
CLEAN_AS(func_02066858, TalkReceiver_Nothing74)

/* func_0206685c (slot 0x70, the talk closes): nothing. */
void TalkReceiver_Nothing70(void) {}
CLEAN_AS(func_0206685c, TalkReceiver_Nothing70)

/* func_02066860 (slot 0x6c): the speaker's kind: none. */
int TalkReceiver_SpeakingKind(void)
{
    return TALK_RECEIVER_NO_KIND;
}
CLEAN_AS(func_02066860, TalkReceiver_SpeakingKind)

/* func_02066864 (slot 0x68): the villager talked to: none (0). */
int TalkReceiver_Villager(void)
{
    return 0;
}
CLEAN_AS(func_02066864, TalkReceiver_Villager)

/* func_02066868 (slot 0x64): nothing. */
void TalkReceiver_Nothing64(void) {}
CLEAN_AS(func_02066868, TalkReceiver_Nothing64)

/* func_0206686c (slot 0x60, the turn passes): nothing. */
void TalkReceiver_Nothing60(void) {}
CLEAN_AS(func_0206686c, TalkReceiver_Nothing60)

/* func_02066870 (slot 0x5c): nothing. */
void TalkReceiver_Nothing5c(void) {}
CLEAN_AS(func_02066870, TalkReceiver_Nothing5c)

/* func_02066874 (slot 0x58): nothing. */
void TalkReceiver_Nothing58(void) {}
CLEAN_AS(func_02066874, TalkReceiver_Nothing58)

/* func_02066878 (slot 0x54): nothing. */
void TalkReceiver_Nothing54(void) {}
CLEAN_AS(func_02066878, TalkReceiver_Nothing54)

/* func_0206687c (slot 0x50): nothing. */
void TalkReceiver_Nothing50(void) {}
CLEAN_AS(func_0206687c, TalkReceiver_Nothing50)

/* func_02066880 (slot 0x4c): nothing. */
void TalkReceiver_Nothing4c(void) {}
CLEAN_AS(func_02066880, TalkReceiver_Nothing4c)

/* func_02066884 (slot 0x48): nothing. */
void TalkReceiver_Nothing48(void) {}
CLEAN_AS(func_02066884, TalkReceiver_Nothing48)

/* func_02066888 (slot 0x44): nothing. */
void TalkReceiver_Nothing44(void) {}
CLEAN_AS(func_02066888, TalkReceiver_Nothing44)

/* func_0206688c (slot 0x40): nothing. */
void TalkReceiver_Nothing40(void) {}
CLEAN_AS(func_0206688c, TalkReceiver_Nothing40)

/* func_02066890 (slot 0x3c): nothing. */
void TalkReceiver_Nothing3c(void) {}
CLEAN_AS(func_02066890, TalkReceiver_Nothing3c)

/* func_02066894 (slot 0x38): nothing. */
void TalkReceiver_Nothing38(void) {}
CLEAN_AS(func_02066894, TalkReceiver_Nothing38)

/* func_02066898 (slot 0x34, a branch): nothing. */
void TalkReceiver_Nothing34(void) {}
CLEAN_AS(func_02066898, TalkReceiver_Nothing34)

/* func_0206689c (slot 0x30): nothing. */
void TalkReceiver_Nothing30(void) {}
CLEAN_AS(func_0206689c, TalkReceiver_Nothing30)

/* func_020668a0 (slot 0x2c): nothing. */
void TalkReceiver_Nothing2c(void) {}
CLEAN_AS(func_020668a0, TalkReceiver_Nothing2c)

/* func_020668a4 (slot 0x28): nothing. */
void TalkReceiver_Nothing28(void) {}
CLEAN_AS(func_020668a4, TalkReceiver_Nothing28)

/* func_020668a8 (slot 0x24): nothing. */
void TalkReceiver_Nothing24(void) {}
CLEAN_AS(func_020668a8, TalkReceiver_Nothing24)

/* func_020668ac (slot 0x20): nothing. */
void TalkReceiver_Nothing20(void) {}
CLEAN_AS(func_020668ac, TalkReceiver_Nothing20)

/* func_020668b0 (slot 0x1c): nothing. */
void TalkReceiver_Nothing1c(void) {}
CLEAN_AS(func_020668b0, TalkReceiver_Nothing1c)

/* func_020668b4 (slot 0x18, the player's answer): nothing. */
void TalkReceiver_Nothing18(void) {}
CLEAN_AS(func_020668b4, TalkReceiver_Nothing18)

/* func_020668b8 (slot 0x14, what follows a message): nothing. */
void TalkReceiver_Nothing14(void) {}
CLEAN_AS(func_020668b8, TalkReceiver_Nothing14)

/* func_020668bc (slot 0x10): nothing. */
void TalkReceiver_Nothing10(void) {}
CLEAN_AS(func_020668bc, TalkReceiver_Nothing10)

/* func_020668c0 (slot 0x0c): the folder of the message files, "/script/KOR/message". */
int TalkReceiver_Folder(void)
{
    return (int) (uintptr_t) data_020df080;
}
CLEAN_AS(func_020668c0, TalkReceiver_Folder)

/* func_020668c8: the style given with the speaker's name. */
int TalkReceiver_SpeakerStyle(const TalkReceiver *receiver)
{
    return receiver->speaker.style;
}
CLEAN_AS(func_020668c8, TalkReceiver_SpeakerStyle)

/* func_020668cc: whether the speaker's name was cleared. */
u8 TalkReceiver_IsNameless(const TalkReceiver *receiver)
{
    return receiver->nameless;
}
CLEAN_AS(func_020668cc, TalkReceiver_IsNameless)

/* func_020668d4: the speaker's name. */
TalkReceiverName *TalkReceiver_SpeakerName(TalkReceiver *receiver)
{
    return &receiver->speaker;
}
CLEAN_AS(func_020668d4, TalkReceiver_SpeakerName)

/* func_020668d8: the speaker named `name` with `style` for the next line; when the talk is
 * neither closed nor gone (states 0 and 5, read before the name is set), its name plate is
 * drawn again and its last characters told.
 * REQUIRES: the receiver has a talk. */
void TalkReceiver_NextSpeaker(TalkReceiver *receiver, TextBase *name, int style)
{
    s32 state = receiver->talk->state;
    TalkReceiver_SetSpeakerText(receiver, name, style);
    if (state != TALK_OBJECT_CLOSED && state != TALK_OBJECT_GONE) {
        TalkObject_ColourNamePlate(receiver->talk);
        TalkVoice_TakeSpeakerMode(&receiver->talk->voice);
    }
}
CLEAN_AS(func_020668d8, TalkReceiver_NextSpeaker)

/* func_02066914: the speaker's name emptied, with `style`; the speaker is nameless. */
void TalkReceiver_ClearSpeaker(TalkReceiver *receiver, int style)
{
    TextBase_Clear(&receiver->speaker);
    receiver->speaker.style = style;
    receiver->nameless = 1;
}
CLEAN_AS(func_02066914, TalkReceiver_ClearSpeaker)

/* func_02066934: the speaker's name copied from the text `name`, with `style`. */
void TalkReceiver_SetSpeakerText(TalkReceiver *receiver, TextBase *name, int style)
{
    TextBase_Copy((TextBase *) (void *) &receiver->speaker, name);
    receiver->speaker.style = style;
    receiver->nameless = 0;
}
CLEAN_AS(func_02066934, TalkReceiver_SetSpeakerText)

/* func_02066954: the speaker's name set from the characters `name`, with `style`. */
void TalkReceiver_SetSpeaker(TalkReceiver *receiver, const char *name, int style)
{
    TextBase_SetChars((TextBase *) (void *) &receiver->speaker, name);
    receiver->speaker.style = style;
    receiver->nameless = 0;
}
CLEAN_AS(func_02066954, TalkReceiver_SetSpeaker)

/* _ZN13Base_0206699417vfunc_02066994_08Ev (slot 0x08): the reset: no file, no message, no
 * speaker's name, no talk. */
void TalkReceiver_Reset(TalkReceiver *receiver)
{
    MessageReceiver_Clear(&receiver->base);
    TextBase_Clear(&receiver->speaker);
    receiver->talk = NULL;
    receiver->nameless = 0;
}
CLEAN_AS(_ZN13Base_0206699417vfunc_02066994_08Ev, TalkReceiver_Reset)

/* The destructor's body: the speaker's name, then the message receiver. */
static void talk_receiver_destruct(TalkReceiver *receiver)
{
    receiver->base.vtable = data_020df008;
    TalkReceiverName_Destruct(&receiver->speaker);
    MessageReceiver_DestructBase(&receiver->base);
}

/* func_02066994: the destructor. */
void *TalkReceiver_Destruct(TalkReceiver *receiver)
{
    talk_receiver_destruct(receiver);
    return receiver;
}
CLEAN_AS(func_02066994, TalkReceiver_Destruct)

/* func_020669b8 (vtable entry 1): the destructor, then the object freed. */
void *TalkReceiver_DestructDelete(TalkReceiver *receiver)
{
    talk_receiver_destruct(receiver);
    Heap_OperatorDeleteB(receiver);
    return receiver;
}
CLEAN_AS(func_020669b8, TalkReceiver_DestructDelete)

/* func_020669e0 (vtable entry 0): the destructor, as func_02066994. */
void *TalkReceiver_DestructSlot(TalkReceiver *receiver)
{
    talk_receiver_destruct(receiver);
    return receiver;
}
CLEAN_AS(func_020669e0, TalkReceiver_DestructSlot)

/* The constructor's body: the message receiver, the vtable, the speaker's name; no talk. The
 * name's style is left as the text base set it. */
static void talk_receiver_construct(TalkReceiver *receiver)
{
    MessageReceiver_Construct(&receiver->base);
    receiver->base.vtable = data_020df008;
    TalkReceiverName_Construct(&receiver->speaker);
    receiver->talk = NULL;
    receiver->nameless = 0;
}

/* func_02066a04: the constructor. */
TalkReceiver *TalkReceiver_Construct(TalkReceiver *receiver)
{
    talk_receiver_construct(receiver);
    return receiver;
}
CLEAN_AS(func_02066a04, TalkReceiver_Construct)

/* func_02066a30: the constructor, as func_02066a04. */
TalkReceiver *TalkReceiver_ConstructBase(TalkReceiver *receiver)
{
    talk_receiver_construct(receiver);
    return receiver;
}
CLEAN_AS(func_02066a30, TalkReceiver_ConstructBase)
