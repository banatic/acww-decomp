/* A town villager's request: the members of the talk scene for its object of type 10 or 19
 * (villager_talk_request.h). */
#include "villager_talk_request.h"

#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "item_object.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_command.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_kinds.h"
#include "villager_part_block.h"
#include "villager_roster.h"
#include "villager_town.h"
#include "main_random.h"
#include "talk_object.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h). */
#define VILLAGER_TALK_REQUEST_RECORD 0x830
/* The talk's members of the request. */
#define VILLAGER_TALK_REQUEST_WAIT 0x158
#define VILLAGER_TALK_REQUEST_WAIT_PLACE 0x159
#define VILLAGER_TALK_REQUEST_OTHER 0x15c
#define VILLAGER_TALK_REQUEST_BLOCK 0x160

/* The talk object's types of a request (step types of band 1, villager_part_block.h). */
#define VILLAGER_TALK_REQUEST_TYPE_ITEM 10
#define VILLAGER_TALK_REQUEST_TYPE_LETTER 19

/* The state an item handed over is put into the pockets with. */
#define VILLAGER_TALK_REQUEST_POCKET_STATE 2
#define VILLAGER_TALK_REQUEST_SOUND_5E 0x5e
#define VILLAGER_TALK_REQUEST_WAITS 3
/* What SceneBase_PutItemName is told the item is. */
#define VILLAGER_TALK_REQUEST_ITEM_KIND 7

/* A text set of the talk lines: its texts and the lines a group has. */
typedef struct VillagerTalkRequestTexts {
    u32 texts;
    u8 count;
} VillagerTalkRequestTexts;

extern const VillagerTalkRequestTexts data_020c89d8; /* "q06_over" */
extern const VillagerTalkRequestTexts data_020c8a70; /* "q07_over" */
extern const VillagerTalkRequestTexts data_020c8c48; /* "q_yes" */
extern const VillagerTalkRequestTexts data_020c8a90; /* "q07_mailgo" */
extern const VillagerTalkRequestTexts data_020c8ab8; /* "q_full" */
extern const VillagerTalkRequestTexts data_020c8c40; /* "q_no" */
extern const VillagerTalkRequestTexts data_020c8c28; /* "q_time" */
extern const VillagerTalkRequestTexts data_020c8c30; /* "q06_req" */
extern const VillagerTalkRequestTexts data_020c8c10; /* "q07_req" */

/* The waits in minutes VillagerTalkRequest_LineTime draws from. */
extern const u8 data_020d8d28[VILLAGER_TALK_REQUEST_WAITS];

/* Member pointer constants the functions here store or set. */
extern const MemberPointer data_020d8f50;
extern const MemberPointer data_020d8f00; /* VillagerTalkRequest_StampWait */
extern const MemberPointer data_020d9130; /* VillagerTalkRequest_Drop */
extern const MemberPointer data_020d9140; /* the reply func_020288bc */

/* A table of three member pointers for 0xb0 to 0xc0. */
extern const MemberPointer data_021c2a04[3];
/* What the choices of VillagerTalkRequest_OfferAccept run, and their messages. */
extern u8 data_021c2a34[];
extern u8 data_021c2a4c[];
extern u8 data_021c2a1c[];
#define VILLAGER_TALK_REQUEST_CHOICE_ACCEPT 0x21
#define VILLAGER_TALK_REQUEST_CHOICE_OTHER 0x22

extern VillagerTown data_021e5a2c; /* the town's villagers */

/* `size` bytes cleared. */
extern void *func_02137550(void *dst, u32 size);

static u8 *request_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *request_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *request_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_REQUEST_RECORD);
}

static u8 *request_byte(VillagerTalk *talk, int offset)
{
    return (u8 *) talk + offset;
}

static NpcId **request_other(VillagerTalk *talk)
{
    return (NpcId **) (void *) ((u8 *) talk + VILLAGER_TALK_REQUEST_OTHER);
}

static VillagerPartBlock *request_block(const VillagerTalk *talk)
{
    return *(VillagerPartBlock **) (void *) ((const u8 *) talk + VILLAGER_TALK_REQUEST_BLOCK);
}

static int request_type(VillagerTalk *talk)
{
    return ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
}

static int request_personality(VillagerTalk *talk)
{
    return NpcId_Personality(TownVillager_NpcId(request_record(talk)));
}

/* The line of group `group` of `texts` drawn for `personality` into the talk's text and
 * message. */
static void request_draw(VillagerTalk *talk, int personality, const VillagerTalkRequestTexts *texts, int group)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, personality, (int) texts->texts,
                               texts->count, group, 0);
}

/* `out` names the talk's text and message. */
static void request_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* The talk's text set by the type of the talk's object: `for_item` (10), `for_letter` (19),
 * else none. */
static const VillagerTalkRequestTexts *request_texts_by_type(VillagerTalk *talk, const VillagerTalkRequestTexts *for_item,
                                                             const VillagerTalkRequestTexts *for_letter)
{
    switch (request_type(talk)) {
        case VILLAGER_TALK_REQUEST_TYPE_ITEM:
            return for_item;
        case VILLAGER_TALK_REQUEST_TYPE_LETTER:
            return for_letter;
        default:
            return NULL;
    }
}

/* Group 0 of `texts` for the talk's villager, when there are texts; `out` names the talk's text
 * either way. */
static void request_line_if(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkRequestTexts *texts)
{
    if (texts != NULL) {
        request_draw(talk, request_personality(talk), texts, 0);
    }
    request_name(talk, out);
}

/* func_02028284: a line of "q06_over" (type 10) or "q07_over" (type 19), its group the talk
 * object's three high bits; with a block, the block's two villagers put into slots 0 and 1 and
 * then the talk object's item into slot 0. `out` names the talk's text either way. */
void VillagerTalkRequest_LineOver(VillagerTalk *talk, VillagerTalkLine *out)
{
    const VillagerTalkRequestTexts *texts = request_texts_by_type(talk, &data_020c89d8, &data_020c8a70);
    if (texts != NULL) {
        int personality = request_personality(talk);
        int group = ItemObject_High3((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
        request_draw(talk, personality, texts, group);
        if (request_block(talk) != NULL) {
            SceneBase_PutNpcName(request_base(talk), VillagerPartBlock_Npc(request_block(talk), 0), 0);
            SceneBase_PutNpcName(request_base(talk), VillagerPartBlock_Npc(request_block(talk), 1), 1);
            /* QUIRK: the item goes into slot 0 too, after the first villager's name. */
            SceneBase_PutItemName(request_base(talk),
                                  (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)),
                                  0, VILLAGER_TALK_REQUEST_ITEM_KIND);
        }
    }
    request_name(talk, out);
}
CLEAN_AS(func_02028284, VillagerTalkRequest_LineOver)

/* func_02028358: the type of the talk's object read, and nothing done with it. */
void VillagerTalkRequest_ReadType(VillagerTalk *talk)
{
    (void) request_type(talk);
}
CLEAN_AS(func_02028358, VillagerTalkRequest_ReadType)

/* func_0202836c: the request accepted. With a block: the block set to the talk object's type
 * (naming the talk's villager and the other resident at 0x15c), the talk's object emptied and
 * the town's dealing done (VillagerKind_DealIfNeeded), the block's object made the talk's and
 * its item kept at 0x124; for type 10 the item put into the current player's first free pocket
 * (state 2), for type 19 the block's letter written into the first free letter when there is
 * one. Then the item shown (motion 13, in mode 2 except for type 19's 0), with data_020d8f50 at
 * the command's end and data_020d8f00 at 0xe8. */
void VillagerTalkRequest_Accept(VillagerTalk *talk)
{
    u8 *player = PlayerRecords_Current();
    (void) PlayerRecord_VillagerPart(player);
    u8 *record = request_record(talk);
    u32 mode = VILLAGER_TALK_REQUEST_POCKET_STATE;
    if (request_block(talk) != NULL) {
        int type = request_type(talk);
        VillagerPartBlock_SetType(request_block(talk), type, TownVillager_NpcId(record), *request_other(talk));
        ItemObject_Clear((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
        VillagerKind_DealIfNeeded(&data_021e5a2c);
        VillagerTalkScene_SetObject(talk,
                                    (u32) (uintptr_t) ((ItemObject *) (void *) VillagerPartBlock_Object(request_block(talk))));
        talk->item = *ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
        switch (request_type(talk)) {
            case VILLAGER_TALK_REQUEST_TYPE_ITEM: {
                int slot = PlayerPockets_FreeSlot(PlayerRecord_Pockets(player));
                /* QUIRK: the pockets are given the slot even when none is free (-1). */
                PlayerPockets_SetSlot(PlayerRecord_Pockets(player), &talk->item, slot, (int) mode);
                break;
            }
            case VILLAGER_TALK_REQUEST_TYPE_LETTER: {
                MailLetter *letter = CurrentPockets_FreeLetter();
                if (letter != NULL) {
                    VillagerPartBlock_WriteLetter(request_block(talk), letter);
                }
                mode = 0;
                break;
            }
        }
    }
    SceneCommand_RequestMotion13(&talk->scene, &talk->item, mode, 5, 0);
    VillagerTalkScene_SetCommandEnd(talk, data_020d8f50);
    VillagerTalkScene_SetE8(talk, data_020d8f00);
}
CLEAN_AS(func_0202836c, VillagerTalkRequest_Accept)

/* func_02028478: with an object, its date set to now plus the wait at 0x158 (minutes) and its
 * three high bits to the wait's place at 0x159. */
void VillagerTalkRequest_StampWait(VillagerTalk *talk)
{
    if (VillagerTalkScene_Object(talk) != 0) {
        DateTime *date = ItemObject_Date((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
        DateTime_Now(date);
        DateTime_AddMinutes(date, *request_byte(talk, VILLAGER_TALK_REQUEST_WAIT));
        ItemObject_SetHigh3((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk),
                            *request_byte(talk, VILLAGER_TALK_REQUEST_WAIT_PLACE));
    }
}
CLEAN_AS(func_02028478, VillagerTalkRequest_StampWait)

/* func_020284c0: a line of "q_yes" (type 10) or "q07_mailgo" (type 19); the sound 0x5e. */
void VillagerTalkRequest_LineYes(VillagerTalk *talk, VillagerTalkLine *out)
{
    request_line_if(talk, out, request_texts_by_type(talk, &data_020c8c48, &data_020c8a90));
    talk->sound = VILLAGER_TALK_REQUEST_SOUND_5E;
}
CLEAN_AS(func_020284c0, VillagerTalkRequest_LineYes)

/* func_0202854c: nothing. */
void VillagerTalkRequest_Nothing(void) {}
CLEAN_AS(func_0202854c, VillagerTalkRequest_Nothing)

/* func_02028550: a line of "q_full" (the pockets are full). */
void VillagerTalkRequest_LineFull(VillagerTalk *talk, VillagerTalkLine *out)
{
    request_line_if(talk, out, &data_020c8ab8);
}
CLEAN_AS(func_02028550, VillagerTalkRequest_LineFull)

/* func_020285b4: the talk's object emptied and the town's dealing done. */
void VillagerTalkRequest_Drop(VillagerTalk *talk)
{
    ItemObject_Clear((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
    VillagerKind_DealIfNeeded(&data_021e5a2c);
}
CLEAN_AS(func_020285b4, VillagerTalkRequest_Drop)

/* func_020285d0: a line of "q_no"; VillagerTalkRequest_Drop to run once at the talk's last
 * message (0xc8). */
void VillagerTalkRequest_LineNo(VillagerTalk *talk, VillagerTalkLine *out)
{
    request_line_if(talk, out, &data_020c8c40);
    talk->on_last_message = data_020d9130;
}
CLEAN_AS(func_020285d0, VillagerTalkRequest_LineNo)

/* func_02028648: two choices offered: message 0x21 running data_021c2a4c when the request can
 * be taken (type 10: there is a current player with a free pocket; type 19: a free letter),
 * else data_021c2a34; message 0x22 running data_021c2a1c. The reply func_020288bc; the talk's
 * byte 0x18 set. */
void VillagerTalkRequest_OfferAccept(VillagerTalk *talk)
{
    u8 *accept = data_021c2a34;
    TalkChoiceList list;
    switch (request_type(talk)) {
        case VILLAGER_TALK_REQUEST_TYPE_ITEM:
            if (PlayerRecords_Current() != NULL &&
                PlayerPockets_FreeSlot(PlayerRecord_Pockets(PlayerRecords_Current())) != -1) {
                accept = data_021c2a4c;
            }
            break;
        case VILLAGER_TALK_REQUEST_TYPE_LETTER:
            if (CurrentPockets_FreeLetterIndex() != -1) {
                accept = data_021c2a4c;
            }
            break;
    }
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, VILLAGER_TALK_REQUEST_CHOICE_ACCEPT, VILLAGER_TALK_REQUEST_CHOICE_ACCEPT,
                    (int) (uintptr_t) accept);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, VILLAGER_TALK_REQUEST_CHOICE_OTHER, VILLAGER_TALK_REQUEST_CHOICE_OTHER,
                    (int) (uintptr_t) data_021c2a1c);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    VillagerTalkScene_SetReply(talk, data_020d9140);
    TalkObject_OpenChoices((TalkObject *) (void *) request_talk(talk), 1);
}
CLEAN_AS(func_02028648, VillagerTalkRequest_OfferAccept)

/* func_020286f8: a wait drawn at random from data_020d8d28 (its place kept at 0x159, the
 * minutes at 0x158), then a line of "q_time" of the group of that place. */
void VillagerTalkRequest_LineTime(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 waits[VILLAGER_TALK_REQUEST_WAITS];
    for (int i = 0; i < VILLAGER_TALK_REQUEST_WAITS; i++) {
        waits[i] = data_020d8d28[i];
    }
    u8 *place = request_byte(talk, VILLAGER_TALK_REQUEST_WAIT_PLACE);
    *place = (u8) MainRandom_Below(VILLAGER_TALK_REQUEST_WAITS);
    *request_byte(talk, VILLAGER_TALK_REQUEST_WAIT) = waits[*place];
    int personality = request_personality(talk);
    request_draw(talk, personality, &data_020c8c28, *place);
    request_name(talk, out);
}
CLEAN_AS(func_020286f8, VillagerTalkRequest_LineTime)

/* func_02028790: the line of the table data_021c2a04 said while the talk is on its message.
 * REQUIRES: the table holds a line function (the original then hands on an unset line). */
void VillagerTalkRequest_Say2a04(VillagerTalk *talk)
{
    VillagerTalkLine line = {0};
    VillagerTalkScene_SetLines(talk, data_021c2a04);
    if (talk->line.function != 0) {
        void *self = MemberPointer_Object(&talk->line, talk);
        ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, &line);
    }
    u8 message = line.message;
    TalkObject_SetMessageIfNone((TalkObject *) (void *) request_talk(talk), &message,
                                (const char *) (uintptr_t) ((int) line.text));
}
CLEAN_AS(func_02028790, VillagerTalkRequest_Say2a04)

/* func_020287e4: another resident than the talk's villager picked at random, its NpcId kept at
 * 0x15c and its name put into slot 1. */
void VillagerTalkRequest_PickOther(VillagerTalk *talk)
{
    const NpcId *excluded;
    func_02137550(&excluded, sizeof excluded);
    excluded = TownVillager_NpcId(request_record(talk));
    *request_other(talk) = TownVillager_NpcId(VillagerRoster_PickResident(&data_021e5a2c, &excluded, 1));
    SceneBase_PutNpcName(request_base(talk), *request_other(talk), 1);
}
CLEAN_AS(func_020287e4, VillagerTalkRequest_PickOther)

/* func_02028838: a line of "q06_req" (type 10) or "q07_req" (type 19). */
void VillagerTalkRequest_LineAsk(VillagerTalk *talk, VillagerTalkLine *out)
{
    request_line_if(talk, out, request_texts_by_type(talk, &data_020c8c30, &data_020c8c10));
}
CLEAN_AS(func_02028838, VillagerTalkRequest_LineAsk)
