/* The greetings of a town villager's talk scene (villager_talk_greeting.h). */
#include "villager_talk_greeting.h"

#include <string.h>

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "fox_shop.h"
#include "item_object.h"
#include "lookups.h"
#include "mail.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_query.h"
#include "session.h"
#include "sky.h"
#include "town_villager.h"
#include "villager_checks.h"
#include "villager_data.h"
#include "villager_home.h"
#include "villager_kinds.h"
#include "villager_memory_bits.h"
#include "villager_memory_entry.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_part.h"
#include "villager_part_block.h"
#include "villager_part_handover.h"
#include "villager_scene_object.h"
#include "villager_status.h"
#include "villager_town.h"
#include "word_archives.h"
#include "item_lists.h"
#include "letter.h"
#include "main_random.h"
#include "ov003/town_insect.h"
#include "player_id.h"
#include "talk_object.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h) and its position (Vec3). */
#define VILLAGER_TALK_GREETING_RECORD 0x830
#define VILLAGER_TALK_GREETING_POSITION 0x5c
/* The villager scene object's vtable slots: its town record, and whether it has fleas. */
#define VILLAGER_TALK_GREETING_SLOT_RECORD 0x64
#define VILLAGER_TALK_GREETING_SLOT_FLEA 0xb0
/* The talk's block of a request (villager_talk_request.h), and the place and the memory of the
 * partner villager's memory of the player. */
#define VILLAGER_TALK_GREETING_BLOCK 0x160
#define VILLAGER_TALK_GREETING_PARTNER_INDEX 0x130

#define VILLAGER_TALK_GREETING_NO_ITEM 0xfff1
#define VILLAGER_TALK_GREETING_NO_KIND (-1)
/* What SceneBase_PutItemName is told the item is. */
#define VILLAGER_TALK_GREETING_ITEM_KIND 7
/* The fields DateTime_Compare looks at: all six. */
#define VILLAGER_TALK_GREETING_ALL_FIELDS 0x3f

/* The insects (0x12b0-0x12e7, 56 kinds) and the two poisonous kinds looked for. */
#define VILLAGER_TALK_GREETING_INSECT_FIRST 0x12b0
#define VILLAGER_TALK_GREETING_INSECT_KINDS 0x38
#define VILLAGER_TALK_GREETING_POISON_KINDS 2
#define VILLAGER_TALK_GREETING_POISON_DISTANCE 0x6000
/* The insects of the field (overlay 3's slots). */
#define VILLAGER_TALK_GREETING_INSECT_SLOTS 8

/* VillagerTalkGreeting_SinceLastTalk's answers. */
#define VILLAGER_TALK_GREETING_FIRST 0
#define VILLAGER_TALK_GREETING_EARLIER_DAY 1
#define VILLAGER_TALK_GREETING_TODAY 2
#define VILLAGER_TALK_GREETING_WEEK 3
#define VILLAGER_TALK_GREETING_MONTH 4
#define VILLAGER_TALK_GREETING_FOREIGN 5
#define VILLAGER_TALK_GREETING_OTHER_TOWN 6
#define VILLAGER_TALK_GREETING_WEEK_DAYS 7
#define VILLAGER_TALK_GREETING_MONTH_DAYS 30
/* From this many days the "ai_30days" line takes group 5 and one line a group. */
#define VILLAGER_TALK_GREETING_LONG_DAYS 0x186

/* The villager's moods (byte 0x18 of its state entry). */
#define VILLAGER_TALK_GREETING_MOOD_ANGRY 2
#define VILLAGER_TALK_GREETING_MOOD_SAD 3
#define VILLAGER_TALK_GREETING_MOOD_TIRED 4
#define VILLAGER_TALK_GREETING_MOOD_JOY 1

/* The weather (Sky_Falling) and the villager's modes the greeting looks at. */
#define VILLAGER_TALK_GREETING_RAIN 1
#define VILLAGER_TALK_GREETING_SNOW 2
#define VILLAGER_TALK_GREETING_MODE_SHOP2 3
#define VILLAGER_TALK_GREETING_MODE_SHOP1 4
#define VILLAGER_TALK_GREETING_MODE_BOOM 8
#define VILLAGER_TALK_GREETING_SCENE_SHOP2 10

/* What VillagerStatus_Came says of a villager: 1 (moved in from no player's town), 2 (from
 * another player's town, named in the line). */
#define VILLAGER_TALK_GREETING_CAME_1 1
#define VILLAGER_TALK_GREETING_CAME_FROM_TOWN 2

/* A request's object types (villager_talk_request.h) and the handover's. */
#define VILLAGER_TALK_GREETING_TYPE_ITEM 10
#define VILLAGER_TALK_GREETING_TYPE_LETTER 19
#define VILLAGER_TALK_GREETING_LETTER_STATE 8
#define VILLAGER_TALK_GREETING_KNOWN_TYPES 0x16

/* The text sets. */
extern const VillagerTalkGreetingTexts data_020c89f8; /* "ai_fall" */
extern const VillagerTalkGreetingTexts data_020c8b28; /* "ai_run" */
extern const VillagerTalkGreetingTexts data_020c8dd8; /* "ai_mfirst" */
extern const VillagerTalkGreetingTexts data_020c8ca0; /* "ai_flea" */
extern const VillagerTalkGreetingTexts data_020c8d10; /* "ai_30days" */
extern const VillagerTalkGreetingTexts data_020c89d0; /* "ai_7days" */
extern const VillagerTalkGreetingTexts data_020c8a38; /* "ai_anger" */
extern const VillagerTalkGreetingTexts data_020c8970; /* "ai_sad" */
extern const VillagerTalkGreetingTexts data_020c8c88; /* "ai_tire" */
extern const VillagerTalkGreetingTexts data_020c8ac8; /* "ai_password" */
extern const VillagerTalkGreetingTexts data_020c8c70; /* "ai_fortune" */
extern const VillagerTalkGreetingTexts data_020c8c38; /* "ai_shop1" */
extern const VillagerTalkGreetingTexts data_020c8c90; /* "ai_shop2" */
extern const VillagerTalkGreetingTexts data_020c8a80; /* "ai_shop3" */
extern const VillagerTalkGreetingTexts data_020c8a78; /* "ai_indoor" */
extern const VillagerTalkGreetingTexts data_020c8cf0; /* "ai_rain1" */
extern const VillagerTalkGreetingTexts data_020c8a18; /* "ai_snow1" */
extern const VillagerTalkGreetingTexts data_020c8b78; /* "ai_today1" */
extern const VillagerTalkGreetingTexts data_020c8a00; /* "ai_boom" */
extern const VillagerTalkGreetingTexts data_020c8b90; /* "ai_persis" */
extern const VillagerTalkGreetingTexts data_020c8b60; /* "ai_joy" */
extern const VillagerTalkGreetingTexts data_020c8bc8; /* "ai_rain2" */
extern const VillagerTalkGreetingTexts data_020c8d80; /* "ai_snow2" */
extern const VillagerTalkGreetingTexts data_020c8c58; /* "ai_today2" */
extern const VillagerTalkGreetingTexts data_020c89f0; /* "ai_bee" */
extern const VillagerTalkGreetingTexts data_020c8b40; /* "ai_poison" */
extern const VillagerTalkGreetingTexts data_020c8cf8; /* "ai_foreign" */
/* "ai_first", "ai_nfirst" and "ai_mfirst", by what VillagerStatus_Came says. */
extern const VillagerTalkGreetingTexts data_020c8f64[3];
/* The talk of two villagers: no texts, three lines a group; and the "3p_*" texts of the six
 * personalities. */
extern const VillagerTalkGreetingTexts data_020d8f40;
extern const u32 data_020d9d4c[6];

/* The poisonous insects' kinds (0x37, 0x36). */
extern const s8 data_020c892c[VILLAGER_TALK_GREETING_POISON_KINDS];
/* The word archives of the talk's slots 2 to 6 (VillagerTalkGreeting_LineThree) and 7 to 10
 * (VillagerTalkGreeting_FillSlots). */
extern const u8 data_020c8940[5];
extern const u8 data_020c8938[4];
/* What SceneBase_PutBytes is handed in the place of the size. */
extern u8 data_020d9f48[];
extern u8 data_020d9fb4[];

/* Tables of three member pointers for 0xb0 to 0xc0. */
extern const MemberPointer data_021c2a64[3];
extern const MemberPointer data_021c2aac[3];
extern const MemberPointer data_021c3094[3];
extern const MemberPointer data_021c1d54[3];

extern u8 data_020e54a8;           /* the kind of field: 0 the town */
extern const u8 data_021dc7aa[];   /* this town: its number and name */
extern u8 data_021f3b30[];         /* the fox's shop */
extern VillagerTown data_021e5a2c; /* the town's villagers */
extern NetSession *data_020ccf94;  /* the session */

/* The item list VillagerTalkGreeting_Line draws a fortune's item from. */
typedef struct VillagerTalkGreetingItemList {
    s32 words[5];
} VillagerTalkGreetingItemList;

static u8 *greeting_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *greeting_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *greeting_record_of(const u8 *villager)
{
    return *(u8 **) (void *) (villager + VILLAGER_TALK_GREETING_RECORD);
}

static u8 *greeting_record(const VillagerTalk *talk)
{
    return greeting_record_of(talk->villager);
}

static int greeting_personality(u8 *record)
{
    return NpcId_Personality(TownVillager_NpcId(record));
}

static VillagerMemory *greeting_memory(const VillagerTalk *talk)
{
    return (VillagerMemory *) (void *) talk->memory;
}

/* The villager scene object's virtual function at `slot` (taking the object). */
static u32 greeting_virtual(VillagerTalk *talk, int slot)
{
    u8 *villager = talk->villager;
    const u8 *vtable = *(const u8 *const *) (void *) villager;
    u32 code = *(const u32 *) (const void *) (vtable + slot);
    return ((u32 (*)(void *))(uintptr_t) code)(villager);
}

/* `out` names the talk's text and message. */
static void greeting_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* The villager's mode (villager_mode_record.h). */
static int greeting_mode(u8 *record)
{
    return VillagerModeRecord_Mode(VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record)));
}

/* Whether two towns (a number, then a name of 12 bytes) differ. */
static int greeting_towns_differ(const u8 *a, const u8 *b)
{
    u16 number_a;
    u16 number_b;
    memcpy(&number_a, a, sizeof number_a);
    memcpy(&number_b, b, sizeof number_b);
    return number_a != number_b || memcmp(a + 2, b + 2, 0xc) != 0;
}

/* The request block the talk keeps. */
static VillagerPartBlock *greeting_block(const VillagerTalk *talk)
{
    return *(VillagerPartBlock **) (void *) ((u8 *) talk + VILLAGER_TALK_GREETING_BLOCK);
}

static ItemObject *greeting_block_object(const VillagerTalk *talk)
{
    return (ItemObject *) (void *) VillagerPartBlock_Object(greeting_block(talk));
}

/* func_0202b94c: the line of a talk of two villagers with the player. The player is noted in
 * the villager's memory and, when the villager scene object has a partner (its word 0x644), in
 * the partner's (into 0x134 and 0x130). The line is of the "3p_*" text of the partner's
 * personality (that of personality 0 without a partner; none for a personality of 6 or more),
 * three lines a group, for the villager's personality; `out` names the talk's text and message
 * either way. The talk's slot 0 gets the villager's name, slot 1 the partner's, slots 2 to 6
 * random words of the archives of data_020c8940. */
void VillagerTalkGreeting_LineThree(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkGreetingTexts texts = data_020d8f40;
    int personality = greeting_personality(greeting_record(talk));
    unsigned int partner_personality = 0;
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, greeting_record(talk), 0);
    if (VillagerSceneObject_Word644((u32 *) (void *) talk->villager) != 0) {
        u8 *partner = greeting_record_of((u8 *) (uintptr_t) VillagerSceneObject_Word644((u32 *) (void *) talk->villager));
        partner_personality = (unsigned int) greeting_personality(partner);
        VillagerTalkScene_NoteMemory(talk, &talk->partner_memory,
                                     (s32 *) (void *) ((u8 *) talk + VILLAGER_TALK_GREETING_PARTNER_INDEX), partner, 0);
    }
    if (partner_personality < 6) {
        texts.texts = data_020d9d4c[partner_personality];
    }
    if (texts.texts != 0) {
        VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, personality, (int) texts.texts,
                                   texts.count, 0, 0);
    }
    greeting_name(talk, out);

    SceneBase_PutNpcName(greeting_base(talk), TownVillager_NpcId(greeting_record(talk)), 0);
    if (VillagerSceneObject_Word644((u32 *) (void *) talk->villager) != 0) {
        u8 *partner = greeting_record_of((u8 *) (uintptr_t) VillagerSceneObject_Word644((u32 *) (void *) talk->villager));
        SceneBase_PutNpcName(greeting_base(talk), TownVillager_NpcId(partner), 1);
    }
    for (int i = 0; i < 5; i++) {
        VillagerTalkGreeting_PutRandomWord(talk, i + 2, data_020c8940[i]);
    }
}
CLEAN_AS(func_0202b94c, VillagerTalkGreeting_LineThree)

/* func_0202ba94: the line said for what the villager knows of the current player
 * (VillagerKind_Known, a type below 22). For class 1, the request block of the player's
 * villager part it names is kept at 0x160; while its object's five low bits are 0, the table
 * data_021c2a64 when the object's date is past (and the object kept at 0x154), else for type
 * 10 the table data_021c2aac when the pockets hold no item like the object's, and for type 19
 * the same when the pockets' first letter of state 7 or 8 has state 8 (that letter then
 * emptied). For class 3, the table data_021c3094 (and the handover's object kept at 0x154) when
 * the part's handover holds an object of type 21 with low bits 0 from this villager whose date
 * is behind now. Without an object at 0x154, the table data_021c1d54. Then the line of the line
 * function said while the talk is on its message.
 * REQUIRES: a line function set (the original then hands on an unset line). */
void VillagerTalkGreeting_SayByKnownObject(VillagerTalk *talk)
{
    u8 *player = PlayerRecords_Current();
    u8 *record = greeting_record(talk);
    VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(player);
    unsigned int type = (unsigned int) VillagerKind_Known(&data_021e5a2c, record, player);
    if (type < VILLAGER_TALK_GREETING_KNOWN_TYPES) {
        DateTime now = {0};
        DateTime_Now(&now);
        switch (ItemObject_ClassOfType(type)) {
            case 1: {
                VillagerPartBlock *block = VillagerPart_Block(part, ItemObject_Class1SplitOfType(type));
                *(VillagerPartBlock **) (void *) ((u8 *) talk + VILLAGER_TALK_GREETING_BLOCK) = block;
                if (greeting_block(talk) == NULL || ItemObject_Low5(greeting_block_object(talk)) != 0) {
                    break;
                }
                if (DateTime_Compare(ItemObject_Date(greeting_block_object(talk)), &now, VILLAGER_TALK_GREETING_ALL_FIELDS) ==
                    -1) {
                    VillagerTalkScene_SetLines(talk, data_021c2a64);
                    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) greeting_block_object(talk));
                    break;
                }
                switch (ItemObject_Type(greeting_block_object(talk))) {
                    case VILLAGER_TALK_GREETING_TYPE_ITEM: {
                        PlayerPockets *pockets = PlayerRecord_Pockets(player);
                        if (VillagerTalkScene_PocketOfItem(pockets, ItemObject_Item(greeting_block_object(talk))) == -1) {
                            VillagerTalkScene_SetLines(talk, data_021c2aac);
                            VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) greeting_block_object(talk));
                        }
                        break;
                    }
                    case VILLAGER_TALK_GREETING_TYPE_LETTER: {
                        Letter *letter = VillagerTalkScene_LetterToSend(PlayerRecord_Pockets(player));
                        if (letter != NULL && Letter_State(letter) == VILLAGER_TALK_GREETING_LETTER_STATE) {
                            Letter_Clear(letter);
                            VillagerTalkScene_SetLines(talk, data_021c2aac);
                            VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) greeting_block_object(talk));
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 3: {
                VillagerPartHandover *handover = (VillagerPartHandover *) (void *) part->rest_a4;
                ItemObject *object = (ItemObject *) (void *) handover->object;
                if (ItemObject_IsInUse(object) != 0 && ItemObject_Type(object) == VILLAGER_PART_HANDOVER_TYPE &&
                    ItemObject_Low5(object) == 0 && VillagerPartHandover_IsFrom(handover, TownVillager_NpcId(record)) != 0 &&
                    DateTime_Compare(&now, &handover->date, VILLAGER_TALK_GREETING_ALL_FIELDS) == 1) {
                    VillagerTalkScene_SetLines(talk, data_021c3094);
                    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
                }
                break;
            }
            default:
                break;
        }
    }
    if (VillagerTalkScene_Object(talk) == 0) {
        VillagerTalkScene_SetLines(talk, data_021c1d54);
    }

    VillagerTalkLine line = {0};
    if (talk->line.function != 0) {
        void *self = MemberPointer_Object(&talk->line, talk);
        ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, &line);
    }
    u8 message = line.message;
    TalkObject_SetMessageIfNone((TalkObject *) (void *) greeting_talk(talk), &message,
                                (const char *) (uintptr_t) ((int) line.text));
}
CLEAN_AS(func_0202ba94, VillagerTalkGreeting_SayByKnownObject)

/* func_0202bca0: the player noted in the villager's memory. */
void VillagerTalkGreeting_NoteMemory(VillagerTalk *talk, void *unused)
{
    (void) unused;
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, greeting_record(talk), 0);
}
CLEAN_AS(func_0202bca0, VillagerTalkGreeting_NoteMemory)

/* func_0202bcd4: with a town record, the talk's slot 0 gets the villager's star sign (from its
 * birthday) and slot 6 its byte 0x29; slots 7 to 10 get random words of the archives of
 * data_020c8938. */
void VillagerTalkGreeting_FillSlots(VillagerTalk *talk)
{
    u8 *record = greeting_record(talk);
    if (record != NULL) {
        char sign[2];
        sign[0] = (char) Lookups_StarSignOf(VillagerData_Birthday(record));
        sign[1] = 0;
        SceneBase_PutBytes(greeting_base(talk), 0, sign, (int) (uintptr_t) data_020d9f48, &sign[1]);
        VillagerTalkGreeting_PutByte29(talk, 6, record);
    }
    for (int i = 0; i < 4; i++) {
        VillagerTalkGreeting_PutRandomWord(talk, i + 7, data_020c8938[i]);
    }
}
CLEAN_AS(func_0202bcd4, VillagerTalkGreeting_FillSlots)

/* func_0202bd40: the villager data's byte 0x29 (when there is one) put into the talk's slot. */
void VillagerTalkGreeting_PutByte29(VillagerTalk *talk, int slot, u8 *villager)
{
    const u8 *byte = VillagerData_Byte29(villager);
    if (byte != NULL) {
        char bytes[2];
        bytes[0] = (char) *byte;
        bytes[1] = 0;
        SceneBase_PutBytes(greeting_base(talk), slot, bytes, (int) (uintptr_t) data_020d9fb4, &bytes[1]);
    }
}
CLEAN_AS(func_0202bd40, VillagerTalkGreeting_PutByte29)

/* func_0202bd7c: a word drawn at random from the archive put into the talk's slot (its
 * message as a byte, the archive's name in the place of the size). */
int VillagerTalkGreeting_PutRandomWord(VillagerTalk *talk, int slot, int archive)
{
    int message = 0;
    int name = WordArchives_Random(&message, archive);
    char bytes[2];
    bytes[0] = (char) message;
    bytes[1] = 0;
    return SceneBase_PutBytes(greeting_base(talk), slot, bytes, name, &bytes[1]);
}
CLEAN_AS(func_0202bd7c, VillagerTalkGreeting_PutRandomWord)

/* The text set of the last greetings: the rain or snow while in the town, else "ai_today2"
 * with, nine times in ten, the last group of its random part, and the part of the day. */
static const VillagerTalkGreetingTexts *greeting_weather(int falling, int *group, int *range)
{
    unsigned int town = data_020e54a8 == 0 ? 1 : 0;
    if (town != 0 && falling == VILLAGER_TALK_GREETING_RAIN) {
        return &data_020c8bc8;
    }
    if (town != 0 && falling == VILLAGER_TALK_GREETING_SNOW) {
        return &data_020c8d80;
    }
    if (MainRandom_Below(9) != 0) {
        *range = (u8) (data_020c8c58.count - 1);
    }
    *group = Calendar_PartOfDay();
    return &data_020c8c58;
}

/* func_0202bdb4: the greeting line. The slots are filled (VillagerTalkGreeting_FillSlots), then
 * the greetings are asked in turn and the first that holds gives the text set, the group and
 * the random part (0 unless said):
 * - a fall (never); running: both set the byte 0x13c when the player is met for the first time;
 * - a first meeting (VillagerTalkGreeting_FirstTexts); a player of another town than the
 *   memory's ("ai_mfirst", group 7, part 3);
 * - a poisonous insect near; fleas; another town (VillagerTalkGreeting_ForeignTexts);
 * - 30 days or more ("ai_30days"; from 390 days one line a group, group 5, part 1); 7 days;
 * - bee stings; anger, sadness or tiredness;
 * - the fox's shop's password (shown in the talk's slot 4) while the villager is the one of
 *   index 161, the shop has the item 0x5012 after six and the current player is not marked;
 * - with no session linked, the memory's bit 5 and a free pocket: a fortune, an item drawn into
 *   the gift at 0x19c (shown in slot 0) and bit 5 cleared;
 * - in Nook's shop ("ai_shop1", group 1 unless the villager's mode is 4), in the scene 10
 *   ("ai_shop2", group 1 unless the mode is 3), in a scene of the set 20 at index 1;
 * - met on an earlier day: indoors, rain, snow or today, the group the part of the day;
 * - the villager's mode 8; its persistence (group 1 at level 2); its joy (byte 0x18 at 1, the
 *   group the part of the day); else greeting_weather.
 * For a player met before, slot 2 gets the weeks (at most 9, from 70 days) and slot 3 the months
 * (at most 12, from 390 days). Flag 2 of the villager's state entry is set; `out` names the
 * talk's text and message. */
void VillagerTalkGreeting_Line(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = greeting_record(talk);
    VillagerState *entry = VillagerStatus_StateEntry(record);
    int personality = greeting_personality(record);
    int days = 0;
    int since = VillagerTalkGreeting_SinceLastTalk(talk, &days);
    int mood = VillagerState_GetByte18(entry);
    int falling = Sky_Falling();
    int group = 0;
    (void) PlayerRecords_Current();
    int range = 0;
    int per_group = -1;
    int kind = VILLAGER_TALK_GREETING_NO_KIND;
    const VillagerTalkGreetingTexts *texts;
    const Vec3 *position = (const Vec3 *) (void *) (talk->villager + VILLAGER_TALK_GREETING_POSITION);
    VillagerTalkGreeting_FillSlots(talk);

    if (VillagerTalkGreeting_IsFallen(talk) != 0) {
        texts = &data_020c89f8;
        if (since == VILLAGER_TALK_GREETING_FIRST) {
            talk->no_memory = 1;
        }
    } else if (VillagerTalkGreeting_IsRun(talk) != 0) {
        texts = &data_020c8b28;
        if (since == VILLAGER_TALK_GREETING_FIRST) {
            talk->no_memory = 1;
        }
    } else if (VillagerTalkGreeting_IsFirst(talk, since) != 0) {
        texts = (const VillagerTalkGreetingTexts *) (uintptr_t) VillagerTalkGreeting_FirstTexts(talk, &group, record);
    } else if (since == VILLAGER_TALK_GREETING_OTHER_TOWN) {
        texts = &data_020c8dd8;
        group = 7;
        range = 3;
    } else if (VillagerTalkGreeting_FindPoisonous(talk, &kind, position) != 0) {
        texts = VillagerTalkGreeting_PoisonTexts(talk, kind);
    } else if (VillagerTalkGreeting_HasFlea(talk) != 0) {
        texts = &data_020c8ca0;
    } else if (VillagerTalkGreeting_IsForeign(talk, since) != 0) {
        texts = VillagerTalkGreeting_ForeignTexts(talk);
    } else if (since == VILLAGER_TALK_GREETING_MONTH) {
        texts = &data_020c8d10;
        if (days >= VILLAGER_TALK_GREETING_LONG_DAYS) {
            per_group = 1;
            group = 5;
            range = 1;
        }
    } else if (since == VILLAGER_TALK_GREETING_WEEK) {
        texts = &data_020c89d0;
    } else if (VillagerTalkGreeting_IsStung(talk, entry) != 0) {
        texts = VillagerTalkGreeting_BeeTexts(talk, &group, entry);
    } else if (VillagerTalkGreeting_IsAngry(talk, mood) != 0) {
        texts = &data_020c8a38;
    } else if (VillagerTalkGreeting_IsSad(talk, mood) != 0) {
        texts = &data_020c8970;
    } else if (VillagerTalkGreeting_IsTired(talk, mood) != 0) {
        texts = &data_020c8c88;
    } else if (VillagerCheck_IsIndex161(record) != 0 && FoxShop_Has5012AfterSix() != 0 && FoxShop_CurrentPlayerMarked() == 0) {
        FoxShopText password;
        FoxShopText_Construct(&password);
        FoxPassword_LoadLetterText(FoxShop_Password((FoxShop *) (void *) data_021f3b30), &password);
        texts = &data_020c8ac8;
        TalkObject_SetPart((TalkObject *) (void *) greeting_talk(talk), 4, (TextBase *) &password);
        FoxShopText_Destruct(&password);
    } else if (Session_IsLinked(data_020ccf94) == 0 && greeting_memory(talk) != NULL &&
               VillagerMemoryBits_Bit5(greeting_memory(talk)) != 0 && CurrentPockets_FreeSlot() != -1) {
        VillagerTalkGreetingItemList list;
        u16 item;
        texts = &data_020c8c70;
        ItemList_Construct((ItemList *) &list, 0, 0);
        ItemLists_Draw(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
        talk->gift = item;
        ItemList_Destruct(&list);
        talk->gift_from_items = 0;
        SceneBase_PutItemName(greeting_base(talk), (int) (uintptr_t) &talk->gift, 0, VILLAGER_TALK_GREETING_ITEM_KIND);
        if (greeting_memory(talk) != NULL) {
            VillagerMemoryBits_ClearBit5(greeting_memory(talk));
        }
    } else if (SceneQuery_CurrentInNook() != 0) {
        texts = &data_020c8c38;
        if (greeting_mode(record) != VILLAGER_TALK_GREETING_MODE_SHOP1) {
            group = 1;
        }
    } else if (SceneQuery_Current() == VILLAGER_TALK_GREETING_SCENE_SHOP2) {
        texts = &data_020c8c90;
        if (greeting_mode(record) != VILLAGER_TALK_GREETING_MODE_SHOP2) {
            group = 1;
        }
    } else if (SceneQuery_CurrentIn20() != 0 && SceneQuery_IndexIn20(SceneQuery_Current()) == 1) {
        texts = &data_020c8a80;
    } else if (since == VILLAGER_TALK_GREETING_EARLIER_DAY) {
        if (SceneQuery_CurrentIn11() != 0) {
            texts = &data_020c8a78;
        } else if (falling == VILLAGER_TALK_GREETING_RAIN) {
            texts = &data_020c8cf0;
        } else if (falling == VILLAGER_TALK_GREETING_SNOW) {
            texts = &data_020c8a18;
        } else {
            texts = &data_020c8b78;
        }
        group = Calendar_PartOfDay();
    } else if (greeting_mode(record) == VILLAGER_TALK_GREETING_MODE_BOOM) {
        texts = &data_020c8a00;
    } else if (VillagerTally_Level(VillagerState_Tally(entry)) != 0) {
        texts = &data_020c8b90;
        if (VillagerTally_Level(VillagerState_Tally(entry)) == 2) {
            group = 1;
        }
    } else if (mood == VILLAGER_TALK_GREETING_MOOD_JOY) {
        texts = &data_020c8b60;
        group = Calendar_PartOfDay();
    } else {
        texts = greeting_weather(falling, &group, &range);
    }

    if (texts != NULL) {
        if (per_group == -1) {
            per_group = texts->count;
        }
        VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, personality, (int) texts->texts,
                                   (u8) per_group, group, range);
    }

    if (days > 0) {
        int weeks = days >= 70 ? 9 : days / 7;
        int months = days >= VILLAGER_TALK_GREETING_LONG_DAYS ? 12 : days / 30;
        SceneBase_PutValue(greeting_base(talk), weeks, 2, 1, 0, 0);
        SceneBase_PutValue(greeting_base(talk), months, 3, 2, 0, 0);
    }
    entry->flags |= VILLAGER_STATE_FLAG_2;
    greeting_name(talk, out);
}
CLEAN_AS(func_0202bdb4, VillagerTalkGreeting_Line)

/* func_0202c230: whether the villager is tired (its mood 4). */
int VillagerTalkGreeting_IsTired(VillagerTalk *talk, int mood)
{
    (void) talk;
    return mood == VILLAGER_TALK_GREETING_MOOD_TIRED;
}
CLEAN_AS(func_0202c230, VillagerTalkGreeting_IsTired)

/* func_0202c23c: whether the villager is sad (its mood 3). */
int VillagerTalkGreeting_IsSad(VillagerTalk *talk, int mood)
{
    (void) talk;
    return mood == VILLAGER_TALK_GREETING_MOOD_SAD;
}
CLEAN_AS(func_0202c23c, VillagerTalkGreeting_IsSad)

/* func_0202c248: whether the villager is angry (its mood 2). */
int VillagerTalkGreeting_IsAngry(VillagerTalk *talk, int mood)
{
    (void) talk;
    return mood == VILLAGER_TALK_GREETING_MOOD_ANGRY;
}
CLEAN_AS(func_0202c248, VillagerTalkGreeting_IsAngry)

/* func_0202c254: "ai_bee", the group the part of the day; flag 0 of the villager's state entry
 * set so that it is said once. */
const VillagerTalkGreetingTexts *VillagerTalkGreeting_BeeTexts(VillagerTalk *talk, int *group, VillagerState *entry)
{
    (void) talk;
    *group = Calendar_PartOfDay();
    entry->flags |= VILLAGER_STATE_FLAG_0;
    return &data_020c89f0;
}
CLEAN_AS(func_0202c254, VillagerTalkGreeting_BeeTexts)

/* func_0202c27c: whether the current player was stung by bees (PlayerRecord_Flag0) and the
 * villager has not said so yet (flag 0 of its state entry). */
int VillagerTalkGreeting_IsStung(VillagerTalk *talk, VillagerState *entry)
{
    (void) talk;
    u8 *player = PlayerRecords_Current();
    if ((entry->flags & VILLAGER_STATE_FLAG_0) != 0 || player == NULL) {
        return 0;
    }
    return PlayerRecord_Flag0(player) != 0;
}
CLEAN_AS(func_0202c27c, VillagerTalkGreeting_IsStung)

/* func_0202c2a8: whether the villager has fleas (its scene object's virtual function at
 * 0xb0). */
int VillagerTalkGreeting_HasFlea(VillagerTalk *talk)
{
    return (int) greeting_virtual(talk, VILLAGER_TALK_GREETING_SLOT_FLEA);
}
CLEAN_AS(func_0202c2a8, VillagerTalkGreeting_HasFlea)

/* func_0202c2c4: "ai_poison"; the insect of `kind` (one of the poisonous kinds at random for
 * -1) named in the talk's slot 0. */
const VillagerTalkGreetingTexts *VillagerTalkGreeting_PoisonTexts(VillagerTalk *talk, int kind)
{
    if (kind == VILLAGER_TALK_GREETING_NO_KIND) {
        kind = data_020c892c[MainRandom_Below(VILLAGER_TALK_GREETING_POISON_KINDS)];
    }
    if (kind != VILLAGER_TALK_GREETING_NO_KIND) {
        u16 item =
            (u16) ((unsigned int) kind < VILLAGER_TALK_GREETING_INSECT_KINDS ? VILLAGER_TALK_GREETING_INSECT_FIRST + kind
                                                                             : VILLAGER_TALK_GREETING_INSECT_FIRST);
        SceneBase_PutItemName(greeting_base(talk), (int) (uintptr_t) &item, 0, VILLAGER_TALK_GREETING_ITEM_KIND);
    }
    return &data_020c8b40;
}
CLEAN_AS(func_0202c2c4, VillagerTalkGreeting_PoisonTexts)

/* func_0202c31c: the kind of a poisonous insect within 0x6000 of `position` into `*kind` (-1
 * for none); whether there is one. */
int VillagerTalkGreeting_FindPoisonous(VillagerTalk *talk, int *kind, const Vec3 *position)
{
    (void) talk;
    Vec3 at;
    *kind = VillagerTalkGreeting_FindNearInsect(&at, data_020c892c, VILLAGER_TALK_GREETING_POISON_KINDS, position,
                                                VILLAGER_TALK_GREETING_POISON_DISTANCE);
    return *kind != VILLAGER_TALK_GREETING_NO_KIND;
}
CLEAN_AS(func_0202c31c, VillagerTalkGreeting_FindPoisonous)

/* func_0202c350: "ai_foreign"; the town of the villager's memory of the player (when there is
 * one) named in the talk's slot 1. */
const VillagerTalkGreetingTexts *VillagerTalkGreeting_ForeignTexts(VillagerTalk *talk)
{
    if (greeting_memory(talk) != NULL) {
        int town = VillagerMemoryEntry_Town(greeting_memory(talk));
        SceneBase_PutNameAt2(greeting_base(talk), (unsigned int) town, 1);
    }
    return &data_020c8cf8;
}
CLEAN_AS(func_0202c350, VillagerTalkGreeting_ForeignTexts)

/* func_0202c37c: whether the memory's town is not this one (VillagerTalkGreeting_SinceLastTalk
 * said 5). */
int VillagerTalkGreeting_IsForeign(VillagerTalk *talk, int since)
{
    (void) talk;
    return since == VILLAGER_TALK_GREETING_FOREIGN;
}
CLEAN_AS(func_0202c37c, VillagerTalkGreeting_IsForeign)

/* func_0202c388: the first meeting's text set (its address), by how the villager came to the
 * town (VillagerStatus_Came; 1 counts as 0 for a current player of another town or none): for 2
 * the town it came from is named in the talk's slot 1, else `*group` is the part of the day. */
int VillagerTalkGreeting_FirstTexts(VillagerTalk *talk, int *group, u8 *villager)
{
    u8 *player = PlayerRecords_Current();
    int came = VillagerStatus_Came(villager);
    if (came == VILLAGER_TALK_GREETING_CAME_1 && PlayerId_WhichTown(PlayerRecord_Player(player)) != 0) {
        came = 0;
    }
    if (came == VILLAGER_TALK_GREETING_CAME_FROM_TOWN) {
        SceneBase_PutNameAt2(greeting_base(talk), (unsigned int) (uintptr_t) VillagerHome_LastTown(villager), 1);
    } else {
        *group = Calendar_PartOfDay();
    }
    /* VillagerStatus_Came gives 0 to 2, the sets of the table; the address is made the same way
     * for any other number. */
    return (int) ((uintptr_t) data_020c8f64 + (uintptr_t) came * sizeof data_020c8f64[0]);
}
CLEAN_AS(func_0202c388, VillagerTalkGreeting_FirstTexts)

/* func_0202c3e4: whether this is a first meeting (VillagerTalkGreeting_SinceLastTalk said 0). */
int VillagerTalkGreeting_IsFirst(VillagerTalk *talk, int since)
{
    (void) talk;
    return since == VILLAGER_TALK_GREETING_FIRST;
}
CLEAN_AS(func_0202c3e4, VillagerTalkGreeting_IsFirst)

/* func_0202c3f0: in the town's field, whether the player runs (overlay 3). */
int VillagerTalkGreeting_IsRun(VillagerTalk *talk)
{
    (void) talk;
    unsigned int town = data_020e54a8 == 0 ? 1 : 0;
    return town != 0 && TownInsect_EventShown() != 0;
}
CLEAN_AS(func_0202c3f0, VillagerTalkGreeting_IsRun)

/* func_0202c420: whether the player fell: never. */
int VillagerTalkGreeting_IsFallen(VillagerTalk *talk)
{
    (void) talk;
    return 0;
}
CLEAN_AS(func_0202c420, VillagerTalkGreeting_IsFallen)

/* func_0202c424: how the villager last met the current player (the answers are listed in
 * villager_talk_greeting.h), from the villager's memory of the player; `*days` gets the days
 * since then when the answer depends on them (1 to 4). The villager's own record is asked of
 * its scene object (the virtual function at 0x64) for flag 2 of its state entry. */
int VillagerTalkGreeting_SinceLastTalk(VillagerTalk *talk, int *days)
{
    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    DateTime now = {0};
    if (greeting_memory(talk) == NULL) {
        return VILLAGER_TALK_GREETING_FIRST;
    }
    if (player != NULL && PlayerId_IsSet(player) != 0 && PlayerId_WhichTown(player) != 0) {
        const u8 *current_town = (const u8 *) PlayerId_Town(player);
        const u8 *memory_town = (const u8 *) (PlayerId_Town(VillagerMemoryEntry_Player(greeting_memory(talk))));
        if (greeting_towns_differ(memory_town, current_town)) {
            return VILLAGER_TALK_GREETING_OTHER_TOWN;
        }
    }
    DateTime_Now(&now);
    const DateTime *when = (const DateTime *) (uintptr_t) VillagerMemoryEntry_When(greeting_memory(talk));
    const u8 *memory_town = (const u8 *) (uintptr_t) VillagerMemoryEntry_Town(greeting_memory(talk));
    if (greeting_towns_differ(data_021dc7aa, memory_town)) {
        return VILLAGER_TALK_GREETING_FOREIGN;
    }
    if (DateTime_Compare(when, &now, VILLAGER_TALK_GREETING_ALL_FIELDS) == 1) {
        return VILLAGER_TALK_GREETING_EARLIER_DAY;
    }

    u8 *own = (u8 *) (uintptr_t) greeting_virtual(talk, VILLAGER_TALK_GREETING_SLOT_RECORD);
    int greeted = 0;
    if (own != NULL && NpcId_IsValid(TownVillager_NpcId(own)) != 0 && VillagerStatus_StateEntry(own) != NULL &&
        (VillagerStatus_StateEntry(own)->flags & VILLAGER_STATE_FLAG_2) != 0) {
        greeted = 1;
    }
    *days = DateTime_DaysBetween(when, &now);
    if (PlayerId_WhichTown(player) != 0) {
        return *days >= 1 && greeted == 0 ? VILLAGER_TALK_GREETING_EARLIER_DAY : VILLAGER_TALK_GREETING_TODAY;
    }
    if (*days >= VILLAGER_TALK_GREETING_MONTH_DAYS) {
        return VILLAGER_TALK_GREETING_MONTH;
    }
    if (*days >= VILLAGER_TALK_GREETING_WEEK_DAYS) {
        return VILLAGER_TALK_GREETING_WEEK;
    }
    return *days >= 1 && greeted == 0 ? VILLAGER_TALK_GREETING_EARLIER_DAY : VILLAGER_TALK_GREETING_TODAY;
}
CLEAN_AS(func_0202c424, VillagerTalkGreeting_SinceLastTalk)

/* func_0202c934: in the town's field, the first of the eight insects (overlay 3) whose kind is
 * one of the `count` of `kinds` and that is less than `distance` from `position` in the ground
 * plane; its kind (its point left in `*at`), else -1. */
int VillagerTalkGreeting_FindNearInsect(Vec3 *at, const s8 *kinds, int count, const Vec3 *position, fx32 distance)
{
    unsigned int town = data_020e54a8 == 0 ? 1 : 0;
    if (town == 0) {
        return VILLAGER_TALK_GREETING_NO_KIND;
    }
    for (int slot = 0; slot < VILLAGER_TALK_GREETING_INSECT_SLOTS; slot++) {
        int kind = TownInsect_GetPosition(at, slot);
        int found = VillagerTalkGreeting_FindInList(kind, kinds, count);
        if (found == VILLAGER_TALK_GREETING_NO_KIND) {
            continue;
        }
        if (Vec_DistanceXZ(position, at) >= distance) {
            continue;
        }
        return found;
    }
    return VILLAGER_TALK_GREETING_NO_KIND;
}
CLEAN_AS(func_0202c934, VillagerTalkGreeting_FindNearInsect)

/* func_0202c99c: `value` when it is one of the `count` signed bytes of `list`, else -1. */
int VillagerTalkGreeting_FindInList(int value, const s8 *list, int count)
{
    for (int i = 0; i < count; i++) {
        if (list[i] == value) {
            return value;
        }
    }
    return -1;
}
CLEAN_AS(func_0202c99c, VillagerTalkGreeting_FindInList)
