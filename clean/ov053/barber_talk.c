/* The barber's talk scene (barber_talk.h): its class's constructor and destructors, its topic,
 * the line it starts with, the player's answers and what follows the end of a line. */
#include "barber_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "barber.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_bells.h"
#include "main/screen_panels.h"
#include "main/sound.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "ov004/room_player_actor.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(BarberTalk, topic) == 0xb0 && offsetof(BarberTalk, owner) == 0xb4, "BarberTalk");
static_assert(offsetof(BarberTalk, other_styles) == 0xb8 && offsetof(BarberTalk, pages) == 0xb9, "BarberTalk");
static_assert(offsetof(BarberTalk, style) == 0xba && offsetof(BarberTalk, colour) == 0xbb, "BarberTalk");
static_assert(offsetof(BarberTalk, old_style) == 0xbc && offsetof(BarberTalk, old_colour) == 0xbd, "BarberTalk");
static_assert(sizeof(BarberTalk) == 0xc0, "BarberTalk");
static_assert(sizeof(BarberTalkStart) == 8, "a topic's line");

/* The vtable of its class. */
extern const u8 data_ov053_02261b08[];
/* Its message file's name, "sp_npc_barber" (data_ov053_02261a34). */
extern const char *const data_ov053_02261980;
/* The line of each topic; each name is filled with the message file's on the first call (bit 0
 * of the guard says it was). */
extern BarberTalkStart data_ov053_02261a90[BARBER_TOPICS];
extern u32 data_ov053_02261c60;
/* The colours of the two menus of colours, by answer: {0, 3, 5, 7} and {1, 4, 2, 6}. */
extern const u8 data_ov053_022617c0[];
extern const u8 data_ov053_022617c4[];
/* The style of each line 0x2f to 0x36, two a line: by the player's byte 0x1c. */
extern const u8 data_ov053_022617ec[];
#define BARBER_TALK_STYLE_SETS 2
/* The message number data_021f43e8 holds (shown with no file name). */
extern u8 data_021f43e8;

#define BARBER_TALK_NO_LINE 0xff
#define BARBER_TALK_NO_ANSWER 4

/* The vtable slot of the scene that resets it (SceneBase_Reset). */
#define BARBER_TALK_SLOT_RESET 0x08

/* The price of a cut. */
#define BARBER_TALK_PRICE 3000
/* The flag of the block 0x021d27ac set while a cut is paid for and not given. */
#define BARBER_TALK_FLAG_PAID 7
/* The daily bit set once a cut was had today (TalkChecks_TestSetDailyBit). */
#define BARBER_TALK_DAILY_CUT 0x13
/* The current player's flag set at the first talk with her. */
#define BARBER_TALK_FLAG_MET 0xb
/* The cuts counted (the player's field 0x2416, count 0x0a) from which she offers more. */
#define BARBER_TALK_MANY_CUTS 0x10

/* The music's priority whose value the talk's closing raises. */
#define BARBER_TALK_MUSIC_PRIORITY 0xe
#define BARBER_TALK_MUSIC_VALUE 0x46

/* The sounds when the hat is taken off and put back on. */
#define BARBER_TALK_SE_HAT_OFF 0x43
#define BARBER_TALK_SE_HAT_ON 0x44

/* Lines of "sp_npc_barber" handled here. */
#define BARBER_LINE_PRICE 8
#define BARBER_LINE_PAID 0x3c
#define BARBER_LINE_NO_MONEY 0x3f
#define BARBER_LINE_COLOUR_PICKED 0xc
#define BARBER_LINE_CUT_DONE 0xd
#define BARBER_LINE_NEW_HAIR 0xe
#define BARBER_LINE_SAME_HAIR 0x37
#define BARBER_LINE_OTHER_STYLES 0x17
#define BARBER_LINE_OWN_STYLES 0x18
#define BARBER_LINE_STYLES 0x2f /* to 0x36 */
#define BARBER_LINE_HAT_OFF 0x40
#define BARBER_LINE_HAT_ON 0x41
#define BARBER_LINE_SEND_BACK 0x42
#define BARBER_LINE_CHAIR 0x3e
#define BARBER_LINE_CHAIR_MANY_0 0x15
#define BARBER_LINE_CHAIR_MANY_1 0x16

static TalkObject *barber_talk_object(BarberTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The line shown. */
static u8 barber_talk_shown(const BarberTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `line` of `name`. */
static void barber_talk_say(BarberTalk *talk, int line, const char *name)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(barber_talk_object(talk), &message, name);
}

static u32 *barber_talk_flags(void)
{
    return (u32 *) (void *) Block021d27ac_Get();
}

/* ---- The class */

/* func_ov053_02260bdc (vtable slot 0x04): its destructor, then the scene freed. */
BarberTalk *BarberTalk_DestructDelete(BarberTalk *talk)
{
    talk->base.vtable = data_ov053_02261b08;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov053_02260bdc, BarberTalk_DestructDelete)

/* func_ov053_02260bfc (vtable slot 0x00): the destructor of the scene class it derives from. */
void *BarberTalk_Destruct(void *talk)
{
    *(const u8 **) talk = data_ov053_02261b08;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov053_02260bfc, BarberTalk_Destruct)

/* func_ov053_02260c14: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *BarberTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov053_02261b08;
    return talk;
}
CLEAN_AS(func_ov053_02260c14, BarberTalk_Construct)

/* func_ov053_02260bb8: the scene reset through its vtable slot 0x08, given its owner, and with
 * no topic. */
void BarberTalk_Begin(BarberTalk *talk, Barber *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + BARBER_TALK_SLOT_RESET);
    ((void (*)(BarberTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->topic = BARBER_TOPIC_NONE;
}
CLEAN_AS(func_ov053_02260bb8, BarberTalk_Begin)

/* func_ov053_02260ba8: the topic.
 * REQUIRES: the talk at a word-aligned address, as every object of the game. */
u32 BarberTalk_Topic(BarberTalk *talk)
{
    return talk->topic;
}
CLEAN_AS(func_ov053_02260ba8, BarberTalk_Topic)

/* func_ov053_02260bb0: the topic set.
 * REQUIRES: the talk at a word-aligned address, as every object of the game. */
void BarberTalk_SetTopic(BarberTalk *talk, u32 topic)
{
    talk->topic = topic;
}
CLEAN_AS(func_ov053_02260bb0, BarberTalk_SetTopic)

/* func_ov053_02261514: the hair colour picked. */
u8 BarberTalk_Colour(BarberTalk *talk)
{
    return talk->colour;
}
CLEAN_AS(func_ov053_02261514, BarberTalk_Colour)

/* func_ov053_0226151c: the hair style picked. */
u8 BarberTalk_Style(BarberTalk *talk)
{
    return talk->style;
}
CLEAN_AS(func_ov053_0226151c, BarberTalk_Style)

/* ---- Its lines and answers */

/* func_ov053_0226075c: the line said in the chair: once the current player has had 16 cuts or
 * more (the count 0x0a of its field 0x2416), 0x15 or 0x16 by the player's byte 0x1c (0 or
 * not), else 0x3e. */
int BarberTalk_ChairLine(void *unused)
{
    (void) unused;
    u8 *record = PlayerRecords_Current();
    if ((unsigned int) PlayerField2416_Count0A((PlayerField2416 *) (void *) PlayerRecord_Field2416(record)) >=
        BARBER_TALK_MANY_CUTS) {
        if (PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record)) == 0) {
            return BARBER_LINE_CHAIR_MANY_0;
        }
        return BARBER_LINE_CHAIR_MANY_1;
    }
    return BARBER_LINE_CHAIR;
}
CLEAN_AS(func_ov053_0226075c, BarberTalk_ChairLine)

/* func_ov053_02260790 (vtable slot 0x18, the player's answer), by the line shown:
 * - 1, 2 and 4: the first answer shows the screen's panels (ScreenPanels_Request) and the price
 *   (line 8);
 * - 8, the price: the first answer, when the owner can pay 3,000 bells, takes them, notes the
 *   cut as paid (the flag 7 of the block 0x021d27ac), clears the style and colour picked and
 *   keeps the player's hair style and colour: line 0x3c; when it cannot, line 0x3f;
 * - 9 and 10, and 11 and 0x38: an answer but the fifth picks the colour of the first or the
 *   second menu of colours: line 0xc.
 * QUIRK: the current player's record is fetched first even when not used. */
void BarberTalk_OnAnswer(BarberTalk *talk)
{
    u8 *record = PlayerRecords_Current();
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    const char *name = data_ov053_02261980;
    int line = BARBER_TALK_NO_LINE;

    switch (barber_talk_shown(talk)) {
        case 1:
        case 2:
        case 4:
            if (answer == 0) {
                ScreenPanels_Request();
                line = BARBER_LINE_PRICE;
            }
            break;
        case BARBER_LINE_PRICE:
            if (answer == 0) {
                int owner = (int) (uintptr_t) talk->owner;
                if (SceneBells_CanPay(owner, BARBER_TALK_PRICE)) {
                    SceneBells_Take(owner, BARBER_TALK_PRICE);
                    line = BARBER_LINE_PAID;
                    Block021d27ac_SetFlag(barber_talk_flags(), BARBER_TALK_FLAG_PAID);
                    talk->style = 0;
                    talk->colour = 0;
                    talk->old_style = (u8) PlayerRecord_HeadKind(record);
                    talk->old_colour = (u8) PlayerRecord_HairColor(record);
                } else {
                    line = BARBER_LINE_NO_MONEY;
                }
            }
            break;
        case 9:
        case 10:
            if (answer != BARBER_TALK_NO_ANSWER) {
                talk->colour = data_ov053_022617c4[answer];
                line = BARBER_LINE_COLOUR_PICKED;
            }
            break;
        case 11:
        case 0x38:
            if (answer != BARBER_TALK_NO_ANSWER) {
                talk->colour = data_ov053_022617c0[answer];
                line = BARBER_LINE_COLOUR_PICKED;
            }
            break;
        default:
            break;
    }
    if (line != BARBER_TALK_NO_LINE) {
        barber_talk_say(talk, line, name);
    }
}
CLEAN_AS(func_ov053_02260790, BarberTalk_OnAnswer)

/* func_ov053_02260894 (vtable slot 0x14, a line ended), by the line shown:
 * - 0xd, the cut done: line 0x37 when the style and colour picked are the player's old ones,
 *   else 0xe; no page of it gone on yet;
 * - 0x17 and 0x18: the styles offered become the other set's, or the player's own;
 * - 0x2f to 0x36: the line's style picked, of the set by the player's byte 0x1c (the other set
 *   when asked for);
 * - 0x40: the player's hat and accessory taken off (sound 0x43), then the chair's line
 *   (BarberTalk_ChairLine);
 * - 0x41: they are put back on (sound 0x44);
 * - 0x42: the owner sends the player back (its state 9);
 * - 0xe and 0x37, the cut's last line: the daily bit 0x13 set, the cut no longer owed (the
 *   flag 7 cleared), and the talk given the message number data_021f43e8 holds.
 * QUIRK: the current player's record is fetched first even when not used. A byte 0x1c other
 * than 0 and 1 reads the style of the next line's set. */
void BarberTalk_OnLineEnded(BarberTalk *talk)
{
    u8 *record = PlayerRecords_Current();
    const char *name = data_ov053_02261980;
    int line = BARBER_TALK_NO_LINE;
    u8 shown = barber_talk_shown(talk);

    switch (shown) {
        case BARBER_LINE_CUT_DONE:
            if (talk->style == talk->old_style && talk->colour == talk->old_colour) {
                line = BARBER_LINE_SAME_HAIR;
            } else {
                line = BARBER_LINE_NEW_HAIR;
            }
            talk->pages = 0;
            break;
        case BARBER_LINE_OTHER_STYLES:
            talk->other_styles = 1;
            break;
        case BARBER_LINE_OWN_STYLES:
            talk->other_styles = 0;
            break;
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36: {
            int set = PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record));
            if (talk->other_styles != 0) {
                set = set == 0 ? 1 : 0;
            }
            talk->style = data_ov053_022617ec[(shown - BARBER_LINE_STYLES) * BARBER_TALK_STYLE_SETS + set];
            break;
        }
        case BARBER_LINE_HAT_OFF:
            RoomPlayerActor_SwitchHeadwear(0);
            SoundSys_PlaySe(BARBER_TALK_SE_HAT_OFF);
            line = BarberTalk_ChairLine(talk);
            break;
        case BARBER_LINE_SEND_BACK:
            Barber_SetState(talk->owner, BARBER_STATE_SEND_BACK);
            break;
        case BARBER_LINE_NEW_HAIR:
        case BARBER_LINE_SAME_HAIR:
            TalkChecks_TestSetDailyBit(BARBER_TALK_DAILY_CUT, 1);
            Block021d27ac_ClearFlag(barber_talk_flags(), BARBER_TALK_FLAG_PAID);
            TalkObject_SetMessage(barber_talk_object(talk), &data_021f43e8, NULL);
            break;
        case BARBER_LINE_HAT_ON:
            RoomPlayerActor_SwitchHeadwear(1);
            SoundSys_PlaySe(BARBER_TALK_SE_HAT_ON);
            break;
        default:
            break;
    }
    if (line != BARBER_TALK_NO_LINE) {
        barber_talk_say(talk, line, name);
    }
}
CLEAN_AS(func_ov053_02260894, BarberTalk_OnLineEnded)

/* func_ov053_022609fc (vtable slot 0x70, the talk closes): after line 0xc (a colour picked) the
 * music's priority 0xe gets the value 0x46 at once. */
void BarberTalk_OnClose(BarberTalk *talk)
{
    if (barber_talk_shown(talk) == BARBER_LINE_COLOUR_PICKED) {
        Music_AddValue(BARBER_TALK_MUSIC_PRIORITY, BARBER_TALK_MUSIC_VALUE, 0);
    }
}
CLEAN_AS(func_ov053_022609fc, BarberTalk_OnClose)

/* func_ov053_02260a18 (vtable slot 0x74, the talk goes on in the same window): on the cut's
 * last line, a page is counted; at the second page of line 0xe or the third of 0x37 this console's
 * player's field actor is asked to stay at its spot (state 0x28, a blend of 10 frames) and the
 * current player's cuts are counted one more. */
void BarberTalk_OnGoOn(BarberTalk *talk)
{
    u8 shown = barber_talk_shown(talk);
    if (shown != BARBER_LINE_NEW_HAIR && shown != BARBER_LINE_SAME_HAIR) {
        return;
    }
    if ((shown == BARBER_LINE_NEW_HAIR && talk->pages == 1) || (shown == BARBER_LINE_SAME_HAIR && talk->pages == 2)) {
        RoomPlayerActor_RequestSpotStay();
        PlayerField2416_AddCount0A((PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current()), 1);
    }
    talk->pages++;
}
CLEAN_AS(func_ov053_02260a18, BarberTalk_OnGoOn)

/* func_ov053_02260a68 (vtable slot 0x78, the line the talk starts with), of "sp_npc_barber":
 * - the topic seated: the chair's line (BarberTalk_ChairLine);
 * - for a topic picked afresh (not call, seated with a hat, cut, not seated, leaving, hat back
 *   or claimed): with the cut paid for, paid; else, once a cut was had today, one of the cut
 *   today's three at random; else the first visit (the current player's flag 0xb set then) or
 *   the welcome;
 * then the line of the topic, from the table (whose names are filled on the first call).
 * QUIRK: a topic outside the table (only none, which is always picked afresh) leaves `out`
 * as it was. */
void BarberTalk_Line(BarberTalk *talk, BarberTalkStart *out)
{
    u8 *record = PlayerRecords_Current();
    {
        u32 flags = data_ov053_02261c60;
        if ((flags & 1) == 0) {
            const char *name = data_ov053_02261980;
            for (int i = 0; i < BARBER_TOPICS; i++) {
                data_ov053_02261a90[i].name = name;
            }
            data_ov053_02261c60 = flags | 1;
        }
    }

    if (talk->topic == BARBER_TOPIC_SEATED) {
        out->name = data_ov053_02261a90[BARBER_TOPIC_SEATED].name;
        out->message = (u8) BarberTalk_ChairLine(talk);
        return;
    }
    switch (talk->topic) {
        case BARBER_TOPIC_CALL:
        case BARBER_TOPIC_SEATED_HAT:
        case BARBER_TOPIC_CUT:
        case BARBER_TOPIC_NOT_SEATED:
        case BARBER_TOPIC_LEAVING:
        case BARBER_TOPIC_HAT_BACK:
        case BARBER_TOPIC_CLAIMED:
            break;
        default:
            if (Barber_IsPaid((int) (uintptr_t) talk->owner)) {
                BarberTalk_SetTopic(talk, BARBER_TOPIC_PAID);
            } else if (TalkChecks_TestSetDailyBit(BARBER_TALK_DAILY_CUT, 0)) {
                BarberTalk_SetTopic(talk, (u32) (BARBER_TOPIC_CUT_TODAY + (int) MainRandom_Below(3)));
            } else if (PlayerRecord_TestFlag(record, BARBER_TALK_FLAG_MET) == 0) {
                BarberTalk_SetTopic(talk, BARBER_TOPIC_FIRST_VISIT);
                PlayerRecord_SetFlag(record, BARBER_TALK_FLAG_MET);
            } else {
                BarberTalk_SetTopic(talk, BARBER_TOPIC_WELCOME);
            }
            break;
    }
    s32 topic = (s32) talk->topic;
    if (topic >= 0 && topic < BARBER_TOPICS) {
        out->message = data_ov053_02261a90[topic].message;
        out->name = data_ov053_02261a90[topic].name;
    }
}
CLEAN_AS(func_ov053_02260a68, BarberTalk_Line)
