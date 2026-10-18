/* The cafe's guest and its talk scene (cafe_guest.h). */
#include "cafe_guest.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/music_beat.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/calendar.h"
#include "main/camera_modes.h"
#include "main/current_pockets.h"
#include "main/date_time.h"
#include "main/day_plan.h"
#include "main/event_queue.h"
#include "main/game_variables.h"
#include "main/group_params.h"
#include "main/item_lists.h"
#include "main/main_random.h"
#include "main/music_queue.h"
#include "main/name_texts.h"
#include "main/nook_store.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_base.h"
#include "main/scene_lights.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/special_scene_object.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_start_day.h"
#include "ov004/cafe_props.h"
#include "ov004/member_pointer.h"
#include "ov004/music_show_overlay.h"
#include "ov004/room_camera.h"
#include "ov004/room_player_actor.h"

static_assert(sizeof(SceneCommandScene) == 0xb0, "scene command scene");
static_assert(sizeof(CafeGuestShow) == 0x14, "show");
static_assert(offsetof(CafeGuestScene, phase) == 0xb0, "phase");
static_assert(offsetof(CafeGuestScene, owner) == 0xb4, "owner");
static_assert(offsetof(CafeGuestScene, step) == 0xb8, "step");
static_assert(offsetof(CafeGuestScene, show) == 0xbc, "show");
static_assert(offsetof(CafeGuestScene, show_started) == 0xd0, "show started");
static_assert(sizeof(CafeGuestScene) == 0xd4, "scene");
static_assert(offsetof(CafeGuest, flags) == 0x4e8, "flags");
static_assert(offsetof(CafeGuest, song) == 0x652, "song");
static_assert(offsetof(CafeGuest, music) == 0x654, "music");
static_assert(offsetof(CafeGuest, state) == 0x658, "state");
static_assert(offsetof(CafeGuest, scene) == 0x65c, "scene");
static_assert(offsetof(CafeGuest, kind) == 0x730, "kind");
static_assert(offsetof(CafeGuest, typed_name) == 0x734, "typed name");
static_assert(offsetof(CafeGuest, timer) == 0x748, "timer");
static_assert(offsetof(CafeGuest, agreed) == 0x74a, "agreed");
static_assert(offsetof(CafeGuest, no_such_song) == 0x74b, "no such song");
static_assert(offsetof(CafeGuest, names_song) == 0x74c, "names song");
static_assert(sizeof(CafeGuest) == 0x750, "the size CafeGuest_Create allocates");

/* A step of the scene (data_ov068_02277d70). */
typedef struct CafeGuestStep {
    MemberPointer run;
    u8 each_frame; /* runs each frame while the talk's link is open, else once it closes */
    u8 unk_09[3];
} CafeGuestStep;

/* A state's start and update (data_ov068_02278840). */
typedef struct CafeGuestStateFns {
    MemberPointer start;
    MemberPointer update;
} CafeGuestStateFns;

/* A row of the tables of message handlers: the message and its handler (a function-local
 * static whose messages are in the overlay's data and whose handlers are copied in once). */
typedef struct CafeGuestHandler {
    u32 message;
    MemberPointer handler;
} CafeGuestHandler;

static_assert(sizeof(CafeGuestStep) == 0xc, "step row");
static_assert(sizeof(CafeGuestStateFns) == 0x10, "state row");
static_assert(sizeof(CafeGuestHandler) == 0xc, "handler row");

/* The vtables of the guest and of its scene. */
extern const u8 data_ov068_02277e50[];
extern const u8 data_ov068_02277dc0[];
/* The scene's steps and the guest's states. */
extern CafeGuestStep data_ov068_02277d70[CAFE_GUEST_STEPS];
extern CafeGuestStateFns data_ov068_02278840[CAFE_GUEST_STATES];
/* By kind: the message file, the person code, the model's and the texture's file names. */
extern const char *const data_ov068_02277ca4[CAFE_GUEST_KINDS];
extern const u16 data_ov068_022767ec[CAFE_GUEST_KINDS];
extern const char *const data_ov068_02277cc8[CAFE_GUEST_KINDS];
extern const char *const data_ov068_02277d10[CAFE_GUEST_KINDS];
/* The message the talk starts with in each phase after the first (9 and 6). */
extern const u8 data_ov068_022767e8[4];
/* The faces of the show's track kinds ("m.0" to "m.5"), and "m.0" for none. */
extern const char *const data_ov068_02277b94[6];
extern const char data_ov068_022779a8[];
/* The answers' handlers (messages 1, 2, 3, 5 and 0xe) and their constants. */
#define CAFE_GUEST_ANSWER_ROWS 5
extern u32 data_ov068_02278838;
extern CafeGuestHandler data_ov068_02277d34[CAFE_GUEST_ANSWER_ROWS];
extern const MemberPointer data_ov068_02277a1c, data_ov068_02277a44, data_ov068_02277a4c, data_ov068_022779c4,
    data_ov068_022779dc;
/* The handlers of the end of messages 7, 6 and 9, and their constants. */
#define CAFE_GUEST_ENDED_ROWS 3
extern u32 data_ov068_0227883c;
extern CafeGuestHandler data_ov068_02277cec[CAFE_GUEST_ENDED_ROWS];
extern const MemberPointer data_ov068_022779fc, data_ov068_02277a04, data_ov068_02277a6c;

/* The word motion requests carry, the steps of the looks, the range of the looks and the point
 * they are given. */
extern u16 data_020c80f8;
extern s16 data_020c80f4;
extern s16 data_020c80ec;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The session, the day the town was started, the day's plan and Nook's store. */
extern NetSession *data_020ccf94;
extern TownStartDay data_021f3b85;
extern u8 data_021ebcd3;
extern NookStore data_021f395c;
/* The vtable of the class 0x020da088 (special_scene_object.h). */
extern const u8 data_020da088[];

/* Of the model's resource (a NitroSystem routine). */
extern void func_021074dc(void *model_resource, int value);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The parts of the guest read here. */
#define GUEST_MODEL 0xec
#define GUEST_STANDARD_ANIMS 0x2a0
#define GUEST_FACE 0x2ac
#define GUEST_ANIM 0x334
#define GUEST_MOVER 0x350
#define GUEST_PROBE 0x3a8
#define GUEST_VALUE_3AA 0x3aa
#define GUEST_LOOK 0x3b0
#define GUEST_TALK_STATE 0x418
#define GUEST_EFFECTS 0x420
#define GUEST_COLLIDER 0x49c
#define GUEST_CARRIER 0x4cc
#define GUEST_SHADOW 0x511 /* u8: its shadow is drawn (scene_object.c) */
#define GUEST_EMITTER 0x514
#define GUEST_FOOTSTEPS 0x558
#define GUEST_MOTION 0x564
#define GUEST_ACTION 0x618
#define GUEST_HEAP 0x640
#define GUEST_PERSON 0xea
#define GUEST_WALK_ANGLE 0x94
#define GUEST_NO_PERSON 0xfff1
#define GUEST_HELD 2
#define GUEST_PLAYER 4
#define GUEST_SCENE_SLOT_RESET_INDEX 2 /* the talk scene's vtable slot 0x08 */

/* The songs: 70 items from 0x1323; each song's music is 0x63 plus its number. */
#define CAFE_GUEST_SONG_FIRST 0x1323
#define CAFE_GUEST_SONG_LAST 0x1368
#define CAFE_GUEST_SONGS 0x46
#define CAFE_GUEST_SONG_STYLE 0xa
#define CAFE_GUEST_SONG_MUSIC 0x63
/* The musics played when the name matched no song: 0xa9 plus 0-3. */
#define CAFE_GUEST_OTHER_MUSIC 0xa9
#define CAFE_GUEST_OTHER_MUSIC_VARIABLE 0x4e
#define CAFE_GUEST_OTHER_MUSICS 4

/* The items of the trade after message 0xe (and the hour's talk). */
#define CAFE_GUEST_ITEM_TAKEN 0x3530
#define CAFE_GUEST_ITEM_GIVEN 0x4a34

/* The messages of kind 7. */
#define CAFE_GUEST_MESSAGE_AGREED 0
#define CAFE_GUEST_MESSAGE_FIRST 1
#define CAFE_GUEST_MESSAGE_TODAY 2
#define CAFE_GUEST_MESSAGE_AGAIN 3
#define CAFE_GUEST_MESSAGE_NAME_SCREEN 7
#define CAFE_GUEST_MESSAGE_TYPED 8
#define CAFE_GUEST_MESSAGE_NO_SONG 0xb
#define CAFE_GUEST_MESSAGE_GIVEN 0xc
#define CAFE_GUEST_MESSAGE_NOT_GIVEN 0xd
#define CAFE_GUEST_MESSAGE_TRADE 0xe
#define CAFE_GUEST_MESSAGE_HEARD 0x12
#define CAFE_GUEST_MESSAGE_EARLY 0x13
#define CAFE_GUEST_EARLY_HOUR 19 /* before the show */
#define CAFE_GUEST_FLAG_MET 7    /* the player's record flag of the first talk */
#define CAFE_GUEST_DAILY_TALKED 0xc
#define CAFE_GUEST_DAILY_HEARD 0xd /* a song was given today */
#define CAFE_GUEST_DAILY_KIND 0x21 /* plus the kind: the other kinds' talk today */
#define CAFE_GUEST_VALUE_KIND 7    /* the talk's value kind of the names put in */

/* The steps. */
#define CAFE_GUEST_STEP_NONE 0
#define CAFE_GUEST_STEP_NAME 1
#define CAFE_GUEST_STEP_MUSIC 2
#define CAFE_GUEST_STEP_SHOW 3
#define CAFE_GUEST_STEP_GIVE 4
#define CAFE_GUEST_STEP_LOOK 5
#define CAFE_GUEST_MUSIC_FRAMES 0x2d
#define CAFE_GUEST_SHOW_END_FRAMES 0x14
#define CAFE_GUEST_LIGHTS_FRAMES 0x1e

/* The name screen: screen mode 13, through the command's screen of group 9. */
#define CAFE_GUEST_NAME_SCREEN_MODE 13
#define CAFE_GUEST_NAME_SCREEN SCENE_COMMAND_SCREEN_MODE

/* The music's queue. */
#define CAFE_GUEST_MUSIC_PRIORITY 0xf
#define CAFE_GUEST_MUSIC_0C 0x7f
#define CAFE_GUEST_TALK_PRIORITY 0x10
#define CAFE_GUEST_TALK_VALUE 0xf

/* The looks: pitch 0xf3e8 looks up, yaw 0x1000 ahead. */
#define CAFE_GUEST_LOOK_UP 0xf3e8
#define CAFE_GUEST_LOOK_AHEAD 0x1000
#define CAFE_GUEST_LOOK_STEP 0x276
#define CAFE_GUEST_SHOW_PITCH_STEP 0x100
#define CAFE_GUEST_SHOW_YAW_STEP 0x200

/* The animations (scene_motion_request.h) and the player's states. */
#define CAFE_GUEST_ANIM_TALK 0x102
#define CAFE_GUEST_ANIM_SHOW_3 0x103
#define CAFE_GUEST_ANIM_SHOW_4 0x104
#define CAFE_GUEST_ANIM_WAIT 0x105
#define CAFE_GUEST_ANIM_KIND_3 0x142
#define CAFE_GUEST_SHOW_FIRST_WORD 0x28
#define CAFE_GUEST_PLAYER_AT_SEAT 37
#define CAFE_GUEST_PLAYER_LISTENING 0x28
#define CAFE_GUEST_SEAT_X 9
#define CAFE_GUEST_SEAT_Z 13

/* Kind 7's position, reach and the actor it brings. */
#define CAFE_GUEST_MUSIC_X 0xf000
#define CAFE_GUEST_MUSIC_Z 0x13000
#define CAFE_GUEST_MUSIC_REACH 0x5000
#define CAFE_GUEST_MUSIC_ACTOR 0x10
#define CAFE_GUEST_STANDARD_MUSIC 0x102
#define CAFE_GUEST_STANDARD 0x1e

static u8 *guest_at(CafeGuest *self, u32 offset)
{
    return (u8 *) self + offset;
}

static SceneLook *guest_look(CafeGuest *self)
{
    return (SceneLook *) (void *) guest_at(self, GUEST_LOOK);
}

static SceneMotion *guest_motion(CafeGuest *self)
{
    return (SceneMotion *) (void *) guest_at(self, GUEST_MOTION);
}

static SceneAction *guest_action(CafeGuest *self)
{
    return (SceneAction *) (void *) guest_at(self, GUEST_ACTION);
}

static SceneFace *guest_face(CafeGuest *self)
{
    return (SceneFace *) (void *) guest_at(self, GUEST_FACE);
}

static LayeredModel *guest_model(CafeGuest *self)
{
    return (LayeredModel *) (void *) guest_at(self, GUEST_MODEL);
}

static SceneStandardAnims *guest_standard_anims(CafeGuest *self)
{
    return (SceneStandardAnims *) (void *) guest_at(self, GUEST_STANDARD_ANIMS);
}

static SceneObjectBase *guest_base(CafeGuest *self)
{
    return (SceneObjectBase *) (void *) self;
}

static SceneBase *scene_base(CafeGuestScene *scene)
{
    return (SceneBase *) (void *) &scene->base;
}

static TalkObject *scene_talk(CafeGuestScene *scene)
{
    return (TalkObject *) (void *) scene->base.talk;
}

static u8 scene_message(const CafeGuestScene *scene)
{
    return ((const MessageReceiver *) (const void *) scene)->message;
}

/* The talk scene's vtable slot 0x08 (its reset), called virtually. */
static void reset_scene(CafeGuestScene *scene)
{
    const u32 *vtable = *(const u32 *const *) (const void *) scene;
    ((void (*)(CafeGuestScene *))(uintptr_t) vtable[GUEST_SCENE_SLOT_RESET_INDEX])(scene);
}

/* A handler taking the scene and an answer, called through its member pointer. */
static void call_with_answer(const MemberPointer *member, CafeGuestScene *scene, int answer)
{
    void *self = MemberPointer_Object(member, scene);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(member, self))(self, answer);
}

/* The handlers of a table copied in from their constants, once. */
static void init_handlers(u32 *guard, CafeGuestHandler *rows, const MemberPointer *const *constants, int count)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        for (int i = 0; i < count; i++) {
            rows[i].handler = *constants[i];
        }
        *guard = flags | 1;
    }
}

/* The name the player typed put into the talk's slot 0, as an 8-bit text. */
static void put_typed_name(CafeGuestScene *scene, CafeGuest *owner)
{
    NameText text;
    NameWideText wide;
    NameText_Construct(&text);
    NameWideText_Construct(&wide);
    TextBase_SetWide(&wide, owner->typed_name, CAFE_GUEST_NAME_UNITS);
    TextBase_WideToBytes((TextBase *) (void *) &text, (WideTextBase *) (void *) &wide, 0, 0);
    TalkObject_SetValue(scene_talk(scene), 0, (TextBase *) (void *) &text, CAFE_GUEST_VALUE_KIND);
    NameWideText_Destruct(&wide);
    NameText_Destruct(&text);
}

/* The song's name put into the talk's slot `slot`. */
static void put_song_name(CafeGuestScene *scene, int slot)
{
    u16 song = scene->owner->song;
    SceneBase_PutItemName(scene_base(scene), (int) (uintptr_t) &song, slot, CAFE_GUEST_VALUE_KIND);
}

/* Whether the player carries the item CAFE_GUEST_ITEM_TAKEN. */
static int player_has_trade_item(void)
{
    u16 item = CAFE_GUEST_ITEM_TAKEN;
    return CurrentPockets_FindItem(&item) != -1;
}

/* func_ov068_02273920 (slot 0x40): its scene's destructor, then the special character's
 * (SpecialSceneObject_DestructBody); the object. */
CafeGuest *CafeGuest_Destruct(CafeGuest *self)
{
    *(const u8 **) (void *) self = data_ov068_02277e50;
    CafeGuestScene_Destruct(&self->scene);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov068_02273920, CafeGuest_Destruct)

/* func_ov068_02273948 (slot 0x44): the same, then the object freed (Heap_FreeAux). */
CafeGuest *CafeGuest_DestructDelete(CafeGuest *self)
{
    *(const u8 **) (void *) self = data_ov068_02277e50;
    CafeGuestScene_Destruct(&self->scene);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov068_02273948, CafeGuest_DestructDelete)

/* func_ov068_02273974 (overlay 4's cafe asks it): its kind. */
int CafeGuest_Kind(CafeGuest *self)
{
    return self->kind;
}
CLEAN_AS(func_ov068_02273974, CafeGuest_Kind)

/* func_ov068_02273980: a song drawn (ItemLists_DrawRange) from those the current player's item
 * record does not have; when that gives none, from all of them. */
unsigned short CafeGuest_DrawSong(void)
{
    u16 song;
    u16 again;
    u8 *record = PlayerRecords_Current();
    ItemLists_DrawRange(&song, CAFE_GUEST_SONG_FIRST, CAFE_GUEST_SONGS, NULL, 0, record, 0, CAFE_GUEST_SONG_STYLE, NULL, 1);
    if (song >= CAFE_GUEST_SONG_FIRST && song <= CAFE_GUEST_SONG_LAST) {
        return song;
    }
    ItemLists_DrawRange(&again, CAFE_GUEST_SONG_FIRST, CAFE_GUEST_SONGS, NULL, 0, NULL, 1, CAFE_GUEST_SONG_STYLE, NULL, 1);
    return again;
}
CLEAN_AS(func_ov068_02273980, CafeGuest_DrawSong)

/* func_ov068_022739f4 (kind 7's part of CAFE_GUEST_WAIT): once the player has agreed, when the
 * player is in state 37 on tile (9, 13) (its seat), an event of kind 7 is asked for. 1, or 0
 * before the player agreed.
 * QUIRK: the current player's record is asked for and not used. */
int CafeGuest_WaitForListener(CafeGuest *self)
{
    if (self->agreed == 0) {
        return 0;
    }
    (void) PlayerRecords_Current();
    const Vec3 *at = PlayerActorOps_StartPosition(GUEST_PLAYER);
    Position position = {at->x, at->y, at->z};
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, &position);
    if (PlayerActorOps_InState(CAFE_GUEST_PLAYER_AT_SEAT, GUEST_PLAYER) != 0 && x == CAFE_GUEST_SEAT_X &&
        z == CAFE_GUEST_SEAT_Z) {
        EventQueue_RequestKind7(self, 0);
    }
    return 1;
}
CLEAN_AS(func_ov068_022739f4, CafeGuest_WaitForListener)

/* The talk scene reset (its slot 0x08) and given the player's object as its motion argument. */
static void restart_scene(CafeGuest *self)
{
    reset_scene(&self->scene);
    SceneBase_SetMotionArg(scene_base(&self->scene), SceneObject_ActorObject((u8 *) self, GUEST_PLAYER));
}

/* func_ov068_02273a5c (slot 0x4c): told of an event: 0 restarts the talk (kind 7 in its first
 * phase) and gives CAFE_GUEST_TALK; 1 restarts it in the phase of the song (named or any) and
 * gives CAFE_GUEST_SEATED; 8 (ended) gives CAFE_GUEST_WAIT. */
void CafeGuest_OnEvent(CafeGuest *self, int code)
{
    switch (code) {
        case 0:
            restart_scene(self);
            if (self->kind == CAFE_GUEST_KIND_MUSIC) {
                CafeGuestScene_SetPhase(&self->scene, CAFE_GUEST_PHASE_ASK);
            }
            CafeGuest_SetState(self, CAFE_GUEST_TALK);
            break;
        case 1:
            restart_scene(self);
            CafeGuestScene_SetPhase(&self->scene, self->names_song != 0 ? CAFE_GUEST_PHASE_NAMED : CAFE_GUEST_PHASE_ANY_SONG);
            CafeGuest_SetState(self, CAFE_GUEST_SEATED);
            break;
        case 8:
            CafeGuest_SetState(self, CAFE_GUEST_WAIT);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_02273a5c, CafeGuest_OnEvent)

/* func_ov068_02273b04 (slot 0x48): whether the player may act on it: in CAFE_GUEST_WAIT. */
int CafeGuest_MayAct(CafeGuest *self)
{
    return self->state == CAFE_GUEST_WAIT;
}
CLEAN_AS(func_ov068_02273b04, CafeGuest_MayAct)

/* func_ov068_02273b18 (step 5): once the timer runs out, the guest looks ahead, the talk opens
 * again, and the scene goes back to step 0. */
void CafeGuestScene_LookAhead(CafeGuestScene *scene)
{
    CafeGuest *owner = scene->owner;
    if (Countdown_Tick16(&owner->timer) != 0) {
        return;
    }
    SceneLook_RequestAngles(guest_look(owner), 0, 0, CAFE_GUEST_LOOK_AHEAD, CAFE_GUEST_LOOK_STEP, CAFE_GUEST_LOOK_STEP);
    scene_talk(scene)->next_state = TALK_OBJECT_OPENING;
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_NONE);
}
CLEAN_AS(func_ov068_02273b18, CafeGuestScene_LookAhead)

/* func_ov068_02273b70 (step 4): once the timer runs out, the player agreed no more, and the
 * last message: 0xb when the name matched no song; else the song's item put in the player's
 * pockets, with message 0xc and today's bit 0xd set, or message 0xd when there was no room.
 * Then overlay 93's object is released, the music dropped, the lights changed over 30 frames,
 * and step 5 follows 30 frames later. */
void CafeGuestScene_GiveSong(CafeGuestScene *scene)
{
    CafeGuest *owner = scene->owner;
    if (Countdown_Tick16(&owner->timer) != 0) {
        return;
    }
    owner->agreed = 0;
    u8 message;
    if (owner->no_such_song != 0) {
        message = CAFE_GUEST_MESSAGE_NO_SONG;
    } else {
        u16 song = owner->song;
        if (CurrentPockets_Give(&song, 0) != 0) {
            TalkChecks_TestSetDailyBit(CAFE_GUEST_DAILY_HEARD, 1);
            message = CAFE_GUEST_MESSAGE_GIVEN;
        } else {
            message = CAFE_GUEST_MESSAGE_NOT_GIVEN;
        }
    }
    TalkObject_SetMessage(scene_talk(scene), &message, data_ov068_02277ca4[owner->kind]);
    MusicShowOverlay_Close();
    Music_DropMusic((u16) owner->music);
    owner->timer = CAFE_GUEST_LIGHTS_FRAMES;
    SceneLights_RequestOff(1, 1);
    SceneLights_RequestOn(0, CAFE_GUEST_LIGHTS_FRAMES, 0);
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_LOOK);
}
CLEAN_AS(func_ov068_02273b70, CafeGuestScene_GiveSong)

/* func_ov068_02273c7c (step 3): what changed in the music's show since the last frame (unless
 * a pause goes on, var2 1 then and now) is followed:
 * - var3: 2 switches overlay 93's object one way (func_ov004_02246e88, func_ov004_0224692c), 0
 *   or 1 the other (func_ov004_02246e98);
 * - the track kind: the face "m.0" to "m.5" (or "m.0" for none);
 * - var0 or the type: the guest looks ahead (var0 1) or up, and types 3 and 4 play animations
 *   0x103 and 0x104 (the first one with the word 0x28);
 * - with type 3 or 4 (each frame), the model's base animation set to its start and stepped by
 *   the show's frame_a;
 * - var2: 0 ends a pause (overlay 93's object restarted), 1 starts one (face "m.0" and off, the
 *   guest stands).
 * Then what the show is now is kept, and at its end (func_ov004_02246900) step 4 follows 20
 * frames later.
 * BUG: with no entry in the sound system, its data is copied from address 0. */
void CafeGuestScene_FollowShow(CafeGuestScene *scene)
{
    const CafeGuestShow *now = (const CafeGuestShow *) (const void *) SoundSys_FirstEntryData();
    CafeGuestShow *seen = &scene->show;
    CafeGuest *owner = scene->owner;
    MusicShowOverlay_Update();
    if (now != NULL && !(now->var2 == 1 && seen->var2 == 1)) {
        if (now->var3 != seen->var3) {
            if (now->var3 == 2) {
                RoomCamera_ShowViews();
                MusicShowOverlay_SetDisplay();
            } else if ((u8) now->var3 <= 1) {
                RoomCamera_ShowNextSpot();
            }
        }
        if (now->track_kind != seen->track_kind) {
            if (now->track_kind == -1) {
                SceneFace_MapNamed(guest_face(owner), (void *) (uintptr_t) data_ov068_022779a8);
            } else {
                /* REQUIRES: the track kind is -1 to 5 (MusicBeatShow_FindTrack) */
                SceneFace_MapNamed(guest_face(owner), (void *) (uintptr_t) data_ov068_02277b94[now->track_kind]);
            }
        }
        if (now->var0 != seen->var0 || now->type != seen->type) {
            if (now->var0 == 1) {
                SceneLook_RequestAngles(guest_look(owner), 0, 0, 0, CAFE_GUEST_SHOW_PITCH_STEP, CAFE_GUEST_SHOW_YAW_STEP);
            } else {
                SceneLook_RequestAngles(guest_look(owner), 0, CAFE_GUEST_LOOK_UP, 0, CAFE_GUEST_SHOW_PITCH_STEP,
                                        CAFE_GUEST_SHOW_YAW_STEP);
            }
            u16 word = data_020c80f8;
            if (scene->show_started == 0) {
                word = CAFE_GUEST_SHOW_FIRST_WORD;
                scene->show_started = 1;
            }
            if (now->type == 3) {
                SceneMotion_RequestAnimation(guest_motion(owner), 2, CAFE_GUEST_ANIM_SHOW_3, 0, word, 0);
            } else if (now->type == 4) {
                SceneMotion_RequestAnimation(guest_motion(owner), 2, CAFE_GUEST_ANIM_SHOW_4, 0, word, 0);
            }
        }
        if ((u8) (now->type - 3) <= 1) {
            LayeredModel *model = guest_model(owner);
            model->base_frames.frame = 0;
            model->base_frames.speed = now->frame_a;
            LayeredModel_UpdateB(model);
            model->base_frames.speed = 0;
        }
        if (now->var2 != seen->var2) {
            if (now->var2 == 0) {
                MusicShowOverlay_Update();
                MusicShowOverlay_Restart(0);
                MusicShowOverlay_Upload();
            }
            if (now->var2 == 1) {
                SceneFace_MapNamed(guest_face(owner), (void *) (uintptr_t) data_ov068_022779a8);
                SceneFace_DisableNamed(guest_face(owner));
                SceneMotion_RequestStand(guest_motion(owner), 2, CAFE_GUEST_SHOW_FIRST_WORD);
            }
        }
    }
    MusicShowOverlay_Upload();
    MI_CpuCopy8(now, seen, sizeof(CafeGuestShow));
    if (MusicShowOverlay_HasEnded() != 0) {
        owner->timer = CAFE_GUEST_SHOW_END_FRAMES;
        CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_GIVE);
    }
}
CLEAN_AS(func_ov068_02273c7c, CafeGuestScene_FollowShow)

/* func_ov068_02273eb0 (step 2): once the talk is gone: at 45 frames left the lights change
 * and the guest looks up; once the timer runs out overlay 4's func_ov004_02246ea8 runs, the
 * music is picked (when the name matched no song one of 0xa9-0xac: the game's variable 0x4e
 * less 1, kept to 0-3, when it is set, else at random of the first three; else 0x63 plus the
 * song's number) and added, the show starts again, overlay 93's object is made, and step 3
 * follows.
 * QUIRK: a song out of 0x1323-0x1368 gives music 0x62. */
void CafeGuestScene_StartMusic(CafeGuestScene *scene)
{
    CafeGuest *owner = scene->owner;
    if (TalkObject_Get(0)->state != TALK_OBJECT_GONE) {
        return;
    }
    if (owner->timer == CAFE_GUEST_MUSIC_FRAMES) {
        SceneLights_RequestOff(0, CAFE_GUEST_LIGHTS_FRAMES);
        SceneLights_RequestOn(1, 1, 0);
        SceneLook_RequestAngles(guest_look(owner), 0, CAFE_GUEST_LOOK_UP, 0, CAFE_GUEST_LOOK_STEP, CAFE_GUEST_LOOK_STEP);
    }
    if (Countdown_Tick16(&owner->timer) != 0) {
        return;
    }
    RoomCamera_ShowClose();
    owner->music = 0;
    if (owner->no_such_song != 0) {
        owner->music = MainRandom_Below(3) + CAFE_GUEST_OTHER_MUSIC;
        s16 chosen = (s16) *GameVariables_Slot(0, CAFE_GUEST_OTHER_MUSIC_VARIABLE);
        if (chosen != 0) {
            int index = (s16) *GameVariables_Slot(0, CAFE_GUEST_OTHER_MUSIC_VARIABLE) - 1;
            if (index < 0) {
                index = 0;
            } else if (index > CAFE_GUEST_OTHER_MUSICS - 1) {
                index = CAFE_GUEST_OTHER_MUSICS - 1;
            }
            owner->music = (u32) index + CAFE_GUEST_OTHER_MUSIC;
        }
    } else {
        u16 song = owner->song;
        u32 number = (u32) -1;
        if (song >= CAFE_GUEST_SONG_FIRST && song <= CAFE_GUEST_SONG_LAST) {
            number = (u32) song - CAFE_GUEST_SONG_FIRST;
        }
        owner->music = number + CAFE_GUEST_SONG_MUSIC;
    }
    Music_Add(CAFE_GUEST_MUSIC_PRIORITY, (u16) owner->music, CAFE_GUEST_MUSIC_0C, 0);
    scene->show_started = 0;
    MusicShowOverlay_Open();
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_SHOW);
}
CLEAN_AS(func_ov068_02273eb0, CafeGuestScene_StartMusic)

/* func_ov068_02273ff0 (step 1, once the talk closes after the name screen): the name typed on
 * the screen (GroupParams_Text) kept and put into the talk's slot 0; when it named a song
 * (GroupParams_C4CIs1, its number GroupParams_Arg, the first song for one past the last) that
 * song is taken and its name put into slot 1; else a song is drawn and the name matched none.
 * The talk goes on with message 8. */
void CafeGuestScene_TakeName(CafeGuestScene *scene)
{
    CafeGuest *owner = scene->owner;
    NameText text;
    NameWideText wide;
    MI_CpuCopy8(GroupParams_Text(), owner->typed_name, sizeof(owner->typed_name));
    NameText_Construct(&text);
    NameWideText_Construct(&wide);
    TextBase_SetWide(&wide, owner->typed_name, CAFE_GUEST_NAME_UNITS);
    TextBase_WideToBytes((TextBase *) (void *) &text, (WideTextBase *) (void *) &wide, 0, 0);
    TalkObject_SetValue(scene_talk(scene), 0, (TextBase *) (void *) &text, CAFE_GUEST_VALUE_KIND);
    if (GroupParams_C4CIs1()) {
        owner->no_such_song = 0;
        u32 number = GroupParams_Arg();
        owner->song = number < CAFE_GUEST_SONGS ? (u16) (number + CAFE_GUEST_SONG_FIRST) : CAFE_GUEST_SONG_FIRST;
        put_song_name(scene, 1);
    } else {
        owner->no_such_song = 1;
        owner->song = CafeGuest_DrawSong();
    }
    u8 message = CAFE_GUEST_MESSAGE_TYPED;
    TalkObject_SetMessage(scene_talk(scene), &message, data_ov068_02277ca4[owner->kind]);
    NameWideText_Destruct(&wide);
    NameText_Destruct(&text);
}
CLEAN_AS(func_ov068_02273ff0, CafeGuestScene_TakeName)

/* func_ov068_022740f8 */
void CafeGuestScene_SetStep(CafeGuestScene *scene, unsigned long step)
{
    scene->step = (s32) step;
}
CLEAN_AS(func_ov068_022740f8, CafeGuestScene_SetStep)

/* func_ov068_02274100 (slot 0x84, once the talk's link has closed): a step that runs once it
 * closes, when there is one, is run, and the scene goes back to step 0. */
void CafeGuestScene_OnTalkClosed(CafeGuestScene *scene)
{
    const CafeGuestStep *step = &data_ov068_02277d70[scene->step];
    if (step->each_frame != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, scene);
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_NONE);
}
CLEAN_AS(func_ov068_02274100, CafeGuestScene_OnTalkClosed)

/* func_ov068_02274150 (slot 0x80, each frame the talk's link stays open): a step that runs
 * each frame, when there is one, is run. */
void CafeGuestScene_WhileTalkOpen(CafeGuestScene *scene)
{
    const CafeGuestStep *step = &data_ov068_02277d70[scene->step];
    if (step->each_frame == 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, scene);
}
CLEAN_AS(func_ov068_02274150, CafeGuestScene_WhileTalkOpen)

/* func_ov068_02274194 (the answer to message 5): answer 0, the player will name the song;
 * else any song: one is drawn. */
void CafeGuestScene_OnSongAnswer(CafeGuestScene *scene, int answer)
{
    CafeGuest *owner = scene->owner;
    if (answer == 0) {
        owner->names_song = 1;
    } else {
        owner->names_song = 0;
        owner->no_such_song = 0;
        owner->song = CafeGuest_DrawSong();
    }
}
CLEAN_AS(func_ov068_02274194, CafeGuestScene_OnSongAnswer)

/* func_ov068_022741e4 (the answer to message 0xe): with answer 0, the item 0x3530 the player
 * carries is taken from its slot and the item 0x4a34 put into the pockets. */
void CafeGuestScene_OnTradeAnswer(int unused, int answer)
{
    (void) unused;
    if (answer != 0) {
        return;
    }
    u16 taken = CAFE_GUEST_ITEM_TAKEN;
    int slot = CurrentPockets_FindItem(&taken);
    if (slot == -1) {
        return;
    }
    CurrentPockets_Empty(slot);
    u16 given = CAFE_GUEST_ITEM_GIVEN;
    CurrentPockets_Give(&given, 0);
}
CLEAN_AS(func_ov068_022741e4, CafeGuestScene_OnTradeAnswer)

/* func_ov068_02274224 (the answer to messages 1-3): answer 0, the player agreed to listen. */
void CafeGuestScene_OnListenAnswer(CafeGuestScene *scene, int answer)
{
    if (answer == 0) {
        scene->owner->agreed = 1;
    }
}
CLEAN_AS(func_ov068_02274224, CafeGuestScene_OnListenAnswer)

/* func_ov068_02274238: the handler of the message answered (1, 2 and 3: CafeGuestScene_
 * OnListenAnswer, 5: CafeGuestScene_OnSongAnswer, 0xe: CafeGuestScene_OnTradeAnswer; through a
 * table filled once) given the choice picked. */
void CafeGuestScene_OnAnswerKind7(CafeGuestScene *scene, int answer)
{
    static const MemberPointer *const handlers[CAFE_GUEST_ANSWER_ROWS] = {
        &data_ov068_02277a1c, &data_ov068_02277a44, &data_ov068_02277a4c, &data_ov068_022779c4, &data_ov068_022779dc,
    };
    (void) answer;
    init_handlers(&data_ov068_02278838, data_ov068_02277d34, handlers, CAFE_GUEST_ANSWER_ROWS);
    for (int i = 0; i < CAFE_GUEST_ANSWER_ROWS; i++) {
        if (data_ov068_02277d34[i].message == scene_message(scene)) {
            TalkObject *talk = scene_talk(scene);
            int picked = (int) TalkAnswers_Picked(TalkObject_Answers(talk));
            call_with_answer(&data_ov068_02277d34[i].handler, scene, picked);
        }
    }
}
CLEAN_AS(func_ov068_02274238, CafeGuestScene_OnAnswerKind7)

/* func_ov068_022742f4 (the scene's slot 0x18, the player's answer): for kind 7 only. */
void CafeGuestScene_OnAnswer(CafeGuestScene *scene, int answer)
{
    if (scene->owner->kind == CAFE_GUEST_KIND_MUSIC) {
        CafeGuestScene_OnAnswerKind7(scene, answer);
    }
}
CLEAN_AS(func_ov068_022742f4, CafeGuestScene_OnAnswer)

/* func_ov068_02274314 (after messages 6 and 9): the talk's mode cleared, and the music's step
 * follows in 45 frames. */
void CafeGuestScene_ToMusic(CafeGuestScene *scene)
{
    scene_talk(scene)->mode = 0;
    scene->owner->timer = CAFE_GUEST_MUSIC_FRAMES;
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_MUSIC);
}
CLEAN_AS(func_ov068_02274314, CafeGuestScene_ToMusic)

/* func_ov068_02274334 (after message 7): the name screen asked for, and step 1. */
void CafeGuestScene_ToNameScreen(CafeGuestScene *scene)
{
    SceneCommand_SetScreenMode(&scene->base, CAFE_GUEST_NAME_SCREEN_MODE, 0);
    SceneCommand_RequestScreen(&scene->base, CAFE_GUEST_NAME_SCREEN);
    CafeGuestScene_SetStep(scene, CAFE_GUEST_STEP_NAME);
}
CLEAN_AS(func_ov068_02274334, CafeGuestScene_ToNameScreen)

/* func_ov068_02274358: the handler of the message that ended (7: CafeGuestScene_ToNameScreen,
 * 6 and 9: CafeGuestScene_ToMusic; through a table filled once). The argument is not read. */
void CafeGuestScene_OnMessageEndedKind7(CafeGuestScene *scene, void *arg)
{
    static const MemberPointer *const handlers[CAFE_GUEST_ENDED_ROWS] = {
        &data_ov068_022779fc,
        &data_ov068_02277a04,
        &data_ov068_02277a6c,
    };
    (void) arg;
    init_handlers(&data_ov068_0227883c, data_ov068_02277cec, handlers, CAFE_GUEST_ENDED_ROWS);
    for (int i = 0; i < CAFE_GUEST_ENDED_ROWS; i++) {
        if (data_ov068_02277cec[i].message == scene_message(scene)) {
            MemberPointer_CallVoid(&data_ov068_02277cec[i].handler, scene);
        }
    }
}
CLEAN_AS(_ZN18Obj_ov068_02277dc019func_ov068_02274358EPv, CafeGuestScene_OnMessageEndedKind7)

/* func_ov068_022743ec (the scene's slot 0x14, a message ended): for kind 7 only. */
void CafeGuestScene_OnMessageEnded(CafeGuestScene *scene, void *arg)
{
    if (scene->owner->kind == CAFE_GUEST_KIND_MUSIC) {
        CafeGuestScene_OnMessageEndedKind7(scene, arg);
    }
}
CLEAN_AS(_ZN18Obj_ov068_02277dc019func_ov068_022743ecEPv, CafeGuestScene_OnMessageEnded)

/* func_ov068_0227440c: the values of messages 0xc and 0xd (the song's name in slot 1) and of
 * message 0xb (the typed name in slot 0). */
void CafeGuestScene_PutValuesKind7(CafeGuestScene *scene, int unused)
{
    (void) unused;
    switch (scene_message(scene)) {
        case CAFE_GUEST_MESSAGE_GIVEN:
        case CAFE_GUEST_MESSAGE_NOT_GIVEN:
            put_song_name(scene, 1);
            break;
        case CAFE_GUEST_MESSAGE_NO_SONG:
            put_typed_name(scene, scene->owner);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_0227440c, CafeGuestScene_PutValuesKind7)

/* func_ov068_02274490 (the scene's slot 0x10, which the talk calls with a message): for kind 7
 * only. */
void CafeGuestScene_PutValues(CafeGuestScene *scene, int unused)
{
    if (scene->owner->kind == CAFE_GUEST_KIND_MUSIC) {
        CafeGuestScene_PutValuesKind7(scene, unused);
    }
}
CLEAN_AS(func_ov068_02274490, CafeGuestScene_PutValues)

/* The first message of kind 7 in its first phase: at 19:00-19:59, 0xe when the player carries
 * the item 0x3530, else 0x13; once the player agreed, 0; when a song was given today, 0xe or
 * 0x12 the same way; the first time (the player's record flag 7, then set), 1; the first time
 * today (today's bit 0xc, then set), 2; else 3. */
static u8 first_message(CafeGuest *owner, u8 *record)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour == CAFE_GUEST_EARLY_HOUR) {
        return player_has_trade_item() ? CAFE_GUEST_MESSAGE_TRADE : CAFE_GUEST_MESSAGE_EARLY;
    }
    if (owner->agreed != 0) {
        return CAFE_GUEST_MESSAGE_AGREED;
    }
    if (TalkChecks_TestSetDailyBit(CAFE_GUEST_DAILY_HEARD, 0) != 0) {
        return player_has_trade_item() ? CAFE_GUEST_MESSAGE_TRADE : CAFE_GUEST_MESSAGE_HEARD;
    }
    if (PlayerRecord_TestFlag(record, CAFE_GUEST_FLAG_MET) == 0) {
        PlayerRecord_SetFlag(record, CAFE_GUEST_FLAG_MET);
        return CAFE_GUEST_MESSAGE_FIRST;
    }
    if (TalkChecks_TestSetDailyBit(CAFE_GUEST_DAILY_TALKED, 1) == 0) {
        return CAFE_GUEST_MESSAGE_TODAY;
    }
    return CAFE_GUEST_MESSAGE_AGAIN;
}

/* func_ov068_022744b0 (the scene's slot 0x78, the talk starting): the show seen cleared, and
 * the talk starts in the kind's message file. Kind 7: in its first phase with the message
 * first_message picks; in the others, after the typed name put into slot 0 (phase 1) or the
 * song's name into slots 1 and 2 (phase 2), with the phase's message. Another kind: a message
 * at random, 0-2 the first time today (today's bit 0x21 plus the kind, then set), else 3-7.
 * REQUIRES: the phase is 0-3. */
void CafeGuestScene_StartTalk(CafeGuestScene *scene, CafeGuestTalkStart *start)
{
    CafeGuest *owner = scene->owner;
    scene->show.type = -1;
    scene->show.track_kind = -1;
    scene->show.var0 = -1;
    scene->show.var2 = -1;
    scene->show.var3 = -1;
    u8 *record = PlayerRecords_Current();
    start->name = data_ov068_02277ca4[owner->kind];
    s32 kind = owner->kind;
    if (kind != CAFE_GUEST_KIND_MUSIC) {
        if (TalkChecks_TestSetDailyBit(kind + CAFE_GUEST_DAILY_KIND, 1) == 0) {
            start->message = (u8) MainRandom_Below(3);
        } else {
            start->message = (u8) (MainRandom_Below(5) + 3);
        }
        return;
    }
    unsigned long phase = CafeGuestScene_Phase(scene);
    if (phase == CAFE_GUEST_PHASE_ASK) {
        start->message = first_message(owner, record);
        return;
    }
    if (phase == CAFE_GUEST_PHASE_NAMED) {
        put_typed_name(scene, owner);
    } else if (phase == CAFE_GUEST_PHASE_ANY_SONG) {
        put_song_name(scene, 1);
        put_song_name(scene, 2);
    }
    start->message = data_ov068_022767e8[scene->phase];
    start->name = data_ov068_02277ca4[owner->kind];
}
CLEAN_AS(func_ov068_022744b0, CafeGuestScene_StartTalk)

/* func_ov068_022746b0 */
unsigned long CafeGuestScene_Phase(CafeGuestScene *scene)
{
    return (unsigned long) scene->phase;
}
CLEAN_AS(func_ov068_022746b0, CafeGuestScene_Phase)

/* func_ov068_022746b8 */
void CafeGuestScene_SetPhase(CafeGuestScene *scene, unsigned long phase)
{
    scene->phase = (s32) phase;
}
CLEAN_AS(func_ov068_022746b8, CafeGuestScene_SetPhase)

/* func_ov068_022746c0: the scene reset (its slot 0x08) and given its guest. */
void CafeGuestScene_Begin(CafeGuestScene *scene, CafeGuest *owner)
{
    reset_scene(scene);
    scene->owner = owner;
}
CLEAN_AS(func_ov068_022746c0, CafeGuestScene_Begin)

/* func_ov068_022746dc (the scene's slot 0x04): the destructor of main's class 0x020d9ff8, then
 * the scene freed (Heap_OperatorDeleteB). */
CafeGuestScene *CafeGuestScene_DestructDelete(CafeGuestScene *scene)
{
    *(const u8 **) (void *) scene = data_ov068_02277dc0;
    Obj020d9ff8_DestructBody(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_ov068_022746dc, CafeGuestScene_DestructDelete)

/* func_ov068_022746fc (the scene's slot 0x00): the destructor of main's class 0x020d9ff8. */
CafeGuestScene *CafeGuestScene_Destruct(CafeGuestScene *scene)
{
    *(const u8 **) (void *) scene = data_ov068_02277dc0;
    Obj020d9ff8_DestructBody(scene);
    return scene;
}
CLEAN_AS(func_ov068_022746fc, CafeGuestScene_Destruct)

/* func_ov068_02274714: the constructor: a scene of main's class 0x020d9ff8 given this class's
 * vtable, and its show seen set up (MusicShowState_Init). */
CafeGuestScene *CafeGuestScene_Construct(CafeGuestScene *scene)
{
    Obj020d9ff8_Construct(scene);
    *(const u8 **) (void *) scene = data_ov068_02277dc0;
    /* only the first 0x14 bytes, which the scene has, are set up */
    MusicShowState_Init((MusicShowState *) (void *) &scene->show);
    return scene;
}
CLEAN_AS(func_ov068_02274714, CafeGuestScene_Construct)

/* ---- The guest's states, vtable slots and creation */

/* After its talk while the music's show runs: the event finished; when the player is still
 * listening, overlay 4's func_ov004_0222c070(0); the music of priority 0x10 dropped, the
 * camera's mode reset, and CAFE_GUEST_DONE. */
static void end_play(CafeGuest *self)
{
    EventQueue_FinishObjectEvent(self);
    if (PlayerActorOps_InState(CAFE_GUEST_PLAYER_LISTENING, GUEST_PLAYER) != 0) {
        RoomPlayerActor_RequestSpotMove(0);
    }
    Music_DropPriority(CAFE_GUEST_TALK_PRIORITY);
    Music_Clear2f4();
    CameraControl_ResetMode();
    CafeGuest_SetState(self, CAFE_GUEST_DONE);
}

/* func_ov068_02274734 (update of CAFE_GUEST_PLAY): once its talk has ended, end_play.
 * QUIRK: whether the talk goes on is asked twice. */
int CafeGuest_UpdatePlay(CafeGuest *self)
{
    if (SceneAction_IsBusy(guest_action(self)) != 0) {
        return 1;
    }
    if (SceneAction_IsBusy(guest_action(self)) == 0) {
        end_play(self);
    }
    return 1;
}
CLEAN_AS(func_ov068_02274734, CafeGuest_UpdatePlay)

/* func_ov068_02274790 (start of CAFE_GUEST_PLAY): animation 0x102, overlay 4's
 * func_ov004_02246eb8, the guest looks ahead and talks (keeping the camera), and value 0xf is
 * added to the music of priority 0x10. */
int CafeGuest_StartPlay(CafeGuest *self)
{
    SceneMotion_RequestAnimation(guest_motion(self), 1, CAFE_GUEST_ANIM_TALK, 0, data_020c80f8, 0);
    RoomCamera_SetModeShow();
    SceneLook_RequestAngles(guest_look(self), 0, 0, CAFE_GUEST_LOOK_AHEAD, data_020c80f4, data_020c80ec);
    SceneAction_RequestTalk(guest_action(self), 0, 1);
    Music_AddValue(CAFE_GUEST_TALK_PRIORITY, CAFE_GUEST_TALK_VALUE, 0);
    Music_Set2f4();
    return 1;
}
CLEAN_AS(func_ov068_02274790, CafeGuest_StartPlay)

/* func_ov068_02274810 (update of CAFE_GUEST_SEATED): once the player is in state 0x28,
 * CAFE_GUEST_PLAY. */
int CafeGuest_UpdateSeated(CafeGuest *self)
{
    if (PlayerActorOps_InState(CAFE_GUEST_PLAYER_LISTENING, GUEST_PLAYER) != 0) {
        CafeGuest_SetState(self, CAFE_GUEST_PLAY);
    }
    return 1;
}
CLEAN_AS(func_ov068_02274810, CafeGuest_UpdateSeated)

/* func_ov068_02274830 (start of CAFE_GUEST_SEATED) */
int CafeGuest_StartSeated(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02274830, CafeGuest_StartSeated)

/* func_ov068_02274834 (update of CAFE_GUEST_DONE) */
int CafeGuest_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02274834, CafeGuest_UpdateDone)

/* func_ov068_02274838 (start of CAFE_GUEST_DONE) */
int CafeGuest_StartDone(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02274838, CafeGuest_StartDone)

/* func_ov068_0227483c (update of CAFE_GUEST_TALK): once its talk has ended, its event is
 * finished and CAFE_GUEST_DONE.
 * QUIRK: whether the talk goes on is asked twice. */
int CafeGuest_UpdateTalk(CafeGuest *self)
{
    if (SceneAction_IsBusy(guest_action(self)) != 0) {
        return 1;
    }
    if (SceneAction_IsBusy(guest_action(self)) == 0) {
        EventQueue_FinishObjectEvent(self);
        CafeGuest_SetState(self, CAFE_GUEST_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov068_0227483c, CafeGuest_UpdateTalk)

/* func_ov068_02274878 (start of CAFE_GUEST_TALK): kind 7 takes animation 0x102; the guest looks
 * at the player (look kind 4) and talks. */
int CafeGuest_StartTalk(CafeGuest *self)
{
    if (self->kind == CAFE_GUEST_KIND_MUSIC) {
        SceneMotion_RequestAnimation(guest_motion(self), 1, CAFE_GUEST_ANIM_TALK, 0, data_020c80f8, 0);
    }
    SceneLook_Request(guest_look(self), 4, 0, 0, &data_021fbee8, GUEST_PLAYER, data_020c814c, 0);
    SceneAction_RequestTalk(guest_action(self), 0, 0);
    return 1;
}
CLEAN_AS(func_ov068_02274878, CafeGuest_StartTalk)

/* func_ov068_022748f0 (update of CAFE_GUEST_WAIT): kind 8 (none) is deleted; kind 7 waits for
 * the player at its seat; the others show parts 6 and 7 of the cafe's counter (cafe_props.h),
 * and kind 6 its part 8 too. */
int CafeGuest_UpdateWait(CafeGuest *self)
{
    s32 kind = self->kind;
    if (kind == CAFE_GUEST_KIND_NONE) {
        Process_RequestDelete((Process *) (void *) self);
        return 1;
    }
    if (kind == CAFE_GUEST_KIND_MUSIC) {
        CafeGuest_WaitForListener(self);
    } else {
        CafeProps_ShowParts6And7();
    }
    if (self->kind == CAFE_GUEST_KIND_PLAN_3) {
        CafeProps_ShowPart8();
    }
    return 1;
}
CLEAN_AS(func_ov068_022748f0, CafeGuest_UpdateWait)

/* func_ov068_0227492c (start of CAFE_GUEST_WAIT): kind 7 looks about (look kind 0, within view),
 * takes animation 0x105 and looks up; the others look about with look kind 1. */
int CafeGuest_StartWait(CafeGuest *self)
{
    if (self->kind == CAFE_GUEST_KIND_MUSIC) {
        SceneLook_Request(guest_look(self), 0, 0, 0, &data_021fbee8, GUEST_PLAYER, data_020c814c, 1);
        SceneMotion_RequestAnimation(guest_motion(self), 1, CAFE_GUEST_ANIM_WAIT, 0, data_020c80f8, 0);
        SceneLook_RequestAngles(guest_look(self), 0, CAFE_GUEST_LOOK_UP, 0, data_020c80f4, data_020c80ec);
    } else {
        SceneLook_Request(guest_look(self), 1, 0, 0, &data_021fbee8, GUEST_PLAYER, data_020c814c, 1);
    }
    return 1;
}
CLEAN_AS(func_ov068_0227492c, CafeGuest_StartWait)

/* func_ov068_022749dc: the state's start run (when it has one); unless it answers 0 the state
 * is taken.
 * REQUIRES: `state` is one of the five. */
void CafeGuest_SetState(CafeGuest *self, int state)
{
    const CafeGuestStateFns *fns = &data_ov068_02278840[state];
    int taken = 1;
    if (fns->start.function != 0) {
        taken = MemberPointer_CallInt(&fns->start, self);
    }
    if (taken != 0) {
        self->state = state;
    }
}
CLEAN_AS(func_ov068_022749dc, CafeGuest_SetState)

/* func_ov068_02274a20 (slot 0x68): the state's update (when it has one); its answer, else 0.
 * REQUIRES: the state is one of the five. */
int CafeGuest_Update(CafeGuest *self)
{
    const CafeGuestStateFns *fns = &data_ov068_02278840[self->state];
    if (fns->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&fns->update, self);
}
CLEAN_AS(func_ov068_02274a20, CafeGuest_Update)

/* func_ov068_02274a6c (slot 0x70): the model's file name of its kind. */
unsigned int CafeGuest_ModelName(CafeGuest *self)
{
    return (unsigned int) (uintptr_t) data_ov068_02277cc8[self->kind];
}
CLEAN_AS(func_ov068_02274a6c, CafeGuest_ModelName)

/* func_ov068_02274a80 (slot 0x6c): the texture's file name of its kind. */
int CafeGuest_TextureName(CafeGuest *self)
{
    return (int) (uintptr_t) data_ov068_02277d10[self->kind];
}
CLEAN_AS(func_ov068_02274a80, CafeGuest_TextureName)

/* func_ov068_02274a94 (slot 0x0c): unless the base class refuses to leave, kind 7 releases
 * overlay 93's object. Whether it left. */
int CafeGuest_Leave(CafeGuest *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    if ((u32) self->kind == CAFE_GUEST_KIND_MUSIC) {
        MusicShowOverlay_Close();
    }
    return 1;
}
CLEAN_AS(func_ov068_02274a94, CafeGuest_Leave)

/* func_ov068_02274abc (slot 0x00): unless the base class refuses to start, kind 7 sets its
 * model's func_021074dc to 3; CAFE_GUEST_WAIT; it is held (flag 2 at 0x4e8); kind 3 plays its
 * animation 0x142 and moves its nodes 12-14 to layer A. Whether it started. */
int CafeGuest_Start(CafeGuest *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    if (self->kind == CAFE_GUEST_KIND_MUSIC) {
        func_021074dc(guest_model(self)->model_resource, 3);
    }
    CafeGuest_SetState(self, CAFE_GUEST_WAIT);
    self->flags |= GUEST_HELD;
    if (self->kind == CAFE_GUEST_KIND_PLAN_4) {
        SpeakerAnim_Play((SpeakerAnim *) (void *) guest_at(self, GUEST_ANIM), (u8 *) self, CAFE_GUEST_ANIM_KIND_3, 0, 0,
                         0x1000, 0, 1);
        LayeredModel_MoveNodesToA(guest_model(self), 0xc, 0xe);
    }
    return 1;
}
CLEAN_AS(func_ov068_02274abc, CafeGuest_Start)

/* The kind the plan's noon or afternoon value gives (none for 0 and above 4). */
static void kind_of_plan(CafeGuest *self, unsigned int value)
{
    switch (value) {
        case 2:
            self->kind = CAFE_GUEST_KIND_PLAN_2;
            break;
        case 1:
            self->kind = CAFE_GUEST_KIND_PLAN_1;
            break;
        case 3:
            self->kind = CAFE_GUEST_KIND_PLAN_3;
            break;
        case 4:
            self->kind = CAFE_GUEST_KIND_PLAN_4;
            break;
        default:
            break;
    }
}

/* func_ov068_02274b44 (slot 0x04): unless the base class refuses, its scene is its talk (which
 * gets it as its owner), it has no shadow, and its kind is picked: none while this system is
 * linked to a session or the town's first day counts; else by the weekday and the clock
 * (Saturday 19:30-23:59 kind 7, which brings the actor of profile 0x10; 21:00-21:54 kind 1
 * except on Saturdays; weekdays 23:00-23:59 kind 2 with the plan's night bit and Nook's store
 * at level 3; 12:00-13:29 and 14:30-15:59 by the plan's noon and afternoon values; 6:00-6:54
 * kind 0 with the plan's morning bit, a later rule winning). Then it takes the kind's person
 * code; kind 7 stands at (15.0, 19.0) at angle 0 with a reach of 5.0, its standard
 * animations 0x102 and a look about within view, the others the standard animations 0x1e and
 * no pitch limit. Whether it was set up. */
int CafeGuest_Init(CafeGuest *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, scene_base(&self->scene));
    CafeGuestScene_Begin(&self->scene, self);
    *guest_at(self, GUEST_SHADOW) = 0;
    DateTime now = {0};
    DateTime_Now(&now);
    u8 hour = now.hour;
    u8 minute = now.minute;
    self->kind = CAFE_GUEST_KIND_NONE;
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0) {
        return 1;
    }
    if (TownStartDay_IsSet(&data_021f3b85) != 0) {
        return 1;
    }
    const u8 *plan = &data_021ebcd3;
    switch (Calendar_TodayWeekday()) {
        case 6:
            if ((hour == 19 && minute >= 30) || hour == 20 || hour == 21 || hour == 22 || (hour == 23 && minute <= 59)) {
                self->kind = CAFE_GUEST_KIND_MUSIC;
                Actor_Spawn(CAFE_GUEST_MUSIC_ACTOR, 0, NULL, NULL, NULL);
            }
            break;
        case 0:
            if (hour == 21 && minute < 55) {
                self->kind = CAFE_GUEST_KIND_NIGHT;
            }
            break;
        default:
            if (hour == 21 && minute < 55) {
                self->kind = CAFE_GUEST_KIND_NIGHT;
            }
            if (hour == 23 && minute <= 59 && DayPlan_Night(plan) != 0 && NookStore_Level(&data_021f395c) == 3) {
                self->kind = CAFE_GUEST_KIND_LATE;
            }
            break;
    }
    if (hour == 12 || (hour == 13 && minute < 30)) {
        kind_of_plan(self, (unsigned int) DayPlan_Noon(plan));
    }
    if ((hour == 14 && minute >= 30) || (hour == 15 && minute <= 59)) {
        kind_of_plan(self, (unsigned int) DayPlan_Afternoon(plan));
    }
    if (hour == 6 && minute < 55 && DayPlan_Morning(plan) != 0) {
        self->kind = CAFE_GUEST_KIND_MORNING;
    }
    u16 person = data_ov068_022767ec[self->kind];
    SceneObject_SetPerson((u8 *) self, &person);
    SceneStandardAnims *standard = guest_standard_anims(self);
    if (self->kind == CAFE_GUEST_KIND_MUSIC) {
        SceneObjectBase_SetReach(guest_base(self), CAFE_GUEST_MUSIC_REACH);
        guest_base(self)->position.x = CAFE_GUEST_MUSIC_X;
        guest_base(self)->position.z = CAFE_GUEST_MUSIC_Z;
        guest_base(self)->yaw = 0;
        *(u16 *) (void *) guest_at(self, GUEST_WALK_ANGLE) = 0;
        SceneStandardAnims_SetFirst(standard, CAFE_GUEST_STANDARD_MUSIC);
        SceneStandardAnims_SetSecond(standard, CAFE_GUEST_STANDARD_MUSIC);
        SceneStandardAnims_SetThird(standard, CAFE_GUEST_STANDARD_MUSIC);
        SceneLook_Request(guest_look(self), 0, 0, 0, &data_021fbee8, GUEST_PLAYER, data_020c814c, 1);
    } else {
        SceneStandardAnims_SetFirst(standard, CAFE_GUEST_STANDARD);
        SceneStandardAnims_SetSecond(standard, CAFE_GUEST_STANDARD);
        SceneStandardAnims_SetThird(standard, CAFE_GUEST_STANDARD);
        SceneLook_SetPitchLimit(guest_look(self), 0);
    }
    return 1;
}
CLEAN_AS(func_ov068_02274b44, CafeGuest_Init)

/* func_ov068_02274dc8 (its record's create function): a zeroed block of 0x750 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then the
 * class's vtable and its talk scene. Null when there is no room. */
CafeGuest *CafeGuest_Create(void)
{
    CafeGuest *self = (CafeGuest *) Heap_AllocAuxZeroed(sizeof(CafeGuest));
    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct(guest_base(self));
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) guest_at(self, GUEST_PERSON) = GUEST_NO_PERSON;
    LayeredModel_ConstructB(guest_model(self));
    SceneStandardAnims_Init(guest_standard_anims(self));
    SceneFace_Construct(guest_face(self));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) guest_at(self, GUEST_ANIM));
    SceneMover_Construct((SceneMover *) (void *) guest_at(self, GUEST_MOVER));
    SceneProbe_Construct(guest_at(self, GUEST_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) guest_at(self, GUEST_VALUE_3AA));
    SceneLook_Construct(guest_look(self));
    SceneTalkState_Construct((SceneTalkState *) (void *) guest_at(self, GUEST_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) guest_at(self, GUEST_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) guest_at(self, GUEST_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) guest_at(self, GUEST_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) guest_at(self, GUEST_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) guest_at(self, GUEST_FOOTSTEPS));
    SceneMotion_Construct(guest_motion(self));
    SceneAction_Construct(guest_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) guest_at(self, GUEST_HEAP));
    *(const u8 **) (void *) self = data_ov068_02277e50;
    CafeGuestScene_Construct(&self->scene);
    return self;
}
CLEAN_AS(func_ov068_02274dc8, CafeGuest_Create)
