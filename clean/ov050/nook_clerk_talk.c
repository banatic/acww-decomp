/* The clerks' talk scene (nook_clerk_talk.h): the deals, the answers, the ends of lines, the
 * line a talk starts with, the part-time job's lines, the sequences after the screens, and the
 * scene's class. */
#include "nook_clerk_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/actor.h"
#include "main/block_021d27ac.h"
#include "main/calendar.h"
#include "main/camera_control.h"
#include "main/current_pockets.h"
#include "main/game_variables.h"
#include "main/group_params.h"
#include "main/house_record.h"
#include "main/item_code.h"
#include "main/item_object.h"
#include "main/item_traits.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/nook_store.h"
#include "main/npc_id.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/room_interior.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/shops.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/turnip_prices.h"
#include "main/villager_events.h"
#include "main/villager_part.h"
#include "main/villager_part_block.h"
#include "main/villager_part_entry.h"
#include "main/villager_town.h"
#include "ov004/room_camera.h"

static_assert(sizeof(NookClerkLine) == 8, "a line");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");
static_assert(sizeof(PocketsMarks) == 4, "the pockets' marks");
static_assert(sizeof(PlayerIdText) == 0x20, "a name's text");

/* The vtable of its class. */
extern const u8 data_ov050_02265b14[];
/* Its message files. */
extern const char data_ov050_02265804[]; /* "sp_npc_twins" */
extern const char data_ov050_02265814[]; /* "sp_npc_drama2" */
extern const char data_ov050_02265824[]; /* "sp_npc_raccoon" */
extern const char data_ov050_02265834[]; /* "sp_etc_sequence5_1" */
/* The file of the roof's paints' names: "st_roof_paint". */
extern const char data_ov050_02265e9c[];
/* The paints of the roof by the row of the answers asked and the answer (four each). */
extern const u8 data_ov050_022650b4[];
#define NOOK_CLERK_PAINT_ANSWERS 4
/* The line of a dated event of kind 3 by its two fields (rows of six). */
extern const u8 data_ov050_022650c4[][6];
/* The line the talk starts with by talk mode. */
extern const NookClerkLine data_ov050_02265114[NOOK_CLERK_MODES];
/* The state block (its flags), the player's house, Nook's store, the turnip prices, the
 * players' ids (PlayerRecords_FindIndex) and the session of the multiplayer game. */
extern u32 data_021dc7a8[];
extern HouseRecord data_021ebcd4;
#define NOOK_CLERK_HOUSE_IN_STATE 0xf52c
extern NookStore data_021f395c;
extern TurnipPrices data_021f3b0c;
extern u8 data_021dc7bc[];
extern u8 data_021e5a2c[]; /* the town's villagers (VillagerTown) */
extern NetSession *data_020ccf94;
/* A message shown with no file (an empty line). */
extern const u8 data_021f43e8[];

/* The handlers by line: each table is a function-local static the compiler fills from the
 * constants on the first call (bit 0 of its guard says it was). */
typedef struct NookClerkHandler {
    s32 line;
    MemberPointer handler;
} NookClerkHandler;
static_assert(sizeof(NookClerkHandler) == 0xc, "a line's handler");

/* The answers to the lines of the talk's own file (NookClerkTalk_OnPlainAnswer):
 * void (talk, int answer). */
#define NOOK_CLERK_ANSWERS 37
extern NookClerkHandler data_ov050_02265ce0[NOOK_CLERK_ANSWERS];
extern u32 data_ov050_02265ec0;
extern const MemberPointer data_ov050_02265548, data_ov050_02265540, data_ov050_02265538, data_ov050_02265530,
    data_ov050_02265528, data_ov050_02265520, data_ov050_022655f8, data_ov050_022654d8, data_ov050_022654f0,
    data_ov050_022654f8, data_ov050_02265620, data_ov050_02265618, data_ov050_022655f0, data_ov050_02265600,
    data_ov050_022656f8, data_ov050_02265780, data_ov050_022654c8, data_ov050_022654c0, data_ov050_022655a8,
    data_ov050_02265768, data_ov050_02265740, data_ov050_02265728, data_ov050_02265568, data_ov050_02265558,
    data_ov050_02265478, data_ov050_02265480, data_ov050_022654d0, data_ov050_02265518, data_ov050_02265500,
    data_ov050_02265508, data_ov050_022655e8, data_ov050_022657d0, data_ov050_02265440, data_ov050_02265778,
    data_ov050_02265580, data_ov050_02265490, data_ov050_02265488;

/* The answers of the part-time job (NookClerkTalk_OnJobAnswer): one. */
#define NOOK_CLERK_JOB_ANSWERS 1
extern NookClerkHandler data_ov050_022657f8[NOOK_CLERK_JOB_ANSWERS];
extern u32 data_ov050_02265ec8;
extern const MemberPointer data_ov050_02265660;

/* The answer handlers by situation (NookClerkTalk_OnAnswer): the plain ones, at talk mode 0xf
 * (a dated event), and at work. */
extern MemberPointer data_ov050_02265ef0[3];
extern u32 data_ov050_02265ed0;
extern const MemberPointer data_ov050_02265570, data_ov050_02265700, data_ov050_02265560;
#define NOOK_CLERK_ANSWERS_PLAIN 0
#define NOOK_CLERK_ANSWERS_DATED 1
#define NOOK_CLERK_ANSWERS_JOB 2

/* The ends of the lines of the talk's own file (NookClerkTalk_OnLineEnded): void (talk). */
#define NOOK_CLERK_LINE_ENDS 13
extern NookClerkHandler data_ov050_022659bc[NOOK_CLERK_LINE_ENDS];
extern u32 data_ov050_02265ecc;
extern const MemberPointer data_ov050_02265650, data_ov050_02265668, data_ov050_022656d0, data_ov050_02265730,
    data_ov050_02265770, data_ov050_022655c8, data_ov050_022655c0, data_ov050_022655b8, data_ov050_022655b0,
    data_ov050_02265788, data_ov050_022655a0, data_ov050_02265760, data_ov050_02265750;

/* The ends of the part-time job's lines (NookClerkTalk_OnJobLineEnded): void (talk, part). */
#define NOOK_CLERK_JOB_LINE_ENDS 24
extern NookClerkHandler data_ov050_02265bc0[NOOK_CLERK_JOB_LINE_ENDS];
extern u32 data_ov050_02265ec4;
extern const MemberPointer data_ov050_022656f0, data_ov050_022656e8, data_ov050_022656e0, data_ov050_022656d8,
    data_ov050_02265550, data_ov050_022656c8, data_ov050_022656c0, data_ov050_022656b8, data_ov050_022656b0,
    data_ov050_022656a8, data_ov050_022656a0, data_ov050_02265698, data_ov050_02265690, data_ov050_02265688,
    data_ov050_02265680, data_ov050_02265678, data_ov050_02265670, data_ov050_02265498, data_ov050_02265610,
    data_ov050_02265658, data_ov050_02265510, data_ov050_02265648, data_ov050_02265640, data_ov050_02265638;

/* The sequences (NookClerkTalk_SetSequence). */
extern MemberPointer data_ov050_02265ed8[NOOK_CLERK_SEQUENCES];
extern u32 data_ov050_02265ed4;
extern const MemberPointer data_ov050_02265718, data_ov050_02265710, data_ov050_02265708;
/* The null member pointer. */
extern const MemberPointer __ptmf_null;

/* The game's functions handed to the game: the test of the pockets' items for an errand, and
 * of an empty pocket. */
extern unsigned short func_ov050_022637c0(unsigned short *r0, int r1);
extern int func_ov050_022634b4(unsigned short *p);

#define NOOK_CLERK_NO_LINE 0xff
#define NOOK_CLERK_NO_ITEM 0xfff1

/* The game variable (bank 0) that, when set, makes the clerks act as when linked; the player
 * record's flag set while the player works for Tom Nook. */
#define NOOK_CLERK_TALK_VARIABLE 0x4a
#define NOOK_CLERK_TALK_JOB_FLAG 1

/* The vtable slot of the scene that resets it, the first of the job's lines by type (0xb), and
 * the job's line ends. */
#define NOOK_CLERK_TALK_SLOT_RESET 0x08
#define NOOK_CLERK_TALK_SLOT_JOB_LINE 0x88
#define NOOK_CLERK_TALK_SLOT_JOB_ENDED 0xa8

/* The kinds of what a value put in the talk is shown as (SceneBase_PutValue, PutItemName). */
#define NOOK_CLERK_VALUE_BELLS 10
#define NOOK_CLERK_VALUE_TURNIPS 3
#define NOOK_CLERK_VALUE_ITEM 7

/* The item classes of the deals (their codes). */
#define NOOK_CLERK_WALLPAPER_FIRST 0x1100
#define NOOK_CLERK_WALLPAPER_LAST 0x1143
#define NOOK_CLERK_PAINT_FIRST 0x1521
#define NOOK_CLERK_PAINT_LAST 0x1530
#define NOOK_CLERK_TURNIPS_FIRST 0x1531
#define NOOK_CLERK_TURNIPS_LAST 0x153a
#define NOOK_CLERK_FOSSIL_FIRST 0x38e4
#define NOOK_CLERK_FOSSIL_LAST 0x3933
#define NOOK_CLERK_FOSSIL_KINDS 0x14
#define NOOK_CLERK_FOSSIL_ASSESSED 0x3934
#define NOOK_CLERK_ERRAND_FIRST 0x155f
#define NOOK_CLERK_ERRAND_LAST 0x1560
#define NOOK_CLERK_ERRAND_STATE 2
/* The uniform of the part-time job, the item 0x36fc the player brings back (its pocket in
 * NookClerkTalk.package_slot), and the item 0x4a30 given for it. */
#define NOOK_CLERK_UNIFORM 0x11a8
#define NOOK_CLERK_PACKAGE 0x36fc
#define NOOK_CLERK_PACKAGE_GIFT 0x4a30

/* The dated events of kind 3 and Tom Nook's person codes (an errand for him names any). */
#define NOOK_CLERK_TALK_EVENT_KIND 3
#define NOOK_CLERK_TALK_FIRST_LOOK 0xd019
#define NOOK_CLERK_TALK_LOOKS 4

/* The state block's flags: the loan's news told (0x10), the house's growth told (0xd, 0xe). */
#define NOOK_CLERK_STATE_LOAN_TOLD 0x10
#define NOOK_CLERK_STATE_HOUSE_GROWN 0xd
#define NOOK_CLERK_STATE_HOUSE_DONE 0xe

/* The player record's flags of the store's news: the upgrades told (0x24 to 0x26) and the
 * date of the record's field 0x2416 (3). */
#define NOOK_CLERK_FLAG_UPGRADE_1 0x24
#define NOOK_CLERK_FLAG_UPGRADE_2 0x25
#define NOOK_CLERK_FLAG_UPGRADE_3 0x26
#define NOOK_CLERK_FLAG_FIELD_DATE 3

/* The part-time job's step of the errand block's object (main's villager_part.h). */
#define NOOK_CLERK_JOB_TYPE_FIRST 0x0b
#define NOOK_CLERK_JOB_TYPE_LAST 0x12

/* The modes of the screens (SceneCommand_SetScreenMode): the items to sell, the catalog. */
#define NOOK_CLERK_SCREEN_SELL 0x1d
#define NOOK_CLERK_SCREEN_ORDER 0x3e

static TalkObject *ntalk_object(NookClerkTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *ntalk_scene(NookClerkTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

static int ntalk_owner(NookClerkTalk *talk)
{
    return (int) (uintptr_t) talk->owner;
}

/* The line shown. */
static u8 ntalk_shown(const NookClerkTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The answer picked in the talk's choices. */
static int ntalk_answer(NookClerkTalk *talk)
{
    return (int) TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
}

/* Line `line` of `file` shown. */
static void ntalk_say(NookClerkTalk *talk, u8 line, const char *file)
{
    TalkObject_SetMessage(ntalk_object(talk), &line, file);
}

/* The talk's file: Tom Nook's, or the twins'. */
static const char *ntalk_file(NookClerkTalk *talk)
{
    return NookClerk_IsNook(talk->owner) ? data_ov050_02265824 : data_ov050_02265804;
}

/* Whether the item code at `item` is empty (0xfff1, or a variant of the empty item). */
static int ntalk_is_empty(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = NOOK_CLERK_NO_ITEM;
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(&none);
    }
    return *item == NOOK_CLERK_NO_ITEM;
}

static int ntalk_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* The object of block 0 of a villager part: the job's errand. */
static ItemObject *ntalk_errand(VillagerPart *part)
{
    return (ItemObject *) (void *) VillagerPartBlock_Object(VillagerPart_Block(part, 0));
}

/* The current player's villager part. */
static VillagerPart *ntalk_current_part(void)
{
    return (VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current());
}

/* The speaker shows `item` (scene command 3, motion 13) with `a`. */
static void ntalk_show_item(NookClerkTalk *talk, u16 item, u32 a)
{
    SceneCommand_RequestMotion13(ntalk_scene(talk), &item, a, 5, 0);
}

/* `item` given to the pockets in `state`; whether it went in. */
static int ntalk_give(u16 item, int state)
{
    return CurrentPockets_Give(&item, state);
}

/* Calls `handler` with the talk (adjusted) and `arg`. */
static void ntalk_call(const MemberPointer *handler, NookClerkTalk *talk, int arg)
{
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(handler, self))(self, arg);
}

/* The handlers of `table` (filled from `constants` once) whose line is the one shown, each
 * called with `arg`. */
static void ntalk_dispatch(NookClerkTalk *talk, u32 *guard, NookClerkHandler *table, const MemberPointer *const *constants,
                           u32 count, int arg)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        for (u32 i = 0; i < count; i++) {
            table[i].handler = *constants[i];
        }
        *guard = flags | 1;
    }
    for (u32 i = 0; i < count; i++) {
        const NookClerkHandler *entry = &table[i];
        if (entry->line == ntalk_shown(talk)) {
            ntalk_call(&entry->handler, talk, arg);
        }
    }
}

/* ---- The deals */

/* func_ov050_02260dd4: the item on display bought: noted as bought, its price taken, the item
 * given to the pockets (state 0), the player's index among the players looked up (not used),
 * the item taken from Nook's store at its tile, and the villagers told (event 4). */
void NookClerkTalk_Buy(NookClerkTalk *talk)
{
    NookClerk *owner = talk->owner;
    owner->bought = 1;
    SceneBells_Take(ntalk_owner(talk), talk->price);
    CurrentPockets_Give(&talk->owner->item, 0);
    PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (void *) PlayerRecord_Player(PlayerRecords_Current()));
    Shops_TakeFromStore((void *) (uintptr_t) (u32) talk->owner->tile_x, (void *) (uintptr_t) (u32) talk->owner->tile_z,
                        talk->price, SceneQuery_Current());
    VillagerEvent_Report4();
}
CLEAN_AS(func_ov050_02260dd4, NookClerkTalk_Buy)

/* func_ov050_02260e50 (the job's answer at line 0x22): the first answer gives line 0x25 with a
 * free pocket slot, else 0x17. */
void NookClerkTalk_OnAnswerJobSlot(NookClerkTalk *talk, int answer)
{
    PlayerRecords_Current();
    if (answer == 0) {
        talk->line = CurrentPockets_FreeSlot() >= 0 ? 0x25 : 0x17;
    }
}
CLEAN_AS(func_ov050_02260e50, NookClerkTalk_OnAnswerJobSlot)

/* func_ov050_02260e80 (the answers at work): the handler of the line shown gets the answer
 * picked; the line it asks for is shown from "sp_etc_sequence5_1". */
void NookClerkTalk_OnJobAnswer(NookClerkTalk *talk, int arg)
{
    static const MemberPointer *const handlers[NOOK_CLERK_JOB_ANSWERS] = {
        &data_ov050_02265660, /* 0x22: NookClerkTalk_OnAnswerJobSlot */
    };
    (void) arg;
    int answer = ntalk_answer(talk);
    talk->line = NOOK_CLERK_NO_LINE;
    ntalk_dispatch(talk, &data_ov050_02265ec8, data_ov050_022657f8, handlers, NOOK_CLERK_JOB_ANSWERS, answer);
    if (talk->line != NOOK_CLERK_NO_LINE) {
        ntalk_say(talk, (u8) talk->line, data_ov050_02265834);
    }
}
CLEAN_AS(_ZN18Obj_ov050_02265b1419func_ov050_02260e80Ei, NookClerkTalk_OnJobAnswer)

/* The common answers (NookClerkTalk_OnAnswerCommon and the answers at talk mode 0xf): 0 line 7;
 * 1 line 0x59 unless this system is the host or alone, then 0x18 when a letter can be posted,
 * else 0x17; 2 today's turnip price put in (value 1) and line 0x16, on Sunday line 0x0d; and
 * `answer_3`'s line for the fourth. */
static void ntalk_common_answer(NookClerkTalk *talk, int answer, int line_3)
{
    switch (answer) {
        case 0:
            talk->line = 7;
            break;
        case 1:
            if (TalkChecks_IsHostOrAlone() == 0) {
                talk->line = 0x59;
            } else if (Shops_CanMail() != 0) {
                talk->line = 0x18;
            } else {
                talk->line = 0x17;
            }
            break;
        case 2:
            if (Calendar_TodayWeekday() != 0) {
                int price = TurnipPrices_Current(&data_021f3b0c);
                SceneBase_PutValue(&talk->base, price, 1, NOOK_CLERK_VALUE_TURNIPS, 0, 0);
                talk->line = 0x16;
            } else {
                talk->line = 0x0d;
            }
            break;
        case 3:
            if (line_3 >= 0) {
                talk->line = line_3;
            }
            break;
        default:
            break;
    }
}

/* func_ov050_02260f28 (the answers at talk mode 0xf, after a dated event's line): at the lines
 * up to 0x14, unless the fourth answer is picked the talk goes back to mode 5; the answers 0 to
 * 2 as the common ones, 4 line 0x15; the fourth marks Tom Nook's dated event of kind 3 today.
 * The line asked for is shown from "sp_npc_raccoon". */
void NookClerkTalk_OnDatedAnswer(NookClerkTalk *talk)
{
    int answer = ntalk_answer(talk);
    PlayerRecords_Current();
    if (ntalk_shown(talk) > 0x14) {
        return;
    }
    talk->line = NOOK_CLERK_NO_LINE;
    if (answer != 3) {
        NookClerkTalk_SetMode(talk, NOOK_CLERK_MODE_NOOK_TALKED);
    }
    if (answer == 3) {
        if (NookClerk_IsNook(talk->owner)) {
            u8 event[2];
            if (TalkChecks_TodaysEventOfKind(ntalk_owner(talk), event, NOOK_CLERK_TALK_EVENT_KIND)) {
                TalkChecks_MarkDayEvent(ntalk_owner(talk), event);
            }
        }
    } else if (answer == 4) {
        talk->line = 0x15;
    } else {
        ntalk_common_answer(talk, answer, -1);
    }
    if (talk->line != NOOK_CLERK_NO_LINE) {
        u8 line = (u8) talk->line;
        TalkObject_SetMessage(ntalk_object(talk), &line, data_ov050_02265824);
    }
}
CLEAN_AS(func_ov050_02260f28, NookClerkTalk_OnDatedAnswer)

/* func_ov050_02261040 (the answer at line 0x46): unless cancelled (answer 4), the paint of row
 * 3 picked and line 0x48. */
void NookClerkTalk_OnAnswerPaintRow3(NookClerkTalk *talk, int answer)
{
    if (answer == 4) {
        return;
    }
    NookClerkTalk_PickPaint(talk, 3, (unsigned int) answer);
    talk->line = 0x48;
}
CLEAN_AS(func_ov050_02261040, NookClerkTalk_OnAnswerPaintRow3)

/* func_ov050_0226105c (the answer at line 0x45): the same with row 2. */
void NookClerkTalk_OnAnswerPaintRow2(NookClerkTalk *talk, int answer)
{
    if (answer != 4) {
        NookClerkTalk_PickPaint(talk, 2, (unsigned int) answer);
        talk->line = 0x48;
    }
}
CLEAN_AS(func_ov050_0226105c, NookClerkTalk_OnAnswerPaintRow2)

/* func_ov050_02261078 (the answer at line 0x44): the same with row 1. */
void NookClerkTalk_OnAnswerPaintRow1(NookClerkTalk *talk, int answer)
{
    if (answer != 4) {
        NookClerkTalk_PickPaint(talk, 1, (unsigned int) answer);
        talk->line = 0x48;
    }
}
CLEAN_AS(func_ov050_02261078, NookClerkTalk_OnAnswerPaintRow1)

/* func_ov050_02261094 (the answers at lines 0x42, 0x43, 0x47, 0x55 and 0x56): the same with row
 * 0. */
void NookClerkTalk_OnAnswerPaintRow0(NookClerkTalk *talk, int answer)
{
    if (answer != 4) {
        NookClerkTalk_PickPaint(talk, 0, (unsigned int) answer);
        talk->line = 0x48;
    }
}
CLEAN_AS(func_ov050_02261094, NookClerkTalk_OnAnswerPaintRow0)

/* func_ov050_022610b0 (the answers at lines 0x0e, 0x11 and 0x40, a sale's price): agreed
 * (answer 0), by where the bells fit: the wallet, paid now and counted as spent at the store
 * (line 0x12); the wallet and bags, counted (line 0x13, paid at its end); nowhere, line 0x5d and
 * the listed items not converted. Declined: the listed items converted only at line 0x40. */
void NookClerkTalk_OnAnswerSale(NookClerkTalk *talk, int answer)
{
    if (answer == 0) {
        switch (SceneBells_Fit(ntalk_owner(talk), talk->price, talk->extra_bags)) {
            case SCENE_BELLS_FIT_WALLET:
                SceneBells_Give(ntalk_owner(talk), talk->price);
                Shops_SpendAtStore(talk->price);
                talk->line = 0x12;
                break;
            case SCENE_BELLS_FIT_BAGS:
                Shops_SpendAtStore(talk->price);
                talk->line = 0x13;
                break;
            case SCENE_BELLS_FIT_NONE:
                talk->line = 0x5d;
                Pockets_ConvertListed(0);
                break;
            default:
                break;
        }
    } else if (ntalk_shown(talk) != 0x40) {
        Pockets_ConvertListed(0);
    } else {
        Pockets_ConvertListed(1);
    }
}
CLEAN_AS(func_ov050_022610b0, NookClerkTalk_OnAnswerSale)

/* func_ov050_02261138 (the answer at line 0x35): agreed, the item 0x36fc (when its pocket was
 * found) is taken out of the pockets and shown (scene command 4); line 0x37. */
void NookClerkTalk_OnAnswerPackage(NookClerkTalk *talk, int answer)
{
    if (answer != 0) {
        return;
    }
    int slot = talk->package_slot;
    if (slot >= 0) {
        CurrentPockets_Empty(slot);
        u16 item = NOOK_CLERK_PACKAGE;
        SceneCommand_RequestMotion14(ntalk_scene(talk), &item, 0, 5, 0);
    }
    talk->line = 0x37;
}
CLEAN_AS(func_ov050_02261138, NookClerkTalk_OnAnswerPackage)

/* func_ov050_02261174 (the answer at line 0x2e, a roof paint's price): agreed, without the
 * bells line 0x21; else line 0x22, the paint noted as bought, its price taken, the player's
 * index among the players looked up (not used) and the paint taken from Nook's store at its
 * tile (the paint is not given to the pockets). */
void NookClerkTalk_OnAnswerPaint(NookClerkTalk *talk, int answer)
{
    if (answer != 0) {
        return;
    }
    if (SceneBells_CanPay(ntalk_owner(talk), talk->price) == 0) {
        talk->line = 0x21;
        return;
    }
    talk->line = 0x22;
    talk->owner->bought = 1;
    SceneBells_Take(ntalk_owner(talk), talk->price);
    PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (void *) PlayerRecord_Player(PlayerRecords_Current()));
    NookClerk *owner = talk->owner;
    Shops_TakeFromStore((void *) (uintptr_t) (u32) owner->tile_x, (void *) (uintptr_t) (u32) owner->tile_z, talk->price,
                        SceneQuery_Current());
}
CLEAN_AS(func_ov050_02261174, NookClerkTalk_OnAnswerPaint)

/* The item on display bought when the player has a free pocket slot and the bells: line 0x20
 * (no room), 0x21 (no bells) or 0x22 (bought, NookClerkTalk_Buy). */
static void ntalk_buy_if_able(NookClerkTalk *talk)
{
    if (CurrentPockets_FreeSlot() < 0) {
        talk->line = 0x20;
    } else if (SceneBells_CanPay(ntalk_owner(talk), talk->price) == 0) {
        talk->line = 0x21;
    } else {
        talk->line = 0x22;
        NookClerkTalk_Buy(talk);
    }
}

/* func_ov050_02261200 (the answer at line 0x2b, wallpaper or a carpet): 0, bought
 * (ntalk_buy_if_able); 1, tried on in the room: wallpaper with the camera's mode 11, a
 * carpet with mode 12. */
void NookClerkTalk_OnAnswerTryOn(NookClerkTalk *talk, int answer)
{
    if (answer == 0) {
        ntalk_buy_if_able(talk);
    } else if (answer == 1) {
        u16 *item = &talk->owner->item;
        if (ntalk_is_empty(item) == 0) {
            if (ntalk_in(talk->owner->item, NOOK_CLERK_WALLPAPER_FIRST, NOOK_CLERK_WALLPAPER_LAST)) {
                RoomCamera_SetMode11();
                RoomInterior_SetWallpaper(&talk->owner->item, 0, 1, 1);
            } else {
                RoomCamera_SetMode12();
                RoomInterior_SetCarpet(&talk->owner->item, 0, 1, 1);
            }
        }
    }
}
CLEAN_AS(func_ov050_02261200, NookClerkTalk_OnAnswerTryOn)

/* func_ov050_022612f4 (the answer at line 0x2c, after a try-on): the room's own wallpaper or
 * carpet sent again and the camera's previous mode; then as NookClerkTalk_OnAnswerBuy. */
void NookClerkTalk_OnAnswerEndTryOn(NookClerkTalk *talk, int answer)
{
    u16 *item = &talk->owner->item;
    if (ntalk_is_empty(item) == 0) {
        if (ntalk_in(talk->owner->item, NOOK_CLERK_WALLPAPER_FIRST, NOOK_CLERK_WALLPAPER_LAST)) {
            RoomInterior_ResendWallpaper(1);
        } else {
            RoomInterior_ResendCarpet(1);
        }
        CameraControl_SetPreviousMode();
    }
    NookClerkTalk_OnAnswerBuy(talk, answer);
}
CLEAN_AS(func_ov050_022612f4, NookClerkTalk_OnAnswerEndTryOn)

/* func_ov050_02261390 (the answers at lines 0x1e, 0x2a and 0x31, an item's price): agreed,
 * without a free pocket slot line 0x20, without the bells line 0x21, else line 0x22 and the
 * item bought (NookClerkTalk_Buy). */
void NookClerkTalk_OnAnswerBuy(NookClerkTalk *talk, int answer)
{
    if (answer == 0) {
        ntalk_buy_if_able(talk);
    }
}
CLEAN_AS(func_ov050_02261390, NookClerkTalk_OnAnswerBuy)

/* func_ov050_022613d8 (the answer at line 0x1a, an order from the catalog): agreed, with the
 * bells their price is taken, line 0x1c, and the item (unless empty) is mailed by Tom Nook;
 * without them line 0x1d. Declined, line 0x1b. */
void NookClerkTalk_OnAnswerOrder(NookClerkTalk *talk, int answer)
{
    if (answer != 0) {
        talk->line = 0x1b;
        return;
    }
    if (SceneBells_CanPay(ntalk_owner(talk), talk->price) == 0) {
        talk->line = 0x1d;
        return;
    }
    SceneBells_Take(ntalk_owner(talk), talk->price);
    talk->line = 0x1c;
    if (ntalk_is_empty(&talk->owner->item) == 0) {
        Shops_MailNookItem(&talk->owner->item);
    }
}
CLEAN_AS(func_ov050_022613d8, NookClerkTalk_OnAnswerOrder)

/* func_ov050_02261480 (the answer at line 0x0a): any but the first, the listed items are not
 * converted. */
void NookClerkTalk_OnAnswerConvert(int unused, int answer)
{
    (void) unused;
    if (answer != 0) {
        Pockets_ConvertListed(0);
    }
}
CLEAN_AS(func_ov050_02261480, NookClerkTalk_OnAnswerConvert)

/* func_ov050_02261494 (the answer at line 5): agreed, the pockets' screen opens on the
 * errand's items (func_ov050_022637c0, argument 13), then sequence 2; else line 15. */
void NookClerkTalk_OnAnswerErrand(NookClerkTalk *talk, int answer)
{
    if (answer == 0) {
        SceneCommand_SetPocketPredicate(ntalk_scene(talk), (PocketPredicate) (uintptr_t) func_ov050_022637c0, 13, 0);
        SceneCommand_RequestScreen(ntalk_scene(talk), SCENE_COMMAND_SCREEN_POCKETS);
        NookClerkTalk_SetSequence(talk, NOOK_CLERK_SEQUENCE_ERRAND);
    } else {
        talk->line = 15;
    }
}
CLEAN_AS(func_ov050_02261494, NookClerkTalk_OnAnswerErrand)

/* func_ov050_022614c8 (the common answers: lines 0, 2, 6, 8, 0xb, 0xc, 0xf, 0x12, 0x17, 0x19,
 * 0x1b to 0x1d, 0x58, 0x59 and 0x5d): 0 to 2 as ntalk_common_answer, 3 line 0x15. */
void NookClerkTalk_OnAnswerCommon(NookClerkTalk *talk, int answer)
{
    PlayerRecords_Current();
    ntalk_common_answer(talk, answer, 0x15);
}
CLEAN_AS(func_ov050_022614c8, NookClerkTalk_OnAnswerCommon)

/* func_ov050_02261560 (the plain answers): the handlers of the line shown get the answer
 * picked; the line one asks for is shown from the talk's file. */
void NookClerkTalk_OnPlainAnswer(NookClerkTalk *talk, int arg)
{
    static const MemberPointer *const handlers[NOOK_CLERK_ANSWERS] = {
        &data_ov050_02265548, /* 0x00: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265540, /* 0x02: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265538, /* 0x05: NookClerkTalk_OnAnswerErrand */
        &data_ov050_02265530, /* 0x06: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265528, /* 0x08: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265520, /* 0x0a: NookClerkTalk_OnAnswerConvert */
        &data_ov050_022655f8, /* 0x0b: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022654d8, /* 0x0c: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022654f0, /* 0x0e: NookClerkTalk_OnAnswerSale */
        &data_ov050_022654f8, /* 0x0f: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265620, /* 0x11: NookClerkTalk_OnAnswerSale */
        &data_ov050_02265618, /* 0x12: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022655f0, /* 0x17: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265600, /* 0x19: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022656f8, /* 0x1a: NookClerkTalk_OnAnswerOrder */
        &data_ov050_02265780, /* 0x1b: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022654c8, /* 0x1c: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022654c0, /* 0x1d: NookClerkTalk_OnAnswerCommon */
        &data_ov050_022655a8, /* 0x1e: NookClerkTalk_OnAnswerBuy */
        &data_ov050_02265768, /* 0x2a: NookClerkTalk_OnAnswerBuy */
        &data_ov050_02265740, /* 0x2b: NookClerkTalk_OnAnswerTryOn */
        &data_ov050_02265728, /* 0x2c: NookClerkTalk_OnAnswerEndTryOn */
        &data_ov050_02265568, /* 0x2e: NookClerkTalk_OnAnswerPaint */
        &data_ov050_02265558, /* 0x31: NookClerkTalk_OnAnswerBuy */
        &data_ov050_02265478, /* 0x35: NookClerkTalk_OnAnswerPackage */
        &data_ov050_02265480, /* 0x40: NookClerkTalk_OnAnswerSale */
        &data_ov050_022654d0, /* 0x42: NookClerkTalk_OnAnswerPaintRow0 */
        &data_ov050_02265518, /* 0x43: NookClerkTalk_OnAnswerPaintRow0 */
        &data_ov050_02265500, /* 0x44: NookClerkTalk_OnAnswerPaintRow1 */
        &data_ov050_02265508, /* 0x45: NookClerkTalk_OnAnswerPaintRow2 */
        &data_ov050_022655e8, /* 0x46: NookClerkTalk_OnAnswerPaintRow3 */
        &data_ov050_022657d0, /* 0x47: NookClerkTalk_OnAnswerPaintRow0 */
        &data_ov050_02265440, /* 0x55: NookClerkTalk_OnAnswerPaintRow0 */
        &data_ov050_02265778, /* 0x56: NookClerkTalk_OnAnswerPaintRow0 */
        &data_ov050_02265580, /* 0x58: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265490, /* 0x59: NookClerkTalk_OnAnswerCommon */
        &data_ov050_02265488, /* 0x5d: NookClerkTalk_OnAnswerCommon */
    };
    (void) arg;
    int answer = ntalk_answer(talk);
    talk->line = NOOK_CLERK_NO_LINE;
    ntalk_dispatch(talk, &data_ov050_02265ec0, data_ov050_02265ce0, handlers, NOOK_CLERK_ANSWERS, answer);
    if (talk->line != NOOK_CLERK_NO_LINE) {
        const char *file = ntalk_file(talk);
        u8 line = (u8) talk->line;
        TalkObject_SetMessage(ntalk_object(talk), &line, file);
    }
}
CLEAN_AS(_ZN18Obj_ov050_02265b1419func_ov050_02261560Ei, NookClerkTalk_OnPlainAnswer)

/* func_ov050_02261830 (vtable slot 0x18, the player's answer): to NookClerkTalk_OnJobAnswer
 * while the player is at work, else to NookClerkTalk_OnDatedAnswer in talk mode 0xf, else to
 * NookClerkTalk_OnPlainAnswer, with `arg`. */
void NookClerkTalk_OnAnswer(NookClerkTalk *talk, int arg)
{
    static const MemberPointer *const kinds[3] = {
        &data_ov050_02265570, /* NookClerkTalk_OnPlainAnswer */
        &data_ov050_02265700, /* NookClerkTalk_OnDatedAnswer */
        &data_ov050_02265560, /* NookClerkTalk_OnJobAnswer */
    };
    MemberTable_InitOnce(&data_ov050_02265ed0, data_ov050_02265ef0, kinds, 3);
    int kind = NOOK_CLERK_ANSWERS_PLAIN;
    u8 *record = PlayerRecords_Current();
    PlayerRecord_VillagerPart(record);
    if (PlayerRecord_TestFlag(record, NOOK_CLERK_TALK_JOB_FLAG) != 0) {
        kind = NOOK_CLERK_ANSWERS_JOB;
    } else if (talk->mode == NOOK_CLERK_MODE_DRAMA) {
        kind = NOOK_CLERK_ANSWERS_DATED;
    }
    ntalk_call(&data_ov050_02265ef0[kind], talk, arg);
}
CLEAN_AS(_ZN18Obj_ov050_02265b1419func_ov050_02261830Ei, NookClerkTalk_OnAnswer)

/* func_ov050_022618d0: the paint `answer` of `row` (data_ov050_022650b4): its name put in part 2
 * of the talk (from "st_roof_paint") and the house's next look ordered with it.
 * REQUIRES: `row` is 0 to 3 and `answer` 0 to 3. */
void NookClerkTalk_PickPaint(NookClerkTalk *talk, int row, unsigned int answer)
{
    u8 paint = data_ov050_022650b4[(row << 2) + answer];
    u8 name = paint;
    TalkObject_LoadPart(ntalk_object(talk), 2, &name, (unsigned int) (uintptr_t) data_ov050_02265e9c);
    HouseRecord_OrderWithLook(&data_021ebcd4, paint);
}
CLEAN_AS(func_ov050_022618d0, NookClerkTalk_PickPaint)

/* ---- The ends of lines */

/* func_ov050_02261908 (the ends of lines 0x49 to 0x53, the house grown): the house's next loan
 * taken. */
void NookClerkTalk_PayLoanLine(void)
{
    HouseRecord_TakeNextLoan(&data_021ebcd4);
}
CLEAN_AS(func_ov050_02261908, NookClerkTalk_PayLoanLine)

/* The items whose first purchase Tom Nook remarks on: the item range, the player record's flag
 * that notes it, and the line. */
typedef struct NookClerkFirstBuy {
    u16 first;
    u16 last;
    u8 flag;
    u8 line;
} NookClerkFirstBuy;

/* func_ov050_02261918 (the end of line 0x23, an item bought): unless the item is empty: the
 * first of the items below bought for the first time (its flag not set yet) gives its line and
 * sets its flag; else, when this system is the host or alone and the clerk is Tom Nook, the
 * first purchase there gives line 0x30 and sets the flag 0x38. Otherwise the talk's message is
 * the empty one (data_021f43e8, no file). */
void NookClerkTalk_ReactToPurchase(NookClerkTalk *talk)
{
    static const NookClerkFirstBuy first_buys[] = {
        {0x1369, 0x1369, 0x29, 0x24}, {0x1376, 0x1376, 0x2a, 0x25}, {0x1374, 0x1374, 0x2b, 0x26}, {0x136b, 0x1372, 0x2c, 0x27},
        {0x1378, 0x1378, 0x2d, 0x28}, {0x137a, 0x137a, 0x2e, 0x29}, {0x151f, 0x151f, 0x2f, 0x39}, {0x156c, 0x156c, 0x37, 0x10},
    };
    if (ntalk_is_empty(&talk->owner->item)) {
        return;
    }
    u8 *record = PlayerRecords_Current();
    for (size_t i = 0; i < sizeof first_buys / sizeof first_buys[0]; i++) {
        const NookClerkFirstBuy *buy = &first_buys[i];
        if (ntalk_in(talk->owner->item, buy->first, buy->last) && PlayerRecord_TestFlag(record, buy->flag) == 0) {
            talk->line = buy->line;
            PlayerRecord_SetFlag(record, buy->flag);
            break;
        }
    }
    if (talk->line == NOOK_CLERK_NO_LINE && TalkChecks_IsHostOrAlone() != 0 && NookClerk_IsNook(talk->owner) != 0 &&
        PlayerRecord_TestFlag(record, 0x38) == 0) {
        talk->line = 0x30;
        PlayerRecord_SetFlag(record, 0x38);
    } else {
        TalkObject_SetMessage(ntalk_object(talk), data_021f43e8, NULL);
    }
}
CLEAN_AS(func_ov050_02261918, NookClerkTalk_ReactToPurchase)

/* func_ov050_02261bb8 (the end of line 0x22, a purchase thanked for): unless the item is
 * empty, a roof paint gives line 0x2f and becomes the house's look; anything else line 0x23. */
void NookClerkTalk_PaintBought(NookClerkTalk *talk)
{
    if (ntalk_is_empty(&talk->owner->item)) {
        return;
    }
    u16 item = talk->owner->item;
    if (ntalk_in(item, NOOK_CLERK_PAINT_FIRST, NOOK_CLERK_PAINT_LAST)) {
        talk->line = 0x2f;
        item = talk->owner->item;
        int look = ntalk_in(item, NOOK_CLERK_PAINT_FIRST, NOOK_CLERK_PAINT_LAST) ? item - NOOK_CLERK_PAINT_FIRST : -1;
        HouseRecord_SetLook(&data_021ebcd4, (unsigned char) look);
    } else {
        talk->line = 0x23;
    }
}
CLEAN_AS(func_ov050_02261bb8, NookClerkTalk_PaintBought)

/* func_ov050_02261c7c (the end of line 0x18): the catalog's screen (mode 0x3e), sequence 1. */
void NookClerkTalk_OpenOrder(NookClerkTalk *talk)
{
    SceneCommand_SetScreenMode(ntalk_scene(talk), NOOK_CLERK_SCREEN_ORDER, 0);
    SceneCommand_RequestScreen(ntalk_scene(talk), SCENE_COMMAND_SCREEN_MODE);
    NookClerkTalk_SetSequence(talk, NOOK_CLERK_SEQUENCE_ORDER);
}
CLEAN_AS(func_ov050_02261c7c, NookClerkTalk_OpenOrder)

/* func_ov050_02261ca0 (the end of line 0x13): the price of the items sold paid. */
void NookClerkTalk_PaySale(NookClerkTalk *talk)
{
    SceneBells_Give(ntalk_owner(talk), talk->price);
}
CLEAN_AS(func_ov050_02261ca0, NookClerkTalk_PaySale)

/* func_ov050_02261cb4 (the end of line 7): the screen of the items to sell (mode 0x1d),
 * sequence 0. */
void NookClerkTalk_OpenSell(NookClerkTalk *talk)
{
    SceneCommand_SetScreenMode(ntalk_scene(talk), NOOK_CLERK_SCREEN_SELL, 0);
    SceneCommand_RequestScreen(ntalk_scene(talk), SCENE_COMMAND_SCREEN_MODE);
    NookClerkTalk_SetSequence(talk, NOOK_CLERK_SEQUENCE_SELL);
}
CLEAN_AS(func_ov050_02261cb4, NookClerkTalk_OpenSell)

/* func_ov050_02261cd8 (the end of line 0x36): the item 0x36fc no longer looked for. */
void NookClerkTalk_PackageDone(NookClerkTalk *talk)
{
    talk->package_slot = -2;
}
CLEAN_AS(func_ov050_02261cd8, NookClerkTalk_PackageDone)

/* func_ov050_02261ce4 (the end of line 0x37): the item 0x4a30 shown (scene command 3) and given
 * to the pockets (state 0); the item 0x36fc to be looked for again; line 0x38. */
void NookClerkTalk_GivePackage(NookClerkTalk *talk)
{
    ntalk_show_item(talk, NOOK_CLERK_PACKAGE_GIFT, 0);
    ntalk_give(NOOK_CLERK_PACKAGE_GIFT, 0);
    talk->package_slot = -1;
    talk->line = 0x38;
}
CLEAN_AS(func_ov050_02261ce4, NookClerkTalk_GivePackage)

/* func_ov050_02261d28 (vtable slot 0x14, a line ended): while the player is at work, to the
 * job's line ends (vtable slot 0xa8). Tom Nook's talk only takes the ends of the lines of
 * "sp_npc_raccoon"; the handlers of the line shown run, and the line one asks for is shown from
 * the talk's file. */
void NookClerkTalk_OnLineEnded(NookClerkTalk *talk)
{
    static const MemberPointer *const handlers[NOOK_CLERK_LINE_ENDS] = {
        &data_ov050_02265650, /* 0x37: NookClerkTalk_GivePackage */
        &data_ov050_02265668, /* 0x36: NookClerkTalk_PackageDone */
        &data_ov050_022656d0, /* 0x07: NookClerkTalk_OpenSell */
        &data_ov050_02265730, /* 0x13: NookClerkTalk_PaySale */
        &data_ov050_02265770, /* 0x18: NookClerkTalk_OpenOrder */
        &data_ov050_022655c8, /* 0x22: NookClerkTalk_PaintBought */
        &data_ov050_022655c0, /* 0x23: NookClerkTalk_ReactToPurchase */
        &data_ov050_022655b8, /* 0x49: NookClerkTalk_PayLoanLine */
        &data_ov050_022655b0, /* 0x4b: NookClerkTalk_PayLoanLine */
        &data_ov050_02265788, /* 0x4d: NookClerkTalk_PayLoanLine */
        &data_ov050_022655a0, /* 0x4f: NookClerkTalk_PayLoanLine */
        &data_ov050_02265760, /* 0x51: NookClerkTalk_PayLoanLine */
        &data_ov050_02265750, /* 0x53: NookClerkTalk_PayLoanLine */
    };
    u8 *record = PlayerRecords_Current();
    PlayerRecord_VillagerPart(record);
    if (PlayerRecord_TestFlag(record, NOOK_CLERK_TALK_JOB_FLAG) != 0) {
        u32 vtable = *(const u32 *) (const void *) talk;
        u32 code = *(const u32 *) (uintptr_t) (vtable + NOOK_CLERK_TALK_SLOT_JOB_ENDED);
        ((void (*)(NookClerkTalk *))(uintptr_t) code)(talk);
        return;
    }
    if (NookClerk_IsNook(talk->owner) != 0 &&
        strncmp((const char *) talk->base.receiver, data_ov050_02265824, strlen(data_ov050_02265824)) != 0) {
        return;
    }
    const char *file = ntalk_file(talk);
    talk->line = NOOK_CLERK_NO_LINE;
    ntalk_dispatch(talk, &data_ov050_02265ecc, data_ov050_022659bc, handlers, NOOK_CLERK_LINE_ENDS, 0);
    if (talk->line != NOOK_CLERK_NO_LINE) {
        u8 line = (u8) talk->line;
        TalkObject_SetMessage(ntalk_object(talk), &line, file);
    }
}
CLEAN_AS(func_ov050_02261d28, NookClerkTalk_OnLineEnded)

/* ---- The line a talk starts with */

/* The part-time job's first line (talk at work): a twin says line 3 of "sp_npc_twins"; else
 * from "sp_etc_sequence5_1": with an item on display talked about, it is forgotten and line 0xb;
 * in talk mode 0x1e line 0xc and the talk goes back to mode 5; else line 0, and with the errand
 * block's object in use, the job's line of its type (vtable slots 0x88 to 0xa4, the types 0x12
 * down to 0xb, each type read again after a slot ran). */
static void ntalk_job_line(NookClerkTalk *talk, NookClerkLine *out, VillagerPart *part)
{
    ItemObject *errand = ntalk_errand(part);
    u16 profile = *(const u16 *) (const void *) (talk->owner->base + 0x0c);
    if (profile == NOOK_CLERK_TWIN_B || profile == NOOK_CLERK_TWIN_A) {
        out->text = data_ov050_02265804;
        out->message = 3;
        return;
    }
    out->text = data_ov050_02265834;
    if (ntalk_is_empty(&talk->owner->item) == 0) {
        talk->owner->item = NOOK_CLERK_NO_ITEM;
        out->message = 0xb;
        return;
    }
    if (talk->mode == NOOK_CLERK_MODE_JOB_DOOR) {
        out->message = 0xc;
        talk->mode = NOOK_CLERK_MODE_NOOK_TALKED;
        return;
    }
    out->message = 0;
    if (ItemObject_IsInUse(errand) == 0) {
        return;
    }
    for (int type = NOOK_CLERK_JOB_TYPE_LAST; type >= NOOK_CLERK_JOB_TYPE_FIRST; type--) {
        if (ItemObject_Type(errand) == type) {
            u32 vtable = *(const u32 *) (const void *) talk;
            u32 slot = NOOK_CLERK_TALK_SLOT_JOB_LINE + 4 * (u32) (type - NOOK_CLERK_JOB_TYPE_FIRST);
            u32 code = *(const u32 *) (uintptr_t) (vtable + slot);
            ((void (*)(NookClerkTalk *, NookClerkLine *))(uintptr_t) code)(talk, out);
        }
    }
}

/* Tom Nook's news when greeting (talk mode 0), in order; whether one was told (its line in
 * `out`):
 * - unless the flag 0x26 is set: with no upgrade of the store pending and its last upgrade
 *   today, the store's level's line (0x59 plus the level) when the clerk was made for the
 *   level's look and its flag (0x24 to 0x26) is not set yet; the flags of the levels up to the
 *   store's are then set;
 * - unless the flag 3 is set: the date of the player record's field 0x2416, when set and not
 *   today, line 0x3b and the flag set;
 * - unless the state block's flag 0x10 is set: the house loan's news (NookClerkTalk_LoanNews)
 *   and the flag set;
 * - the first time today, when the store closes tomorrow for its upgrade: its month and day
 *   put in (7 and 8), talk mode 7, and the daily bit 0 set. */
static int ntalk_news(NookClerkTalk *talk, NookClerkLine *out, u8 *record, int *closing)
{
    if (PlayerRecord_TestFlag(record, NOOK_CLERK_FLAG_UPGRADE_3) == 0) {
        NookUpgrade upgrade = *NookStore_Upgrade(&data_021f395c);
        Date today;
        Calendar_Today(&today);
        out->message = 0;
        if (upgrade.pending == 0) {
            Date day = {upgrade.day, upgrade.month, upgrade.year, upgrade.pending};
            int days = Calendar_DaysFrom(&today, &day);
            u32 code = *(const u32 *) (const void *) (talk->owner->base + 0x08);
            if (code == NOOK_CLERK_TALK_FIRST_LOOK + 1 && PlayerRecord_TestFlag(record, NOOK_CLERK_FLAG_UPGRADE_1) == 0 &&
                days == 0) {
                out->message = (u8) (NookStore_Level(&data_021f395c) + 0x59);
            }
            if (code == NOOK_CLERK_TALK_FIRST_LOOK + 2 && NookStore_Level(&data_021f395c) == 2 &&
                PlayerRecord_TestFlag(record, NOOK_CLERK_FLAG_UPGRADE_2) == 0 && days == 0) {
                out->message = (u8) (NookStore_Level(&data_021f395c) + 0x59);
            }
            if (code == NOOK_CLERK_TALK_FIRST_LOOK + 3 && NookStore_Level(&data_021f395c) == 3 &&
                PlayerRecord_TestFlag(record, NOOK_CLERK_FLAG_UPGRADE_3) == 0 && days == 0) {
                out->message = (u8) (NookStore_Level(&data_021f395c) + 0x59);
            }
            switch (NookStore_Level(&data_021f395c)) {
                case 3:
                    PlayerRecord_SetFlag(record, NOOK_CLERK_FLAG_UPGRADE_3);
                    /* fall through */
                case 2:
                    PlayerRecord_SetFlag(record, NOOK_CLERK_FLAG_UPGRADE_2);
                    /* fall through */
                case 1:
                    PlayerRecord_SetFlag(record, NOOK_CLERK_FLAG_UPGRADE_1);
                    break;
                default:
                    break;
            }
            if (out->message != 0) {
                return 1;
            }
        }
    }
    if (PlayerRecord_TestFlag(record, NOOK_CLERK_FLAG_FIELD_DATE) == 0) {
        const Date *date = (const Date *) (uintptr_t) (u32) PlayerField2416_Date04(
            (PlayerField2416 *) (void *) PlayerRecord_Field2416(record));
        if (date->year != 0 || date->month != 0) {
            Date today;
            Calendar_Today(&today);
            if (Calendar_DaysFrom(&today, date) != 0) {
                out->message = 0x3b;
                PlayerRecord_SetFlag(record, NOOK_CLERK_FLAG_FIELD_DATE);
                return 1;
            }
        }
    }
    if (StateBlock_TestFlag(data_021dc7a8, NOOK_CLERK_STATE_LOAN_TOLD) == 0) {
        out->message = (u8) NookClerkTalk_LoanNews(talk);
        if (out->message != 0) {
            StateBlock_SetFlag(data_021dc7a8, NOOK_CLERK_STATE_LOAN_TOLD);
            return 1;
        }
    }
    if (TalkChecks_TestSetDailyBit(0, 0) == 0 && NookStore_IsClosedTomorrow(&data_021f395c) != 0) {
        Date closed = NookStore_ClosedDay(&data_021f395c);
        SceneBase_PutNumberAlt(&talk->base, (void *) (uintptr_t) closed.month, 7);
        SceneBase_PutNumber(&talk->base, closed.day, 8);
        NookClerkTalk_SetMode(talk, 7);
        *closing = 1;
        TalkChecks_TestSetDailyBit(0, 1);
    }
    return 0;
}

/* func_ov050_02261ed0 (vtable slot 0x78, the line the talk starts with):
 * - at work, the job's first line (ntalk_job_line);
 * - Tom Nook in talk mode 5, unlinked (and without the game variable 0x4a): with the item
 *   0x36fc in the pockets (looked for once) talk mode 0xe; with an errand for him (any of his
 *   codes) mode 0x10; else with a dated event of kind 3 today, its line of "sp_npc_drama2" and
 *   mode 0xf;
 * - in talk mode 0 (from "sp_npc_raccoon") Tom Nook's news (ntalk_news); in modes 0 and 0x11,
 *   unless the store closes tomorrow: a bonus day today gives mode 2 (0x1a for a twin's
 *   greeting), a time sale mode 3 (0x1b), an item of kind 4 in the stock mode 4 (0x1c);
 * - in the other modes with an item on display: in modes 0xc, 0xd, 0x18 and 0x19 the name of
 *   the roof paint (part 2, "st_roof_paint"), and in those and modes 8 to 0xb and 0x14 to
 *   0x17 the store's price (value 4) and the item's name (value 1);
 * then the line of the talk mode (data_ov050_02265114); in mode 0x12 the other twin, when
 * there is one, stands still (state 12). */
void NookClerkTalk_Line(NookClerkTalk *talk, NookClerkLine *out)
{
    u8 *record = PlayerRecords_Current();
    VillagerPartEntry *errands =
        (VillagerPartEntry *) (void *) VillagerPart_Object94((VillagerPart *) (void *) PlayerRecord_VillagerPart(record));
    VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(record);

    if (PlayerRecord_TestFlag(record, NOOK_CLERK_TALK_JOB_FLAG) != 0) {
        ntalk_job_line(talk, out, part);
        return;
    }

    int skip = 0;
    if (NookClerk_IsNook(talk->owner) != 0 && talk->mode == NOOK_CLERK_MODE_NOOK_TALKED &&
        Session_IsLinked(data_020ccf94) == 0 && *GameVariables_Slot(0, NOOK_CLERK_TALK_VARIABLE) == 0) {
        if (talk->package_slot == -1) {
            u16 package = NOOK_CLERK_PACKAGE;
            talk->package_slot = CurrentPockets_FindItem(&package);
        }
        if (talk->package_slot >= 0) {
            talk->mode = 0xe;
            skip = 1;
        }
        for (int i = 0; !skip && i < NOOK_CLERK_TALK_LOOKS; i++) {
            u16 code = (u16) (NOOK_CLERK_TALK_FIRST_LOOK + i);
            if (VillagerPartEntry_Accepts(errands, &code) != 0) {
                talk->mode = 0x10;
                skip = 1;
            }
        }
        u8 event[4];
        if (!skip && TalkChecks_TodaysEventOfKind(ntalk_owner(talk), event, NOOK_CLERK_TALK_EVENT_KIND) != 0) {
            out->text = data_ov050_02265814;
            out->message = data_ov050_022650c4[(event[0] >> 2) & 7][(event[0] >> 5) & 7];
            NookClerkTalk_SetMode(talk, NOOK_CLERK_MODE_DRAMA);
            return;
        }
    }

    if (talk->mode == NOOK_CLERK_MODE_NOOK_GREET || talk->mode == NOOK_CLERK_MODE_TWIN_GREET) {
        int closing = 0;
        if (talk->mode == NOOK_CLERK_MODE_NOOK_GREET) {
            out->text = data_ov050_02265824;
            if (ntalk_news(talk, out, record, &closing)) {
                return;
            }
        }
        if (closing == 0) {
            if (NookStore_IsBonusDayToday(&data_021f395c) != 0) {
                NookClerkTalk_SetMode(talk, talk->mode == NOOK_CLERK_MODE_NOOK_GREET ? 2 : 0x1a);
            } else if (NookStore_IsTimeSale(&data_021f395c) != 0) {
                NookClerkTalk_SetMode(talk, talk->mode == NOOK_CLERK_MODE_NOOK_GREET ? 3 : 0x1b);
            } else if (NookStore_HasKind4Item(&data_021f395c) != 0) {
                NookClerkTalk_SetMode(talk, talk->mode == NOOK_CLERK_MODE_NOOK_GREET ? 4 : 0x1c);
            }
        }
    } else if (ntalk_is_empty(&talk->owner->item) == 0) {
        switch (talk->mode) {
            case 0x0c:
            case 0x0d:
            case 0x18:
            case 0x19:
                if (ntalk_is_empty(&talk->owner->item) == 0) {
                    u16 item = talk->owner->item;
                    u8 paint =
                        (u8) (ntalk_in(item, NOOK_CLERK_PAINT_FIRST, NOOK_CLERK_PAINT_LAST) ? item - NOOK_CLERK_PAINT_FIRST
                                                                                            : -1);
                    TalkObject_LoadPart(ntalk_object(talk), 2, &paint, (unsigned int) (uintptr_t) data_ov050_02265e9c);
                }
                /* fall through */
            case 0x08:
            case 0x09:
            case 0x0a:
            case 0x0b:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
                if (ntalk_is_empty(&talk->owner->item) == 0) {
                    talk->price = ItemTraits_StorePrice(&talk->owner->item);
                    SceneBase_PutValue(&talk->base, talk->price, 4, NOOK_CLERK_VALUE_BELLS, 0, 0);
                    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->owner->item, 1, NOOK_CLERK_VALUE_ITEM);
                }
                break;
            default:
                break;
        }
    }

    if (talk->mode < NOOK_CLERK_MODES) {
        out->message = data_ov050_02265114[talk->mode].message;
        out->text = data_ov050_02265114[talk->mode].text;
        if (talk->mode == NOOK_CLERK_MODE_TWIN_SPOT) {
            NookClerk *other = (NookClerk *) Actor_FindNextOfProfile(NookClerk_OtherTwin(talk->owner), NULL);
            if (other != NULL) {
                NookClerk_SetState(other, NOOK_CLERK_STATE_STILL);
            }
        }
    }
}
CLEAN_AS(func_ov050_02261ed0, NookClerkTalk_Line)

/* ---- The part-time job's line ends */

/* func_ov050_02262618 (the job's end of line 0xc): the clerk leads the player (state 17). */
void NookClerkTalk_JobLead(NookClerkTalk *talk, int unused)
{
    (void) unused;
    NookClerk_SetState(talk->owner, NOOK_CLERK_STATE_LEAD);
}
CLEAN_AS(func_ov050_02262618, NookClerkTalk_JobLead)

/* func_ov050_02262628 (the job's ends of lines 0x35 and 0x36, the job done): the errand step
 * ended, the player no longer at work, main's block's flag 5 set, and the date of the player
 * record's field 0x2416 today. */
void NookClerkTalk_JobEnd(int unused, int part)
{
    (void) unused;
    VillagerPart_EndStep((VillagerPart *) (uintptr_t) (u32) part);
    u8 *record = PlayerRecords_Current();
    PlayerRecord_ClearFlag(record, NOOK_CLERK_TALK_JOB_FLAG);
    PlayerField2416 *field = (PlayerField2416 *) (void *) PlayerRecord_Field2416(record);
    Block021d27ac_SetFlag((u32 *) (void *) Block021d27ac_Get(), 5);
    PlayerField2416_SetDate04Today(field);
}
CLEAN_AS(func_ov050_02262628, NookClerkTalk_JobEnd)

/* func_ov050_0226265c (the job's end of line 0x33): with a loan below 1401 bells, line 0x36;
 * else 1400 bells of it paid, the loan left put in (value 2) and line 0x34. */
void NookClerkTalk_JobPayLoan(NookClerkTalk *talk, int unused)
{
    (void) unused;
    HouseRecord *house = &data_021ebcd4;
    if (HouseRecord_Loan(house) < 0x579) {
        talk->line = 0x36;
        return;
    }
    HouseRecord_SetLoan(house, HouseRecord_Loan(house) - 0x578);
    int left = HouseRecord_Loan((const HouseRecord *) (const void *) ((const u8 *) data_021dc7a8 + NOOK_CLERK_HOUSE_IN_STATE));
    SceneBase_PutValue(&talk->base, left, 2, NOOK_CLERK_VALUE_BELLS, 0, 0);
    talk->line = 0x34;
}
CLEAN_AS(func_ov050_0226265c, NookClerkTalk_JobPayLoan)

/* func_ov050_022626c8 (the job's end of line 0x31): the errand's object at step 2, the block
 * set to type 18, and the job's talk back at its start. */
void NookClerkTalk_JobErrand18(NookClerkTalk *talk, VillagerPart *part)
{
    ItemObject_SetLow5(ntalk_errand(part), 2);
    VillagerPart_SetType18(part);
    talk->owner->job_step = 0;
}
CLEAN_AS(func_ov050_022626c8, NookClerkTalk_JobErrand18)

/* func_ov050_02262700 (the job's end of line 0x2e): the item 0x1564 shown (argument 2), and the
 * job's talk back at its start. */
void NookClerkTalk_JobShowItem1564(NookClerkTalk *talk, int unused)
{
    (void) unused;
    ntalk_show_item(talk, 0x1564, 2);
    talk->owner->job_step = 0;
}
CLEAN_AS(func_ov050_02262700, NookClerkTalk_JobShowItem1564)

/* func_ov050_02262734 (the job's end of line 0x2c): the item 0x1564 given (state 2): the block
 * set to type 17, the villager it is for named in part 1, line 0x2e; else line 0x17. */
void NookClerkTalk_JobGive1564(NookClerkTalk *talk, VillagerPart *part)
{
    if (ntalk_give(0x1564, 2) == 0) {
        talk->line = 0x17;
        return;
    }
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    VillagerPart_SetSecondAgain(part);
    u16 item = 0x1564;
    VillagerPart_NameFor(part, &name, &item);
    TalkObject_SetPart(ntalk_object(talk), 1, (TextBase *) (void *) &name);
    talk->line = 0x2e;
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov050_02262734, NookClerkTalk_JobGive1564)

/* func_ov050_02262798 (the job's end of line 0x29): when the item 0x1561 goes into the pockets
 * (state 2) it is shown. */
void NookClerkTalk_JobShowItem1561(NookClerkTalk *talk, int unused)
{
    (void) unused;
    if (ntalk_give(0x1561, 2) != 0) {
        ntalk_show_item(talk, 0x1561, 0);
    }
}
CLEAN_AS(func_ov050_02262798, NookClerkTalk_JobShowItem1561)

/* func_ov050_022627d4 (the job's end of line 0x28): the errand's object at step 2 and the job's
 * talk back at its start; with a free pocket slot the block set to type 16, the villager the
 * item 0x1561 is for named in part 1 and line 0x29, else line 0x17. */
void NookClerkTalk_JobGive1561(NookClerkTalk *talk, VillagerPart *part)
{
    ItemObject *errand = ntalk_errand(part);
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    ItemObject_SetLow5(errand, 2);
    talk->owner->job_step = 0;
    if (CurrentPockets_FreeSlot() >= 0) {
        VillagerPart_SetThirdPick(part);
        u16 item = 0x1561;
        VillagerPart_NameFor(part, &name, &item);
        TalkObject_SetPart(ntalk_object(talk), 1, (TextBase *) (void *) &name);
        talk->line = 0x29;
    } else {
        talk->line = 0x17;
    }
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov050_022627d4, NookClerkTalk_JobGive1561)

/* func_ov050_02262850 (the job's end of line 0x27): the errand's object at step 0; with a free
 * pocket slot line 0x25, else the talk's message is the empty one. */
void NookClerkTalk_JobStep0(NookClerkTalk *talk, VillagerPart *part)
{
    ItemObject_SetLow5(ntalk_errand(part), 0);
    if (CurrentPockets_FreeSlot() >= 0) {
        talk->line = 0x25;
    } else {
        TalkObject_SetMessage(ntalk_object(talk), data_021f43e8, NULL);
    }
}
CLEAN_AS(func_ov050_02262850, NookClerkTalk_JobStep0)

/* func_ov050_0226288c (the job's end of line 0x25): the errand's object at step 0, the job's
 * talk at step 1, then as at line 0x1f (NookClerkTalk_JobGive1020). */
void NookClerkTalk_JobStep0Again(NookClerkTalk *talk, VillagerPart *part)
{
    ItemObject_SetLow5(ntalk_errand(part), 0);
    talk->owner->job_step = 1;
    NookClerkTalk_JobGive1020(talk, (int) (uintptr_t) part);
}
CLEAN_AS(func_ov050_0226288c, NookClerkTalk_JobStep0Again)

/* func_ov050_022628c8 (the job's end of line 0x21): at the job talk's step 0 with a free pocket
 * slot, line 0x22; else the talk's step 1 and the empty message. */
void NookClerkTalk_JobAskAgain(NookClerkTalk *talk, int unused)
{
    (void) unused;
    if (talk->owner->job_step == 0 && CurrentPockets_FreeSlot() != -1) {
        talk->line = 0x22;
        return;
    }
    talk->owner->job_step = 1;
    TalkObject_SetMessage(ntalk_object(talk), data_021f43e8, NULL);
}
CLEAN_AS(func_ov050_022628c8, NookClerkTalk_JobAskAgain)

/* func_ov050_02262910 (the job's end of line 0x1f): when the item 0x1020 goes into the pockets
 * (state 0) it is shown; at line 0x1f line 0x20 and the job talk's step 2, else line 0x26. */
void NookClerkTalk_JobGive1020(NookClerkTalk *talk, int unused)
{
    (void) unused;
    if (ntalk_give(0x1020, 0) != 0) {
        ntalk_show_item(talk, 0x1020, 0);
    }
    if (ntalk_shown(talk) == 0x1f) {
        talk->line = 0x20;
        talk->owner->job_step = 2;
    } else {
        talk->line = 0x26;
    }
}
CLEAN_AS(func_ov050_02262910, NookClerkTalk_JobGive1020)

/* func_ov050_02262970 (the job's end of line 0x1e): the errand's object at step 1; with a free
 * pocket slot the block set to type 15, its second villager (when there is one) named in part
 * 0, the job's talk back at its start and line 0x1f; else line 0x17. */
void NookClerkTalk_JobSecondPick(NookClerkTalk *talk, VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    ItemObject_SetLow5((ItemObject *) (void *) VillagerPartBlock_Object(block), 1);
    if (CurrentPockets_FreeSlot() < 0) {
        talk->line = 0x17;
        return;
    }
    VillagerPart_SetSecondPick(part);
    NpcId *npc = VillagerPartBlock_Npc(block, 1);
    if (npc != NULL) {
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        NpcId_FormatName(npc, (char *) (void *) &name);
        TalkObject_SetPart(ntalk_object(talk), 0, (TextBase *) (void *) &name);
        PlayerIdText_Destruct(&name);
    }
    talk->owner->job_step = 0;
    talk->line = 0x1f;
}
CLEAN_AS(func_ov050_02262970, NookClerkTalk_JobSecondPick)

/* func_ov050_022629ec (the job's end of line 0x18): when the item 0x1563 goes into the pockets
 * (state 2) it is shown (argument 2). */
void NookClerkTalk_JobShowItem1563(NookClerkTalk *talk, int unused)
{
    (void) unused;
    if (ntalk_give(0x1563, 2) == 0) {
        return;
    }
    ntalk_show_item(talk, 0x1563, 2);
}
CLEAN_AS(func_ov050_022629ec, NookClerkTalk_JobShowItem1563)

/* func_ov050_02262a28 (the job's ends of lines 0x16 and 0x1a): the errand's object of type 0xd
 * goes to step 1; with a free pocket slot the block set to type 14, the villager the item 0x1563
 * is for named in part 1, the job's talk back at its start and line 0x18; else line 0x17. */
void NookClerkTalk_JobGive1563(NookClerkTalk *talk, VillagerPart *part)
{
    ItemObject *errand = ntalk_errand(part);
    if (ItemObject_IsInUse(errand) != 0 && ItemObject_Type(errand) == 0xd) {
        ItemObject_SetLow5(errand, 1);
    }
    if (CurrentPockets_FreeSlot() < 0) {
        talk->line = 0x17;
        return;
    }
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    VillagerPart_SetFirstPick(part);
    u16 item = 0x1563;
    VillagerPart_NameFor(part, &name, &item);
    TalkObject_SetPart(ntalk_object(talk), 1, (TextBase *) (void *) &name);
    talk->owner->job_step = 0;
    talk->line = 0x18;
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov050_02262a28, NookClerkTalk_JobGive1563)

/* func_ov050_02262ab8 (the job's end of line 0x12): the block set to type 13. */
void NookClerkTalk_JobType13(int unused, VillagerPart *part)
{
    (void) unused;
    PlayerRecords_Current();
    VillagerPart_SetType13(part);
}
CLEAN_AS(func_ov050_02262ab8, NookClerkTalk_JobType13)

/* func_ov050_02262acc (the job's end of line 0x0e): the villager part's flag cleared. */
void NookClerkTalk_JobClearFlag(int unused, VillagerPart *part)
{
    (void) unused;
    VillagerPart_ClearFlag(part);
}
CLEAN_AS(func_ov050_02262acc, NookClerkTalk_JobClearFlag)

/* func_ov050_02262ad8 (the job's end of line 8): the job's items given
 * (NookClerkTalk_JobGiveItems), the block set to type 12, the job's talk back at its start and
 * line 0xa. */
void NookClerkTalk_JobType12(NookClerkTalk *talk, VillagerPart *part)
{
    NookClerkTalk_JobGiveItems(talk);
    VillagerPart_SetType12(part);
    talk->owner->job_step = 0;
    talk->line = 0xa;
}
CLEAN_AS(func_ov050_02262ad8, NookClerkTalk_JobType12)

/* func_ov050_02262b08 (the job's end of line 7): with 7 or more empty pockets line 8, else 9;
 * the villager part's flag set and the errand's object at step 2. */
void NookClerkTalk_JobCountFree(NookClerkTalk *talk, VillagerPart *part)
{
    PocketsMarks marks;
    CurrentPockets_Mark(&marks, (int (*)(u16 *)) func_ov050_022634b4);
    talk->line = marks.count >= 7 ? 8 : 9;
    ItemObject *errand = ntalk_errand(part);
    VillagerPart_SetFlag(part);
    ItemObject_SetLow5(errand, 2);
}
CLEAN_AS(func_ov050_02262b08, NookClerkTalk_JobCountFree)

/* func_ov050_02262b58 (the job's ends of lines 3 and 4): the uniform shown, line 6, and the
 * errand's object of type 0xb goes to step 1. */
void NookClerkTalk_JobShowUniform(NookClerkTalk *talk, VillagerPart *part)
{
    ntalk_show_item(talk, NOOK_CLERK_UNIFORM, 0);
    talk->line = 6;
    ItemObject *errand = ntalk_errand(part);
    if (ItemObject_IsInUse(errand) != 0 && ItemObject_Type(errand) == 0xb) {
        ItemObject_SetLow5(errand, 1);
    }
}
CLEAN_AS(func_ov050_02262b58, NookClerkTalk_JobShowUniform)

/* func_ov050_02262bac (the job's end of line 0): the uniform given (state 0): the villager part
 * reset and line 3; else line 1. */
void NookClerkTalk_JobGiveUniform(NookClerkTalk *talk, VillagerPart *part)
{
    if (ntalk_give(NOOK_CLERK_UNIFORM, 0) != 0) {
        VillagerPart_Reset(part);
        talk->line = 3;
    } else {
        talk->line = 1;
    }
}
CLEAN_AS(func_ov050_02262bac, NookClerkTalk_JobGiveUniform)

/* func_ov050_02262be8 (vtable slot 0xa8, the job's line ended): the handlers of the line shown
 * get the current player's villager part (its errand's object asked for first, and not used);
 * the line one asks for is shown from "sp_etc_sequence5_1". */
void NookClerkTalk_OnJobLineEnded(NookClerkTalk *talk, int unused)
{
    static const MemberPointer *const handlers[NOOK_CLERK_JOB_LINE_ENDS] = {
        &data_ov050_022656f0, /* 0x00: NookClerkTalk_JobGiveUniform */
        &data_ov050_022656e8, /* 0x03: NookClerkTalk_JobShowUniform */
        &data_ov050_022656e0, /* 0x04: NookClerkTalk_JobShowUniform */
        &data_ov050_022656d8, /* 0x07: NookClerkTalk_JobCountFree */
        &data_ov050_02265550, /* 0x08: NookClerkTalk_JobType12 */
        &data_ov050_022656c8, /* 0x0e: NookClerkTalk_JobClearFlag */
        &data_ov050_022656c0, /* 0x12: NookClerkTalk_JobType13 */
        &data_ov050_022656b8, /* 0x16: NookClerkTalk_JobGive1563 */
        &data_ov050_022656b0, /* 0x1a: NookClerkTalk_JobGive1563 */
        &data_ov050_022656a8, /* 0x18: NookClerkTalk_JobShowItem1563 */
        &data_ov050_022656a0, /* 0x1e: NookClerkTalk_JobSecondPick */
        &data_ov050_02265698, /* 0x1f: NookClerkTalk_JobGive1020 */
        &data_ov050_02265690, /* 0x21: NookClerkTalk_JobAskAgain */
        &data_ov050_02265688, /* 0x25: NookClerkTalk_JobStep0Again */
        &data_ov050_02265680, /* 0x27: NookClerkTalk_JobStep0 */
        &data_ov050_02265678, /* 0x28: NookClerkTalk_JobGive1561 */
        &data_ov050_02265670, /* 0x29: NookClerkTalk_JobShowItem1561 */
        &data_ov050_02265498, /* 0x2c: NookClerkTalk_JobGive1564 */
        &data_ov050_02265610, /* 0x2e: NookClerkTalk_JobShowItem1564 */
        &data_ov050_02265658, /* 0x31: NookClerkTalk_JobErrand18 */
        &data_ov050_02265510, /* 0x33: NookClerkTalk_JobPayLoan */
        &data_ov050_02265648, /* 0x35: NookClerkTalk_JobEnd */
        &data_ov050_02265640, /* 0x36: NookClerkTalk_JobEnd */
        &data_ov050_02265638, /* 0x0c: NookClerkTalk_JobLead */
    };
    (void) unused;
    VillagerPart *part = ntalk_current_part();
    VillagerPartBlock_Object(VillagerPart_Block(part, 0));
    talk->line = NOOK_CLERK_NO_LINE;
    ntalk_dispatch(talk, &data_ov050_02265ec4, data_ov050_02265bc0, handlers, NOOK_CLERK_JOB_LINE_ENDS,
                   (int) (uintptr_t) part);
    if (talk->line != NOOK_CLERK_NO_LINE) {
        ntalk_say(talk, (u8) talk->line, data_ov050_02265834);
    }
}
CLEAN_AS(_ZN18Obj_ov050_02265b1419func_ov050_02262be8Ei, NookClerkTalk_OnJobLineEnded)

/* ---- The part-time job's first lines */

/* The errand step of the current player's villager part's errand object. */
static int ntalk_errand_step(void)
{
    return ItemObject_Low5(ntalk_errand(ntalk_current_part()));
}

/* The first line of an errand type whose step 1 gives `at_step_1`, and else the first time
 * `first` (the job talk at step 1 then), later 0x10. Not without the uniform. */
static void ntalk_job_line_simple(NookClerkTalk *talk, NookClerkLine *out, u8 at_step_1, u8 first)
{
    if (NookClerkTalk_JobNotInUniform(talk, out) != 0) {
        return;
    }
    if (ntalk_errand_step() == 1) {
        out->message = at_step_1;
    } else if (talk->owner->job_step == 0) {
        out->message = first;
        talk->owner->job_step = 1;
    } else {
        out->message = 0x10;
    }
}

/* func_ov050_02262e34 (vtable slot 0xa4, type 0x12): step 1 line 0x33, else 0x32 the first
 * time, then 0x10. */
void NookClerkTalk_JobLine12(NookClerkTalk *talk, NookClerkLine *out)
{
    ntalk_job_line_simple(talk, out, 0x33, 0x32);
}
CLEAN_AS(func_ov050_02262e34, NookClerkTalk_JobLine12)

/* func_ov050_02262e90 (vtable slot 0xa0, type 0x11): step 1 line 0x31, else 0x2b the first
 * time, then 0x10. */
void NookClerkTalk_JobLine11(NookClerkTalk *talk, NookClerkLine *out)
{
    ntalk_job_line_simple(talk, out, 0x31, 0x2b);
}
CLEAN_AS(func_ov050_02262e90, NookClerkTalk_JobLine11)

/* func_ov050_02262eec (vtable slot 0x9c, type 0x10): step 1 line 0x2c, else 0x2b the first
 * time, then 0x10. */
void NookClerkTalk_JobLine10(NookClerkTalk *talk, NookClerkLine *out)
{
    ntalk_job_line_simple(talk, out, 0x2c, 0x2b);
}
CLEAN_AS(func_ov050_02262eec, NookClerkTalk_JobLine10)

/* func_ov050_02262f48 (vtable slot 0x98, type 0xf): not without the uniform. With the errand's
 * object at step 2 line 0x28; at step 0, at the job talk's step 0 or 2 the block's second
 * villager (when there is one) named in part 0 and line 0x21 (step 2 becomes 1), else 0x10; at
 * step 1 the villager named and line 0x27. */
void NookClerkTalk_JobLine0F(NookClerkTalk *talk, NookClerkLine *out)
{
    if (NookClerkTalk_JobNotInUniform(talk, out) != 0) {
        return;
    }
    VillagerPartBlock *block = VillagerPart_Block(ntalk_current_part(), 0);
    ItemObject *errand = (ItemObject *) (void *) VillagerPartBlock_Object(block);
    NpcId *npc = VillagerPartBlock_Npc(block, 1);
    PlayerIdText name;
    PlayerIdText_Construct(&name);

    if (ItemObject_Low5(errand) == 2) {
        out->message = 0x28;
    } else if (ItemObject_Low5(errand) == 0) {
        if (talk->owner->job_step == 0 || talk->owner->job_step == 2) {
            if (npc != NULL) {
                NpcId_FormatName(npc, (char *) (void *) &name);
                TalkObject_SetPart(ntalk_object(talk), 0, (TextBase *) (void *) &name);
            }
            out->message = 0x21;
            if (talk->owner->job_step == 2) {
                talk->owner->job_step = 1;
            }
        } else {
            out->message = 0x10;
        }
    } else if (ItemObject_Low5(errand) == 1) {
        if (npc != NULL) {
            NpcId_FormatName(npc, (char *) (void *) &name);
            TalkObject_SetPart(ntalk_object(talk), 0, (TextBase *) (void *) &name);
        }
        out->message = 0x27;
    }
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov050_02262f48, NookClerkTalk_JobLine0F)

/* func_ov050_02263028 (vtable slot 0x94, type 0xe): step 1 line 0x1e, else 0x1c the first
 * time, then 0x10. */
void NookClerkTalk_JobLine0E(NookClerkTalk *talk, NookClerkLine *out)
{
    ntalk_job_line_simple(talk, out, 0x1e, 0x1c);
}
CLEAN_AS(func_ov050_02263028, NookClerkTalk_JobLine0E)

/* Whether every villager of the town remembers the current player, the record's flag 0xa set. */
static int ntalk_known_to_all(u8 *record)
{
    return PlayerRecord_TestFlag(record, 0xa) != 0 &&
           VillagerTown_AllRemember((VillagerTown *) (void *) data_021e5a2c, PlayerRecord_Player(record)) != 0;
}

/* func_ov050_02263084 (vtable slot 0x90, type 0xd): the errand's object and a free pocket slot
 * asked for first (not used); not without the uniform. Unless the player's record has the flag
 * 0xa and every villager remembers the player: line 0x13 at the job talk's step 1 or more,
 * else 0x14. Else line 0x15 without a birthday set, 0x16 with one. */
void NookClerkTalk_JobLine0D(NookClerkTalk *talk, NookClerkLine *out)
{
    u8 *record = PlayerRecords_Current();
    VillagerPartBlock_Object(VillagerPart_Block((VillagerPart *) (void *) PlayerRecord_VillagerPart(record), 0));
    CurrentPockets_FreeSlot();
    if (NookClerkTalk_JobNotInUniform(talk, out) != 0) {
        return;
    }
    if (!ntalk_known_to_all(record)) {
        out->message = talk->owner->job_step != 0 ? 0x13 : 0x14;
        return;
    }
    if (*(const u16 *) (const void *) PlayerRecord_Birthday(PlayerRecords_Current()) == 0) {
        out->message = 0x15;
    } else {
        out->message = 0x16;
    }
}
CLEAN_AS(func_ov050_02263084, NookClerkTalk_JobLine0D)

/* func_ov050_0226310c (vtable slot 0x8c, type 0xc): the errand's object and a free pocket slot
 * asked for first (not used); not without the uniform. While the pockets still hold one of the
 * job's items (the item 0x151d, or for one of three colours the items 0x14fe, 0x1504, 0x150a and
 * 0x1510 plus the colour, looked for in that order), line 0xf plus the job talk's step, then
 * step 1. With none left the talk is at step 1; when the player's record has the flag 0xa, every
 * villager remembers the player and a birthday is set, the errand's object goes to step 1 and
 * line 0x1a; else 0x11. */
void NookClerkTalk_JobLine0C(NookClerkTalk *talk, NookClerkLine *out)
{
    u8 *record = PlayerRecords_Current();
    ItemObject *errand = (ItemObject *) (void *) VillagerPartBlock_Object(
        VillagerPart_Block((VillagerPart *) (void *) PlayerRecord_VillagerPart(record), 0));
    CurrentPockets_FreeSlot();
    if (NookClerkTalk_JobNotInUniform(talk, out) != 0) {
        return;
    }
    for (int colour = 0; colour < 3; colour++) {
        u16 items[5] = {0x151d, (u16) (0x14fe + colour), (u16) (0x1504 + colour), (u16) (0x150a + colour),
                        (u16) (0x1510 + colour)};
        for (int i = 0; i < 5; i++) {
            if (CurrentPockets_FindItem(&items[i]) >= 0) {
                out->message = (u8) (talk->owner->job_step + 0xf);
                talk->owner->job_step = 1;
                return;
            }
        }
    }
    talk->owner->job_step = 1;
    if (ntalk_known_to_all(record) && *(const u16 *) (const void *) PlayerRecord_Birthday(PlayerRecords_Current()) != 0) {
        ItemObject_SetLow5(errand, 1);
        out->message = 0x1a;
        return;
    }
    out->message = 0x11;
}
CLEAN_AS(func_ov050_0226310c, NookClerkTalk_JobLine0C)

/* Whether the player record's clothes are the uniform (a variant of it too). */
static int ntalk_in_uniform(u8 *record)
{
    u16 *clothes = PlayerRecord_Clothes(record);
    if (ItemCode_HasVariant(clothes)) {
        u16 uniform = NOOK_CLERK_UNIFORM;
        return ItemCode_VariantItem(clothes) == ItemCode_VariantItem(&uniform);
    }
    return *clothes == NOOK_CLERK_UNIFORM;
}

/* func_ov050_02263258 (vtable slot 0x88, type 0xb), with the current player's errand's object
 * (a free pocket slot asked for first, not used):
 * - of type 0xb past step 0 and past its type's limit: unless the player is not in uniform,
 *   line 8 with 7 or more empty pockets, else 9;
 * - of type 0xb past step 0: in uniform line 7; else with the uniform not in the pockets, line
 *   4 when it goes in (state 0), else 2; with it there, line 5;
 * - else when the uniform goes into the pockets (state 0) the villager part is reset and line
 *   3; else line 1. */
void NookClerkTalk_JobLine0B(NookClerkTalk *talk, NookClerkLine *out)
{
    u8 *record = PlayerRecords_Current();
    VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(record);
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    ItemObject *errand = (ItemObject *) (void *) VillagerPartBlock_Object(block);
    CurrentPockets_FreeSlot();

    if (ItemObject_Type(errand) == 0xb && (unsigned int) ItemObject_Low5(errand) >= 1 &&
        VillagerPartBlock_IsOwnTypePastLimit(block) != 0) {
        if (NookClerkTalk_JobNotInUniform(talk, out) == 0) {
            PocketsMarks marks;
            CurrentPockets_Mark(&marks, (int (*)(u16 *)) func_ov050_022634b4);
            out->message = marks.count >= 7 ? 8 : 9;
        }
        return;
    }
    if (ItemObject_Type(errand) == 0xb && (unsigned int) ItemObject_Low5(errand) >= 1) {
        if (ntalk_in_uniform(record)) {
            out->message = 7;
            return;
        }
        u16 uniform = NOOK_CLERK_UNIFORM;
        if (CurrentPockets_FindItem(&uniform) < 0) {
            out->message = ntalk_give(NOOK_CLERK_UNIFORM, 0) != 0 ? 4 : 2;
        } else {
            out->message = 5;
        }
        return;
    }
    if (ntalk_give(NOOK_CLERK_UNIFORM, 0) != 0) {
        VillagerPart_Reset(part);
        out->message = 3;
    } else {
        out->message = 1;
    }
}
CLEAN_AS(func_ov050_02263258, NookClerkTalk_JobLine0B)

/* func_ov050_02263394: with the villager part's flag set, whether the player (with a record) is
 * not in uniform: then the job's line 0xe. */
int NookClerkTalk_JobNotInUniform(void *talk, NookClerkLine *out)
{
    (void) talk;
    u8 *record = PlayerRecords_Current();
    if (VillagerPart_Flag((const VillagerPart *) (void *) PlayerRecord_VillagerPart(record)) == 0) {
        return 0;
    }
    /* QUIRK: the record is tested for null only after its villager part was asked for. */
    if (record == NULL) {
        return 0;
    }
    if (ntalk_in_uniform(record)) {
        return 0;
    }
    out->message = 0xe;
    return 1;
}
CLEAN_AS(func_ov050_02263394, NookClerkTalk_JobNotInUniform)

/* func_ov050_02263408: the job's items given (state 0): one of the items 0x14fe, 0x1504, 0x150a
 * and 0x1510 each in a colour drawn at random (0 to 2), three of the item 0x151d, and the item
 * 0x151d shown. */
void NookClerkTalk_JobGiveItems(NookClerkTalk *talk)
{
    static const u16 firsts[4] = {0x14fe, 0x1504, 0x150a, 0x1510};
    for (int i = 0; i < 4; i++) {
        ntalk_give((u16) (MainRandom_Below(3) + firsts[i]), 0);
    }
    for (int i = 0; i < 3; i++) {
        ntalk_give(0x151d, 0);
    }
    ntalk_show_item(talk, 0x151d, 0);
}
CLEAN_AS(func_ov050_02263408, NookClerkTalk_JobGiveItems)

/* func_ov050_022634b4 (the test the pockets are marked with): whether a pocket is empty. */
int NookClerkTalk_IsEmptySlot(unsigned short *item)
{
    return *item == NOOK_CLERK_NO_ITEM;
}
CLEAN_AS(func_ov050_022634b4, NookClerkTalk_IsEmptySlot)

/* func_ov050_022634c8: the line of the house loan's news, 0 for none: not once the state
 * block's flag 0xe is set. With no loan, the smallest house not being extended: line 0x41. For
 * the sizes 1 to 6: just built, line 0x49 plus twice the size less 1 (the state block's flag 0xd
 * cleared); with no loan and not being extended, the line after it (at size 6 the flag 0xe set
 * too). */
int NookClerkTalk_LoanNews(NookClerkTalk *talk)
{
    (void) talk;
    HouseRecord *house = &data_021ebcd4;
    const HouseRecord *in_state =
        (const HouseRecord *) (const void *) ((const u8 *) data_021dc7a8 + NOOK_CLERK_HOUSE_IN_STATE);
    int loan = HouseRecord_Loan(house);
    unsigned int size = HouseRecord_Size(house);
    int built = HouseRecord_JustBuilt(house);
    if (StateBlock_TestFlag(data_021dc7a8, NOOK_CLERK_STATE_HOUSE_DONE) != 0) {
        return 0;
    }
    if (loan == 0 && size == 0 && HouseRecord_IsExtending(in_state) == 0) {
        return 0x41;
    }
    for (unsigned int grown = 1; grown <= 6; grown++) {
        if (size == grown && built != 0) {
            StateBlock_ClearFlag(data_021dc7a8, NOOK_CLERK_STATE_HOUSE_GROWN);
            return (int) (0x49 + 2 * (grown - 1));
        }
        if (loan == 0 && size == grown && HouseRecord_IsExtending(in_state) == 0) {
            if (grown == 6) {
                StateBlock_SetFlag(data_021dc7a8, NOOK_CLERK_STATE_HOUSE_DONE);
            }
            return (int) (0x4a + 2 * (grown - 1));
        }
    }
    return 0;
}
CLEAN_AS(func_ov050_022634c8, NookClerkTalk_LoanNews)

/* ---- The class */

/* func_ov050_02263638: its talk mode. */
unsigned long NookClerkTalk_Mode(NookClerkTalk *talk)
{
    return talk->mode;
}
CLEAN_AS(func_ov050_02263638, NookClerkTalk_Mode)

/* func_ov050_02263640: its talk mode set. */
void NookClerkTalk_SetMode(NookClerkTalk *talk, unsigned long mode)
{
    talk->mode = (u32) mode;
}
CLEAN_AS(func_ov050_02263640, NookClerkTalk_SetMode)

/* func_ov050_02263648: the scene reset through its vtable slot 0x08, given its owner, and the
 * item 0x36fc to be looked for. */
void NookClerkTalk_Begin(NookClerkTalk *talk, NookClerk *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + NOOK_CLERK_TALK_SLOT_RESET);
    ((void (*)(NookClerkTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->package_slot = -1;
}
CLEAN_AS(func_ov050_02263648, NookClerkTalk_Begin)

/* func_ov050_0226366c (slot 0x08): the scene reset, with no sequence. */
void NookClerkTalk_Reset(NookClerkTalk *talk)
{
    SceneBase_Reset(&talk->base);
    talk->sequence = __ptmf_null;
}
CLEAN_AS(func_ov050_0226366c, NookClerkTalk_Reset)

/* func_ov050_02263690 (slot 0x04): its destructor, then the scene freed. */
void *NookClerkTalk_DestructDelete(NookClerkTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov050_02265b14;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov050_02263690, NookClerkTalk_DestructDelete)

/* func_ov050_022636b0 (slot 0x00): the scene class's destructor. */
void *NookClerkTalk_Destruct(NookClerkTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov050_02265b14;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov050_022636b0, NookClerkTalk_Destruct)

/* func_ov050_022636c8: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *NookClerkTalk_Construct(NookClerkTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) (void *) talk = data_ov050_02265b14;
    return talk;
}
CLEAN_AS(func_ov050_022636c8, NookClerkTalk_Construct)

/* ---- The sequences */

/* func_ov050_022636e0 (sequence 2, after the pockets' screen of an errand): with an item picked
 * (GroupParams_C4CIs1) and this system the host or alone, the item in the pocket picked is taken
 * out, shown (scene command 4, argument 2) unless empty, the errand's entry goes to step 1 and
 * line 3; else line 4. */
void NookClerkTalk_TakeErrandItem(NookClerkTalk *talk)
{
    TalkObject *object = ntalk_object(talk);
    u8 line = 4;
    if (GroupParams_C4CIs1() != 0) {
        u8 *record = PlayerRecords_Current();
        if (TalkChecks_IsHostOrAlone() != 0) {
            int slot = GroupParams_Arg();
            u16 item = CurrentPockets_Item((u32) slot);
            if (slot >= 0) {
                CurrentPockets_Empty(slot);
            }
            if (ntalk_is_empty(&item) == 0) {
                SceneCommand_RequestMotion14(ntalk_scene(talk), &item, 2, 5, 0);
            }
            line = 3;
            VillagerPartEntry *entry = VillagerPartEntry_Self((VillagerPartEntry *) (void *) VillagerPart_Object94(
                (VillagerPart *) (void *) PlayerRecord_VillagerPart(record)));
            ItemObject_SetLow5((ItemObject *) (void *) entry, 1);
        }
    }
    TalkObject_SetMessage(object, &line, ntalk_file(talk));
}
CLEAN_AS(func_ov050_022636e0, NookClerkTalk_TakeErrandItem)

/* func_ov050_022637c0 (the pockets' test of an errand's items): in state 2, whether the item
 * is 0x155f or 0x1560. */
unsigned short NookClerkTalk_IsErrandItem(unsigned short *item, int state)
{
    if (state == NOOK_CLERK_ERRAND_STATE) {
        return (unsigned short) (*item >= NOOK_CLERK_ERRAND_FIRST && *item <= NOOK_CLERK_ERRAND_LAST);
    }
    return 0;
}
CLEAN_AS(func_ov050_022637c0, NookClerkTalk_IsErrandItem)

/* func_ov050_022637e8 (sequence 1, after the catalog's screen): with an item picked, it is the
 * item talked about; unless empty and with a member's price, the price is kept and put in
 * (value 0) with its name (value 1), line 0x1a; else line 0x1b. */
void NookClerkTalk_PriceOrder(NookClerkTalk *talk)
{
    TalkObject *object = ntalk_object(talk);
    u8 line = 0x1b;
    if (GroupParams_C4CIs1() == 1) {
        talk->owner->item = GroupParams_ItemB();
        if (ntalk_is_empty(&talk->owner->item) == 0) {
            talk->price = ItemTraits_MemberPrice(&talk->owner->item);
            if (talk->price != 0) {
                SceneBase_PutValue(&talk->base, talk->price, 0, NOOK_CLERK_VALUE_BELLS, 0, 0);
                SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->owner->item, 1, NOOK_CLERK_VALUE_ITEM);
                line = 0x1a;
            }
        }
    }
    TalkObject_SetMessage(object, &line, ntalk_file(talk));
}
CLEAN_AS(func_ov050_022637e8, NookClerkTalk_PriceOrder)

/* func_ov050_022638d4 (sequence 0, after the screen of the items to sell): the price of the
 * items listed (Pockets_List, up to 15, until an empty one): fossils (0x38e4-0x3933) by their
 * assessed kind's price, turnips at today's price each (not sold on Sunday), the rest a quarter
 * of their price. Line 0xd with turnips on Sunday; with one of the items 0x136a, 0x1373,
 * 0x1375, 0x1377, 0x1379 or 0x137b the price (value 0) and line 0x11; with a fossil the price
 * and line 0x40; with nothing to pay line 0xa; else the price and line 0xe. Nothing picked:
 * line 8. The price is kept, with no extra bags. */
void NookClerkTalk_PriceSale(NookClerkTalk *talk)
{
    static const u16 special[6] = {0x136a, 0x1373, 0x1375, 0x1377, 0x1379, 0x137b};
    TalkObject *object = ntalk_object(talk);
    u8 line = 8;
    talk->price = 0;
    talk->extra_bags = 0;
    if (GroupParams_C4CIs1() != 0) {
        u16 *list = Pockets_List();
        int has_special = 0;
        int turnips_on_sunday = 0;
        int has_fossil = 0;
        for (int i = 0; i < 0xf; i++) {
            if (list[i] == NOOK_CLERK_NO_ITEM) {
                break;
            }
            u16 item = list[i];
            for (int k = 0; k < 6; k++) {
                if (item == special[k]) {
                    has_special = 1;
                }
            }
            if (ntalk_in(item, NOOK_CLERK_FOSSIL_FIRST, NOOK_CLERK_FOSSIL_LAST)) {
                has_fossil = 1;
                unsigned int kind = (unsigned int) (item - NOOK_CLERK_FOSSIL_FIRST) >> 2;
                u16 assessed = (u16) (kind < NOOK_CLERK_FOSSIL_KINDS ? kind * 4 + NOOK_CLERK_FOSSIL_ASSESSED
                                                                     : NOOK_CLERK_FOSSIL_ASSESSED);
                talk->price = talk->price + ItemTraits_Price(&assessed) / 4;
            } else if (PlayerRecords_Current() != NULL) {
                if (ntalk_in(item, NOOK_CLERK_TURNIPS_FIRST, NOOK_CLERK_TURNIPS_LAST)) {
                    if (Calendar_TodayWeekday() == 0) {
                        turnips_on_sunday = 1;
                    } else {
                        int each = TurnipPrices_Current(&data_021f3b0c);
                        talk->price = talk->price + ItemTraits_Price(&item) * each;
                    }
                } else {
                    talk->price = talk->price + ItemTraits_Price(&item) / 4;
                }
            }
        }
        if (turnips_on_sunday == 1) {
            line = 0xd;
        } else if (has_special == 1) {
            SceneBase_PutValue(&talk->base, talk->price, 0, NOOK_CLERK_VALUE_BELLS, 0, 0);
            line = 0x11;
        } else if (has_fossil == 1) {
            line = 0x40;
            SceneBase_PutValue(&talk->base, talk->price, 0, NOOK_CLERK_VALUE_BELLS, 0, 0);
        } else if (talk->price == 0) {
            line = 0xa;
        } else {
            line = 0xe;
            SceneBase_PutValue(&talk->base, talk->price, 0, NOOK_CLERK_VALUE_BELLS, 0, 0);
        }
    }
    TalkObject_SetMessage(object, &line, ntalk_file(talk));
}
CLEAN_AS(func_ov050_022638d4, NookClerkTalk_PriceSale)

/* func_ov050_02263b38: the sequence `sequence` to run when a command of the scene ends (the
 * table filled once).
 * REQUIRES: `sequence` is 0 to 2. */
void NookClerkTalk_SetSequence(NookClerkTalk *talk, int sequence)
{
    static const MemberPointer *const sequences[NOOK_CLERK_SEQUENCES] = {
        &data_ov050_02265718, /* 0: NookClerkTalk_PriceSale */
        &data_ov050_02265710, /* 1: NookClerkTalk_PriceOrder */
        &data_ov050_02265708, /* 2: NookClerkTalk_TakeErrandItem */
    };
    MemberTable_InitOnce(&data_ov050_02265ed4, data_ov050_02265ed8, sequences, NOOK_CLERK_SEQUENCES);
    talk->sequence = data_ov050_02265ed8[sequence];
}
CLEAN_AS(func_ov050_02263b38, NookClerkTalk_SetSequence)

/* func_ov050_02263ba0 (slot 0x84, a command of the scene ended): the sequence, when there is
 * one, runs and is cleared. */
void NookClerkTalk_RunSequence(NookClerkTalk *talk)
{
    if (talk->sequence.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->sequence, talk);
    talk->sequence = __ptmf_null;
}
CLEAN_AS(func_ov050_02263ba0, NookClerkTalk_RunSequence)
