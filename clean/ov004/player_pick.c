/* The process that picks this system's player in the room (player_pick.h). */
#include "player_pick.h"

#include "autoload_2/approach.h" /* Countdown_Tick16 */
#include "autoload_2/heap.h"     /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "autoload_2/input.h"    /* PadState */
#include "clean.h"
#include "main/activity_job.h"
#include "main/actor.h"
#include "main/camera_control.h"
#include "main/control_mode_icon.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/message_reader.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_query.h"
#include "main/screen_transition.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sound.h"
#include "main/state_block.h"
#include "main/state_flags.h"
#include "main/touch_pick_shapes.h"
#include "member_pointer.h"
#include "rmo_telephone.h"

static_assert(sizeof(PlayerPick) == 0x358, "the process");
static_assert(offsetof(PlayerPick, cursor) == 0x50, "the cursor");
static_assert(offsetof(PlayerPick, tags) == 0x9c, "the name tags");
static_assert(offsetof(PlayerPick, selection) == 0x31c, "the selection");
static_assert(offsetof(PlayerPick, state) == 0x320, "the state");
static_assert(offsetof(PlayerPick, timer) == 0x324, "the timer");
static_assert(offsetof(PlayerPick, opened) == 0x328, "the time of creation");
static_assert(offsetof(PlayerPick, cursor_x) == 0x330, "the cursor's place");
static_assert(offsetof(PlayerPick, fixed) == 0x338, "the fixed tag's text");

/* The buttons (PadState.pressed). */
#define PLAYER_PICK_PAD_A 0x0001
#define PLAYER_PICK_PAD_START 0x0008
#define PLAYER_PICK_PAD_RIGHT 0x0010
#define PLAYER_PICK_PAD_LEFT 0x0020
#define PLAYER_PICK_PAD_UP 0x0040
#define PLAYER_PICK_PAD_DOWN 0x0080
/* Any button that makes the touch state give way to the buttons: all but select and start. */
#define PLAYER_PICK_PAD_ANY 0x0ff3

/* The players' grid: 0 and 1 above 2 and 3. */
#define PLAYER_PICK_ROW 2

/* The cursor's animations. */
#define PLAYER_PICK_CURSOR_OFF 0
#define PLAYER_PICK_CURSOR_ON 7

/* The cursor's sound when it moves while picking with the buttons. */
#define PLAYER_PICK_SE_MOVE 11
/* The fixed tag's message of the menu files. */
#define PLAYER_PICK_FIXED_MESSAGE 0x81
/* The touch picks' kind for the players: the index is the player. */
#define PLAYER_PICK_TOUCH_PLAYER 1
/* The telephone's vtable slot (a byte offset) that answers its point. */
#define PLAYER_PICK_PHONE_SLOT_POINT 0x50
/* This system's player, as the field actor functions number it. */
#define PLAYER_PICK_LOCAL 4
/* The frames of states 3 and 4. */
#define PLAYER_PICK_PICKED_FRAMES 0x19
#define PLAYER_PICK_TURN_FRAMES 5
/* How far the player walks off from the start position, along z. */
#define PLAYER_PICK_LEAVE_DISTANCE 0x6000
#define PLAYER_PICK_LEAVE_ACCEL 0x2b8
/* The scene's player actor action of state 3 (func_ov004_0222c110's last argument). */
#define PLAYER_PICK_ACTION_ARG 1
/* The cell layer sprite's and the name tags' vtable slots: draw and step. */
#define PLAYER_PICK_SLOT_DRAW 2
#define PLAYER_PICK_SLOT_STEP 3

/* A place on the screen. */
typedef struct PlayerPickOffset {
    int x;
    int y;
} PlayerPickOffset;

/* A state's entry and update. */
typedef struct PlayerPickStateFns {
    MemberPointer enter;
    MemberPointer update;
} PlayerPickStateFns;

/* The states' functions (filled by __sinit_ov004_0224f8a4). */
extern PlayerPickStateFns data_ov004_0225fe94[PLAYER_PICK_STATES];

/* The cursor's offset over the telephone (-6, -14), the fixed tag's place (15, -92), the
 * cursor's offsets over each player and the tags' offsets from each player. */
extern const PlayerPickOffset data_ov004_0224be14;
extern const PlayerPickOffset data_ov004_0224be1c;
extern const PlayerPickOffset data_ov004_0224be24[PLAYER_PICK_PLAYERS];
extern const PlayerPickOffset data_ov004_0224be44[PLAYER_PICK_PLAYERS];

/* The vtables: this class's and the scene class of autoload_2. */
extern const u32 data_ov004_0225684c[];
extern const u32 data_020da13c[];

extern u8 data_021c75b8;          /* the screen transition's state (screen_transition.h) */
extern NetSession *data_020ccf94; /* the session */
extern StateBlock data_021dc7a8;  /* the state block */
extern u8 data_021dc7bc[];        /* the town's four players' records (0x14 into the state block) */
extern PadState data_021fbe40;    /* the buttons */
extern u8 data_021fbdd8;          /* the pen is down */
extern u8 data_021fbddc;          /* the pen went down or up this frame */
extern u8 data_021f6c38;          /* the pen was down (touch_history.c) */
extern u8 data_021f6c34;          /* the pen went down or up */

/* The scene's player actor told to take action 6 to the side `left` (func_ov004_0222b9d4). */
extern int func_ov004_0222c110(int left, int arg);
/* Overlay 4's camera follows the field camera again (func_ov004_022473a8). */
extern int func_ov004_02246a74(void);

/* The name tags' destructor and constructor, as the game hands them to the array helpers. */
extern void func_0208e408(void *tag);
extern void func_0208e438(void *tag);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* A sprite's (or tag's) vtable slot, called with the sprite. */
static void PlayerPick_call_slot(void *sprite, int slot)
{
    const u32 *vtable = *(const u32 *const *) sprite;
    ((void (*)(void *))(uintptr_t) vtable[slot])(sprite);
}

/* Whether the screen is shown (no transition goes on). */
static int PlayerPick_screen_shown(void)
{
    return data_021c75b8 == SCREEN_TRANSITION_SHOWN;
}

/* A field actor's position, from its handle (0x5c past a handle of 0 when there is none). */
static const Vec3 *PlayerPick_actor_position(int handle)
{
    return (const Vec3 *) (uintptr_t) ((u32) handle + offsetof(Actor, position));
}

/* func_ov004_0224564c: the cursor placed over the telephone (at the point its vtable slot 0x50
 * answers) or over the picked player's field actor, at the screen position plus the offset;
 * the cursor's sound while picking with the buttons when the place changed; the cursor
 * stepped, and the place kept.
 * REQUIRES: the telephone exists while the cursor is on it. */
void PlayerPick_PlaceCursor(PlayerPick *self)
{
    const Vec3 *point;
    if (self->on_telephone) {
        u32 phone = RmoTelephone_Current();
        const u32 *vtable = *(const u32 *const *) (uintptr_t) phone;
        point = ((const Vec3 *(*) (void *) )(uintptr_t) vtable[PLAYER_PICK_PHONE_SLOT_POINT / 4])((void *) (uintptr_t) phone);
    } else {
        point = PlayerPick_actor_position(SessionPlayers_ActorHandle(self->selection));
    }

    int x;
    int y;
    CameraControl_ScreenPosition(&x, &y, point);
    if (!self->on_telephone) {
        x += data_ov004_0224be24[self->selection].x;
        y += data_ov004_0224be24[self->selection].y;
    } else {
        x += data_ov004_0224be14.x;
        y += data_ov004_0224be14.y;
    }

    if (PlayerPick_screen_shown() && self->state == PLAYER_PICK_BUTTONS && (self->cursor_x != x || self->cursor_y != y)) {
        SoundSys_PlaySe(PLAYER_PICK_SE_MOVE);
    }
    CellLayerSprite_SetOffset(&self->cursor, x, y);
    PlayerPick_call_slot(&self->cursor, PLAYER_PICK_SLOT_STEP);
    self->cursor_x = x;
    self->cursor_y = y;
}
CLEAN_AS(func_ov004_0224564c, PlayerPick_PlaceCursor)

/* func_ov004_02245744: each of the town's players that has a field actor gets its tag placed
 * over the actor's screen position (plus the tag's offset) with the player's name, and
 * stepped; then the fixed tag is placed, given its text and stepped. */
void PlayerPick_PlaceTags(PlayerPick *self)
{
    for (u8 i = 0; i < PLAYER_PICK_PLAYERS; i++) {
        if (PlayerRecords_TownExists(data_021dc7bc, i) == 0) {
            continue;
        }
        int handle = SessionPlayers_ActorHandle(i);
        if (handle == 0) {
            continue;
        }
        Vec3 position = *PlayerPick_actor_position(handle);
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        PlayerId_NameToText(PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, i)), (TextBase *) (void *) &name);
        int x;
        int y;
        CameraControl_ScreenPosition(&x, &y, &position);
        x += data_ov004_0224be44[i].x;
        y += data_ov004_0224be44[i].y;
        NameTag *tag = &self->tags[i];
        NameTag_SetPlace(tag, x, y);
        NameTag_SetText(tag, (TextBase *) (void *) &name);
        PlayerPick_call_slot(tag, PLAYER_PICK_SLOT_STEP);
        PlayerIdText_Destruct(&name);
    }
    NameTag *fixed = &self->tags[NAME_TAG_KIND_FIXED];
    NameTag_SetPlace(fixed, data_ov004_0224be1c.x, data_ov004_0224be1c.y);
    NameTag_SetText(fixed, (TextBase *) (void *) &self->fixed);
    PlayerPick_call_slot(fixed, PLAYER_PICK_SLOT_STEP);
}
CLEAN_AS(func_ov004_02245744, PlayerPick_PlaceTags)

/* func_ov004_02245818 (update of PLAYER_PICK_LEAVE): nothing. */
void PlayerPick_UpdateLeave(void) {}
CLEAN_AS(func_ov004_02245818, PlayerPick_UpdateLeave)

/* func_ov004_0224581c (entry of PLAYER_PICK_LEAVE): this system's player walks to 0x6000 past
 * its start position along z. */
void PlayerPick_EnterLeave(void)
{
    Vec3 target = *PlayerActorOps_StartPosition(PLAYER_PICK_LOCAL);
    target.z += PLAYER_PICK_LEAVE_DISTANCE;
    PlayerActorOps_MoveTo(&target, PLAYER_PICK_LEAVE_ACCEL, PLAYER_PICK_LOCAL);
}
CLEAN_AS(func_ov004_0224581c, PlayerPick_EnterLeave)

/* func_ov004_02245850 (update of PLAYER_PICK_ASK): once the activity job is idle, on to
 * PLAYER_PICK_LEAVE. */
void PlayerPick_UpdateAsk(PlayerPick *self)
{
    if (ActivityJob_IsIdleForOv004() != 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_LEAVE);
    }
}
CLEAN_AS(func_ov004_02245850, PlayerPick_UpdateAsk)

/* func_ov004_0224586c (entry of PLAYER_PICK_ASK): activity job 3 asked for. */
void PlayerPick_EnterAsk(void)
{
    ActivityJob_Ask3();
}
CLEAN_AS(func_ov004_0224586c, PlayerPick_EnterAsk)

/* func_ov004_02245874 (update of PLAYER_PICK_TURN): once the timer runs out, on to
 * PLAYER_PICK_ASK. */
void PlayerPick_UpdateTurn(PlayerPick *self)
{
    if (Countdown_Tick16(&self->timer) == 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_ASK);
    }
}
CLEAN_AS(func_ov004_02245874, PlayerPick_UpdateTurn)

/* func_ov004_02245898 (entry of PLAYER_PICK_TURN): overlay 4's camera follows the field camera
 * again, this system's player turns to yaw 0, and 5 frames.
 * QUIRK: it answers 0x324 (the timer's offset, left in the result register); nothing reads
 * it. */
int PlayerPick_EnterTurn(PlayerPick *self)
{
    func_ov004_02246a74();
    PlayerActorOps_Turn(0, PLAYER_PICK_LOCAL);
    self->timer = PLAYER_PICK_TURN_FRAMES;
    return (int) offsetof(PlayerPick, timer);
}
CLEAN_AS(func_ov004_02245898, PlayerPick_EnterTurn)

/* func_ov004_022458b8 (update of PLAYER_PICK_PICKED): once the timer runs out, on to
 * PLAYER_PICK_TURN. */
void PlayerPick_UpdatePicked(PlayerPick *self)
{
    if (Countdown_Tick16(&self->timer) == 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_TURN);
    }
}
CLEAN_AS(func_ov004_022458b8, PlayerPick_UpdatePicked)

/* func_ov004_022458dc (entry of PLAYER_PICK_PICKED): the scene's player actor takes its action
 * to the left for players 0 and 2 (the left column), else to the right; the cursor off, the
 * tags hidden, and 25 frames. */
void PlayerPick_EnterPicked(PlayerPick *self)
{
    int left = 0;
    if (self->selection == 0 || self->selection == 2) {
        left = 1;
    }
    func_ov004_0222c110(left, PLAYER_PICK_ACTION_ARG);
    CellLayerSprite_SetAnim(&self->cursor, PLAYER_PICK_CURSOR_OFF);
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        NameTag_Hide(&self->tags[i]);
    }
    self->timer = PLAYER_PICK_PICKED_FRAMES;
}
CLEAN_AS(func_ov004_022458dc, PlayerPick_EnterPicked)

/* func_ov004_0224592c (update of PLAYER_PICK_BUTTONS), while the screen is shown: with a local
 * player already set (not 4), on to PLAYER_PICK_PICKED; while the telephone talks, back to
 * PLAYER_PICK_WAIT; the pen coming down turns the control mode to touch and goes to
 * PLAYER_PICK_TOUCH. Else the d-pad moves the cursor: from the telephone down (or right or left
 * onto a player with a field actor) to the players; among the players on the grid, onto one
 * with a field actor (from the bottom row up, the player above or beside it, else the
 * telephone; from the top row up, the telephone). A or start then talks to the telephone or
 * takes the picked player as the local player and goes to PLAYER_PICK_PICKED. */
void PlayerPick_UpdateButtons(PlayerPick *self)
{
    if (!PlayerPick_screen_shown()) {
        return;
    }
    NetSession *session = data_020ccf94;
    if (session->local_player != PLAYER_PICK_LOCAL) {
        PlayerPick_EnterState(self, PLAYER_PICK_PICKED);
        return;
    }
    if (RmoTelephone_IsTalking() != 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_WAIT);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        ControlModeIcon_SetTouch();
        PlayerPick_EnterState(self, PLAYER_PICK_TOUCH);
        return;
    }

    u16 pressed = data_021fbe40.pressed;
    if (self->on_telephone) {
        if (pressed & PLAYER_PICK_PAD_DOWN) {
            self->on_telephone = 0;
        } else if ((pressed & PLAYER_PICK_PAD_RIGHT) || (pressed & PLAYER_PICK_PAD_LEFT)) {
            u8 selection = self->selection;
            if (pressed & PLAYER_PICK_PAD_RIGHT) {
                selection = 1;
            } else if (pressed & PLAYER_PICK_PAD_LEFT) {
                selection = 0;
            }
            if (SessionPlayers_ActorHandle(selection) != 0) {
                self->on_telephone = 0;
                self->selection = selection;
            }
        }
    } else {
        u8 selection = self->selection;
        switch (selection) {
            case 0:
                if (pressed & PLAYER_PICK_PAD_RIGHT) {
                    selection++;
                } else if (pressed & PLAYER_PICK_PAD_DOWN) {
                    selection += PLAYER_PICK_ROW;
                    if (SessionPlayers_ActorHandle(selection) == 0) {
                        selection++;
                    }
                } else if (pressed & PLAYER_PICK_PAD_UP) {
                    self->on_telephone = 1;
                }
                break;
            case 1:
                if (pressed & PLAYER_PICK_PAD_LEFT) {
                    selection--;
                } else if (pressed & PLAYER_PICK_PAD_DOWN) {
                    selection += PLAYER_PICK_ROW;
                    if (SessionPlayers_ActorHandle(selection) == 0) {
                        selection--;
                    }
                } else if (pressed & PLAYER_PICK_PAD_UP) {
                    self->on_telephone = 1;
                }
                break;
            case 2:
                if (pressed & PLAYER_PICK_PAD_RIGHT) {
                    selection++;
                } else if (pressed & PLAYER_PICK_PAD_UP) {
                    selection -= PLAYER_PICK_ROW;
                    if (SessionPlayers_ActorHandle(selection) == 0) {
                        selection++;
                        if (SessionPlayers_ActorHandle(selection) == 0) {
                            self->on_telephone = 1;
                        }
                    }
                }
                break;
            case 3:
                if (pressed & PLAYER_PICK_PAD_LEFT) {
                    selection--;
                } else if (pressed & PLAYER_PICK_PAD_UP) {
                    selection -= PLAYER_PICK_ROW;
                    if (SessionPlayers_ActorHandle(selection) == 0) {
                        selection--;
                        if (SessionPlayers_ActorHandle(selection) == 0) {
                            self->on_telephone = 1;
                        }
                    }
                }
                break;
        }
        if (SessionPlayers_ActorHandle(selection) != 0) {
            self->selection = selection;
        }
    }

    if ((pressed & PLAYER_PICK_PAD_START) || (pressed & PLAYER_PICK_PAD_A)) {
        if (self->on_telephone) {
            RmoTelephone_EnterState10Current();
        } else {
            session->local_player = self->selection;
            PlayerPick_EnterState(self, PLAYER_PICK_PICKED);
        }
    }
}
CLEAN_AS(func_ov004_0224592c, PlayerPick_UpdateButtons)

/* func_ov004_02245b8c (entry of PLAYER_PICK_BUTTONS): the cursor shown, and the tags. */
void PlayerPick_EnterButtons(PlayerPick *self)
{
    CellLayerSprite_SetAnim(&self->cursor, PLAYER_PICK_CURSOR_ON);
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        NameTag_Show(&self->tags[i]);
    }
}
CLEAN_AS(func_ov004_02245b8c, PlayerPick_EnterButtons)

/* func_ov004_02245bb8 (update of PLAYER_PICK_TOUCH), while the screen is shown: in the touch
 * control mode, the pen coming down on a player's field actor (a touch pick of kind 1) takes
 * that player as the local player and goes to PLAYER_PICK_PICKED. Else while the telephone
 * talks, back to PLAYER_PICK_WAIT; any button but select and start turns the control mode to
 * the buttons and goes to PLAYER_PICK_BUTTONS. */
void PlayerPick_UpdateTouch(PlayerPick *self)
{
    if (!PlayerPick_screen_shown()) {
        return;
    }
    if (ControlModeIcon_IsTouch() != 0 && data_021f6c38 != 0 && data_021f6c34 != 0) {
        Vec3 point;
        u32 kind;
        u8 index;
        if (TouchPick_GetPick((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &point, &kind, &index) != 0 &&
            kind == PLAYER_PICK_TOUCH_PLAYER) {
            data_020ccf94->local_player = index;
            self->selection = index;
            PlayerPick_EnterState(self, PLAYER_PICK_PICKED);
            return;
        }
    }
    if (RmoTelephone_IsTalking() != 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_WAIT);
    } else if ((data_021fbe40.pressed & PLAYER_PICK_PAD_ANY) != 0) {
        ControlModeIcon_SetButtons();
        PlayerPick_EnterState(self, PLAYER_PICK_BUTTONS);
    }
}
CLEAN_AS(func_ov004_02245bb8, PlayerPick_UpdateTouch)

/* func_ov004_02245c70 (entry of PLAYER_PICK_TOUCH): the cursor off, the tags shown. */
void PlayerPick_EnterTouch(PlayerPick *self)
{
    CellLayerSprite_SetAnim(&self->cursor, PLAYER_PICK_CURSOR_OFF);
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        NameTag_Show(&self->tags[i]);
    }
}
CLEAN_AS(func_ov004_02245c70, PlayerPick_EnterTouch)

/* func_ov004_02245c9c (update of PLAYER_PICK_WAIT): once the telephone does not talk, on to
 * PLAYER_PICK_BUTTONS in the buttons' control mode, else PLAYER_PICK_TOUCH. */
void PlayerPick_UpdateWait(PlayerPick *self)
{
    if (RmoTelephone_IsTalking() != 0) {
        return;
    }
    if (ControlModeIcon_IsButtons() != 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_BUTTONS);
    } else {
        PlayerPick_EnterState(self, PLAYER_PICK_TOUCH);
    }
}
CLEAN_AS(func_ov004_02245c9c, PlayerPick_UpdateWait)

/* func_ov004_02245cc8 (entry of PLAYER_PICK_WAIT): the cursor off, the tags hidden. */
void PlayerPick_EnterWait(PlayerPick *self)
{
    CellLayerSprite_SetAnim(&self->cursor, PLAYER_PICK_CURSOR_OFF);
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        NameTag_Hide(&self->tags[i]);
    }
}
CLEAN_AS(func_ov004_02245cc8, PlayerPick_EnterWait)

/* func_ov004_02245cf4: `state` entered: its entry run (when it has one), then the state set.
 * REQUIRES: `state` is 0-6. */
void PlayerPick_EnterState(PlayerPick *self, int state)
{
    const MemberPointer *enter = &data_ov004_0225fe94[state].enter;
    if (enter->function != 0) {
        MemberPointer_CallVoid(enter, self);
    }
    self->state = state;
}
CLEAN_AS(func_ov004_02245cf4, PlayerPick_EnterState)

/* func_ov004_02245d30 (vtable slot 9, the drawing): the cursor drawn, then the tags. */
int PlayerPick_Draw(PlayerPick *self)
{
    PlayerPick_call_slot(&self->cursor, PLAYER_PICK_SLOT_DRAW);
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        PlayerPick_call_slot(&self->tags[i], PLAYER_PICK_SLOT_DRAW);
    }
    return 1;
}
CLEAN_AS(func_ov004_02245d30, PlayerPick_Draw)

/* func_ov004_02245d60 (vtable slot 6, the execution): the cursor and the tags placed, then the
 * state's update (when it has one).
 * REQUIRES: the state is 0-6. */
int PlayerPick_Execute(PlayerPick *self)
{
    PlayerPick_PlaceCursor(self);
    PlayerPick_PlaceTags(self);
    const MemberPointer *update = &data_ov004_0225fe94[self->state].update;
    if (update->function != 0) {
        MemberPointer_CallVoid(update, self);
    }
    return 1;
}
CLEAN_AS(func_ov004_02245d60, PlayerPick_Execute)

/* func_ov004_02245db0 (vtable slot 3, the deletion): the event queue's flag 1 cleared and the
 * tags rewound; with state flag 0x40 set, flags 8, 0x20 and 0x40 cleared and then 0x20 set
 * when the time of creation is earlier than now (seconds to years), else 8. */
int PlayerPick_Delete(PlayerPick *self)
{
    EventQueue_ClearFlag1();
    u8 i = 0;
    do {
        NameTag_Rewind(&self->tags[i]);
        i++;
    } while (i < PLAYER_PICK_TAGS);
    if (StateFlags_Test40() != 0) {
        StateFlags_Clear8And20And40();
        DateTime now = {0};
        DateTime_Now(&now);
        int fields = DATE_TIME_SECOND | DATE_TIME_MINUTE | DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR;
        if (DateTime_Compare(&self->opened, &now, fields) == -1) {
            StateFlags_Set20();
        } else {
            StateFlags_Set8();
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02245db0, PlayerPick_Delete)

/* func_ov004_02245e18 (vtable slot 0, the creation): the event queue's flag 1 set; the first of
 * the town's four players with a player in its record picked; the tags given their kinds; the
 * fixed tag's text loaded (message 0x81); then PLAYER_PICK_WAIT until flag 0 of the state block
 * is set, else the state of the control mode; the cursor off the telephone, and the time
 * kept. */
int PlayerPick_Create(PlayerPick *self)
{
    EventQueue_SetFlag1();
    for (u8 i = 0; i < PLAYER_PICK_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record != NULL && PlayerRecord_HasPlayer(record) != 0) {
            self->selection = i;
            break;
        }
    }
    for (u8 i = 0; i < PLAYER_PICK_TAGS; i++) {
        NameTag_SetKind(&self->tags[i], i);
    }
    u8 message = PLAYER_PICK_FIXED_MESSAGE;
    MessageReader_LoadMenuMessage((int) (uintptr_t) &self->fixed, &message, NULL);
    if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, 0) == 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_WAIT);
    } else if (ControlModeIcon_IsButtons() != 0) {
        PlayerPick_EnterState(self, PLAYER_PICK_BUTTONS);
    } else {
        PlayerPick_EnterState(self, PLAYER_PICK_TOUCH);
    }
    self->on_telephone = 0;
    DateTime_Now(&self->opened);
    return 1;
}
CLEAN_AS(func_ov004_02245e18, PlayerPick_Create)

/* The destructor's work: the fixed tag's text, the tags (last first) and the cursor
 * destructed, then the base process. */
static void PlayerPick_destruct_members(PlayerPick *self)
{
    self->base.vtable = data_ov004_0225684c;
    PlayerIdText_Destruct(&self->fixed);
    __cxa_vec_cleanup(self->tags, PLAYER_PICK_TAGS, sizeof(NameTag), func_0208e408);
    CellLayerSprite_Destruct(&self->cursor);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_02245ed8 (vtable slot 17): the destructor, and the process freed. */
PlayerPick *PlayerPick_DestructFree(PlayerPick *self)
{
    PlayerPick_destruct_members(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02245ed8, PlayerPick_DestructFree)

/* func_ov004_02245f28 (vtable slot 16): the destructor. */
PlayerPick *PlayerPick_Destruct(PlayerPick *self)
{
    PlayerPick_destruct_members(self);
    return self;
}
CLEAN_AS(func_ov004_02245f28, PlayerPick_Destruct)

/* func_ov004_02245f70: the constructor: the cursor on the main screen, the tags, no time yet
 * and the fixed tag's text. */
PlayerPick *PlayerPick_Construct(PlayerPick *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_0225684c;
    CellLayerSprite_ConstructCopy(&self->cursor, 1);
    __cxa_vec_ctor(self->tags, PLAYER_PICK_TAGS, sizeof(NameTag), func_0208e438, func_0208e408);
    self->opened = (DateTime){0};
    PlayerIdText_Construct(&self->fixed);
    return self;
}
CLEAN_AS(func_ov004_02245f70, PlayerPick_Construct)

/* func_ov004_02245fd8 (the profile): a process from the auxiliary heap. */
void PlayerPick_New(void)
{
    PlayerPick *self = Heap_AllocAuxZeroed(sizeof(PlayerPick));
    if (self == NULL) {
        return;
    }
    PlayerPick_Construct(self);
}
CLEAN_AS(func_ov004_02245fd8, PlayerPick_New)
