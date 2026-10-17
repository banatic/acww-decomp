/* The mole's talk scene (mole_talk.h): his lines, the phrase, his music and the talk's
 * sequences. */
#include "mole_talk.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/group_params.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/sound_emitter.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "ov003/field_actor.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(MoleTalk, sequence) == 0xb0 && offsetof(MoleTalk, countdown) == 0xb4, "MoleTalk");
static_assert(offsetof(MoleTalk, owner) == 0xb8 && offsetof(MoleTalk, music_started) == 0xbc, "MoleTalk");
static_assert(sizeof(MoleTalk) == 0xc0, "MoleTalk");
static_assert(sizeof(MoleTalkSequence) == 12, "a sequence");
static_assert(sizeof(MoleTalkLine) == 8, "a line");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The class's vtable. */
extern const u8 data_ov077_022797fc[];
/* A word holding the address of "sp_npc_reset", the message file of his lines. */
extern const char *const data_ov077_02279700;
/* "st_general", the message file of the phrases. */
extern const char data_ov077_02279938[];
/* The first lines, by the count (MoleTalk_FirstLine). */
extern const u8 data_ov077_02279600[5];
/* His sound emitter in his object (scene_object.h). */
#define MOLE_TALK_EMITTER 0x514

/* The talk scene's vtable slot that resets it. */
#define MOLE_TALK_SLOT_RESET 2

/* No line to say. */
#define MOLE_TALK_NO_LINE 0xff

/* The lines of "sp_npc_reset" his code picks. */
#define MOLE_LINE_CLOSE_3 0x03 /* the lines whose close changes his music */
#define MOLE_LINE_CLOSE_8 0x08
#define MOLE_LINE_ASK 0x0b /* answered 0: 0x0d or 0x0e at random, else 0x0c or 0x0e */
#define MOLE_LINE_ASK_YES 0x0d
#define MOLE_LINE_ASK_NO 0x0c
#define MOLE_LINE_ASK_EITHER 0x0e
#define MOLE_LINE_WAIT 0x0f /* ends with the 90 frames' wait */
#define MOLE_LINE_WAITED 0x10
#define MOLE_LINE_PHRASE 0x17 /* begins with the phrase picked, ends with its screen */
#define MOLE_LINE_PHRASE_DONE 0x18
#define MOLE_LINE_PHRASE_OK 0x19 /* the screen's result 1: 0x19 or 0x1a */
#define MOLE_LINE_PHRASE_OK_2 0x1a
#define MOLE_LINE_CLOSE_18 0x12
#define MOLE_LINE_CLOSE_26 0x1a
#define MOLE_LINE_GUESS_FIRST 0x1f /* 0x1f-0x21: 0x22 when the answer's step is in range */
#define MOLE_LINE_GUESS_LAST 0x21
#define MOLE_LINE_GUESS_HIT 0x22
#define MOLE_LINE_GUESS_MISS 0x20 /* or 0x21 */
#define MOLE_LINE_CLOSE_35 0x23

/* The phrases: one of 16 messages of "st_general". */
#define MOLE_PHRASES 16

/* The answer's step hits when it is between a number below 13 and five more. */
#define MOLE_GUESS_RANGE 13
#define MOLE_GUESS_WIDTH 5

/* The screen the phrase is given to (scene_command.h) and its mode. */
#define MOLE_PHRASE_SCREEN 3
#define MOLE_PHRASE_SCREEN_MODE 0xc

/* The frames of the wait (MOLE_TALK_SEQ_WAIT). */
#define MOLE_WAIT_FRAMES 0x5a

/* The first lines by the count: the counts' index goes up to 4; above that one at random. */
#define MOLE_FIRST_LINES 5
#define MOLE_FIRST_COUNT_RANDOM 5

/* The tags of slot 0x1c, and his sounds for them with their volume. */
#define MOLE_TAG_PLAYER_ANIMATION 0
#define MOLE_TAG_SOUND_1 1
#define MOLE_TAG_SOUND_2 2
#define MOLE_SOUND_TAG_1 0x7f4
#define MOLE_SOUND_TAG_2 0x7f5
#define MOLE_SOUND_VOLUME 0x7f

/* His music (music_queue.h): 0x43 at priority 0x18; at a close, the value 0x16 for 0x20 frames
 * at priority 0x17. */
#define MOLE_MUSIC 0x43
#define MOLE_MUSIC_PRIORITY 0x18
#define MOLE_MUSIC_DROPPED_PRIORITY 0x17
#define MOLE_MUSIC_VOLUME 0x7f
#define MOLE_MUSIC_CLOSE_VALUE 0x16
#define MOLE_MUSIC_CLOSE_FRAMES 0x20

/* What the talk object is told when the wait begins (TalkObject.mode). */
#define MOLE_TALK_MODE_WAIT 0

static u8 mole_line_shown(const MoleTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *mole_talk_object(const MoleTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *mole_command(MoleTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

static TalkAnswers *mole_choices(MoleTalk *talk)
{
    return (TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene);
}

/* Line `line` of "sp_npc_reset" shown. */
static void mole_say(const MoleTalk *talk, u8 line)
{
    TalkObject_SetMessage(mole_talk_object(talk), &line, data_ov077_02279700);
}

/* One of two lines, at random: `first` when the draw is 0. */
static u8 mole_either(u8 first, u8 second)
{
    return MainRandom_Below(2) == 0 ? first : second;
}

/* func_ov077_02278a9c (slot 0x18, the player's answer), by the line shown:
 * - 0x0b: answered 0, 0x0e or 0x0d; else 0x0e or 0x0c (at random);
 * - 0x1f-0x21: with a number r below 13 drawn, 0x22 when the answer's step is between r and
 *   r + 5, else 0x20 or 0x21 at random.
 * The line, when one was picked, is shown. */
void MoleTalk_OnAnswer(MoleTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked(mole_choices(talk));
    u8 line = MOLE_TALK_NO_LINE;
    u8 shown = mole_line_shown(talk);

    if (shown == MOLE_LINE_ASK) {
        line = mole_either(MOLE_LINE_ASK_EITHER, answer == 0 ? MOLE_LINE_ASK_YES : MOLE_LINE_ASK_NO);
    } else if (shown >= MOLE_LINE_GUESS_FIRST && shown <= MOLE_LINE_GUESS_LAST) {
        int low = (int) MainRandom_Below(MOLE_GUESS_RANGE);
        int step = (int) TalkAnswers_PickedStep(mole_choices(talk));
        if (Math_IsBetween(step, low, low + MOLE_GUESS_WIDTH)) {
            line = MOLE_LINE_GUESS_HIT;
        } else {
            line = mole_either(MOLE_LINE_GUESS_MISS, MOLE_LINE_GUESS_MISS + 1);
        }
    }
    if (line != MOLE_TALK_NO_LINE) {
        mole_say(talk, line);
    }
}
CLEAN_AS(func_ov077_02278a9c, MoleTalk_OnAnswer)

/* func_ov077_02278b54 (slot 0x14, a line ended): line 0x0f, the talk object's mode 0 and the
 * wait (sequence 2); line 0x17, the screen of mode 0xc given the phrase, screen 3 asked for, and
 * sequence 1 after it. */
void MoleTalk_OnLineEnded(MoleTalk *talk)
{
    switch (mole_line_shown(talk)) {
        case MOLE_LINE_WAIT:
            mole_talk_object(talk)->mode = MOLE_TALK_MODE_WAIT;
            MoleTalk_SetSequence(talk, MOLE_TALK_SEQ_WAIT);
            break;
        case MOLE_LINE_PHRASE:
            SceneCommand_SetScreenModeArg(mole_command(talk), MOLE_PHRASE_SCREEN_MODE, talk->owner->phrase, 0);
            SceneCommand_RequestScreen(mole_command(talk), MOLE_PHRASE_SCREEN);
            MoleTalk_SetSequence(talk, MOLE_TALK_SEQ_AFTER_PHRASE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov077_02278b54, MoleTalk_OnLineEnded)

/* func_ov077_02278ba0 (slot 0x10, a line begins): at line 0x17 a phrase drawn below 16, the
 * next one (16 going back to 0) when it is the one picked before, kept by the owner and loaded
 * from "st_general" into the talk's part 0. */
void MoleTalk_OnLineBegins(MoleTalk *talk)
{
    if (mole_line_shown(talk) != MOLE_LINE_PHRASE) {
        return;
    }
    u8 phrase = (u8) MainRandom_Below(MOLE_PHRASES);
    if (phrase == talk->owner->phrase) {
        phrase++;
        if (phrase == MOLE_PHRASES) {
            phrase = 0;
        }
    }
    talk->owner->phrase = phrase;
    u8 message = talk->owner->phrase;
    TalkObject_LoadPart(mole_talk_object(talk), 0, &message, (unsigned int) (uintptr_t) data_ov077_02279938);
}
CLEAN_AS(func_ov077_02278ba0, MoleTalk_OnLineBegins)

/* func_ov077_02278bfc (slot 0x78, the line the talk starts with), of "sp_npc_reset": by the
 * current player's count 0x0d less one, kept to 0-5; at 5 a number 1-4 drawn instead; the line
 * of data_ov077_02279600 at that index. */
void MoleTalk_FirstLine(MoleTalk *talk, MoleTalkLine *out)
{
    (void) talk;
    PlayerField2416 *field = (PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current());
    int index = PlayerField2416_Count0D(field) - 1;
    if (index < 0) {
        index = 0;
    } else if (index > MOLE_FIRST_COUNT_RANDOM) {
        index = MOLE_FIRST_COUNT_RANDOM;
    }
    if (index == MOLE_FIRST_COUNT_RANDOM) {
        index = (int) MainRandom_Below(MOLE_FIRST_LINES - 1) + 1;
    }
    if (index > MOLE_FIRST_LINES - 1) {
        index = MOLE_FIRST_LINES - 1;
    }
    out->message = data_ov077_02279600[index];
    out->text = (u32) (uintptr_t) data_ov077_02279700;
}
CLEAN_AS(func_ov077_02278bfc, MoleTalk_FirstLine)

/* func_ov077_02278c50 (slot 0x1c, a message's tag): 0, the player's animation 99
 * (FieldActor_PlayerAnimation99); 1 and 2, his sounds 0x7f4 and 0x7f5. */
static void mole_play(MoleTalk *talk, int sound)
{
    SoundEmitter_Play((SoundEmitter *) (void *) (talk->owner->base + MOLE_TALK_EMITTER), sound, MOLE_SOUND_VOLUME, 0);
}

void MoleTalk_OnTag(MoleTalk *talk, int tag)
{
    switch (tag) {
        case MOLE_TAG_PLAYER_ANIMATION:
            FieldActor_PlayerAnimation99();
            break;
        case MOLE_TAG_SOUND_1:
            mole_play(talk, MOLE_SOUND_TAG_1);
            break;
        case MOLE_TAG_SOUND_2:
            mole_play(talk, MOLE_SOUND_TAG_2);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov077_02278c50, MoleTalk_OnTag)

/* func_ov077_02278ca0: the talk reset through its vtable slot 0x08 and given its owner. */
void MoleTalk_Begin(MoleTalk *talk, Mole *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(MoleTalk *))(uintptr_t) vtable[MOLE_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov077_02278ca0, MoleTalk_Begin)

/* func_ov077_02278cbc (slot 0x70, the talk's close): after the lines 0x03, 0x08, 0x12, 0x1a and
 * 0x23 his music 0x43 is dropped and the queue of priority 0x17 gets the value 0x16 for 0x20
 * frames. */
void MoleTalk_OnClose(MoleTalk *talk)
{
    switch (mole_line_shown(talk)) {
        case MOLE_LINE_CLOSE_3:
        case MOLE_LINE_CLOSE_8:
        case MOLE_LINE_CLOSE_18:
        case MOLE_LINE_CLOSE_26:
        case MOLE_LINE_CLOSE_35:
            Music_DropMusic(MOLE_MUSIC);
            Music_AddValue(MOLE_MUSIC_DROPPED_PRIORITY, MOLE_MUSIC_CLOSE_VALUE, MOLE_MUSIC_CLOSE_FRAMES);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov077_02278cbc, MoleTalk_OnClose)

/* func_ov077_02278d00 (slot 0x74, the talk going on in its window): the first time, the music
 * of priority 0x17 dropped and his music 0x43 asked for at priority 0x18. */
void MoleTalk_OnGoOn(MoleTalk *talk)
{
    if (talk->music_started == 0) {
        Music_DropPriority(MOLE_MUSIC_DROPPED_PRIORITY);
        Music_Add(MOLE_MUSIC_PRIORITY, MOLE_MUSIC, MOLE_MUSIC_VOLUME, 1);
        talk->music_started = 1;
    }
}
CLEAN_AS(func_ov077_02278d00, MoleTalk_OnGoOn)

/* func_ov077_02278d2c (slot 0x04): destructed, then freed. */
MoleTalk *MoleTalk_DestructDelete(MoleTalk *talk)
{
    talk->scene.vtable = data_ov077_022797fc;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov077_02278d2c, MoleTalk_DestructDelete)

/* func_ov077_02278d4c (slot 0x00): the destructor: its class's vtable, then the scene class's
 * body. */
MoleTalk *MoleTalk_Destruct(MoleTalk *talk)
{
    talk->scene.vtable = data_ov077_022797fc;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov077_02278d4c, MoleTalk_Destruct)

/* func_ov077_02278d64: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
MoleTalk *MoleTalk_Construct(MoleTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov077_022797fc;
    return talk;
}
CLEAN_AS(func_ov077_02278d64, MoleTalk_Construct)

/* func_ov077_02278d7c (sequence 1, once a command of the scene ended): when the screen's
 * group may open (GroupParams_CanOpen), line 0x18, or with the screen's result 1 line 0x1a or
 * 0x19 at random; then no sequence. */
void MoleTalk_AfterPhrase(MoleTalk *talk)
{
    if (GroupParams_CanOpen() == 0) {
        return;
    }
    u8 line = MOLE_LINE_PHRASE_DONE;
    if (GroupParams_C4CIs1() != 0) {
        line = mole_either(MOLE_LINE_PHRASE_OK_2, MOLE_LINE_PHRASE_OK);
    }
    mole_say(talk, line);
    MoleTalk_SetSequence(talk, MOLE_TALK_SEQ_NONE);
}
CLEAN_AS(func_ov077_02278d7c, MoleTalk_AfterPhrase)

/* func_ov077_02278dd4 (sequence 2, each frame): the frames counted down; once they are up,
 * line 0x10, the scene's next line asked for, and no sequence. */
void MoleTalk_Wait(MoleTalk *talk)
{
    if (Countdown_Tick8(&talk->countdown) == 0) {
        mole_say(talk, MOLE_LINE_WAITED);
        SceneCommand_RequestNextLine(mole_command(talk));
        MoleTalk_SetSequence(talk, MOLE_TALK_SEQ_NONE);
    }
}
CLEAN_AS(func_ov077_02278dd4, MoleTalk_Wait)

/* func_ov077_02278e10: the sequence `sequence` set, with 90 frames to count down. */
void MoleTalk_SetSequence(MoleTalk *talk, int sequence)
{
    talk->sequence = sequence;
    talk->countdown = MOLE_WAIT_FRAMES;
}
CLEAN_AS(func_ov077_02278e10, MoleTalk_SetSequence)

/* func_ov077_02278e20 (slot 0x84, a command of the scene ended): the sequence, when it is not
 * one run each frame and has a function, run; then no sequence.
 * REQUIRES: the sequence is below 3. */
void MoleTalk_RunAfterCommand(MoleTalk *talk)
{
    const MoleTalkSequence *sequence = &data_ov077_022797d0[talk->sequence];
    if (sequence->each_frame != 0 || sequence->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&sequence->run, talk);
    MoleTalk_SetSequence(talk, MOLE_TALK_SEQ_NONE);
}
CLEAN_AS(func_ov077_02278e20, MoleTalk_RunAfterCommand)

/* func_ov077_02278e70 (slot 0x80, each frame): the sequence, when it is one run each frame and
 * has a function, run.
 * REQUIRES: the sequence is below 3. */
void MoleTalk_RunEachFrame(MoleTalk *talk)
{
    const MoleTalkSequence *sequence = &data_ov077_022797d0[talk->sequence];
    if (sequence->each_frame != 0 && sequence->run.function != 0) {
        MemberPointer_CallVoid(&sequence->run, talk);
    }
}
CLEAN_AS(func_ov077_02278e70, MoleTalk_RunEachFrame)
