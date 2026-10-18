/* More members of the town villagers' talk scenes (villager_talk_steps.h). */
#include "villager_talk_steps.h"

#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "group_params.h"
#include "item_object.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_command.h"
#include "session_villager.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_entry.h"
#include "villager_kinds.h"
#include "villager_memory_entry.h"
#include "villager_mail.h"
#include "villager_move.h"
#include "villager_move_record.h"
#include "villager_object.h"
#include "villager_part_handover.h"
#include "villager_state.h"
#include "villager_status.h"
#include "villager_town.h"
#include "global_021cfc98.h"
#include "item_lists.h"
#include "talk_item_draw.h"
#include "talk_object.h"
#include "villager_talk_offers.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h), or 0. */
#define VILLAGER_TALK_STEPS_OBJECT_RECORD 0x830
/* The talk's villager object (villager_object.h), at 0x164. */
#define VILLAGER_TALK_STEPS_VILLAGER_OBJECT 0x164
/* The record VillagerPartHandover at 0xa4 of a player's villager part, and its date. */
#define VILLAGER_TALK_STEPS_HANDOVER 0xa4
#define VILLAGER_TALK_STEPS_HANDOVER_DATE 0xc0

#define VILLAGER_TALK_STEPS_NO_ITEM 0xfff1
/* Kept time within this many minutes of now. */
#define VILLAGER_TALK_STEPS_RECENT_MINUTES 30
/* Before this hour of the kept time. */
#define VILLAGER_TALK_STEPS_EARLY_HOUR 6
/* The types of the talk's object at 0x154 (item_object.h). */
#define VILLAGER_TALK_STEPS_TYPE_14 0xe
#define VILLAGER_TALK_STEPS_TYPE_16 0x10
#define VILLAGER_TALK_STEPS_TYPE_17 0x11
/* The sound effects the talk plays (0x15a). */
#define VILLAGER_TALK_STEPS_SOUND_5E 0x5e
#define VILLAGER_TALK_STEPS_SOUND_5F 0x5f

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkStepsTexts {
    u32 texts;
    u8 count;
} VillagerTalkStepsTexts;

/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destructs it. */
typedef struct VillagerTalkStepsItemList {
    u32 kind;
    u32 group;
} VillagerTalkStepsItemList;

/* The text sets. */
extern const VillagerTalkStepsTexts data_020c8a28;
extern const VillagerTalkStepsTexts data_020c8e08;
extern const VillagerTalkStepsTexts data_020c8e18;
extern const VillagerTalkStepsTexts data_020c8e30;
extern const VillagerTalkStepsTexts data_020c8bb0;
extern const VillagerTalkStepsTexts data_020c8bc0;
extern const VillagerTalkStepsTexts data_020c8bd0;
extern const VillagerTalkStepsTexts data_020c89c0;
extern const VillagerTalkStepsTexts data_020c89b8;
extern const VillagerTalkStepsTexts data_020c89a8;
extern const VillagerTalkStepsTexts data_020c8aa8;
extern const VillagerTalkStepsTexts data_020c89e0;
extern const VillagerTalkStepsTexts data_020c8bf8;
extern const VillagerTalkStepsTexts data_020c8c00;
extern const VillagerTalkStepsTexts data_020c8c08;
extern const VillagerTalkStepsTexts data_020c8c18;
extern const VillagerTalkStepsTexts data_020c8cd8;

/* The resource name of the lines by the object's type (Personality_FormatResourceName), by
 * address. */
extern u32 data_020c8c20;

/* Tables of three member pointers for 0xb0 to 0xc0 (func_0202da88). */
extern const MemberPointer data_021c301c[3];
extern const MemberPointer data_021c304c[3];
extern const MemberPointer data_021c3034[3];
extern const MemberPointer data_021c3064[3];
extern const MemberPointer data_021c2f74[3];
extern const MemberPointer data_021c2fd4[3];
extern const MemberPointer data_021c2fa4[3];
extern const MemberPointer data_021c2f8c[3];
extern const MemberPointer data_021c2f14[3];
extern const MemberPointer data_021c2efc[3];
extern const MemberPointer data_021c2adc[3];

/* Member pointer constants the functions here store or hand on. */
extern const MemberPointer data_020d8e90;
extern const MemberPointer data_020d9090;
extern const MemberPointer data_020d8ea0;
extern const MemberPointer data_020d8e58;
extern const MemberPointer data_020d94d0;
extern const MemberPointer data_020d90e0;
extern const MemberPointer data_020d9100;
extern const MemberPointer data_020d8ee8;
extern const MemberPointer data_020d9118;

/* What the choices of VillagerTalkSteps_OfferChoices1f run (their addresses go into
 * TalkChoiceList's functions). */
extern u8 data_021c3004[];
extern u8 data_021c2a1c[];

extern VillagerTown data_021e5a2c; /* the town's villagers */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* Item records: `*item` marked as had. */
extern int OSi_DoUnlockByWord__main_0203cd2c(u8 *items, u16 *item, int mode, int set);
/* The pocket predicate VillagerTalkSteps_AskPocket1561 hands the scene (the game's). */
extern int func_020240a8(u16 *item, int state);

static u8 *steps_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *steps_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *steps_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_STEPS_OBJECT_RECORD);
}

/* The line drawn for the personality of the talk's villager into the talk's text and
 * message. */
static void steps_draw(VillagerTalk *talk, u32 texts, int per_group, int group, int range)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                               NpcId_Personality(TownVillager_NpcId(steps_record(talk))), (int) texts, per_group, group,
                               range);
}

/* `out` names the talk's text and message. */
static void steps_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* A line of a text set (its count the lines per group, group 0) named in `out`. */
static void steps_line(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkStepsTexts *texts)
{
    steps_draw(talk, texts->texts, texts->count, 0, 0);
    steps_name(talk, out);
}

/* The line's text named by its resource name for the villager's personality. */
static void steps_format(VillagerTalk *talk)
{
    Personality_FormatResourceName(talk->text, VILLAGER_TALK_TEXT_SIZE, (const char *) (uintptr_t) data_020c8c20,
                                   NpcId_Personality(TownVillager_NpcId(steps_record(talk))));
}

/* A member pointer whose function takes one argument, called. */
static void steps_call(const MemberPointer *member, VillagerTalk *talk, void *arg)
{
    void *self = MemberPointer_Object(member, talk);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(member, self))(self, arg);
}

/* The line of the table's line function (set already) asked for when there is one and given
 * to the talk.
 * REQUIRES: the tables hold a line function (the original then hands an unset line). */
static void steps_say_set(VillagerTalk *talk)
{
    VillagerTalkLine line = {0};
    if (talk->line.function != 0) {
        steps_call(&talk->line, talk, &line);
    }
    u8 message = line.message;
    TalkObject_SetMessage((TalkObject *) (void *) steps_talk(talk), &message, (const char *) (uintptr_t) ((int) line.text));
}

/* The three members set from `table` and their line said. */
static void steps_say(VillagerTalk *talk, const MemberPointer *table)
{
    VillagerTalkScene_SetLines(talk, table);
    steps_say_set(talk);
}

/* The current player's villager part (villager_part.h) at `offset`. */
static u8 *steps_part(int offset)
{
    return PlayerRecord_VillagerPart(PlayerRecords_Current()) + offset;
}

/* func_020231fc: a line of the set at 0x020c8a28. */
void VillagerTalkSteps_Line8a28(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8a28);
}
CLEAN_AS(func_020231fc, VillagerTalkSteps_Line8a28)

/* func_02023260: a line of the set at 0x020c8e08, then what a villager handed over to the
 * current player emptied (the record is found first). */
void VillagerTalkSteps_LineClearHandover(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerPartHandover *handover = (VillagerPartHandover *) (void *) steps_part(VILLAGER_TALK_STEPS_HANDOVER);
    steps_line(talk, out, &data_020c8e08);
    VillagerPartHandover_Clear(handover);
}
CLEAN_AS(func_02023260, VillagerTalkSteps_LineClearHandover)

/* func_020232d4: the date of what a villager handed over to the current player put into the
 * talk's slots (func_02029264), then a line of the set at 0x020c8e18. */
void VillagerTalkSteps_LineHandoverTime(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkOffer_PutTime(talk, (const DateTime *) (void *) steps_part(VILLAGER_TALK_STEPS_HANDOVER_DATE));
    steps_line(talk, out, &data_020c8e18);
}
CLEAN_AS(func_020232d4, VillagerTalkSteps_LineHandoverTime)

/* func_02023348: the talk's villager hands over to the current player: its NpcId and the kept
 * date (func_0206f80c) set in the player's record (VillagerPartHandover_Set), the object of
 * the villager's state entry emptied, then the town's villager kinds dealt when needed. */
void VillagerTalkSteps_HandOver(VillagerTalk *talk)
{
    u8 *part = PlayerRecord_VillagerPart(PlayerRecords_Current());
    DateTime kept = {0};
    Global021cfc98_CopyOut(&kept);
    const NpcId *npc = TownVillager_NpcId(steps_record(talk));
    VillagerPartHandover_Set((VillagerPartHandover *) (void *) (part + VILLAGER_TALK_STEPS_HANDOVER), npc, &kept);
    ItemObject_Clear((ItemObject *) (void *) VillagerState_Object(VillagerStatus_StateEntry(steps_record(talk))));
    VillagerKind_DealIfNeeded(&data_021e5a2c);
}
CLEAN_AS(func_02023348, VillagerTalkSteps_HandOver)

/* func_020233ac: the kept time (func_0206f80c) put into the talk's slots, a line of the set at
 * 0x020c8e30, the sound 0x5e and data_020d8e90 set at 0xe8. */
void VillagerTalkSteps_LineKeptTime(VillagerTalk *talk, VillagerTalkLine *out)
{
    DateTime kept = {0};
    Global021cfc98_CopyOut(&kept);
    VillagerTalkOffer_PutTime(talk, &kept);
    steps_line(talk, out, &data_020c8e30);
    talk->sound = VILLAGER_TALK_STEPS_SOUND_5E;
    VillagerTalkScene_SetE8(talk, data_020d8e90);
}
CLEAN_AS(func_020233ac, VillagerTalkSteps_LineKeptTime)

/* func_0202343c: a line of the set at 0x020c8bb0. */
void VillagerTalkSteps_Line8bb0(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8bb0);
}
CLEAN_AS(func_0202343c, VillagerTalkSteps_Line8bb0)

/* func_020234a0: a line of the set at 0x020c8bc0. */
void VillagerTalkSteps_Line8bc0(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8bc0);
}
CLEAN_AS(func_020234a0, VillagerTalkSteps_Line8bc0)

/* func_02023504: a line of the set at 0x020c8bd0. */
void VillagerTalkSteps_Line8bd0(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8bd0);
}
CLEAN_AS(func_02023504, VillagerTalkSteps_Line8bd0)

/* func_02023568: the line of a table said by the kept time (func_0206f80c): data_021c301c
 * when it is at most 30 minutes after now, data_021c304c when it falls in the villager's
 * sleeping time (VillagerEntry_IsSleepTime), data_021c3034 before 6:00, else data_021c3064. */
void VillagerTalkSteps_SayByKeptTime(VillagerTalk *talk)
{
    DateTime now;
    DateTime kept;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &kept, sizeof kept);
    Global021cfc98_CopyOut(&kept);
    if (DateTime_MinutesBetween(&now, &kept) <= VILLAGER_TALK_STEPS_RECENT_MINUTES) {
        VillagerTalkScene_SetLines(talk, data_021c301c);
    } else if (VillagerEntry_IsSleepTime(steps_record(talk), &kept) != 0) {
        VillagerTalkScene_SetLines(talk, data_021c304c);
    } else if (kept.hour < VILLAGER_TALK_STEPS_EARLY_HOUR) {
        VillagerTalkScene_SetLines(talk, data_021c3034);
    } else {
        VillagerTalkScene_SetLines(talk, data_021c3064);
    }
    steps_say_set(talk);
}
CLEAN_AS(func_02023568, VillagerTalkSteps_SayByKeptTime)

/* func_02023634: the screen of mode 0x31 opened (staying off the line), then data_020d9090 at
 * the command's end. */
void VillagerTalkSteps_OpenScreen31(VillagerTalk *talk, int event)
{
    (void) event;
    SceneCommand_SetScreenMode(&talk->scene, 0x31, 0);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_MODE);
    VillagerTalkScene_SetCommandEnd(talk, data_020d9090);
}
CLEAN_AS(func_02023634, VillagerTalkSteps_OpenScreen31)

/* func_0202365c: a line of the set at 0x020c89c0. */
void VillagerTalkSteps_Line89c0(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c89c0);
}
CLEAN_AS(func_0202365c, VillagerTalkSteps_Line89c0)

/* func_020236c0: two choices offered with cancel choice 1: message 0x1f running data_021c3004
 * and message 0x20 running data_021c2a1c; the reply data_020d8ea0; the talk's byte 0x18 set. */
void VillagerTalkSteps_OfferChoices1f(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x1f, 0x1f, (int) (uintptr_t) data_021c3004);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x20, 0x20, (int) (uintptr_t) data_021c2a1c);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    VillagerTalkScene_SetReply(talk, data_020d8ea0);
    TalkObject_OpenChoices((TalkObject *) (void *) steps_talk(talk), 1);
}
CLEAN_AS(func_020236c0, VillagerTalkSteps_OfferChoices1f)

/* func_0202372c: a line of the set at 0x020c89b8. */
void VillagerTalkSteps_Line89b8(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c89b8);
}
CLEAN_AS(func_0202372c, VillagerTalkSteps_Line89b8)

/* func_02023790: group 2 of the set at 0x020c89a8, its count both the lines per group and the
 * random part. */
void VillagerTalkSteps_Line89a8Group2(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_draw(talk, data_020c89a8.texts, data_020c89a8.count, 2, data_020c89a8.count);
    steps_name(talk, out);
}
CLEAN_AS(func_02023790, VillagerTalkSteps_Line89a8Group2)

/* func_020237f4: the line of the table at data_021c2f74 said when the player has a free pocket,
 * else that of data_021c2fd4. */
void VillagerTalkSteps_SayByFreePocket2fd4(VillagerTalk *talk)
{
    steps_say(talk, CurrentPockets_FreeSlot() != -1 ? data_021c2f74 : data_021c2fd4);
}
CLEAN_AS(func_020237f4, VillagerTalkSteps_SayByFreePocket2fd4)

/* func_02023864: group 1 of the set at 0x020c8aa8, its count both the lines per group and the
 * random part. */
void VillagerTalkSteps_Line8aa8Group1(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_draw(talk, data_020c8aa8.texts, data_020c8aa8.count, 1, data_020c8aa8.count);
    steps_name(talk, out);
}
CLEAN_AS(func_02023864, VillagerTalkSteps_Line8aa8Group1)

/* func_020238c8: the object of the town's moving villager record gets the value 1 in its low
 * bits, when it is in use. */
void VillagerTalkSteps_MarkMoveObject(void)
{
    ItemObject *object = (ItemObject *) (void *) VillagerMoveRecord_Object(VillagerMove_Record(&data_021e5a2c));
    if (ItemObject_IsInUse(object) != 0) {
        ItemObject_SetLow5(object, 1);
    }
}
CLEAN_AS(func_020238c8, VillagerTalkSteps_MarkMoveObject)

/* func_020238f0: a line of the set at 0x020c89e0, then data_020d8e58 run at the last
 * message. */
void VillagerTalkSteps_Line89e0(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c89e0);
    talk->on_last_message = data_020d8e58;
}
CLEAN_AS(func_020238f0, VillagerTalkSteps_Line89e0)

/* func_02023968: the town's moving villager record emptied. */
void VillagerTalkSteps_ClearMove(void)
{
    VillagerMoveRecord_Clear(VillagerMove_Record(&data_021e5a2c));
}
CLEAN_AS(func_02023968, VillagerTalkSteps_ClearMove)

/* func_02023980: a line of the set at 0x020c8bf8, the sound 0x5f, then data_020d94d0 run at
 * the last message. */
void VillagerTalkSteps_Line8bf8(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8bf8);
    talk->sound = VILLAGER_TALK_STEPS_SOUND_5F;
    talk->on_last_message = data_020d94d0;
}
CLEAN_AS(func_02023980, VillagerTalkSteps_Line8bf8)

/* func_02023a00: the line of the table at data_021c2f8c said. */
void VillagerTalkSteps_Say2f8c(VillagerTalk *talk)
{
    steps_say(talk, data_021c2f8c);
}
CLEAN_AS(func_02023a00, VillagerTalkSteps_Say2f8c)

/* func_02023a54: the gift at 0x19c shown (motion 13), put into the current player's first free
 * pocket and marked as had, then data_020d90e0 at the command's end.
 * QUIRK: without a free pocket the gift replaces the first pocket. */
void VillagerTalkSteps_GiveGiftToPockets(VillagerTalk *talk)
{
    u8 *player = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(player);
    int slot = PlayerPockets_FreeSlot(pockets);
    if (slot == -1) {
        slot = 0;
    }
    SceneCommand_RequestMotion13(&talk->scene, &talk->gift, 0, 5, 0);
    PlayerPockets_SetSlot(pockets, &talk->gift, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(player), &talk->gift, 0, 1);
    VillagerTalkScene_SetCommandEnd(talk, data_020d90e0);
}
CLEAN_AS(func_02023a54, VillagerTalkSteps_GiveGiftToPockets)

/* func_02023ac0: the gift at 0x19c drawn (func_0202d5e4) for the current player, or for 0 when
 * that gave none; its name put into the talk's slot 1 when there is one; then a line of the set
 * at 0x020c8c00. */
void VillagerTalkSteps_LineGift(VillagerTalk *talk, VillagerTalkLine *out)
{
    u16 drawn[2];
    TalkItemDraw_ThreeLists(&drawn[0], (int) (uintptr_t) PlayerRecords_Current());
    talk->gift = drawn[0];
    if (talk->gift == VILLAGER_TALK_STEPS_NO_ITEM) {
        TalkItemDraw_ThreeLists(&drawn[1], 0);
        talk->gift = drawn[1];
    }
    if (talk->gift != VILLAGER_TALK_STEPS_NO_ITEM) {
        SceneBase_PutItemName(steps_base(talk), (int) (uintptr_t) &talk->gift, 1, 7);
    }
    steps_line(talk, out, &data_020c8c00);
}
CLEAN_AS(func_02023ac0, VillagerTalkSteps_LineGift)

/* func_02023b70: the line of the table at data_021c2f74 said when the player has a free pocket,
 * else that of data_021c2fa4. */
void VillagerTalkSteps_SayByFreePocket2fa4(VillagerTalk *talk)
{
    steps_say(talk, CurrentPockets_FreeSlot() != -1 ? data_021c2f74 : data_021c2fa4);
}
CLEAN_AS(func_02023b70, VillagerTalkSteps_SayByFreePocket2fa4)

/* func_02023be0: a line of the set at 0x020c8c08. */
void VillagerTalkSteps_Line8c08(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8c08);
}
CLEAN_AS(func_02023be0, VillagerTalkSteps_Line8c08)

/* func_02023c44: a line of the set at 0x020c8c18. */
void VillagerTalkSteps_Line8c18(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8c18);
}
CLEAN_AS(func_02023c44, VillagerTalkSteps_Line8c18)

/* func_02023ca8: a line of the set at 0x020c8cd8. */
void VillagerTalkSteps_Line8cd8(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_line(talk, out, &data_020c8cd8);
}
CLEAN_AS(func_02023ca8, VillagerTalkSteps_Line8cd8)

/* func_02023d0c: the text named by the resource name data_020c8c20 for the villager's
 * personality and the message by the type of the talk's object at 0x154: 11 for type 14, 13
 * for type 16, else 14. */
void VillagerTalkSteps_LineByObjectType(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_format(talk);
    switch (ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case VILLAGER_TALK_STEPS_TYPE_14:
            talk->message = 0xb;
            break;
        case VILLAGER_TALK_STEPS_TYPE_16:
            talk->message = 0xd;
            break;
        default:
            talk->message = 0xe;
            break;
    }
    steps_name(talk, out);
}
CLEAN_AS(func_02023d0c, VillagerTalkSteps_LineByObjectType)

/* func_02023d88: the line of the table at data_021c2f14 said. */
void VillagerTalkSteps_Say2f14(VillagerTalk *talk)
{
    steps_say(talk, data_021c2f14);
}
CLEAN_AS(func_02023d88, VillagerTalkSteps_Say2f14)

/* func_02023ddc: by the type of the talk's object at 0x154: for types 14 and 16 the gift at
 * 0x19c is put into the first free pocket and marked as had when there is one, then shown
 * (motion 13) and data_020d9100 set at the command's end; for type 17 the three members at
 * 0xb0 are cleared. Nothing for others. */
void VillagerTalkSteps_GiveByObjectType(VillagerTalk *talk)
{
    switch (ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case VILLAGER_TALK_STEPS_TYPE_14:
        case VILLAGER_TALK_STEPS_TYPE_16: {
            int slot = CurrentPockets_FreeSlot();
            if (slot >= 0) {
                CurrentPockets_Set(&talk->gift, 0, slot);
                OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(PlayerRecords_Current()), &talk->gift, 0, 1);
            }
            SceneCommand_RequestMotion13(&talk->scene, &talk->gift, 0, 5, 0);
            VillagerTalkScene_SetCommandEnd(talk, data_020d9100);
            break;
        }
        case VILLAGER_TALK_STEPS_TYPE_17:
            VillagerTalkScene_ClearLines(talk);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02023ddc, VillagerTalkSteps_GiveByObjectType)

/* An item drawn from the list of `kind` (group 0) as the gift at 0x19c, named in the talk's
 * slot 0, and the talk's object at 0x154 given the value 1 in its low bits. */
static void steps_draw_gift(VillagerTalk *talk, int kind)
{
    VillagerTalkStepsItemList list;
    u16 item;
    ItemList_Construct((ItemList *) &list, kind, 0);
    ItemLists_Draw(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
    talk->gift = item;
    ItemList_Destruct(&list);
    SceneBase_PutItemName(steps_base(talk), (int) (uintptr_t) &talk->gift, 0, 7);
    ItemObject_SetLow5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk), 1);
}

/* func_02023e54: the text named by the resource name data_020c8c20 for the villager's
 * personality; by the type of the talk's object at 0x154: type 14 gives message 10 and a gift
 * of the item list of kind 0, type 16 message 12 and a gift of kind 3; type 17 message 14 when
 * the player's memory holds a letter from the player (VillagerMail_HoldsLetterFrom), with
 * data_020d8ee8 set as the talk's member event 2 and the memory kept at 0x138, else message
 * 0x16; the object then gets the value 1 in its low bits. Others give message 10. */
void VillagerTalkSteps_LineGiveByObjectType(VillagerTalk *talk, VillagerTalkLine *out)
{
    steps_format(talk);
    switch (ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case VILLAGER_TALK_STEPS_TYPE_14:
            talk->message = 0xa;
            steps_draw_gift(talk, 0);
            break;
        case VILLAGER_TALK_STEPS_TYPE_16:
            talk->message = 0xc;
            steps_draw_gift(talk, 3);
            break;
        case VILLAGER_TALK_STEPS_TYPE_17:
            if (talk->memory != NULL &&
                VillagerMail_HoldsLetterFrom(steps_record(talk),
                                             VillagerMemoryEntry_Player((VillagerMemory *) (void *) talk->memory)) != 0) {
                talk->events[2] = data_020d8ee8;
                talk->record_138 = (u32) (uintptr_t) talk->memory;
                talk->message = 0xe;
            } else {
                talk->message = 0x16;
            }
            ItemObject_SetLow5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk), 1);
            break;
        default:
            talk->message = 0xa;
            break;
    }
    steps_name(talk, out);
}
CLEAN_AS(func_02023e54, VillagerTalkSteps_LineGiveByObjectType)

/* func_02023fc8: when the pockets screen gave a pocket (GroupParams_C4CIs1), its item becomes
 * the item at 0x124 and the pocket is emptied, the table data_021c2efc set and the item taken
 * (motion 14); else the table data_021c2adc. Its line is then said. */
void VillagerTalkSteps_TakePocketAndSay(VillagerTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        u8 slot = GroupParams_Arg();
        PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
        talk->item = *PlayerPockets_Slot(pockets, slot);
        u16 none = VILLAGER_TALK_STEPS_NO_ITEM;
        CurrentPockets_Set(&none, 0, slot);
        VillagerTalkScene_SetLines(talk, data_021c2efc);
        SceneCommand_RequestMotion14(&talk->scene, &talk->item, 0, 5, 0);
    } else {
        VillagerTalkScene_SetLines(talk, data_021c2adc);
    }
    steps_say_set(talk);
}
CLEAN_AS(func_02023fc8, VillagerTalkSteps_TakePocketAndSay)

/* func_02024078: the pockets screen opened on the items 0x1561-0x1564 (the game's
 * func_020240a8, with 13, then the next line), then data_020d9118 at the command's end. */
void VillagerTalkSteps_AskPocket1561(VillagerTalk *talk, void *unused)
{
    (void) unused;
    SceneCommand_SetPocketPredicate(&talk->scene, func_020240a8, 13, 0);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_POCKETS);
    VillagerTalkScene_SetCommandEnd(talk, data_020d9118);
}
CLEAN_AS(func_02024078, VillagerTalkSteps_AskPocket1561)

/* func_020240a8 (a pocket predicate): 1 for an item 0x1561-0x1564, in any state. */
int VillagerTalkSteps_Is1561Item(u16 *item, int state)
{
    (void) state;
    return *item >= 0x1561 && *item <= 0x1564;
}
CLEAN_AS(func_020240a8, VillagerTalkSteps_Is1561Item)

/* func_020240c8: the talk's villager object (0x164) taken to its next step, then the villager
 * sent to the others in the session (SessionVillager_SendObjectOp2). */
void VillagerTalkSteps_NextStep(VillagerTalk *talk)
{
    VillagerObject *object = *(VillagerObject **) (void *) ((u8 *) talk + VILLAGER_TALK_STEPS_VILLAGER_OBJECT);
    VillagerObject_NextStep(object);
    SessionVillager_SendObjectOp2(steps_record(talk));
}
CLEAN_AS(func_020240c8, VillagerTalkSteps_NextStep)
