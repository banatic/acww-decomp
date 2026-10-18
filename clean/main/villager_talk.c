/* A town villager's talk scene (villager_talk.h). */
#include "villager_talk.h"

#include <string.h>

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "lookups.h"
#include "music_queue.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_motion_request.h"
#include "session_villager.h"
#include "sound.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_entry.h"
#include "villager_impression.h"
#include "villager_items.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_roster.h"
#include "villager_scene_object.h"
#include "villager_town.h"
#include "camera_modes.h"
#include "clock.h"
#include "letter.h"
#include "mail_part_texts.h"
#include "mail_text.h"
#include "main_random.h"
#include "player_id.h"
#include "player_options.h"
#include "talk_object.h"
#include "villager_talk_lines.h"
#include "villager_talk_nickname.h"
#include "villager_talk_part.h"
#include "villager_talk_scene.h"
#include "villager_talk_subjects.h"
#include "villager_talk_topics.h"

static_assert(offsetof(VillagerTalk, line) == 0xb0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, on_last_message) == 0xc8, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, on_command_end) == 0xd8, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, walk) == 0xf0, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, villager) == 0x100, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, message) == 0x122, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, item) == 0x124, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, memory) == 0x12c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, partner_memory) == 0x134, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, no_memory) == 0x13c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, functions) == 0x140, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, sound) == 0x15a, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, events) == 0x16c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, villager_bits) == 0x194, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, gift) == 0x19c, "VillagerTalk layout");
static_assert(offsetof(VillagerTalk, bells) == 0x1a0, "VillagerTalk layout");

/* The villager scene object's parts used here. */
#define VILLAGER_TALK_OBJECT_POSITION 0x5c /* three words: x, y, z */
#define VILLAGER_TALK_OBJECT_MOTION 0x564  /* SceneMotion */
#define VILLAGER_TALK_OBJECT_RECORD 0x830  /* its town record (town_villager.h), or 0 */

/* The talk's message number (byte 0x1e77, func_0206844c sets it). */
#define VILLAGER_TALK_TALK_MESSAGE 0x1e77

#define VILLAGER_TALK_NO_ITEM 0xfff1
#define VILLAGER_TALK_ITEM_3818 0x3818

/* A text set of the talk lines: its texts and how many lines a group has. */
typedef struct VillagerTalkTexts {
    u32 texts;
    u8 count;
} VillagerTalkTexts;

extern const MemberPointer __ptmf_null;

/* The talk's two messages that run the members at 0xc0 and 0xc8. */
extern u8 data_021f43f8;
extern u8 data_021f43e8;

/* The event handlers (a function-local table filled once from constants, and its guard). */
extern MemberPointer data_021c2114[VILLAGER_TALK_EVENTS];
extern u32 data_021c1d04;
extern const MemberPointer data_020d8fd8; /* event 1: VillagerTalk_GiveItem */
extern const MemberPointer data_020d8fb0; /* event 7: VillagerTalk_AskBirthday */
extern const MemberPointer data_020d8ee0; /* event 12: VillagerTalk_Event12 */
extern const MemberPointer data_020d8f30; /* event 13: VillagerTalk_Event13 */
extern const MemberPointer data_020d9210; /* event 14: VillagerTalk_Event14 */
extern const MemberPointer data_020d91a0; /* event 15: VillagerTalk_Event15 */
extern const MemberPointer data_020d92c0; /* event 16: VillagerTalk_Event16 */

/* Member pointer constants the functions here store. */
extern const MemberPointer data_020d8e60; /* VillagerTalk_PutBirthday */
extern const MemberPointer data_020d93f8; /* VillagerTalk_HandBells */
extern const MemberPointer data_020d9038; /* VillagerTalk_TakeItem */
extern const MemberPointer data_020d9060; /* VillagerTalk_TakeSoldItem */
extern const MemberPointer data_020d8e18; /* VillagerTalk_NoteMemory */
extern const MemberPointer data_020d9110; /* VillagerTalk_NoteMemory */
extern const MemberPointer data_020d8e50; /* VillagerTalk_NoteMemoryAgain */
extern const MemberPointer data_020d91c8; /* func_020288bc */
extern const MemberPointer data_020d9358; /* func_020288bc */
extern const MemberPointer data_020d91d0; /* VillagerTalk_GiveItem3818 */
extern const MemberPointer data_020d9138; /* VillagerTalk_GiveItem3818 */
extern const MemberPointer data_020d9228; /* VillagerTalk_DropMusic */
extern const MemberPointer data_020d92b0; /* VillagerTalk_PlayMusic */
extern const MemberPointer data_020d8f58; /* VillagerTalk_WalkSay */
extern const MemberPointer data_020d9290; /* VillagerTalk_WalkStand */
extern const MemberPointer data_020d8f98; /* VillagerTalk_WalkStart */

/* Tables of three member pointers for 0xb0 to 0xc0. */
extern const MemberPointer data_021c2274[3];
extern const MemberPointer data_021c228c[3];
extern const MemberPointer data_021c2244[3];
extern const MemberPointer data_021c225c[3];
extern const MemberPointer data_021c222c[3];
extern const MemberPointer data_021c243c[3];
extern const MemberPointer data_021c23ac[3];

/* The text sets of the lines. */
extern const VillagerTalkTexts data_020c8be0;
extern const VillagerTalkTexts data_020c8d68;
extern const VillagerTalkTexts data_020c89f8;
extern const VillagerTalkTexts data_020c8d18;
extern const VillagerTalkTexts data_020c8b50;

/* What the choices run (their addresses go into TalkChoiceList's functions). */
extern u8 data_021c22a4[];
extern u8 data_021c22bc[];
extern u8 data_021c1e14[];
extern u8 data_021c23c4[];
extern u8 data_021c1d6c[];
/* Two ranges of messages for the choices. */
extern const u8 data_020c8928[2];
extern const u8 data_020c8924[2];

extern VillagerTown data_021e5a2c; /* the town's villagers */
extern u16 data_020c80f8;          /* the word of the villager's walk and stand */
extern u8 data_020d9f48[];
extern u8 data_020d9f5c[];
extern const u8 data_020d8d1c[];
extern u8 data_021c2604[]; /* a letter */

/* Item records: `*item` marked as had. */
extern int OSi_DoUnlockByWord__main_0203cd2c(u8 *items, u16 *item, int mode, int set);

static u8 *villager_talk_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneCommandScene *villager_talk_scene(VillagerTalk *talk)
{
    return &talk->scene;
}

static u8 *villager_talk_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_OBJECT_RECORD);
}

static SceneMotion *villager_talk_motion(const VillagerTalk *talk)
{
    return (SceneMotion *) (void *) (talk->villager + VILLAGER_TALK_OBJECT_MOTION);
}

static int villager_talk_personality(const VillagerTalk *talk)
{
    return NpcId_Personality(TownVillager_NpcId(villager_talk_record(talk)));
}

/* A member pointer whose function takes one argument, called. */
static void villager_talk_call(const MemberPointer *member, VillagerTalk *talk, void *arg)
{
    void *self = MemberPointer_Object(member, talk);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(member, self))(self, arg);
}

/* The line of the table's line function said: the three members set from `table`, the line
 * asked for (when there is a line function) and given to the talk.
 * REQUIRES: the tables hold a line function (the original then reads an unset line). */
static void villager_talk_say(VillagerTalk *talk, const MemberPointer *table)
{
    VillagerTalkLine line = {0};
    VillagerTalkScene_SetLines(talk, table);
    if (talk->line.function != 0) {
        villager_talk_call(&talk->line, talk, &line);
    }
    u8 message = line.message;
    TalkObject_SetMessage((TalkObject *) (void *) villager_talk_talk(talk), &message,
                          (const char *) (uintptr_t) ((int) line.text));
}

/* The line drawn into the talk's text and message, which `out` then names. */
static void villager_talk_draw(VillagerTalk *talk, VillagerTalkLine *out, u32 texts, int per_group, int group, int range)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, villager_talk_personality(talk),
                               (int) texts, per_group, group, range);
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* The first villager of `villager_bits` named in slot 0 and taken off. */
static void villager_talk_name_next_villager(VillagerTalk *talk)
{
    for (int i = 0; i < 8; i++) {
        if ((talk->villager_bits >> i) & 1) {
            const NpcId *npc = TownVillager_NpcId(VillagerRoster_At(&data_021e5a2c, i));
            SceneBase_PutNpcName((SceneBase *) (void *) talk, npc, 0);
            talk->villager_bits &= (u8) ~(1 << i);
            talk->villager_count--;
            break;
        }
    }
}

/* func_0201cfe4 (the scene's slot 0x14): unless an event handler takes the event
 * (VillagerTalk_RunEvent), the sound at 0x15a is played and cleared, and the member at 0xc0 is
 * run (on the message data_021f43f8) or the member at 0xc8 run once (on data_021f43e8). On the
 * message data_021f43e8, whatever the handler did, the villager then chooses its impression of
 * the player from its memory (sent to the session for the memory's place when that is not -1)
 * and notes the visitor, and the partner villager (the word at 0x644) does the same with its
 * memory. The message is the one the talk had on entry. */
void VillagerTalk_OnEvent14(VillagerTalk *talk, int event)
{
    u8 message = villager_talk_talk(talk)[VILLAGER_TALK_TALK_MESSAGE];

    if (VillagerTalk_RunEvent(talk, (unsigned int) event) == 0) {
        if (talk->sound != 0) {
            SoundSys_PlaySe(talk->sound);
            talk->sound = 0;
        }
        if (message == data_021f43f8) {
            if (talk->on_each_message.function != 0) {
                villager_talk_call(&talk->on_each_message, talk, (void *) (intptr_t) event);
            }
        } else if (message == data_021f43e8) {
            if (talk->on_last_message.function != 0) {
                villager_talk_call(&talk->on_last_message, talk, (void *) (intptr_t) event);
                talk->on_last_message = __ptmf_null;
            }
        }
    }

    if (message != data_021f43e8) {
        return;
    }
    if (talk->memory != NULL) {
        VillagerImpression_Choose(villager_talk_record(talk), (s8 *) talk->memory, NULL);
        if (talk->memory_index != -1) {
            int impression = VillagerMemoryEntry_Impression((VillagerMemory *) (void *) talk->memory);
            SessionVillager_SendEntryByte6D(villager_talk_record(talk), talk->memory_index, impression);
        }
        if (villager_talk_record(talk) != NULL) {
            VillagerEntry_NoteVisitor(villager_talk_record(talk), NULL);
        }
    }
    if (talk->partner_memory != NULL) {
        if (VillagerSceneObject_Word644((u32 *) (void *) talk->villager) != 0) {
            u8 *partner = (u8 *) (uintptr_t) VillagerSceneObject_Word644((u32 *) (void *) talk->villager);
            u8 *record = *(u8 **) (void *) (partner + VILLAGER_TALK_OBJECT_RECORD);
            VillagerImpression_Choose(record, (s8 *) talk->partner_memory, NULL);
        }
    }
}
CLEAN_AS(func_0201cfe4, VillagerTalk_OnEvent14)

/* func_0201d140 (the scene's slot 0x10): unless an event handler takes the event, the member at
 * 0xb8 is run once with `arg`. */
void VillagerTalk_OnEvent10(VillagerTalk *talk, void *arg)
{
    if (VillagerTalk_RunEvent(talk, (unsigned int) (uintptr_t) arg) == 0) {
        if (talk->on_event_10.function != 0) {
            villager_talk_call(&talk->on_event_10, talk, arg);
            talk->on_event_10 = __ptmf_null;
        }
    }
}
CLEAN_AS(func_0201d140, VillagerTalk_OnEvent10)

/* func_0201d198: the handler of `event` run, its answer given; 0 for an event without one.
 * The handlers are a table filled the first time (bit 0 of the guard says it was): 1, 7 and
 * 12 to 16 have one. */
int VillagerTalk_RunEvent(VillagerTalk *talk, unsigned int event)
{
    static const MemberPointer *const constants[VILLAGER_TALK_EVENTS] = {
        &__ptmf_null,   &data_020d8fd8, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
        &__ptmf_null,   &data_020d8fb0, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
        &data_020d8ee0, &data_020d8f30, &data_020d9210, &data_020d91a0, &data_020d92c0,
    };
    MemberTable_InitOnce(&data_021c1d04, data_021c2114, constants, VILLAGER_TALK_EVENTS);

    if (event < VILLAGER_TALK_EVENTS && data_021c2114[event].function != 0) {
        return MemberPointer_CallInt(&data_021c2114[event], talk);
    }
    return 0;
}
CLEAN_AS(func_0201d198, VillagerTalk_RunEvent)

/* The member of event 12 + `index`, run when set; its answer, else 0. */
static int villager_talk_member_event(VillagerTalk *talk, int index)
{
    if (talk->events[index].function != 0) {
        return MemberPointer_CallInt(&talk->events[index], talk);
    }
    return 0;
}

/* func_0201d294 */
int VillagerTalk_Event16(VillagerTalk *talk)
{
    return villager_talk_member_event(talk, 4);
}
CLEAN_AS(func_0201d294, VillagerTalk_Event16)

/* func_0201d2c8 */
int VillagerTalk_Event15(VillagerTalk *talk)
{
    return villager_talk_member_event(talk, 3);
}
CLEAN_AS(func_0201d2c8, VillagerTalk_Event15)

/* func_0201d2fc */
int VillagerTalk_Event14(VillagerTalk *talk)
{
    return villager_talk_member_event(talk, 2);
}
CLEAN_AS(func_0201d2fc, VillagerTalk_Event14)

/* func_0201d330 */
int VillagerTalk_Event13(VillagerTalk *talk)
{
    return villager_talk_member_event(talk, 1);
}
CLEAN_AS(func_0201d330, VillagerTalk_Event13)

/* func_0201d364 */
int VillagerTalk_Event12(VillagerTalk *talk)
{
    return villager_talk_member_event(talk, 0);
}
CLEAN_AS(func_0201d364, VillagerTalk_Event12)

/* func_0201d398: the player's birthday into the talk: the month into slot 0, the day into
 * slot 1 and the star sign into slot 2. QUIRK: the size given with the sign is the address
 * data_020d9f48, as the original passes it. */
void VillagerTalk_PutBirthday(VillagerTalk *talk)
{
    u8 *birthday = PlayerRecord_Birthday(PlayerRecords_Current());
    u8 sign = (u8) Lookups_StarSign(birthday[1], birthday[0]);
    SceneBase *scene = (SceneBase *) (void *) talk;
    SceneBase_PutNumberAlt(scene, (void *) (uintptr_t) birthday[1], 0);
    SceneBase_PutNumber(scene, birthday[0], 1);
    u8 bytes[2] = {sign, 0};
    SceneBase_PutBytes(scene, 2, bytes, (int) (uintptr_t) data_020d9f48, &bytes[1]);
}
CLEAN_AS(func_0201d398, VillagerTalk_PutBirthday)

/* func_0201d3ec (event 7): the screen in mode 0x32 opened (the birthday's), then
 * VillagerTalk_PutBirthday. */
int VillagerTalk_AskBirthday(VillagerTalk *talk)
{
    SceneCommand_SetScreenMode(villager_talk_scene(talk), 0x32, 0);
    SceneCommand_RequestScreen(villager_talk_scene(talk), SCENE_COMMAND_SCREEN_MODE);
    VillagerTalkScene_SetCommandEnd(talk, data_020d8e60);
    return 1;
}
CLEAN_AS(func_0201d3ec, VillagerTalk_AskBirthday)

/* func_0201d418 */
int VillagerTalk_ClearOption(void)
{
    PlayerOptions_ChangeFlag(0);
    PlayerOptions_Store();
    return 1;
}
CLEAN_AS(func_0201d418, VillagerTalk_ClearOption)

/* func_0201d430 */
int VillagerTalk_SetOption(void)
{
    PlayerOptions_ChangeFlag(1);
    PlayerOptions_Store();
    return 1;
}
CLEAN_AS(func_0201d430, VillagerTalk_SetOption)

/* The gift put into the player's first free pocket and marked as had; 0 without a free one. */
static int villager_talk_give(u16 *item)
{
    u8 *record = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    int slot = PlayerPockets_FreeSlot(pockets);
    if (slot < 0) {
        return 0;
    }
    PlayerPockets_SetSlot(pockets, item, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(record), item, 0, 1);
    return 1;
}

/* func_0201d448: the gift at 0x19c given to the player (into a free pocket, marked as had),
 * taken off the villager's items when it comes from them, and shown (motion 13). 0 when there
 * is no gift or no free pocket. */
int VillagerTalk_GiveGift(VillagerTalk *talk)
{
    if (talk->gift == VILLAGER_TALK_NO_ITEM) {
        return 0;
    }
    if (!villager_talk_give(&talk->gift)) {
        return 0;
    }
    if (talk->gift_from_items == 1) {
        VillagerItems_Remove(villager_talk_record(talk), &talk->gift);
    }
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &talk->gift, 0, 5, 0);
    return 1;
}
CLEAN_AS(func_0201d448, VillagerTalk_GiveGift)

/* func_0201d4d8: the item at 0x124 made the bag of the bells at 0x1a0 and handed over (motion
 * 14); the talk held. */
void VillagerTalk_HandBells(VillagerTalk *talk)
{
    u16 item;
    VillagerTalkPart_BellBag(&item, talk->bells);
    talk->item = item;
    SceneCommand_RequestMotion14(villager_talk_scene(talk), &talk->item, 0, 5, 0);
    TalkObject_Hold((TalkObject *) (void *) villager_talk_talk(talk));
}
CLEAN_AS(func_0201d4d8, VillagerTalk_HandBells)

/* func_0201d514: with a price at 0x1a0 and a gift, the gift given to the player as in
 * VillagerTalk_GiveGift, the price taken from the player's bells, the gift shown, then
 * VillagerTalk_HandBells. 0 when it is not. */
int VillagerTalk_SellGift(VillagerTalk *talk)
{
    if (talk->bells <= 0 || talk->gift == VILLAGER_TALK_NO_ITEM) {
        return 0;
    }
    u8 *record = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    int slot = PlayerPockets_FreeSlot(pockets);
    if (slot < 0) {
        return 0;
    }
    PlayerPockets_SetSlot(pockets, &talk->gift, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(record), &talk->gift, 0, 1);
    if (talk->gift_from_items == 1) {
        VillagerItems_Remove(villager_talk_record(talk), &talk->gift);
    }
    PlayerPockets_AddBells(pockets, -talk->bells, 1);
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &talk->gift, 0, 5, 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d93f8);
    return 1;
}
CLEAN_AS(func_0201d514, VillagerTalk_SellGift)

/* The item at 0x124 taken (motion 14), added to the villager's items and to its memory of the
 * player, when it has a record and the item is set; the talk held. The record is read before
 * the motion. */
static void villager_talk_take_item(VillagerTalk *talk)
{
    u8 *record = villager_talk_record(talk);
    SceneCommand_RequestMotion14(villager_talk_scene(talk), &talk->item, 0, 5, 0);
    if (record != NULL && talk->item != VILLAGER_TALK_NO_ITEM) {
        VillagerItems_Add(record, &talk->item);
        if (talk->memory != NULL) {
            VillagerMemoryEntry_SetItem((VillagerMemory *) (void *) talk->memory, &talk->item);
        }
    }
    TalkObject_Hold((TalkObject *) (void *) villager_talk_talk(talk));
}

/* func_0201d5cc */
void VillagerTalk_TakeItem(VillagerTalk *talk)
{
    villager_talk_take_item(talk);
}
CLEAN_AS(func_0201d5cc, VillagerTalk_TakeItem)

/* func_0201d630: a trade: the gift at 0x19c put into the pocket of the player's item at 0x124
 * and marked as had, shown (motion 13), then VillagerTalk_TakeItem. 0 when either is unset or
 * the player does not have the item. */
int VillagerTalk_TradeItem(VillagerTalk *talk)
{
    if (talk->gift == VILLAGER_TALK_NO_ITEM || talk->item == VILLAGER_TALK_NO_ITEM) {
        return 0;
    }
    u8 *record = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    int slot = CurrentPockets_FindItem(&talk->item);
    if (slot < 0) {
        return 0;
    }
    PlayerPockets_SetSlot(pockets, &talk->gift, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(record), &talk->gift, 0, 1);
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &talk->gift, 0, 5, 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d9038);
    return 1;
}
CLEAN_AS(func_0201d630, VillagerTalk_TradeItem)

/* func_0201d6b8: as VillagerTalk_TakeItem. */
void VillagerTalk_TakeSoldItem(VillagerTalk *talk)
{
    villager_talk_take_item(talk);
}
CLEAN_AS(func_0201d6b8, VillagerTalk_TakeSoldItem)

/* func_0201d71c: the villager buys the player's item at 0x124 for the bells at 0x1a0: its
 * pocket emptied, the bells added, the bag of the bells made the gift at 0x19c and shown
 * (motion 13), then VillagerTalk_TakeSoldItem. 0 without a price, an item or the item in the
 * pockets. */
int VillagerTalk_BuyItem(VillagerTalk *talk)
{
    if (talk->bells <= 0 || talk->item == VILLAGER_TALK_NO_ITEM) {
        return 0;
    }
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
    int slot = CurrentPockets_FindItem(&talk->item);
    if (slot < 0) {
        return 0;
    }
    u16 none = VILLAGER_TALK_NO_ITEM;
    PlayerPockets_SetSlot(pockets, &none, slot, 0);
    PlayerPockets_AddBells(pockets, talk->bells, 1);
    u16 bag;
    VillagerTalkPart_BellBag(&bag, talk->bells);
    talk->gift = bag;
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &talk->gift, 0, 5, 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d9060);
    return 1;
}
CLEAN_AS(func_0201d71c, VillagerTalk_BuyItem)

/* func_0201d7b8: with the address at 0x138 set, the sound with the values at its 0x74; whether
 * it was. */
int VillagerTalk_PlaySound138(VillagerTalk *talk)
{
    u32 record = talk->record_138;
    if (record == 0) {
        return 0;
    }
    SceneCommand_RequestSoundWith(villager_talk_scene(talk), (const u32 *) (uintptr_t) (record + 0x74));
    return 1;
}
CLEAN_AS(func_0201d7b8, VillagerTalk_PlaySound138)

/* func_0201d7dc: a letter shown on the screen of group 12: with the address at 0x138 set, the
 * villager's letter (TownVillager_Letter); else one written into data_021c2604 from three text
 * parts loaded for a letter number the villager's memory of the player draws (0 without a
 * memory), signed with the villager's name. */
int VillagerTalk_ShowLetter(VillagerTalk *talk)
{
    u8 *letter;
    if (talk->record_138 != 0) {
        letter = (u8 *) TownVillager_Letter(villager_talk_record(talk));
    } else {
        u32 part1[0x28 / 4];
        u32 part2[0x98 / 4];
        u32 part3[0x34 / 4];
        u32 name[0x20 / 4];
        int result;

        NpcId *npc = TownVillager_NpcId(villager_talk_record(talk));
        MailSuperText_Construct((MailSuperText *) part1);
        MailMsgText_Construct((MailMsgText *) part2);
        MailPsText_Construct((MailPsText *) part3);
        int number = 0;
        letter = data_021c2604;
        if (talk->memory != NULL) {
            number = VillagerMemoryEntry_DrawUnused((VillagerMemory *) (void *) talk->memory);
        }
        PlayerIdText_Construct((PlayerIdText *) name);
        NpcId_FormatName(npc, (char *) name);
        MailText_SetParticleName(name);
        PlayerIdText_Destruct((PlayerIdText *) name);
        u8 number_byte = (u8) number;
        MailText_LoadMail(part1, part2, part3, (s32 *) &result, &number_byte, (const char *) (uintptr_t) data_020d9f5c);
        Letter_SetBetweenVillagers((Letter *) (void *) letter, (void *) (uintptr_t) part1, (void *) (uintptr_t) part2,
                                   (void *) (uintptr_t) part3, result, data_020d8d1c, (const NpcId *) (uintptr_t) npc,
                                   (const NpcId *) (uintptr_t) npc);
        MailPsText_Destruct((MailPsText *) part3);
        MailMsgText_Destruct((MailMsgText *) part2);
        MailSuperText_Destruct((MailSuperText *) part1);
    }
    SceneCommand_SetScreenPointer(villager_talk_scene(talk), (int) (uintptr_t) letter, 0);
    SceneCommand_RequestScreen(villager_talk_scene(talk), SCENE_COMMAND_SCREEN_GROUP_12);
    return 1;
}
CLEAN_AS(func_0201d7dc, VillagerTalk_ShowLetter)

/* func_0201d8c0 (event 1): the gift at 0x19c, or else the item at 0x124, given to the player
 * (into a free pocket, marked as had) and shown (motion 13); 0 without either or a free
 * pocket. The item given is a copy on the stack. */
int VillagerTalk_GiveItem(VillagerTalk *talk)
{
    u16 item = talk->gift != VILLAGER_TALK_NO_ITEM ? talk->gift : talk->item;
    if (item == VILLAGER_TALK_NO_ITEM) {
        return 0;
    }
    u8 *record = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    int slot = PlayerPockets_FreeSlot(pockets);
    if (slot == -1) {
        return 0;
    }
    PlayerPockets_SetSlot(pockets, &item, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(record), &item, 0, 1);
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &item, 0, 5, 0);
    return 1;
}
CLEAN_AS(func_0201d8c0, VillagerTalk_GiveItem)

/* func_0201d940: a line of the set at 0x020c8be0; VillagerTalk_NoteMemory runs at the last
 * message. */
void VillagerTalk_Line8be0(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8be0.texts, data_020c8be0.count, 0, 0);
    talk->on_last_message = data_020d8e18;
}
CLEAN_AS(func_0201d940, VillagerTalk_Line8be0)

/* func_0201d9b8: the villager notes the player in its memory (func_0202d8f8). */
void VillagerTalk_NoteMemory(VillagerTalk *talk, void *unused)
{
    (void) unused;
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, villager_talk_record(talk), 0);
}
CLEAN_AS(func_0201d9b8, VillagerTalk_NoteMemory)

/* func_0201d9ec: a line of the set at 0x020c8d68; VillagerTalk_NoteMemory at the last
 * message. */
void VillagerTalk_Line8d68(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d68.texts, data_020c8d68.count, 0, 0);
    talk->on_last_message = data_020d9110;
}
CLEAN_AS(func_0201d9ec, VillagerTalk_Line8d68)

/* func_0201da64: as VillagerTalk_NoteMemory. */
void VillagerTalk_NoteMemoryAgain(VillagerTalk *talk, void *unused)
{
    (void) unused;
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, villager_talk_record(talk), 0);
}
CLEAN_AS(func_0201da64, VillagerTalk_NoteMemoryAgain)

/* func_0201da98: a line of the set at 0x020c89f8; without a memory of the player the memory is
 * left alone (byte 0x13c); VillagerTalk_NoteMemoryAgain at the last message. */
void VillagerTalk_Line89f8(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c89f8.texts, data_020c89f8.count, 0, 0);
    if (talk->memory == NULL) {
        talk->no_memory = 1;
    }
    talk->on_last_message = data_020d8e50;
}
CLEAN_AS(func_0201da98, VillagerTalk_Line89f8)

/* func_0201db24: a line of group 4 of the set at 0x020c8d18; its message. */
u8 VillagerTalk_Line8d18Group4(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 4, data_020c8d18.count);
    return talk->message;
}
CLEAN_AS(func_0201db24, VillagerTalk_Line8d18Group4)

/* func_0201db88: group 3 of the set at 0x020c8d18. */
void VillagerTalk_Line8d18Group3(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 3, data_020c8d18.count);
}
CLEAN_AS(func_0201db88, VillagerTalk_Line8d18Group3)

/* func_0201dbec: two choices offered (messages 0x32 and 0x33, running data_021c22a4 and
 * data_021c22bc, no cancel choice) with the reply func_020288bc; the talk's byte 0x18 set. */
void VillagerTalk_OfferChoices32(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x32, 0x32, (int) (uintptr_t) data_021c22a4);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x33, 0x33, (int) (uintptr_t) data_021c22bc);
    list.count = 2;
    list.cancel = -1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    VillagerTalkScene_SetReply(talk, data_020d91c8);
    TalkObject_OpenChoices((TalkObject *) (void *) villager_talk_talk(talk), 1);
}
CLEAN_AS(func_0201dbec, VillagerTalk_OfferChoices32)

/* func_0201dc58: group 2 of the set at 0x020c8d18. */
void VillagerTalk_Line8d18Group2(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 2, data_020c8d18.count);
}
CLEAN_AS(func_0201dc58, VillagerTalk_Line8d18Group2)

/* func_0201dcbc: the item 0x3818 shown (motion 13, a copy on the stack), then
 * VillagerTalk_GiveItem3818. */
void VillagerTalk_ShowItem3818(VillagerTalk *talk)
{
    u16 item = VILLAGER_TALK_ITEM_3818;
    SceneCommand_RequestMotion13(villager_talk_scene(talk), &item, 0, 5, 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d91d0);
}
CLEAN_AS(func_0201dcbc, VillagerTalk_ShowItem3818)

/* func_0201dcf0: group 7 of the set at 0x020c8d18. */
void VillagerTalk_Line8d18Group7(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 7, data_020c8d18.count);
}
CLEAN_AS(func_0201dcf0, VillagerTalk_Line8d18Group7)

/* func_0201dd54: the line of the table at data_021c2274 said. */
void VillagerTalk_Say2274(VillagerTalk *talk)
{
    villager_talk_say(talk, data_021c2274);
}
CLEAN_AS(func_0201dd54, VillagerTalk_Say2274)

/* func_0201dda8: group 6 of the set at 0x020c8d18, and the next villager of 0x194 named. */
void VillagerTalk_Line8d18Group6(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 6, data_020c8d18.count);
    villager_talk_name_next_villager(talk);
}
CLEAN_AS(func_0201dda8, VillagerTalk_Line8d18Group6)

/* func_0201de64: group 5 of the set at 0x020c8d18, and the next villager of 0x194 named. */
void VillagerTalk_Line8d18Group5(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 5, data_020c8d18.count);
    villager_talk_name_next_villager(talk);
}
CLEAN_AS(func_0201de64, VillagerTalk_Line8d18Group5)

/* func_0201df20: the item 0x3818 given to the player (CurrentPockets_Give, a copy on the
 * stack), the player's birthday year set to the clock's year, and the line of the table at
 * data_021c228c said. */
void VillagerTalk_GiveItem3818(VillagerTalk *talk)
{
    u16 item = VILLAGER_TALK_ITEM_3818;
    CurrentPockets_Give(&item, 0);
    u8 *record = PlayerRecords_Current();
    PlayerRecord_SetBirthdayYear(record, (u8) Clock_Year());
    villager_talk_say(talk, data_021c228c);
}
CLEAN_AS(func_0201df20, VillagerTalk_GiveItem3818)

/* func_0201dfa0: by the count at 0x198: two or more, the line of the table at data_021c2244;
 * one, that of data_021c225c; none, the item 0x3818 shown (motion 13, a copy on the stack)
 * and then VillagerTalk_GiveItem3818. */
void VillagerTalk_SayByVillagerCount(VillagerTalk *talk)
{
    int count = talk->villager_count;
    if (count >= 2) {
        villager_talk_say(talk, data_021c2244);
    } else if (count == 1) {
        villager_talk_say(talk, data_021c225c);
    } else {
        u16 item = VILLAGER_TALK_ITEM_3818;
        SceneCommand_RequestMotion13(villager_talk_scene(talk), &item, 0, 5, 0);
        VillagerTalkScene_SetCommandEnd(talk, data_020d9138);
    }
}
CLEAN_AS(func_0201dfa0, VillagerTalk_SayByVillagerCount)

/* func_0201e074: group 1 of the set at 0x020c8d18; then the town's other villagers fond of the
 * player (fondness 0x40 or more in their memory of the player) are counted at 0x198 with
 * their places as bits at 0x194, when there is a player (set up, func_020951bc) and the
 * villager is valid; a count of one is dropped to none. VillagerTalk_DropMusic at 0xf8.
 * The other villagers are those whose NpcId differs from this one's in its first halfword,
 * the 12 bytes after it or its number. (The original also tests the address of the town's
 * villagers for 0, which it never is.) */
void VillagerTalk_Line8d18Group1(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 1, data_020c8d18.count);

    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    NpcId *self = NULL;
    if (villager_talk_record(talk) != NULL) {
        self = TownVillager_NpcId(villager_talk_record(talk));
    }
    talk->villager_bits = 0;
    talk->villager_count = 0;

    if (player != NULL && PlayerId_IsSet(player) != 0 && self != NULL && NpcId_IsValid(self) != 0) {
        for (int i = 0; i < 8; i++) {
            u8 *other = VillagerRoster_At(&data_021e5a2c, i);
            if (other == NULL || NpcId_IsValid(TownVillager_NpcId(other)) == 0) {
                continue;
            }
            const NpcId *npc = TownVillager_NpcId(other);
            if (npc->head.id == self->head.id && memcmp(npc->head.data, self->head.data, sizeof npc->head.data) == 0 &&
                npc->number == self->number) {
                continue;
            }
            VillagerMemory *memory = VillagerMemory_Of(other, player);
            if (memory == NULL || VillagerMemoryEntry_Fondness(memory) < 0x40) {
                continue;
            }
            talk->villager_bits = (u8) (talk->villager_bits | (1 << i));
            talk->villager_count++;
        }
    }
    if (talk->villager_count == 1) {
        talk->villager_bits = 0;
        talk->villager_count = 0;
    }
    talk->music = data_020d9228;
}
CLEAN_AS(func_0201e074, VillagerTalk_Line8d18Group1)

/* func_0201e1d8: the music 0x2f dropped, and the value 0x60 for 0x79 frames at priority 12. */
void VillagerTalk_DropMusic(void)
{
    Music_DropMusic(0x2f);
    Music_AddValue(0xc, 0x60, 0x79);
}
CLEAN_AS(func_0201e1d8, VillagerTalk_DropMusic)

/* func_0201e1f4: priority 18 dropped, the value 0 for 11 frames at priority 12, and the music
 * 0x2f at priority 13. */
void VillagerTalk_PlayMusic(void)
{
    Music_DropPriority(0x12);
    Music_AddValue(0xc, 0, 0xb);
    Music_Add(0xd, 0x2f, 0x7f, 1);
}
CLEAN_AS(func_0201e1f4, VillagerTalk_PlayMusic)

/* func_0201e21c (a walk step): once the villager stands (motion kind 0, done), an effect at a
 * point 0x2000 above it, the line of the table at data_021c222c said, the next line asked for
 * and the walk over. */
void VillagerTalk_WalkSay(VillagerTalk *talk)
{
    SceneMotion *motion = villager_talk_motion(talk);
    if (SceneMotion_Kind(motion) != 0 || SceneMotion_IsDone(motion) == 0) {
        return;
    }
    const s32 *position = (const s32 *) (const void *) (talk->villager + VILLAGER_TALK_OBJECT_POSITION);
    s32 point[3] = {position[0], position[1] + 0x2000, position[2]};
    CameraControl_FocusOn((const Vec3 *) point);
    villager_talk_say(talk, data_021c222c);
    SceneCommand_RequestNextLine(villager_talk_scene(talk));
    talk->walk = __ptmf_null;
}
CLEAN_AS(func_0201e21c, VillagerTalk_WalkSay)

/* func_0201e2d8 (a walk step): once the walk (motion kind 2) is done, the villager stands
 * (priority 2), then VillagerTalk_WalkSay. */
void VillagerTalk_WalkStand(VillagerTalk *talk)
{
    SceneMotion *motion = villager_talk_motion(talk);
    if (SceneMotion_Kind(motion) != 2 || SceneMotion_IsDone(motion) == 0) {
        return;
    }
    SceneMotion_RequestStand(motion, 2, data_020c80f8);
    talk->walk = data_020d8f58;
}
CLEAN_AS(func_0201e2d8, VillagerTalk_WalkStand)

/* func_0201e334: the villager walks (motion kind 2, priority 2) with the point 0x1e00 along x
 * and -0x2800 along z from it, then VillagerTalk_WalkStand. */
void VillagerTalk_WalkStart(VillagerTalk *talk)
{
    const s32 *position = (const s32 *) (const void *) (talk->villager + VILLAGER_TALK_OBJECT_POSITION);
    s32 x = position[0] + 0x1e00;
    s32 z = position[2] - 0x2800;
    SceneMotion_Request(villager_talk_motion(talk), 2, 2, x, z, 0, 0, 0, 0, data_020c80f8, 0);
    talk->walk = data_020d9290;
}
CLEAN_AS(func_0201e334, VillagerTalk_WalkStart)

/* func_0201e3b0: the talk mode 0, then VillagerTalk_WalkStart. */
void VillagerTalk_StartWalk(VillagerTalk *talk)
{
    SceneCommand_RequestTalkMode(villager_talk_scene(talk), 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d8f98);
}
CLEAN_AS(func_0201e3b0, VillagerTalk_StartWalk)

/* func_0201e3d0: group 0 of the set at 0x020c8d18, the player noted in the villager's memory,
 * and VillagerTalk_PlayMusic at 0xf8. */
void VillagerTalk_Line8d18Group0(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8d18.texts, 1, 0, data_020c8d18.count);
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, villager_talk_record(talk), 0);
    talk->music = data_020d92b0;
}
CLEAN_AS(func_0201e3d0, VillagerTalk_Line8d18Group0)

/* The line made into the text and message (by func_02021118 and one of the line makers)
 * given in `out`; the members at 0xb0 cleared. */
static void villager_talk_give_made_line(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
    VillagerTalkScene_ClearLines(talk);
}

/* func_0201e46c */
void VillagerTalk_Line213c(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkTopics_FillSlots(talk);
    VillagerTalkTopics_SayPair(talk);
    villager_talk_give_made_line(talk, out);
}
CLEAN_AS(func_0201e46c, VillagerTalk_Line213c)

/* func_0201e4a0 */
void VillagerTalk_Line2034(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkTopics_FillSlots(talk);
    VillagerTalkTopics_SayByAcre(talk);
    villager_talk_give_made_line(talk, out);
}
CLEAN_AS(func_0201e4a0, VillagerTalk_Line2034)

/* func_0201e4d4 */
void VillagerTalk_Line2454(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkTopics_FillSlots(talk);
    VillagerTalkSubjects_SayLast(talk);
    villager_talk_give_made_line(talk, out);
}
CLEAN_AS(func_0201e4d4, VillagerTalk_Line2454)

/* func_0201e508 */
void VillagerTalk_OfferChoices20360(VillagerTalk *talk)
{
    VillagerTalk_OfferChoices1e14(talk);
}
CLEAN_AS(func_0201e508, VillagerTalk_OfferChoices20360)

/* func_0201e510 */
void VillagerTalk_Line2a5e8(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkNickname_LineConnect(talk, out);
}
CLEAN_AS(func_0201e510, VillagerTalk_Line2a5e8)

/* func_0201e518: the line of the table at data_021c243c said. */
void VillagerTalk_Say243c(VillagerTalk *talk)
{
    villager_talk_say(talk, data_021c243c);
}
CLEAN_AS(func_0201e518, VillagerTalk_Say243c)

/* func_0201e56c: group 18 of the set at 0x020c8b50, the random part below 3. */
void VillagerTalk_Line8b50Group18(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8b50.texts, 1, 0x12, 3);
}
CLEAN_AS(func_0201e56c, VillagerTalk_Line8b50Group18)

/* func_0201e5d0: group 16 of the set at 0x020c8b50. */
void VillagerTalk_Line8b50Group16(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8b50.texts, 1, 0x10, data_020c8b50.count);
}
CLEAN_AS(func_0201e5d0, VillagerTalk_Line8b50Group16)

/* func_0201e634: group 14 of the set at 0x020c8b50; its message. */
u8 VillagerTalk_Line8b50Group14(VillagerTalk *talk, VillagerTalkLine *out)
{
    villager_talk_draw(talk, out, data_020c8b50.texts, 1, 0xe, data_020c8b50.count);
    return talk->message;
}
CLEAN_AS(func_0201e634, VillagerTalk_Line8b50Group14)

/* func_0201e698: a line of the set at 0x020c8b50 by the clock: group 6 before 23:30, 8 before
 * 23:55, 10 before 23:59 and 12 from then. */
void VillagerTalk_LineNewYearsEve(VillagerTalk *talk, VillagerTalkLine *out)
{
    DateTime now = {0};
    DateTime_Now(&now);
    int group;
    if (now.hour < 23 || (now.hour == 23 && now.minute < 30)) {
        group = 6;
    } else if (now.minute < 55) {
        group = 8;
    } else if (now.minute < 59) {
        group = 10;
    } else {
        group = 12;
    }
    villager_talk_draw(talk, out, data_020c8b50.texts, 1, group, data_020c8b50.count);
}
CLEAN_AS(func_0201e698, VillagerTalk_LineNewYearsEve)

/* func_0201e734: a line of the set at 0x020c8b50 by the hour: group 0 before 12, 2 before 17,
 * 4 from then. */
void VillagerTalk_LineTimeOfDay(VillagerTalk *talk, VillagerTalkLine *out)
{
    DateTime now = {0};
    DateTime_Now(&now);
    int group;
    if (now.hour < 12) {
        group = 0;
    } else if (now.hour < 17) {
        group = 2;
    } else {
        group = 4;
    }
    villager_talk_draw(talk, out, data_020c8b50.texts, 1, group, data_020c8b50.count);
}
CLEAN_AS(func_0201e734, VillagerTalk_LineTimeOfDay)

/* func_0201e7b8: two choices offered with cancel choice 1: the messages of data_020c8928
 * running data_021c1e14 or data_021c23c4 (by an even random number below 10), and those of
 * data_020c8924 running data_021c1d6c; the reply func_020288bc; the talk's byte 0x18 set. The
 * list is not cleared first. */
void VillagerTalk_OfferChoicesRandom(VillagerTalk *talk)
{
    TalkChoiceList list;
    u8 *first = data_021c1e14;
    if ((MainRandom_Below(10) & 1) == 0) {
        first = data_021c23c4;
    }
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 0, data_020c8928, (u32) (uintptr_t) first);
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 1, data_020c8924, (u32) (uintptr_t) data_021c1d6c);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    VillagerTalkScene_SetReply(talk, data_020d9358);
    TalkObject_OpenChoices((TalkObject *) (void *) villager_talk_talk(talk), 1);
}
CLEAN_AS(func_0201e7b8, VillagerTalk_OfferChoicesRandom)

/* func_0201e834 */
void VillagerTalk_Line2a5e8Again(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkNickname_LineConnect(talk, out);
}
CLEAN_AS(func_0201e834, VillagerTalk_Line2a5e8Again)

/* func_0201e83c: the line of the table at data_021c23ac said. */
void VillagerTalk_Say23ac(VillagerTalk *talk)
{
    villager_talk_say(talk, data_021c23ac);
}
CLEAN_AS(func_0201e83c, VillagerTalk_Say23ac)
