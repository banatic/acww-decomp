/* The rooms' furniture, the items on it, the objects' states and switches, and whether a house
 * room is lit, kept the same on every system of the session through messages 24-29.
 *
 * A room is a scene whose map (func_0204d5c8: the town for 0, a house room for 1-5) holds the
 * furniture's item codes on layer 0 (the floor) and what stands on top on layer 1. While overlay
 * 4 shows a room (data_020e54a8 is 1), the room's objects stand on its cells
 * (func_ov004_0223cc10) and the map of the scene shown is data_021c80bc. Besides the map, a
 * scene's RoomCells record (room_cells.h) keeps each cell's switch and the steps of the items
 * 0x45dc-0x47d7.
 *
 * Every change is made here and sent to the others (kind 4), except where the session's host
 * (slot 0) decides: a system that is not the host sends its request to the host (kind 0), with
 * the message's relay bit set; the host applies it and sends it on to everyone with that bit
 * clear. The messages:
 *   24  an object's state            (RoomSync_SendState, RoomSync_ReceiveState; relayed)
 *   25  a house room lit or not      (RoomSync_SendLit, RoomSync_ReceiveLit; relayed)
 *   26  an item put on top           (RoomSync_PutItem, RoomSync_ReceivePutItem)
 *   27  furniture taken off the map  (RoomSync_TakeFurniture, RoomSync_ReceiveTakeFurniture)
 *   28  furniture put on the map     (RoomSync_PutFurniture, RoomSync_ReceivePutFurniture)
 *   29  a switch toggled             (RoomSync_ToggleSwitchAt, RoomSync_ReceiveToggle; kind 6, to
 *                                     the systems in the sender's scene)
 * The payloads are bit fields, the first field in the lowest bits (the ROOM_SYNC_* masks
 * below). */
#ifndef CLEAN_MAIN_ROOM_SYNC_H
#define CLEAN_MAIN_ROOM_SYNC_H

#include "autoload_2/vector.h"
#include "types.h"

struct RoomObject;

#define ROOM_SYNC_MSG_STATE 24
#define ROOM_SYNC_MSG_LIT 25
#define ROOM_SYNC_MSG_PUT_ITEM 26
#define ROOM_SYNC_MSG_TAKE_FURNITURE 27
#define ROOM_SYNC_MSG_PUT_FURNITURE 28
#define ROOM_SYNC_MSG_TOGGLE 29

/* The kinds the messages are sent with (Session_EndMessage). */
#define ROOM_SYNC_TO_HOST 0
#define ROOM_SYNC_TO_ALL 4
#define ROOM_SYNC_TO_SCENE 6

/* The items whose cells keep a step (RoomCells). */
#define ROOM_SYNC_STEP_ITEM_FIRST 0x45dc
#define ROOM_SYNC_STEP_ITEM_LAST 0x47d7

/* The code the map holds at the other cells a piece of furniture covers. */
#define ROOM_SYNC_ITEM_COVERED 0xf031

/* The music items: song n is item 0x1323 + n (ov004/music_player.h). */
#define ROOM_SYNC_SONG_ITEM_FIRST 0x1323
#define ROOM_SYNC_SONGS 70

/* No value: what a toggle sends with a state (vtable slot 0x70's second argument). */
#define ROOM_SYNC_NO_VALUE 0xff

/* Message 24, a word. */
#define ROOM_SYNC_STATE_SCENE 0x3f /* bits 0-5 */
#define ROOM_SYNC_STATE_LAYER_SHIFT 6
#define ROOM_SYNC_STATE_ON_SHIFT 7     /* whether the state shows the object on */
#define ROOM_SYNC_STATE_X_SHIFT 8      /* 4 bits */
#define ROOM_SYNC_STATE_Y_SHIFT 12     /* 4 bits */
#define ROOM_SYNC_STATE_STATE_SHIFT 16 /* 5 bits */
#define ROOM_SYNC_STATE_VALUE_SHIFT 21 /* 8 bits */
#define ROOM_SYNC_STATE_RELAY_SHIFT 29
#define ROOM_SYNC_STATE_MUSIC_SHIFT 30 /* the object is a music player (unk_00C 0x3a) */
#define ROOM_SYNC_STATE_FLAG_SHIFT 31

/* Message 25, a byte. */
#define ROOM_SYNC_LIT_SCENE 0x3f
#define ROOM_SYNC_LIT_ON 0x40
#define ROOM_SYNC_LIT_RELAY 0x80

/* Message 26, a word: x (bits 0-3), y (4-7), the item code (8-23). */
#define ROOM_SYNC_PUT_ITEM_Y_SHIFT 4
#define ROOM_SYNC_PUT_ITEM_CODE_SHIFT 8

/* Message 27, a word. */
#define ROOM_SYNC_TAKE_X_SHIFT 1 /* the layer is bit 0 */
#define ROOM_SYNC_TAKE_Y_SHIFT 5
#define ROOM_SYNC_TAKE_WITH_TOP_SHIFT 9
#define ROOM_SYNC_TAKE_ON_SHIFT 10
#define ROOM_SYNC_TAKE_CODE_SHIFT 11 /* 16 bits */

/* Message 28, a word: x (bits 0-3) first. */
#define ROOM_SYNC_PUT_Y_SHIFT 4
#define ROOM_SYNC_PUT_STEP_SHIFT 8
#define ROOM_SYNC_PUT_LAYER_SHIFT 12
#define ROOM_SYNC_PUT_ON_SHIFT 13
#define ROOM_SYNC_PUT_KEEPS_STEP_SHIFT 14
#define ROOM_SYNC_PUT_CODE_SHIFT 15 /* 16 bits */

/* Message 29, a halfword: the scene (bits 0-5) first. */
#define ROOM_SYNC_TOGGLE_LAYER_SHIFT 6
#define ROOM_SYNC_TOGGLE_X_SHIFT 7
#define ROOM_SYNC_TOGGLE_Y_SHIFT 11

void RoomSync_Nothing(void);
int RoomSync_IsFreeTopAt(int x, int y);
void RoomSync_ToggleSwitchAtPoint(int scene, const Vec3 *point, int layer);
void RoomSync_ToggleSwitchAt(u32 scene, u32 x, u32 y, u32 layer);
void RoomSync_SetLit(int scene, int lit);
void RoomSync_ApplyLit(int scene, int lit);
void RoomSync_SendLit(int scene, int lit, int kind);
void RoomSync_PutItem(int scene, int x, int y, u16 *code, u8 send);
void RoomSync_TakeFurniture(int scene, int x, int y, int layer, int on, u16 *code, int with_top, u8 send);
void RoomSync_PutFurniture(int scene, int x, int y, int layer, int on, int keeps_step, int step, u16 *code, u8 send);
int RoomSync_RequestStateAt(int x, int y, int layer, int state, u8 value, u8 flag, u8 send);
int RoomSync_RequestState(struct RoomObject *object, int state, int value, int flag);
int RoomSync_SetStateAt(int x, int y, int layer, int state, u8 value, u8 flag, u8 send);
int RoomSync_SetState(struct RoomObject *object, int state, int value, int flag);
int RoomSync_SendState(int x, int y, int layer, int state, u8 value, u8 flag, int kind);
void RoomSync_ReceiveToggle(const u16 *payload);
void RoomSync_ToggleAt(int scene, int x, int y, int layer, u8 flag);
void RoomSync_ReceivePutItem(int scene, const u32 *payload);
void RoomSync_ReceivePutFurniture(int scene, const u32 *payload);
void RoomSync_ReceiveTakeFurniture(int scene, const u32 *payload);
void RoomSync_ReceiveLit(const u8 *payload);
void RoomSync_ReceiveState(const u32 *payload);
int RoomSync_ApplyState(int scene, int x, int y, int layer, u8 state, u8 on, u8 music, u8 flag, u8 value);

#endif
