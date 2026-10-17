/* The faceless cat's talk scene (mystery_cat_talk.h). */
#include "mystery_cat_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/design.h"
#include "main/design_info.h"
#include "main/group_params.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/name_texts.h"
#include "main/obj_020d9ff8.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/villager_impression.h"
#include "main/wfc_stats.h"

static_assert(sizeof(MysteryCatLine) == 8, "a line");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");
static_assert(sizeof(DesignCreator) == 0x1e, "a player's id");

/* The talk scene's vtable. */
extern const u8 data_ov074_02279bd8[];
/* The message file's name, "sp_npc_mysterycat", and the impressions', "st_impress". */
extern const char data_ov074_02279d14[];
extern const char data_ov074_02279d28[];
/* The functions run once the screens it opens close: after the design screen
 * (MysteryCatTalk_TakeDesign) and after screen mode 0x14 (MysteryCatTalk_TakeImpression), and
 * the table they are copied into the first time one is set (bit 0 of the guard word). */
extern const MemberPointer data_ov074_02279b90;
extern const MemberPointer data_ov074_02279b50;
extern MemberPointer data_ov074_02279d74[2];
extern u32 data_ov074_02279d4c;
/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;
/* The town's statistics record, which keeps her face and the impression she takes. */
extern WfcStats data_021f3278;

/* The daily bit of the current player (TalkChecks_TestSetDailyBit) set once she took an
 * impression of the player today. */
#define MCAT_TALK_DAILY_IMPRESSION 0x2b

/* The screen its commands open (SceneCommand_RequestScreen: group 9 in a mode), and the
 * modes: the design screen and the one after the new face. */
#define MCAT_TALK_SCREEN 2
#define MCAT_TALK_MODE_DESIGN 3
#define MCAT_TALK_MODE_IMPRESSION 0x14

/* The functions MysteryCatTalk_SetAfter picks. */
#define MCAT_TALK_AFTER_DESIGN 0
#define MCAT_TALK_AFTER_IMPRESSION 1

/* What its owner's face is shown on (main's scene_object.h): its model. */
#define MCAT_TALK_OWNER_MODEL 0xec

#define MCAT_TALK_NO_MESSAGE 0xff

/* The vtable slot its talks call first. */
#define MCAT_TALK_SLOT_08 0x08

static u8 mcat_talk_line_shown(const MysteryCatTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *mcat_talk_object(MysteryCatTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* Message `message` of "sp_npc_mysterycat" shown in `object`. */
static void mcat_talk_say(TalkObject *object, u8 message)
{
    TalkObject_SetMessage(object, &message, data_ov074_02279d14);
}

/* The information of her face, the design of the town's record. */
static DesignInfo *mcat_talk_face_info(void)
{
    return (DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) WfcStats_Design(&data_021f3278));
}

/* Whether her face's maker `maker` is set and is the current player: the same town (number and
 * name) and the same player (PlayerId_SamePlayer). */
static int mcat_talk_drawn_by_player(DesignCreator *maker)
{
    if (PlayerId_IsSet(maker) == 0) {
        return 0;
    }
    DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
    return maker->town_id == player->town_id && memcmp(maker->town_name, player->town_name, sizeof maker->town_name) == 0 &&
           PlayerId_SamePlayer(maker, player) != 0;
}

/* func_ov074_02278ba4 (slot 0x18, the player's answer), by the line shown and the answer
 * picked:
 * - 0x03: the first answer, 0x0a when the player drew her face, else 0x09; another answer, 0x0c
 *   when the player drew it, else 0x0b;
 * - 0x0d: any answer but the first, 0x0e.
 * The line, when one was picked, is shown. Copies of her face's information and of its maker
 * are made and destroyed around it. */
void MysteryCatTalk_OnAnswer(MysteryCatTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    DesignInfo info = *mcat_talk_face_info();
    DesignCreator maker = *DesignInfo_Creator(&info);
    int next = MCAT_TALK_NO_MESSAGE;

    switch (mcat_talk_line_shown(talk)) {
        case MYSTERY_CAT_LINE_ASK:
            if (answer == 0) {
                next = mcat_talk_drawn_by_player(&maker) ? MYSTERY_CAT_LINE_OWN_FIRST : MYSTERY_CAT_LINE_OTHER_FIRST;
            } else {
                next = mcat_talk_drawn_by_player(&maker) ? MYSTERY_CAT_LINE_OWN_SECOND : MYSTERY_CAT_LINE_OTHER_SECOND;
            }
            break;
        case MYSTERY_CAT_LINE_ASK_AGAIN:
            if (answer != 0) {
                next = MYSTERY_CAT_LINE_DRAW;
            }
            break;
        default:
            break;
    }
    if (next != MCAT_TALK_NO_MESSAGE) {
        mcat_talk_say(mcat_talk_object(talk), (u8) next);
    }
    PlayerId_Destruct(&maker);
    DesignInfo_Destruct(&info);
}
CLEAN_AS(func_ov074_02278ba4, MysteryCatTalk_OnAnswer)

/* func_ov074_02278d44 (slot 0x14, a line ended), by the line:
 * - 0x09 to 0x0c: line 0x0d is shown;
 * - 0x0e: her face shown again on her model, the design screen opened (mode 3, staying on the
 *   line after it) and MysteryCatTalk_TakeDesign set to run after it;
 * - 0x1c: screen mode 0x14 opened the same way and MysteryCatTalk_TakeImpression set to run
 *   after it. */
void MysteryCatTalk_OnLineEnded(MysteryCatTalk *talk)
{
    SceneCommandScene *scene = (SceneCommandScene *) (void *) talk;
    MysteryCat *owner;

    switch (mcat_talk_line_shown(talk)) {
        case MYSTERY_CAT_LINE_OTHER_FIRST:
        case MYSTERY_CAT_LINE_OWN_FIRST:
        case MYSTERY_CAT_LINE_OTHER_SECOND:
        case MYSTERY_CAT_LINE_OWN_SECOND:
            mcat_talk_say(mcat_talk_object(talk), MYSTERY_CAT_LINE_ASK_AGAIN);
            break;
        case MYSTERY_CAT_LINE_DRAW:
            owner = talk->owner;
            MysteryCatFace_Show(&owner->face, owner->base + MCAT_TALK_OWNER_MODEL);
            SceneCommand_SetScreenMode(scene, MCAT_TALK_MODE_DESIGN, 0);
            SceneCommand_RequestScreen(scene, MCAT_TALK_SCREEN);
            MysteryCatTalk_SetAfter(talk, MCAT_TALK_AFTER_DESIGN);
            break;
        case MYSTERY_CAT_LINE_NEW_FACE:
            SceneCommand_SetScreenMode(scene, MCAT_TALK_MODE_IMPRESSION, 0);
            SceneCommand_RequestScreen(scene, MCAT_TALK_SCREEN);
            MysteryCatTalk_SetAfter(talk, MCAT_TALK_AFTER_IMPRESSION);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov074_02278d44, MysteryCatTalk_OnLineEnded)

/* func_ov074_02278de8 (slot 0x78, the line the talk starts with), of "sp_npc_mysterycat": 0x03
 * (she asks) when a coin says so or the daily bit 0x2b is clear; else 0x18 to 0x1b when the
 * player drew her face, 0x11 to 0x14 otherwise (one of four at random). When her face has a
 * maker, the talk's parts are filled: the maker's name (part 1) and town (part 0), the
 * impression she imitates (part 2, the record's byte 0x237 as a message of "st_impress") and
 * the face's title (part 3). */
void MysteryCatTalk_Line(MysteryCatTalk *talk, MysteryCatLine *out)
{
    out->text = (u32) (uintptr_t) data_ov074_02279d14;
    DesignInfo info = *mcat_talk_face_info();
    DesignCreator maker = *DesignInfo_Creator(&info);

    if (MainRandom_Below(2) == 0 || TalkChecks_TestSetDailyBit(MCAT_TALK_DAILY_IMPRESSION, 0) == 0) {
        out->message = MYSTERY_CAT_LINE_ASK;
    } else if (mcat_talk_drawn_by_player(&maker)) {
        out->message = (u8) (MainRandom_Below(4) + MYSTERY_CAT_LINE_SHOWN_OWN);
    } else {
        out->message = (u8) (MainRandom_Below(4) + MYSTERY_CAT_LINE_SHOWN_OTHER);
    }

    NameText title;
    NameText_Construct(&title);
    if (PlayerId_IsSet(&maker)) {
        SceneBase_PutNameAt10(&talk->base, &maker, 1);
        SceneBase_PutNameAt2(&talk->base, (unsigned int) (uintptr_t) PlayerId_Town(&maker), 0);
        u8 impression = WfcStats_Byte237(&data_021f3278);
        TalkObject_LoadPart(mcat_talk_object(talk), 2, &impression, (unsigned int) (uintptr_t) data_ov074_02279d28);
        DesignInfo_TitleToText(&info, &title);
        TalkObject_SetPart(mcat_talk_object(talk), 3, (TextBase *) (void *) &title);
    }
    NameText_Destruct(&title);
    PlayerId_Destruct(&maker);
    DesignInfo_Destruct(&info);
}
CLEAN_AS(func_ov074_02278de8, MysteryCatTalk_Line)

/* func_ov074_02278fa8: its talk scene told through its vtable slot 0x08 and given its owner. */
void MysteryCatTalk_Begin(MysteryCatTalk *talk, MysteryCat *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + MCAT_TALK_SLOT_08);
    ((void (*)(MysteryCatTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov074_02278fa8, MysteryCatTalk_Begin)

/* func_ov074_02278fc4 (slot 0x04): its destructor, then the scene freed. */
void *MysteryCatTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov074_02279bd8;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov074_02278fc4, MysteryCatTalk_Delete)

/* func_ov074_02278fe4 (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *MysteryCatTalk_Destroy(void *talk)
{
    *(const u8 **) talk = data_ov074_02279bd8;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov074_02278fe4, MysteryCatTalk_Destroy)

/* func_ov074_02278ffc: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *MysteryCatTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov074_02279bd8;
    return talk;
}
CLEAN_AS(func_ov074_02278ffc, MysteryCatTalk_Construct)

/* func_ov074_02279014 (run after screen mode 0x14): when the player confirmed on the screen
 * (GroupParams_C4CIs1), she takes an impression of the current player (VillagerImpression_Pick
 * with fondness 0), kept in the town's record's byte 0x237, the record is marked to be sent
 * (status 3), the daily bit 0x2b is set and one of the lines 5 to 7 is shown; else nothing. */
void MysteryCatTalk_TakeImpression(MysteryCatTalk *talk)
{
    if (!GroupParams_C4CIs1()) {
        return;
    }
    TalkObject *object = mcat_talk_object(talk);
    WfcStats_SetByte237(&data_021f3278, (u8) VillagerImpression_Pick(PlayerRecords_Current(), 0, 0));
    WfcStats_SetStatus(&data_021f3278, WFC_STATS_STATUS_TO_SEND);
    u8 message = (u8) (MainRandom_Below(3) + MYSTERY_CAT_LINE_THANKS);
    TalkChecks_TestSetDailyBit(MCAT_TALK_DAILY_IMPRESSION, 1);
    mcat_talk_say(object, message);
}
CLEAN_AS(func_ov074_02279014, MysteryCatTalk_TakeImpression)

/* func_ov074_02279070 (run after the design screen): when the player gave a design
 * (GroupParams_C4CIs1), her face is shown again on her model and line 0x1c follows; else line
 * 0x0f. */
void MysteryCatTalk_TakeDesign(MysteryCatTalk *talk)
{
    TalkObject *object = mcat_talk_object(talk);
    u8 message = MYSTERY_CAT_LINE_NO_DESIGN;
    if (GroupParams_C4CIs1()) {
        message = MYSTERY_CAT_LINE_NEW_FACE;
        MysteryCat *owner = talk->owner;
        MysteryCatFace_Show(&owner->face, owner->base + MCAT_TALK_OWNER_MODEL);
    }
    mcat_talk_say(object, message);
}
CLEAN_AS(func_ov074_02279070, MysteryCatTalk_TakeDesign)

/* func_ov074_022790b4: the function to run once the scene's command ends: `which` of the two
 * (MCAT_TALK_AFTER_*), from the table filled from the overlay's constants the first time.
 * REQUIRES: `which` is 0 or 1. */
void MysteryCatTalk_SetAfter(MysteryCatTalk *talk, int which)
{
    static const MemberPointer *const constants[2] = {&data_ov074_02279b90, &data_ov074_02279b50};
    MemberTable_InitOnce(&data_ov074_02279d4c, data_ov074_02279d74, constants, 2);
    talk->after = data_ov074_02279d74[which];
}
CLEAN_AS(func_ov074_022790b4, MysteryCatTalk_SetAfter)

/* func_ov074_0227910c (slot 0x84, a command of the scene ended): the function set to run after
 * it, when there is one, runs and is cleared (the null member pointer). */
void MysteryCatTalk_RunAfter(MysteryCatTalk *talk)
{
    if (talk->after.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after, talk);
    talk->after = __ptmf_null;
}
CLEAN_AS(func_ov074_0227910c, MysteryCatTalk_RunAfter)
