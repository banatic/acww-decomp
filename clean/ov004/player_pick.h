/* A process of overlay 4 (vtable data_ov004_0225684c, 0x358 bytes, on the scene class of
 * autoload_2, data_020da13c; profile PlayerPick_New) with which this system's player is picked
 * among the town's players standing in the room, or the room's telephone (rmo_telephone.h) is
 * picked to talk to it.
 *
 * A cursor (a cell layer sprite) stands over the picked player's field actor, or over the
 * telephone, and five name tags (name_tag.h) show the names: tags 0-3 over the town's players
 * (at their screen positions, offset by data_ov004_0224be44), tag 4 at a fixed place with
 * message 0x81 of the menu files. The players are picked on a grid, 0 and 1 above 2 and 3, the
 * telephone above them.
 *
 * Its states (PlayerPickState) each have an entry and an update, as pairs of member pointers
 * in data_ov004_0225fe94 (filled by __sinit_ov004_0224f8a4); PlayerPick_EnterState runs the
 * entry, then sets the state. Picking a player sets the session's local player (session.h,
 * 0x68); the player then turns, activity job 3 is asked for, and once it is done the player
 * walks 0x6000 from the start position. */
#ifndef CLEAN_OV004_PLAYER_PICK_H
#define CLEAN_OV004_PLAYER_PICK_H

#include "autoload_2/process.h"
#include "main/calendar.h"          /* DateTime */
#include "main/cell_layer_sprite.h" /* CellLayerSprite */
#include "main/name_tag.h"          /* NameTag */
#include "main/player_id.h"         /* PlayerIdText */
#include "types.h"

#define PLAYER_PICK_PLAYERS 4 /* the town's players, tags 0-3 */
#define PLAYER_PICK_TAGS 5    /* and the fixed tag */

/* PlayerPick.state */
enum PlayerPickState {
    PLAYER_PICK_WAIT = 0,    /* until the telephone has no talk, then by the control mode 1 or 2 */
    PLAYER_PICK_TOUCH = 1,   /* picking with the pen */
    PLAYER_PICK_BUTTONS = 2, /* picking with the buttons */
    PLAYER_PICK_PICKED = 3,  /* 25 frames */
    PLAYER_PICK_TURN = 4,    /* 5 frames */
    PLAYER_PICK_ASK = 5,     /* activity job 3 asked for, until it is idle */
    PLAYER_PICK_LEAVE = 6,   /* the player walks off */
    PLAYER_PICK_STATES = 7,
};

typedef struct PlayerPick {
    Process base;                   /* 0x000: vtable data_ov004_0225684c */
    CellLayerSprite cursor;         /* 0x050 */
    NameTag tags[PLAYER_PICK_TAGS]; /* 0x09c */
    u8 selection;                   /* 0x31c: the player picked, 0-3 */
    u8 on_telephone;                /* 0x31d: the cursor is on the telephone */
    u8 pad_31e[2];
    s32 state; /* 0x320: PlayerPickState */
    u16 timer; /* 0x324: frames left of states 3 and 4 */
    u8 pad_326[2];
    DateTime opened;    /* 0x328: the time of its creation */
    int cursor_x;       /* 0x330: the cursor's place in the last frame */
    int cursor_y;       /* 0x334 */
    PlayerIdText fixed; /* 0x338: the fixed tag's text */
} PlayerPick;

void PlayerPick_PlaceCursor(PlayerPick *self);
void PlayerPick_PlaceTags(PlayerPick *self);
void PlayerPick_UpdateLeave(void);
void PlayerPick_EnterLeave(void);
void PlayerPick_UpdateAsk(PlayerPick *self);
void PlayerPick_EnterAsk(void);
void PlayerPick_UpdateTurn(PlayerPick *self);
int PlayerPick_EnterTurn(PlayerPick *self);
void PlayerPick_UpdatePicked(PlayerPick *self);
void PlayerPick_EnterPicked(PlayerPick *self);
void PlayerPick_UpdateButtons(PlayerPick *self);
void PlayerPick_EnterButtons(PlayerPick *self);
void PlayerPick_UpdateTouch(PlayerPick *self);
void PlayerPick_EnterTouch(PlayerPick *self);
void PlayerPick_UpdateWait(PlayerPick *self);
void PlayerPick_EnterWait(PlayerPick *self);
void PlayerPick_EnterState(PlayerPick *self, int state);
int PlayerPick_Draw(PlayerPick *self);
int PlayerPick_Execute(PlayerPick *self);
int PlayerPick_Delete(PlayerPick *self);
int PlayerPick_Create(PlayerPick *self);
PlayerPick *PlayerPick_DestructFree(PlayerPick *self);
PlayerPick *PlayerPick_Destruct(PlayerPick *self);
PlayerPick *PlayerPick_Construct(PlayerPick *self);
void PlayerPick_New(void);

#endif
