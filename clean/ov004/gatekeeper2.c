/* The gatekeeper indoors and its talk scene (gatekeeper2.h). */
#include "gatekeeper2.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/design.h"
#include "main/design_sets.h"
#include "main/event_queue.h"
#include "main/group_params.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/pool_link.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/recent_slots.h"
#include "main/scene_action.h"
#include "main/scene_command.h"
#include "main/scene_object.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_query.h"
#include "main/scene_share.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/sound_emitter.h"
#include "main/spawner.h"
#include "main/special_scene_object.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/town_item_lists.h"
#include "main/villager_move.h"
#include "main/villager_move_record.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(Gatekeeper2Talk, owner) == 0xb0, "owner");
static_assert(offsetof(Gatekeeper2Talk, state) == 0xb4, "state");
static_assert(sizeof(Gatekeeper2Talk) == 0xb8, "its talk scene");
static_assert(sizeof(Gatekeeper2Line) == 8, "a line");
static_assert(sizeof(Gatekeeper2TalkStep) == 0xc, "a task's function");
static_assert(offsetof(Gatekeeper2, state) == 0x654, "state");
static_assert(offsetof(Gatekeeper2, talk) == 0x658, "talk scene");
static_assert(offsetof(Gatekeeper2, home_yaw) == 0x710, "home yaw");
static_assert(sizeof(Gatekeeper2) == 0x714, "the size func_ov004_022258c4 allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define GATEKEEPER2_EMITTER 0x514     /* SoundEmitterObject */
#define GATEKEEPER2_PARTICIPANT 0x560 /* u8: whose system the last event came from */
#define GATEKEEPER2_LOCAL 0x563       /* u8: not shared with a session */
#define GATEKEEPER2_ACTION 0x618      /* SceneAction */

/* The field actor of this console's player. */
#define GATEKEEPER2_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define GATEKEEPER2_EVENT_TALK 0
#define GATEKEEPER2_EVENT_1 1
#define GATEKEEPER2_EVENT_STARTS 3
#define GATEKEEPER2_EVENT_REFUSED 4
#define GATEKEEPER2_EVENT_ENDED 8

/* The vtable slot of its talk scene its talks call first (SceneBase_Reset). */
#define GATEKEEPER2_TALK_SLOT_08 0x08

/* Its messages of "sp_npc_gatekeeper2". */
#define GATEKEEPER2_LINE_FIRST 0         /* the player's first talk (the record's flag 0x1b) */
#define GATEKEEPER2_LINE_AGAIN 4         /* then 4 to 7 */
#define GATEKEEPER2_LINE_GUEST 8         /* not the host, or a game started anew: 8 to 10 */
#define GATEKEEPER2_LINE_ASK 15          /* the question its answers below answer */
#define GATEKEEPER2_LINE_DESIGN_ASK 22   /* its first answer opens the design screen 6 */
#define GATEKEEPER2_LINE_SWAP 0x17       /* after it the design screen 9 */
#define GATEKEEPER2_LINE_ITEMS 0x1a      /* list A has items (their count in slot 0) */
#define GATEKEEPER2_LINE_NO_ITEMS 0x1b   /* list A is empty */
#define GATEKEEPER2_LINE_NOT_ONE 0x1c    /* the screen's number is above 1 */
#define GATEKEEPER2_LINE_ITEM 0x1e       /* the first pocket's item named in slot 0 */
#define GATEKEEPER2_LINE_NO_CHOICE 0x20  /* the screen gave no choice */
#define GATEKEEPER2_LINE_NO_VISITOR 0x2e /* no special character visits today */
#define GATEKEEPER2_LINE_ALONE 0x2f      /* linked: no one else; else 0x30, the newest named */
#define GATEKEEPER2_LINE_NEWEST 0x30
#define GATEKEEPER2_LINE_COPIED 0x18
#define GATEKEEPER2_LINE_SWAPPED 0x19
#define GATEKEEPER2_LINE_CANCELLED 1
#define GATEKEEPER2_NO_LINE 0xff

/* The player record's flag set after the first talk with it. */
#define GATEKEEPER2_FLAG_MET 0x1b

/* The screens it opens (SceneCommand_SetScreenMode, screen 2): the design screens and the
 * screen of the items of list A. */
#define GATEKEEPER2_SCREEN 2
#define GATEKEEPER2_SCREEN_COPY 6
#define GATEKEEPER2_SCREEN_SWAP 9
#define GATEKEEPER2_SCREEN_ITEMS 0x1f

/* The designs of its tasks (main's design.h): the player's (by its place in the order of the
 * player's designs) and the one design of kind 5. */
#define GATEKEEPER2_DESIGN_KIND 5
#define GATEKEEPER2_DESIGNS 8
#define GATEKEEPER2_DESIGN_SHIRT 0x12a8 /* the clothes of the player's designs: 0x12a8 to 0x12af */
#define GATEKEEPER2_DESIGN_HAT 0x1429   /* and the hats: 0x1429 to 0x1430 */
#define GATEKEEPER2_DESIGN_SOUND 0x50
#define GATEKEEPER2_SOUND_VOLUME 0x7f

/* How an item's name is put into the talk (SceneBase_PutItemName). */
#define GATEKEEPER2_ITEM_NAME_KIND 7

/* The vtables of the class and of its talk scene. */
extern const u8 data_ov004_02254918[];
extern const u8 data_ov004_02254888[];
/* The functions of its talk scene's tasks (filled at start-up by __sinit_ov004_0224e85c); the
 * flags that say which run at each step are in the overlay's .bss, so all are 0 and every task
 * runs when a command ends. */
extern Gatekeeper2TalkStep data_ov004_02258160[GATEKEEPER2_TALK_STATES];
/* Its message file's name, "sp_npc_gatekeeper2" (an address). */
extern const u32 data_ov004_02254794;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

static u8 *gk2_part(Gatekeeper2 *keeper, u32 offset)
{
    return keeper->base + offset;
}

static int gk2_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void gk2_set_slots(Gatekeeper2 *keeper, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(keeper->base, 1, owner, holder);
}

/* The talk of the scene. */
static TalkObject *gk2_talk_object(Gatekeeper2Talk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The message the talk scene shows. */
static u8 gk2_shown(Gatekeeper2Talk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `message` of "sp_npc_gatekeeper2". */
static void gk2_say(Gatekeeper2Talk *talk, u8 message)
{
    TalkObject_SetMessage(gk2_talk_object(talk), &message, (const char *) (uintptr_t) data_ov004_02254794);
}

static SceneCommandScene *gk2_command_of(Gatekeeper2Talk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* func_ov004_02224d80 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
Gatekeeper2 *Gatekeeper2_Destroy(Gatekeeper2 *keeper)
{
    *(const u8 **) (void *) keeper->base = data_ov004_02254918;
    Gatekeeper2Talk_Destroy(&keeper->talk);
    SpecialSceneObject_DestructBody(keeper);
    return keeper;
}
CLEAN_AS(func_ov004_02224d80, Gatekeeper2_Destroy)

/* func_ov004_02224da8 (vtable slot 0x44): the same, then the object freed. */
Gatekeeper2 *Gatekeeper2_Delete(Gatekeeper2 *keeper)
{
    *(const u8 **) (void *) keeper->base = data_ov004_02254918;
    Gatekeeper2Talk_Destroy(&keeper->talk);
    SpecialSceneObject_DestructBody(keeper);
    Heap_FreeAux(keeper);
    return keeper;
}
CLEAN_AS(func_ov004_02224da8, Gatekeeper2_Delete)

/* func_ov004_02224dd4 (vtable slot 0x4c, told of an event about it by `participant`'s system,
 * 4 for this one); unlike the cafe's master it does not go on to the base class's handling:
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused (state 6); this one's (with the object ours): owned and held by this system,
 *   paused;
 * - 1: it talks (state 1);
 * - 0, the player talks to it: the participant kept; another system's (not this one's slot):
 *   owned and held by it (state 5); this one's (with the object ours): owned and held by this
 *   system, and it talks (state 1);
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, it turns back (state 3); else owned by none and held by this
 *   system, it awaits the session (state 4);
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, it stands. */
void Gatekeeper2_OnEvent(Gatekeeper2 *keeper, unsigned int code, int participant)
{
    switch (code) {
        case GATEKEEPER2_EVENT_STARTS:
            *gk2_part(keeper, GATEKEEPER2_PARTICIPANT) = (u8) participant;
            if (participant != GATEKEEPER2_PLAYER_ACTOR) {
                gk2_set_slots(keeper, gk2_local_slot(), participant);
                Gatekeeper2_SetState(keeper, GATEKEEPER2_PAUSED);
            } else if (SceneShare_IsOurs(keeper->base)) {
                gk2_set_slots(keeper, gk2_local_slot(), gk2_local_slot());
                Gatekeeper2_SetState(keeper, GATEKEEPER2_PAUSED);
            }
            break;
        case GATEKEEPER2_EVENT_1:
            Gatekeeper2_SetState(keeper, GATEKEEPER2_TALK);
            break;
        case GATEKEEPER2_EVENT_TALK:
            *gk2_part(keeper, GATEKEEPER2_PARTICIPANT) = (u8) participant;
            if (participant != GATEKEEPER2_PLAYER_ACTOR && participant != gk2_local_slot()) {
                gk2_set_slots(keeper, participant, participant);
                Gatekeeper2_SetState(keeper, GATEKEEPER2_OTHER);
            } else if (SceneShare_IsOurs(keeper->base)) {
                gk2_set_slots(keeper, gk2_local_slot(), gk2_local_slot());
                Gatekeeper2_SetState(keeper, GATEKEEPER2_TALK);
            }
            break;
        case GATEKEEPER2_EVENT_ENDED:
            if (participant == GATEKEEPER2_PLAYER_ACTOR) {
                if (LinkGlobal_HoldsScene()) {
                    gk2_set_slots(keeper, gk2_local_slot(), SCENE_SHARE_NO_SLOT);
                    Gatekeeper2_SetState(keeper, GATEKEEPER2_TURN_BACK);
                } else {
                    gk2_set_slots(keeper, SCENE_SHARE_NO_SLOT, gk2_local_slot());
                    Gatekeeper2_SetState(keeper, GATEKEEPER2_AWAIT);
                }
            }
            break;
        case GATEKEEPER2_EVENT_REFUSED:
            if (SceneShare_IsHeld(keeper->base) && SceneShare_IsOurs(keeper->base)) {
                int owner = SCENE_SHARE_NO_SLOT;
                int holder = SCENE_SHARE_NO_SLOT;
                if (SceneShare_ReadSlots(keeper->base, &owner, &holder) &&
                    (participant == GATEKEEPER2_PLAYER_ACTOR || participant == holder)) {
                    gk2_set_slots(keeper, gk2_local_slot(), SCENE_SHARE_NO_SLOT);
                    Gatekeeper2_SetState(keeper, GATEKEEPER2_STAND);
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02224dd4, Gatekeeper2_OnEvent)

/* Its action idle and no system holding it. */
static int gk2_may_act(Gatekeeper2 *keeper)
{
    if (SceneAction_IsBusy((SceneAction *) (void *) gk2_part(keeper, GATEKEEPER2_ACTION))) {
        return 0;
    }
    return SceneShare_IsHeld(keeper->base) == 0;
}

/* func_ov004_02224f30 (vtable slot 0x58): agreed when it is not shared with a session, else as
 * Gatekeeper2_MayAct. */
int Gatekeeper2_MayActOrLocal(Gatekeeper2 *keeper)
{
    if (*gk2_part(keeper, GATEKEEPER2_LOCAL)) {
        return 1;
    }
    return gk2_may_act(keeper);
}
CLEAN_AS(func_ov004_02224f30, Gatekeeper2_MayActOrLocal)

/* func_ov004_02224f6c (vtable slot 0x48): whether the player may talk to it: its action idle
 * and no system holding it. */
int Gatekeeper2_MayAct(Gatekeeper2 *keeper)
{
    return gk2_may_act(keeper);
}
CLEAN_AS(func_ov004_02224f6c, Gatekeeper2_MayAct)

/* func_ov004_02224f98 (task 3, after the screen of list A's items): when the screen gave a
 * choice (GroupParams_C4CIs1): message 0x1c when its number is above 1, else the item of the
 * player's first pocket named in slot 0 and message 0x1e; with no choice message 0x20. */
void Gatekeeper2Talk_NameItem(Gatekeeper2Talk *talk)
{
    u8 message = GATEKEEPER2_LINE_NO_CHOICE;

    if (GroupParams_C4CIs1()) {
        if (GroupParams_Arg() > 1) {
            message = GATEKEEPER2_LINE_NOT_ONE;
        } else {
            u16 item = *Pockets_List();
            SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &item, 0, GATEKEEPER2_ITEM_NAME_KIND);
            message = GATEKEEPER2_LINE_ITEM;
        }
    }
    gk2_say(talk, message);
}
CLEAN_AS(func_ov004_02224f98, Gatekeeper2Talk_NameItem)

/* The place in the player's designs' order the screen picked, its design's index. */
static unsigned int gk2_picked_design(u8 *record)
{
    int place = GroupParams_Arg();
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    return DesignOrder_Get((unsigned char *) (uintptr_t) (u32) PlayerDesigns_Order(designs), place);
}

/* func_ov004_02224ff4 (task 2, after the design screen 9): when the screen gave a choice, the
 * current player's design picked is swapped with the design of kind 5 (told to the session),
 * the owner plays sound 0x50, and when the player wears that design's clothes (0x12a8 plus its
 * index) or its hat (0x1429 plus it) the player's field actor changes into it again (state 7,
 * kinds 0 and 2); message 0x19. With no choice message 1.
 * QUIRK: each worn item is read again for the test of its range, which always holds once it
 * equals the design's. */
void Gatekeeper2Talk_SwapDesign(Gatekeeper2Talk *talk)
{
    if (!GroupParams_C4CIs1()) {
        gk2_say(talk, GATEKEEPER2_LINE_CANCELLED);
        return;
    }
    u8 *record = PlayerRecords_Current();
    unsigned int index = gk2_picked_design(record);
    Design_Swap(DESIGN_KIND_LOCAL, (int) index, GATEKEEPER2_DESIGN_KIND, 0, 1);
    SoundEmitter_Play((SoundEmitter *) (void *) (talk->owner->base + GATEKEEPER2_EMITTER), GATEKEEPER2_DESIGN_SOUND,
                      GATEKEEPER2_SOUND_VOLUME, 0);

    u16 shirt = index < GATEKEEPER2_DESIGNS ? (u16) (index + GATEKEEPER2_DESIGN_SHIRT) : GATEKEEPER2_DESIGN_SHIRT;
    u16 hat = index < GATEKEEPER2_DESIGNS ? (u16) (index + GATEKEEPER2_DESIGN_HAT) : GATEKEEPER2_DESIGN_HAT;
    u16 clothes = *PlayerRecord_Clothes(record);
    u16 head = *PlayerRecord_HeadItem(record);

    if (shirt == clothes) {
        u16 worn = *PlayerRecord_Clothes(record);
        if (worn >= GATEKEEPER2_DESIGN_SHIRT && worn <= GATEKEEPER2_DESIGN_SHIRT + GATEKEEPER2_DESIGNS - 1) {
            u16 item = shirt;
            PlayerActorOps_RequestState7Kind0Next10(&item);
        }
    }
    if (hat == head) {
        u16 worn = *PlayerRecord_HeadItem(record);
        if (worn >= GATEKEEPER2_DESIGN_HAT && worn <= GATEKEEPER2_DESIGN_HAT + GATEKEEPER2_DESIGNS - 1) {
            u16 item = hat;
            PlayerActorOps_RequestState7Kind2Next10(&item);
        }
    }
    gk2_say(talk, GATEKEEPER2_LINE_SWAPPED);
}
CLEAN_AS(func_ov004_02224ff4, Gatekeeper2Talk_SwapDesign)

/* func_ov004_0222511c (task 1, after the design screen 6): when the screen gave a choice, the
 * current player's design picked is copied to the design of kind 5 (told to the session), the
 * owner plays sound 0x50 and message 0x18; with no choice message 1. */
void Gatekeeper2Talk_CopyDesign(Gatekeeper2Talk *talk)
{
    if (!GroupParams_C4CIs1()) {
        gk2_say(talk, GATEKEEPER2_LINE_CANCELLED);
        return;
    }
    u8 *record = PlayerRecords_Current();
    unsigned int index = gk2_picked_design(record);
    Design_Copy(DESIGN_KIND_LOCAL, (int) index, GATEKEEPER2_DESIGN_KIND, 0, 1);
    SoundEmitter_Play((SoundEmitter *) (void *) (talk->owner->base + GATEKEEPER2_EMITTER), GATEKEEPER2_DESIGN_SOUND,
                      GATEKEEPER2_SOUND_VOLUME, 0);
    gk2_say(talk, GATEKEEPER2_LINE_COPIED);
}
CLEAN_AS(func_ov004_0222511c, Gatekeeper2Talk_CopyDesign)

/* func_ov004_022251a4: task `state`. */
void Gatekeeper2Talk_SetState(Gatekeeper2Talk *talk, u32 state)
{
    talk->state = state;
}
CLEAN_AS(func_ov004_022251a4, Gatekeeper2Talk_SetState)

/* func_ov004_022251ac (the talk scene's slot 0x84, a command of the scene ended): the task's
 * function, when it is not one run at each step and it has one; then no task.
 * REQUIRES: the task is 0 to 3 (the table is not bounded). */
void Gatekeeper2Talk_RunCommandState(Gatekeeper2Talk *talk)
{
    const Gatekeeper2TalkStep *entry = &data_ov004_02258160[talk->state];
    if (entry->each_step != 0 || entry->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&entry->run, talk);
    Gatekeeper2Talk_SetState(talk, GATEKEEPER2_TALK_NONE);
}
CLEAN_AS(func_ov004_022251ac, Gatekeeper2Talk_RunCommandState)

/* func_ov004_022251fc (the talk scene's slot 0x80, each step): the task's function, when it is
 * one run at each step and it has one (none is).
 * REQUIRES: the task is 0 to 3. */
void Gatekeeper2Talk_RunStepState(Gatekeeper2Talk *talk)
{
    const Gatekeeper2TalkStep *entry = &data_ov004_02258160[talk->state];
    if (entry->each_step == 0 || entry->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&entry->run, talk);
}
CLEAN_AS(func_ov004_022251fc, Gatekeeper2Talk_RunStepState)

/* The message about the special character the spawner would make now (Spawner_PeekCode), by
 * its person code; 0x2e for none or one not listed. */
static u8 gk2_visitor_message(u16 code)
{
    switch (code) {
        case 0xd00a:
            return 0x22;
        case 0xd00e:
            return 0x23;
        case 0xd003:
            return 0x24;
        case 0xd013:
            return 0x25;
        case 0xd00b:
            return 0x26;
        case 0xd002:
            return 0x27;
        case 0xd00d:
            return 0x28;
        case 0xd021:
            return 0x29;
        case 0xd020:
            return 0x2a;
        case 0xd022:
            return 0x2b;
        case 0xd023:
            return 0x2c;
        default:
            return GATEKEEPER2_LINE_NO_VISITOR;
    }
}

/* func_ov004_02225240 (the talk scene's slot 0x18, the player's answer), by the message shown:
 * - 15: the first answer, with this console's slot taken in the session: linked, the player
 *   who joined last named in slot 1 (when there is one) and message 0x30, else 0x2f; not in a
 *   session, the message about today's visiting special character. The second answer: with
 *   items in list A their count in slot 0 (format 2) and message 0x1a, else 0x1b;
 * - 22: the first answer opens the design screen 6 (task 1 once it ends). */
void Gatekeeper2Talk_OnAnswer(Gatekeeper2Talk *talk)
{
    TalkObject *object = gk2_talk_object(talk);
    unsigned int answer = TalkAnswers_Picked(TalkObject_Answers(object));
    u8 message = GATEKEEPER2_NO_LINE;

    switch (gk2_shown(talk)) {
        case GATEKEEPER2_LINE_ASK:
            if (answer == 0) {
                NetSession *session = data_020ccf94;
                if (Session_IsSlotTaken(session, session->local_slot)) {
                    if (Session_IsLinked(session)) {
                        u8 *record = PlayerRecords_OfPlayer(RecentSlots_Newest());
                        if (record != NULL) {
                            SceneBase_PutNameAt10(&talk->base, PlayerRecord_Player(record), 1);
                        }
                        message = GATEKEEPER2_LINE_NEWEST;
                    } else {
                        message = GATEKEEPER2_LINE_ALONE;
                    }
                } else {
                    u16 code;
                    Spawner_PeekCode(&code);
                    message = gk2_visitor_message(code);
                }
            } else if (answer == 1) {
                if (TownItemLists_AnyListA()) {
                    SceneBase_PutValue(&talk->base, TownItemLists_CountListA(), 0, 2, 0, 0);
                    message = GATEKEEPER2_LINE_ITEMS;
                } else {
                    message = GATEKEEPER2_LINE_NO_ITEMS;
                }
            }
            break;
        case GATEKEEPER2_LINE_DESIGN_ASK:
            if (answer == 0) {
                SceneCommand_SetScreenMode(gk2_command_of(talk), GATEKEEPER2_SCREEN_COPY, 0);
                SceneCommand_RequestScreen(gk2_command_of(talk), GATEKEEPER2_SCREEN);
                Gatekeeper2Talk_SetState(talk, GATEKEEPER2_TALK_COPY_DESIGN);
            }
            break;
        default:
            break;
    }
    if (message != GATEKEEPER2_NO_LINE) {
        TalkObject_SetMessage(object, &message, (const char *) (uintptr_t) data_ov004_02254794);
    }
}
CLEAN_AS(func_ov004_02225240, Gatekeeper2Talk_OnAnswer)

/* func_ov004_022253c8 (the talk scene's slot 0x14, a message ended): after message 0x1a the
 * screen of list A's items opens (task 3 once it ends), after 0x17 the design screen 9 (task
 * 2). */
void Gatekeeper2Talk_OnMessageEnded(Gatekeeper2Talk *talk)
{
    switch (gk2_shown(talk)) {
        case GATEKEEPER2_LINE_ITEMS:
            SceneCommand_SetScreenMode(gk2_command_of(talk), GATEKEEPER2_SCREEN_ITEMS, 0);
            SceneCommand_RequestScreen(gk2_command_of(talk), GATEKEEPER2_SCREEN);
            Gatekeeper2Talk_SetState(talk, GATEKEEPER2_TALK_NAME_ITEM);
            break;
        case GATEKEEPER2_LINE_SWAP:
            SceneCommand_SetScreenMode(gk2_command_of(talk), GATEKEEPER2_SCREEN_SWAP, 0);
            SceneCommand_RequestScreen(gk2_command_of(talk), GATEKEEPER2_SCREEN);
            Gatekeeper2Talk_SetState(talk, GATEKEEPER2_TALK_SWAP_DESIGN);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_022253c8, Gatekeeper2Talk_OnMessageEnded)

/* func_ov004_02225410 (the talk scene's slot 0x78, the line to say), of "sp_npc_gatekeeper2":
 * on a console linked with others that is not the host, or when a game is being started anew,
 * one of 8 to 10; else at the player's first talk with it message 0 (the record's flag 0x1b
 * then set), later one of 4 to 7. The talk scene is not used. */
void Gatekeeper2Talk_Line(Gatekeeper2Talk *talk, Gatekeeper2Line *out)
{
    (void) talk;
    u8 *record = PlayerRecords_Current();

    if (!TalkChecks_IsHostOrAlone() || StartKind_IsSet()) {
        out->message = (u8) (MainRandom_Below(3) + GATEKEEPER2_LINE_GUEST);
    } else if (!PlayerRecord_TestFlag(record, GATEKEEPER2_FLAG_MET)) {
        out->message = GATEKEEPER2_LINE_FIRST;
        PlayerRecord_SetFlag(record, GATEKEEPER2_FLAG_MET);
    } else {
        out->message = (u8) (MainRandom_Below(4) + GATEKEEPER2_LINE_AGAIN);
    }
    out->text = data_ov004_02254794;
}
CLEAN_AS(func_ov004_02225410, Gatekeeper2Talk_Line)

/* func_ov004_02225470: its talk scene reset through its vtable slot 0x08 and given its
 * owner. */
void Gatekeeper2Talk_Begin(Gatekeeper2Talk *talk, Gatekeeper2 *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + GATEKEEPER2_TALK_SLOT_08);
    ((void (*)(Gatekeeper2Talk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov004_02225470, Gatekeeper2Talk_Begin)

/* func_ov004_0222548c (the talk scene's vtable slot 0x04): its destructor, then the scene
 * freed. */
Gatekeeper2Talk *Gatekeeper2Talk_Delete(Gatekeeper2Talk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_02254888;
    SceneBase_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_0222548c, Gatekeeper2Talk_Delete)

/* func_ov004_022254ac (the talk scene's vtable slot 0x00): the scene base's destructor. */
Gatekeeper2Talk *Gatekeeper2Talk_Destroy(Gatekeeper2Talk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_02254888;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov004_022254ac, Gatekeeper2Talk_Destroy)

/* func_ov004_022254c4: the constructor: a scene base given this class's vtable. */
Gatekeeper2Talk *Gatekeeper2Talk_Construct(Gatekeeper2Talk *talk)
{
    SceneBase_Construct(&talk->base);
    *(const u8 **) (void *) talk = data_ov004_02254888;
    return talk;
}
CLEAN_AS(func_ov004_022254c4, Gatekeeper2Talk_Construct)

/* func_ov004_022254dc (state 6's update): nothing. 1. */
int Gatekeeper2_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022254dc, Gatekeeper2_UpdatePaused)

/* ---- Its states, its frame and its life */

static_assert(sizeof(Gatekeeper2Step) == 0x10, "a state's functions");

/* The parts of the special character's scene object its life and states use, by place (main's
 * scene_object.h and scene_object_members.h). */
#define GATEKEEPER2_YAW 0x8e             /* s16: where it faces */
#define GATEKEEPER2_PERSON 0xea          /* u16: its person code */
#define GATEKEEPER2_MODEL 0xec           /* LayeredModel */
#define GATEKEEPER2_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define GATEKEEPER2_FACE 0x2ac           /* SceneFace */
#define GATEKEEPER2_ANIM 0x334           /* SpeakerAnim */
#define GATEKEEPER2_MOVER 0x350          /* SceneMover */
#define GATEKEEPER2_PROBE 0x3a8
#define GATEKEEPER2_VALUE_3AA 0x3aa  /* SceneValue3aa */
#define GATEKEEPER2_LOOK 0x3b0       /* SceneLook */
#define GATEKEEPER2_TALK_STATE 0x418 /* SceneTalkState */
#define GATEKEEPER2_EFFECTS 0x420    /* ActEffects */
#define GATEKEEPER2_COLLIDER 0x49c   /* CollisionContacts */
#define GATEKEEPER2_CARRIER 0x4cc    /* FieldOwnedBody */
#define GATEKEEPER2_HELD_FLAGS 0x4e8 /* u32: the scene object's flags (2: held) */
#define GATEKEEPER2_FOOTSTEPS 0x558  /* Footsteps */
#define GATEKEEPER2_MOTION 0x564     /* SceneMotion */
#define GATEKEEPER2_HEAP 0x640       /* PoolLink */

#define GATEKEEPER2_NO_PERSON 0xfff1
#define GATEKEEPER2_HELD 2

/* Its motion's kinds (main's scene_motion_request.h). */
#define GATEKEEPER2_MOTION_TURN 3

/* Its collider's size and its standard animations. */
#define GATEKEEPER2_COLLIDER_SIZE 0x100
#define GATEKEEPER2_ANIM_FIRST 0xd8
#define GATEKEEPER2_ANIM_SECOND 0xd9

/* The scene in which it is shared with a session; elsewhere it is not shared (0x563). */
#define GATEKEEPER2_SHARED_SCENE 0xb

/* The functions of its states (filled at start-up by __sinit_ov004_0224e85c). */
extern Gatekeeper2Step data_ov004_02258190[GATEKEEPER2_STATES];
/* The addresses of its model's and texture's file names, "npc_sp/model/pla.nsbmd" and
 * "npc_sp/model/pla_tex.nsbtx". */
extern const u32 data_ov004_0225478c;
extern const u32 data_ov004_02254790;
/* The vtable of a class it derives from. */
extern const u8 data_020da088[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The town's villagers (main's villager_town.h). */
extern u8 data_021e5a2c[];

static SceneMotion *gk2_motion_of(Gatekeeper2 *keeper)
{
    return (SceneMotion *) (void *) gk2_part(keeper, GATEKEEPER2_MOTION);
}

static SceneAction *gk2_action_of(Gatekeeper2 *keeper)
{
    return (SceneAction *) (void *) gk2_part(keeper, GATEKEEPER2_ACTION);
}

/* Its talk scene's vtable slot 0x08 (SceneBase_Reset). */
static void gk2_reset_talk(Gatekeeper2Talk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + GATEKEEPER2_TALK_SLOT_08);
    ((void (*)(Gatekeeper2Talk *))(uintptr_t) code)(talk);
}

/* func_ov004_022254e0 (state 6's entry): 1. */
int Gatekeeper2_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022254e0, Gatekeeper2_EnterPaused)

/* func_ov004_022254e4 (state 5's update): once the object, ours, is owned by no system and
 * this one holds the scene, it is owned by this system and held by none, and it turns back
 * (state 3). 1. */
int Gatekeeper2_UpdateOther(Gatekeeper2 *keeper)
{
    if (SceneShare_IsOurs(keeper->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(keeper->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            gk2_set_slots(keeper, gk2_local_slot(), SCENE_SHARE_NO_SLOT);
            Gatekeeper2_SetState(keeper, GATEKEEPER2_TURN_BACK);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_022254e4, Gatekeeper2_UpdateOther)

/* func_ov004_0222553c (state 5's entry): 1. */
int Gatekeeper2_EnterOther(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0222553c, Gatekeeper2_EnterOther)

/* func_ov004_02225540 (state 4's update), with the object ours: once this system owns and
 * holds it, it is set so again and it talks (state 1); else, once this system holds the scene
 * and no system holds the object, it is owned by this system and held by none, and it
 * stands. 1. */
int Gatekeeper2_UpdateAwait(Gatekeeper2 *keeper)
{
    if (SceneShare_IsOurs(keeper->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(keeper->base, &owner, &holder) && owner == gk2_local_slot() && owner == holder) {
            gk2_set_slots(keeper, gk2_local_slot(), gk2_local_slot());
            Gatekeeper2_SetState(keeper, GATEKEEPER2_TALK);
        } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
            gk2_set_slots(keeper, gk2_local_slot(), SCENE_SHARE_NO_SLOT);
            Gatekeeper2_SetState(keeper, GATEKEEPER2_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02225540, Gatekeeper2_UpdateAwait)

/* func_ov004_022255bc (state 4's entry): 1. */
int Gatekeeper2_EnterAwait(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022255bc, Gatekeeper2_EnterAwait)

/* func_ov004_022255c0 (state 3's update): once its turn is done, it stands. 1. */
int Gatekeeper2_UpdateTurnBack(Gatekeeper2 *keeper)
{
    if (SceneMotion_Kind(gk2_motion_of(keeper)) == GATEKEEPER2_MOTION_TURN && SceneMotion_IsDone(gk2_motion_of(keeper))) {
        Gatekeeper2_SetState(keeper, GATEKEEPER2_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov004_022255c0, Gatekeeper2_UpdateTurnBack)

/* func_ov004_022255f0 (state 3's entry): it turns (priority 1) to the angle it faced at its
 * start. 1. */
int Gatekeeper2_EnterTurnBack(Gatekeeper2 *keeper)
{
    SceneMotion_Request(gk2_motion_of(keeper), GATEKEEPER2_MOTION_TURN, 1, 0, 0, 0, keeper->home_yaw, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_022255f0, Gatekeeper2_EnterTurnBack)

/* func_ov004_0222562c (state 2's update): nothing. 1. */
int Gatekeeper2_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0222562c, Gatekeeper2_UpdateTalked)

/* func_ov004_02225630 (state 2's entry): 1. */
int Gatekeeper2_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02225630, Gatekeeper2_EnterTalked)

/* func_ov004_02225634 (state 1's update): once its action is idle, the object's event ends and
 * state 2 follows. 1.
 * QUIRK: the action is asked twice whether it is busy. */
int Gatekeeper2_UpdateTalk(Gatekeeper2 *keeper)
{
    if (SceneAction_IsBusy(gk2_action_of(keeper))) {
        return 1;
    }
    if (!SceneAction_IsBusy(gk2_action_of(keeper))) {
        EventQueue_FinishObjectEvent(keeper);
        Gatekeeper2_SetState(keeper, GATEKEEPER2_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov004_02225634, Gatekeeper2_UpdateTalk)

/* func_ov004_02225670 (state 1's entry): its talk scene is reset (vtable slot 0x08) and given
 * this console's player's object as its partner; it turns to the partner (none: angle 0) and
 * talks. 1. */
int Gatekeeper2_EnterTalk(Gatekeeper2 *keeper)
{
    gk2_reset_talk(&keeper->talk);
    SceneBase_SetMotionArg(&keeper->talk.base, SceneObject_ActorObject(keeper->base, GATEKEEPER2_PLAYER_ACTOR));
    int partner = SceneBase_MotionArg(&keeper->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(keeper->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(gk2_action_of(keeper), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov004_02225670, Gatekeeper2_EnterTalk)

/* func_ov004_022256c4 (state 0's update): nothing. 1. */
int Gatekeeper2_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022256c4, Gatekeeper2_UpdateStand)

/* func_ov004_022256c8 (state 0's entry): it stands (priority 1). 1. */
int Gatekeeper2_EnterStand(Gatekeeper2 *keeper)
{
    SceneMotion_RequestStand(gk2_motion_of(keeper), 1, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov004_022256c8, Gatekeeper2_EnterStand)

/* func_ov004_022256ec: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 6 (the table is not bounded). */
void Gatekeeper2_SetState(Gatekeeper2 *keeper, int state)
{
    const Gatekeeper2Step *step = &data_ov004_02258190[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, keeper);
    }
    if (taken != 0) {
        keeper->state = state;
    }
}
CLEAN_AS(func_ov004_022256ec, Gatekeeper2_SetState)

/* func_ov004_02225730 (vtable slot 0x68, each frame): its state's update when it has one (its
 * answer), else 0.
 * REQUIRES: its state is 0 to 6. */
int Gatekeeper2_Update(Gatekeeper2 *keeper)
{
    const Gatekeeper2Step *step = &data_ov004_02258190[(u32) keeper->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, keeper);
}
CLEAN_AS(func_ov004_02225730, Gatekeeper2_Update)

/* func_ov004_0222577c (vtable slot 0x70): the address of its model's file name,
 * "npc_sp/model/pla.nsbmd". */
unsigned int Gatekeeper2_ModelName(void)
{
    return data_ov004_0225478c;
}
CLEAN_AS(func_ov004_0222577c, Gatekeeper2_ModelName)

/* func_ov004_02225788 (vtable slot 0x6c): the address of its texture's file name,
 * "npc_sp/model/pla_tex.nsbtx". */
unsigned int Gatekeeper2_TextureName(void)
{
    return data_ov004_02254790;
}
CLEAN_AS(func_ov004_02225788, Gatekeeper2_TextureName)

/* func_ov004_02225794 (vtable slot 0x0c): when the special character may leave and this
 * console's slot is taken in a session that is not linked, the town's plan of a villager to
 * move away is cleared (when a villager has one). Whether it may leave. */
int Gatekeeper2_Leave(Gatekeeper2 *keeper)
{
    if (SpecialSceneObject_Leave(keeper) == 0) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) && !Session_IsLinked(session)) {
        VillagerTown *town = (VillagerTown *) (void *) data_021e5a2c;
        if (VillagerMove_VillagerIndex(town) != -1) {
            VillagerMoveRecord_Clear(VillagerMove_Record(town));
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02225794, Gatekeeper2_Leave)

/* func_ov004_022257e8 (vtable slot 0x00, its start): unless the special character refuses to
 * start, it notes the angle it faces and is held (flag 2 at 0x4e8). Linked in scene 0xb it
 * stands when the object is ours, else awaits the session (state 4); otherwise it stands.
 * Whether it started. */
int Gatekeeper2_Start(Gatekeeper2 *keeper)
{
    if (SpecialSceneObject_Start(keeper) == 0) {
        return 0;
    }
    keeper->home_yaw = *(const s16 *) (const void *) gk2_part(keeper, GATEKEEPER2_YAW);
    *(u32 *) (void *) gk2_part(keeper, GATEKEEPER2_HELD_FLAGS) |= GATEKEEPER2_HELD;
    if (Session_IsLinked(data_020ccf94) && SceneQuery_Current() == GATEKEEPER2_SHARED_SCENE) {
        if (SceneShare_IsOurs(keeper->base)) {
            Gatekeeper2_SetState(keeper, GATEKEEPER2_STAND);
        } else {
            Gatekeeper2_SetState(keeper, GATEKEEPER2_AWAIT);
        }
    } else {
        Gatekeeper2_SetState(keeper, GATEKEEPER2_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov004_022257e8, Gatekeeper2_Start)

/* func_ov004_0222585c (vtable slot 0x04, its set-up): unless the special character refuses,
 * its talk scene becomes its scene and gets it as its owner; its collider's size and its
 * standard animations (second 0xd9, first 0xd8) are set, and outside scene 0xb it is not
 * shared with a session. Whether it was set up. */
int Gatekeeper2_Init(Gatekeeper2 *keeper)
{
    if (SpecialSceneObject_Init(keeper) == 0) {
        return 0;
    }
    SceneObject_SetScene(keeper->base, &keeper->talk.base);
    Gatekeeper2Talk_Begin(&keeper->talk, keeper);
    SceneObject_SetColliderSize(keeper->base, GATEKEEPER2_COLLIDER_SIZE);
    SceneStandardAnims *anims = (SceneStandardAnims *) (void *) gk2_part(keeper, GATEKEEPER2_STANDARD_ANIMS);
    SceneStandardAnims_SetSecond(anims, GATEKEEPER2_ANIM_SECOND);
    SceneStandardAnims_SetFirst(anims, GATEKEEPER2_ANIM_FIRST);
    if (SceneQuery_Current() != GATEKEEPER2_SHARED_SCENE) {
        *gk2_part(keeper, GATEKEEPER2_LOCAL) = 1;
    }
    return 1;
}
CLEAN_AS(func_ov004_0222585c, Gatekeeper2_Init)

/* func_ov004_022258c4: a zeroed block of 0x714 bytes from the auxiliary heap, constructed: the
 * scene object base, the class 0x020d8c64's vtable and members in place order (no person yet,
 * 0xfff1), the class 0x020da088's vtable and heap link, then the class's vtable and its talk
 * scene. Null when there is no room. */
Gatekeeper2 *Gatekeeper2_Create(void)
{
    Gatekeeper2 *keeper = (Gatekeeper2 *) Heap_AllocAuxZeroed(sizeof(Gatekeeper2));
    if (keeper == NULL) {
        return NULL;
    }
    u8 *object = keeper->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) gk2_part(keeper, GATEKEEPER2_PERSON) = GATEKEEPER2_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) gk2_part(keeper, GATEKEEPER2_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) gk2_part(keeper, GATEKEEPER2_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) gk2_part(keeper, GATEKEEPER2_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) gk2_part(keeper, GATEKEEPER2_ANIM));
    SceneMover_Construct((SceneMover *) (void *) gk2_part(keeper, GATEKEEPER2_MOVER));
    SceneProbe_Construct(gk2_part(keeper, GATEKEEPER2_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) gk2_part(keeper, GATEKEEPER2_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) gk2_part(keeper, GATEKEEPER2_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) gk2_part(keeper, GATEKEEPER2_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) gk2_part(keeper, GATEKEEPER2_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) gk2_part(keeper, GATEKEEPER2_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) gk2_part(keeper, GATEKEEPER2_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) gk2_part(keeper, GATEKEEPER2_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) gk2_part(keeper, GATEKEEPER2_FOOTSTEPS));
    SceneMotion_Construct(gk2_motion_of(keeper));
    SceneAction_Construct(gk2_action_of(keeper));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) gk2_part(keeper, GATEKEEPER2_HEAP));
    *(const u8 **) (void *) object = data_ov004_02254918;
    Gatekeeper2Talk_Construct(&keeper->talk);
    return keeper;
}
CLEAN_AS(func_ov004_022258c4, Gatekeeper2_Create)
