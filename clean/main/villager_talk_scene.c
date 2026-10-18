/* The talk scene of a town villager (villager_talk_scene.h). */
#include "villager_talk_scene.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "item_code.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_motion_request.h"
#include "scene_talk.h"
#include "session_villager.h"
#include "talk_choices.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_scene_object.h"
#include "letter.h"
#include "main_random.h"

static_assert(offsetof(VillagerTalk, line) == 0xb0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, reply) == 0xd0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, on_command_end) == 0xd8, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, unk_e0) == 0xe0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, walk) == 0xf0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, music) == 0xf8, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, villager) == 0x100, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, item) == 0x124, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, memory_index) == 0x128, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, unk_130) == 0x130, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, no_memory) == 0x13c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, unk_154) == 0x154, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, unk_15c) == 0x15c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, events) == 0x16c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, gift) == 0x19c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, bells) == 0x1a0, "VillagerTalk layout");

#define VILLAGER_TALK_SCENE_NO_ITEM 0xfff1
#define VILLAGER_TALK_SCENE_NO_INDEX (-1)
/* The tables of lines VillagerTalkScene_Start can set. */
#define VILLAGER_TALK_SCENE_LINE_TABLES 17
#define VILLAGER_TALK_SCENE_LINES 3
/* The pockets' ten letters, 0x100 bytes apart, and their states to send (7 and 8). */
#define VILLAGER_TALK_SCENE_LETTERS 10
#define VILLAGER_TALK_SCENE_LETTER_SIZE 0x100
#define VILLAGER_TALK_SCENE_LETTER_TO_SEND 7
/* The pockets' fifteen item slots, and the state of a slot holding an item. */
#define VILLAGER_TALK_SCENE_POCKETS 15
#define VILLAGER_TALK_SCENE_POCKET_HELD 2
/* The villager scene object's motion, the kind of stand asked for, and its town record. */
#define VILLAGER_TALK_SCENE_MOTION 0x564
#define VILLAGER_TALK_SCENE_STAND_PRIORITY 2
#define VILLAGER_TALK_SCENE_RECORD 0x830
/* The scene's reset (vtable slot 0x08) and a speaker's "ask for a mood" (slot 0xa4). */
#define VILLAGER_TALK_SCENE_SLOT_RESET 0x08
#define VILLAGER_TALK_SCENE_SLOT_ASK_MOOD 0xa4
/* VillagerTalkScene_SpeakerOf's speakers: the talk's villager and the one at its 0x644. */
#define VILLAGER_TALK_SCENE_SPEAKER_VILLAGER 0
#define VILLAGER_TALK_SCENE_SPEAKER_PARTNER 1
/* The bytes data_021c1e84 holds. */
#define VILLAGER_TALK_SCENE_SHARED_SIZE 0x40

/* The class's vtable. */
extern const u8 data_020d9df8[];
/* The motion's standing word. */
extern const u16 data_020c80f8;
/* The tables of three line members VillagerTalkScene_Start picks from. */
extern const MemberPointer data_021c283c[VILLAGER_TALK_SCENE_LINE_TABLES][VILLAGER_TALK_SCENE_LINES];
/* Bytes all talks share, cleared at each start. */
extern u8 data_021c1e84[VILLAGER_TALK_SCENE_SHARED_SIZE];
extern const MemberPointer __ptmf_null;

/* The SDK's fill. */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static SceneBase *talk_scene_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The members at 0xe0 and 0xe8. */
static MemberPointer *talk_scene_next_command_end(VillagerTalk *talk)
{
    return (MemberPointer *) (void *) &talk->unk_e0[0];
}

static MemberPointer *talk_scene_member_e8(VillagerTalk *talk)
{
    return (MemberPointer *) (void *) &talk->unk_e0[8];
}

/* The word at 0x154 (an object the talk is about) and the words after the memory. */
static u32 *talk_scene_object(VillagerTalk *talk)
{
    return (u32 *) (void *) &talk->unk_154[0];
}

static s32 *talk_scene_word_130(VillagerTalk *talk)
{
    return (s32 *) (void *) &talk->unk_130[0];
}

static u32 talk_scene_slot(const void *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (const void *) (vtable + slot);
}

/* The focus speaker asked for a mood (its slot 0xa4) when there is one. */
static void talk_scene_ask_mood(VillagerTalk *talk, int mood, int length)
{
    typedef void (*AskMood)(void *speaker, int mood, int length);
    void *speaker = (void *) (uintptr_t) SceneBase_FocusSpeaker(talk_scene_base(talk));
    if (speaker != NULL) {
        ((AskMood) (uintptr_t) talk_scene_slot(speaker, VILLAGER_TALK_SCENE_SLOT_ASK_MOOD))(speaker, mood, length);
    }
}

/* A member pointer run when set, then cleared. */
static void talk_scene_run_once(VillagerTalk *talk, MemberPointer *member)
{
    if (member->function != 0) {
        MemberPointer_CallVoid(member, talk);
        *member = __ptmf_null;
    }
}

/* A member pointer copied in two words, the first first. */
static void talk_scene_copy(MemberPointer *to, const MemberPointer *from)
{
    u32 function = from->function;
    s32 adjust = from->adjust;
    to->function = function;
    to->adjust = adjust;
}

/* func_0202d730: the villager's motion asked to stand (with priority 2 and the standing word). */
int VillagerTalkScene_Stand(VillagerTalk *talk)
{
    return SceneMotion_RequestStand((SceneMotion *) (void *) (talk->villager + VILLAGER_TALK_SCENE_MOTION),
                                    VILLAGER_TALK_SCENE_STAND_PRIORITY, data_020c80f8);
}
CLEAN_AS(func_0202d730, VillagerTalkScene_Stand)

/* func_0202d754: the first of the pockets' ten letters whose state is 7 or 8, or 0. */
MailLetter *VillagerTalkScene_LetterToSend(PlayerPockets *pockets)
{
    u8 *letter = (u8 *) PlayerPockets_Letter(pockets, 0);
    for (int i = 0; i < VILLAGER_TALK_SCENE_LETTERS; i++, letter += VILLAGER_TALK_SCENE_LETTER_SIZE) {
        if ((u8) (Letter_State((const Letter *) ((MailLetter *) (void *) letter)) - VILLAGER_TALK_SCENE_LETTER_TO_SEND) <= 1) {
            return (MailLetter *) (void *) letter;
        }
    }
    return NULL;
}
CLEAN_AS(func_0202d754, VillagerTalkScene_LetterToSend)

/* func_0202d794: the place (0-14) of the first pocket holding an item (state 2) like `*item`:
 * of the same variant item when the pocket's item has variants, else the same code; -1 when
 * none does. */
int VillagerTalkScene_PocketOfItem(PlayerPockets *pockets, u16 *item)
{
    u16 *slot = PlayerPockets_Slot(pockets, 0);
    for (int i = 0; i < VILLAGER_TALK_SCENE_POCKETS; i++, slot++) {
        if (PlayerPockets_SlotState(pockets, i) != VILLAGER_TALK_SCENE_POCKET_HELD) {
            continue;
        }
        int same;
        if (ItemCode_HasVariant(slot)) {
            int variant = ItemCode_VariantItem(slot);
            same = variant == ItemCode_VariantItem(item);
        } else {
            same = *slot == *item;
        }
        if (same) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_0202d794, VillagerTalkScene_PocketOfItem)

/* func_0202d808 (slot 0x70): the step at 0xf8 run once. */
void VillagerTalkScene_RunMusic(VillagerTalk *talk)
{
    talk_scene_run_once(talk, &talk->music);
}
CLEAN_AS(func_0202d808, VillagerTalkScene_RunMusic)

/* func_0202d84c (slot 0x30): the focus speaker asked for mood 4. */
void VillagerTalkScene_AskMood4(VillagerTalk *talk, int length)
{
    talk_scene_ask_mood(talk, 4, length);
}
CLEAN_AS(func_0202d84c, VillagerTalkScene_AskMood4)

/* func_0202d86c (slot 0x2c): the focus speaker asked for mood 3. */
void VillagerTalkScene_AskMood3(VillagerTalk *talk, int length)
{
    talk_scene_ask_mood(talk, 3, length);
}
CLEAN_AS(func_0202d86c, VillagerTalkScene_AskMood3)

/* func_0202d88c (slot 0x28): the focus speaker asked for mood 2. */
void VillagerTalkScene_AskMood2(VillagerTalk *talk, int length)
{
    talk_scene_ask_mood(talk, 2, length);
}
CLEAN_AS(func_0202d88c, VillagerTalkScene_AskMood2)

/* func_0202d8ac (slot 0x24): the focus speaker asked for mood 1. */
void VillagerTalkScene_AskMood1(VillagerTalk *talk, int length)
{
    talk_scene_ask_mood(talk, 1, length);
}
CLEAN_AS(func_0202d8ac, VillagerTalkScene_AskMood1)

/* func_0202d8cc (slot 0x20): the focus speaker asked for mood 0 (no mood), of length 0. */
void VillagerTalkScene_AskMood0(VillagerTalk *talk)
{
    talk_scene_ask_mood(talk, 0, 0);
}
CLEAN_AS(func_0202d8cc, VillagerTalkScene_AskMood0)

/* func_0202d8ec (slot 0x60): the talk asked for, without the camera. */
int VillagerTalkScene_RequestTalk(VillagerTalk *talk)
{
    return SceneTalk_Request((u8 *) (void *) talk, 0);
}
CLEAN_AS(func_0202d8ec, VillagerTalkScene_RequestTalk)

/* func_0202d8f8: the player (the current player's when `player` is 0) noted in the villager's
 * memory, unless the talk's byte 0x13c says not to. Without a memory yet (`*memory` 0): when the
 * villager remembers the player already (VillagerMemory_IndexOfPlayer), only its place goes into
 * `*index`; otherwise a memory to reuse is taken for the player (VillagerMemoryEntry_Take) and
 * sent with its sender (SessionVillager_SendEntrySender). With a memory, it is brought up to
 * date (VillagerMemoryEntry_Update) and sent (SessionVillager_SendEntryFill).
 * QUIRK: a memory found by the player leaves `*memory` 0. */
void VillagerTalkScene_NoteMemory(VillagerTalk *talk, u8 **memory, s32 *index, u8 *villager, int player)
{
    if (talk->no_memory != 0) {
        return;
    }
    if (player == 0 && PlayerRecords_Current() != NULL) {
        player = (int) (uintptr_t) PlayerRecord_Player(PlayerRecords_Current());
    }
    if (player == 0 || villager == NULL) {
        return;
    }
    const DesignCreator *who = (const DesignCreator *) (uintptr_t) player;
    if (*memory == NULL) {
        *index = VillagerMemory_IndexOfPlayer(villager, who);
        if (*index != VILLAGER_TALK_SCENE_NO_INDEX) {
            return;
        }
        *index = VillagerMemory_ReusableIndex(villager);
        if (*index == VILLAGER_TALK_SCENE_NO_INDEX) {
            return;
        }
        *memory = (u8 *) VillagerMemory_At(villager, *index);
        VillagerMemoryEntry_Take((VillagerMemory *) (void *) *memory, who, NULL, NULL);
        SessionVillager_SendEntrySender(villager, *index);
    } else {
        VillagerMemoryEntry_Update((VillagerMemory *) (void *) *memory, who, NULL, NULL);
        SessionVillager_SendEntryFill(villager, *index);
    }
}
CLEAN_AS(func_0202d8f8, VillagerTalkScene_NoteMemory)

/* func_0202d994 (slot 0x78): the line member at 0xb0 run with `line` when set. */
void VillagerTalkScene_RunLine(VillagerTalk *talk, VillagerTalkLine *line)
{
    typedef void (*LineMember)(void *talk, VillagerTalkLine *line);
    if (talk->line.function == 0) {
        return;
    }
    void *self = MemberPointer_Object(&talk->line, talk);
    ((LineMember) (uintptr_t) MemberPointer_Code(&talk->line, self))(self, line);
}
CLEAN_AS(func_0202d994, VillagerTalkScene_RunLine)

/* func_0202d9c4: the object the talk is about (the word at 0x154). */
u32 VillagerTalkScene_Object(VillagerTalk *talk)
{
    return *talk_scene_object(talk);
}
CLEAN_AS(func_0202d9c4, VillagerTalkScene_Object)

/* func_0202d9d0 */
void VillagerTalkScene_SetObject(VillagerTalk *talk, u32 object)
{
    *talk_scene_object(talk) = object;
}
CLEAN_AS(func_0202d9d0, VillagerTalkScene_SetObject)

/* func_0202d9dc (slot 0x68): the town record (0x830) of the villager whose turn it is, 0 when
 * there is none. */
void *VillagerTalkScene_SpeakerRecord(VillagerTalk *talk)
{
    int speaker = SceneBase_Speaking(talk_scene_base(talk));
    u8 *villager = (u8 *) (uintptr_t) VillagerTalkScene_SpeakerOf(talk, speaker);
    if (villager == NULL) {
        return NULL;
    }
    return *(void **) (void *) (villager + VILLAGER_TALK_SCENE_RECORD);
}
CLEAN_AS(func_0202d9dc, VillagerTalkScene_SpeakerRecord)

/* func_0202da08: the villager scene object of a speaker: 0 the talk's villager, 1 the one at its
 * word 0x644 (none without a villager), 0 for the others. */
int VillagerTalkScene_SpeakerOf(VillagerTalk *talk, int speaker)
{
    switch (speaker) {
        case VILLAGER_TALK_SCENE_SPEAKER_VILLAGER:
            return (int) (uintptr_t) talk->villager;
        case VILLAGER_TALK_SCENE_SPEAKER_PARTNER:
            if (talk->villager != NULL) {
                return (int) VillagerSceneObject_Word644((u32 *) (void *) talk->villager);
            }
            return 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_0202da08, VillagerTalkScene_SpeakerOf)

/* func_0202da38: a line for the personality: the name of the texts `texts` for the personality
 * into `text` (Personality_FormatResourceName), and the message per_group * group + a random
 * number below `range` (below per_group when `range` is 0) into `*message`; the sum is
 * returned whole.
 * QUIRK: per_group, range and personality count by their low byte, and per_group * group is cut
 * to a byte. */
int VillagerTalkScene_DrawLine(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts,
                               int per_group, int group, int range)
{
    (void) talk;
    u8 first = (u8) ((u8) per_group * group);
    u8 bound = (u8) range != 0 ? (u8) range : (u8) per_group;
    Personality_FormatResourceName(text, size, (const char *) (uintptr_t) texts, (u8) personality);
    int result = first + MainRandom_Below(bound);
    *message = (u8) result;
    return result;
}
CLEAN_AS(func_0202da38, VillagerTalkScene_DrawLine)

/* func_0202da74: the reply (0xd0). */
void VillagerTalkScene_SetReply(VillagerTalk *talk, MemberPointer reply)
{
    talk_scene_copy(&talk->reply, &reply);
}
CLEAN_AS(func_0202da74, VillagerTalkScene_SetReply)

/* func_0202da88: the three line members (0xb0, 0xb8, 0xc0) from a table of three, copied a
 * word at a time in order. */
void VillagerTalkScene_SetLines(VillagerTalk *talk, const MemberPointer *table)
{
    talk_scene_copy(&talk->line, &table[0]);
    talk_scene_copy(&talk->on_event_10, &table[1]);
    talk_scene_copy(&talk->on_each_message, &table[2]);
}
CLEAN_AS(func_0202da88, VillagerTalkScene_SetLines)

/* func_0202dac0: the three line members cleared. */
void VillagerTalkScene_ClearLines(VillagerTalk *talk)
{
    talk->line = __ptmf_null;
    talk->on_event_10 = __ptmf_null;
    talk->on_each_message = __ptmf_null;
}
CLEAN_AS(func_0202dac0, VillagerTalkScene_ClearLines)

/* func_0202db04 (slot 0x7c): the member at 0xe8 run once. */
void VillagerTalkScene_RunOnceE8(VillagerTalk *talk)
{
    talk_scene_run_once(talk, talk_scene_member_e8(talk));
}
CLEAN_AS(func_0202db04, VillagerTalkScene_RunOnceE8)

/* func_0202db48: the member at 0xe8. */
void VillagerTalkScene_SetE8(VillagerTalk *talk, MemberPointer member)
{
    talk_scene_copy(talk_scene_member_e8(talk), &member);
}
CLEAN_AS(func_0202db48, VillagerTalkScene_SetE8)

/* func_0202db5c (slot 0x84): when the scene's command ends, the member at 0xd8 run once; the
 * one waiting at 0xe0 (when set) then takes its place, and 0xe0 is cleared. Nothing when 0xd8
 * is not set. */
void VillagerTalkScene_OnCommandEnd(VillagerTalk *talk)
{
    if (talk->on_command_end.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->on_command_end, talk);
    talk->on_command_end = __ptmf_null;
    MemberPointer *next = talk_scene_next_command_end(talk);
    if (next->function != 0) {
        talk_scene_copy(&talk->on_command_end, next);
    }
    *next = __ptmf_null;
}
CLEAN_AS(func_0202db5c, VillagerTalkScene_OnCommandEnd)

/* func_0202dbdc: the member waiting at 0xe0 to run at the command's end after the one at 0xd8. */
void VillagerTalkScene_SetNextCommandEnd(VillagerTalk *talk, MemberPointer member)
{
    talk_scene_copy(talk_scene_next_command_end(talk), &member);
}
CLEAN_AS(func_0202dbdc, VillagerTalkScene_SetNextCommandEnd)

/* func_0202dbf0: the member run at the command's end (0xd8). */
void VillagerTalkScene_SetCommandEnd(VillagerTalk *talk, MemberPointer member)
{
    talk_scene_copy(&talk->on_command_end, &member);
}
CLEAN_AS(func_0202dbf0, VillagerTalkScene_SetCommandEnd)

/* func_0202dc04 (slot 0x80): before each step, the base's (nothing), then the walk at 0xf0
 * when set. */
void VillagerTalkScene_Step(VillagerTalk *talk)
{
    SceneBase_Nothing80(talk);
    if (talk->walk.function != 0) {
        MemberPointer_CallVoid(&talk->walk, talk);
    }
}
CLEAN_AS(func_0202dc04, VillagerTalkScene_Step)

/* func_0202dc3c: the talk started with a villager scene object: the scene reset (its slot
 * 0x08), the line members from table `lines` of data_021c283c (left as they are for 17 or
 * more), every other member pointer, the item, gift and object cleared, and the place of the
 * current player in the villager's memory and that memory looked up (both -1 and 0 without a
 * player or villager); the choices' functions and the bytes at data_021c1e84 cleared. */
void VillagerTalkScene_Start(VillagerTalk *talk, u8 *villager, unsigned int lines)
{
    typedef void (*Reset)(void *scene);
    const DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    ((Reset) (uintptr_t) talk_scene_slot(talk, VILLAGER_TALK_SCENE_SLOT_RESET))(talk);
    talk->villager = villager;
    if (lines < VILLAGER_TALK_SCENE_LINE_TABLES) {
        VillagerTalkScene_SetLines(talk, data_021c283c[lines]);
    }
    talk->on_last_message = __ptmf_null;
    talk->reply = __ptmf_null;
    talk->on_command_end = __ptmf_null;
    *talk_scene_next_command_end(talk) = __ptmf_null;
    *talk_scene_member_e8(talk) = __ptmf_null;
    talk->walk = __ptmf_null;
    talk->music = __ptmf_null;
    talk->item = VILLAGER_TALK_SCENE_NO_ITEM;
    talk->record_138 = 0;
    talk->memory_index = VILLAGER_TALK_SCENE_NO_INDEX;
    talk->memory = NULL;
    *talk_scene_word_130(talk) = -1;
    talk->partner_memory = NULL;
    if (player != NULL && talk->villager != NULL) {
        u8 *record = *(u8 **) (void *) (talk->villager + VILLAGER_TALK_SCENE_RECORD);
        talk->memory_index = VillagerMemory_IndexOfPlayer(record, player);
        talk->memory =
            (u8 *) VillagerMemory_At(*(u8 **) (void *) (talk->villager + VILLAGER_TALK_SCENE_RECORD), talk->memory_index);
    }
    TalkChoices_ClearFunctions((TalkChoicesScene *) (void *) talk);
    *talk_scene_object(talk) = 0;
    talk->unk_154[4] = 0;
    talk->unk_154[5] = 0;
    for (int i = 0; i < 4; i++) {
        ((u32 *) (void *) talk->unk_15c)[i] = 0;
    }
    for (int i = 0; i < VILLAGER_TALK_MEMBER_EVENTS; i++) {
        talk->events[i] = __ptmf_null;
    }
    talk->gift = VILLAGER_TALK_SCENE_NO_ITEM;
    talk->gift_from_items = 0;
    talk->bells = 0;
    MI_CpuFill8(data_021c1e84, 0, VILLAGER_TALK_SCENE_SHARED_SIZE);
    talk->no_memory = 0;
}
CLEAN_AS(func_0202dc3c, VillagerTalkScene_Start)

/* func_0202de4c: the destructor of the scene part: the base's (SceneBase_DestructBody). Returns
 * the talk. */
VillagerTalk *VillagerTalkScene_DestructBody(VillagerTalk *talk)
{
    *(const u8 **) (void *) talk = data_020d9df8;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_0202de4c, VillagerTalkScene_DestructBody)

/* func_0202de64 (slot 0x04): the destructor that also frees the talk's memory. */
VillagerTalk *VillagerTalkScene_DestructDelete(VillagerTalk *talk)
{
    *(const u8 **) (void *) talk = data_020d9df8;
    SceneBase_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_0202de64, VillagerTalkScene_DestructDelete)

/* func_0202de84 (slot 0x00): the destructor. */
VillagerTalk *VillagerTalkScene_Destruct(VillagerTalk *talk)
{
    *(const u8 **) (void *) talk = data_020d9df8;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_0202de84, VillagerTalkScene_Destruct)

/* The constructor's body: the base's, then no item and no gift. */
static VillagerTalk *talk_scene_construct(VillagerTalk *talk)
{
    SceneBase_Construct(talk_scene_base(talk));
    *(const u8 **) (void *) talk = data_020d9df8;
    talk->item = VILLAGER_TALK_SCENE_NO_ITEM;
    talk->gift = VILLAGER_TALK_SCENE_NO_ITEM;
    return talk;
}

/* func_0202de9c: the constructor. */
VillagerTalk *VillagerTalkScene_Construct(VillagerTalk *talk)
{
    return talk_scene_construct(talk);
}
CLEAN_AS(func_0202de9c, VillagerTalkScene_Construct)

/* func_0202decc: the same constructor a second time in the ROM. */
VillagerTalk *VillagerTalkScene_ConstructAlt(VillagerTalk *talk)
{
    return talk_scene_construct(talk);
}
CLEAN_AS(func_0202decc, VillagerTalkScene_ConstructAlt)
