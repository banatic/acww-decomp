/* Overlay 098's part of the pockets scene (pockets_town.h). */
#include "pockets_town.h"

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/player_messages.h"
#include "main/session.h"
#include "main/sound.h"
#include "ov002/error_message.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov003/field_actor.h"

/* The pockets scene's words at 0x2e14-0x2e27: a point in the town (written by
 * func_0203162c, PocketsTown_FindPointAhead) and a tile (PocketsTown_FindTileAhead). */
static_assert(offsetof(PocketsScreen, pad_2e14) == 0x2e14 && offsetof(PocketsScreen, unk_2e20) == 0x2e20, "point");

static Vec3 *point_of(PocketsScreen *self)
{
    return (Vec3 *) (void *) self->pad_2e14;
}

static MenuScene *scene_of(PocketsScreen *self)
{
    return &self->base;
}

/* The items (main/item_code.h). */
#define ITEM_INSECT_FIRST 0x12b0 /* item 0x12b0 + kind (ov003/field_actor.h) */
#define ITEM_INSECT_LAST 0x12e7
#define ITEM_FISH_FIRST 0x12e8 /* item 0x12e8 + kind */
#define ITEM_FISH_LAST 0x131f
#define ITEM_TOOL_1369 0x1369 /* the two items held (record slot 5) that look for a tile ahead */
#define ITEM_TOOL_136A 0x136a
#define NO_KIND 0xff

/* The actions of the choice rows added here (PocketsScreen_RunAction) and the rows' texts. */
#define ACTION_INSECT 0x15
#define ACTION_TILE 0x16
#define ACTION_TILE_OR_DROP 0x17
#define ACTION_FISH 0x18
#define ACTION_LETTER 0x19
#define ACTION_SHOW 0x21
#define ROW_LET_GO 8
#define ROW_TILE 7
#define ROW_TILE_OR_DROP 6
#define ROW_LETTER 0x11
#define ROW_SHOW 0x1b

/* The scene's sub states (PocketsScreen_RunSubState). */
#define SUB_USE_REQUEST 0x29 /* PocketsScreen_WaitUseRequest29 */
#define SUB_INSECT 0x2c
#define SUB_TILE_REQUEST 0x2d
#define SUB_TILE_STATE 0x2e
#define SUB_TILE_DONE 0x2f /* PocketsScreen_WaitActorState */
#define SUB_FISH 0x30
#define SUB_LETTER_PLACING 0x33
#define SUB_LETTER_PLACED 0x34
#define SUB_SHOW 0x35
#define SUB_SHOWING 0x36
#define SUB_SHOWN 0x37
#define SUB_PUT_AWAY 0x38
#define SUB_SHOW_END 0x39

/* Error messages (PocketsScreen_ShowError) and the sound of a refusal. */
#define ERROR_3 3
#define ERROR_8 8
#define ERROR_13 13
#define SOUND_ERROR 0x73

/* Requests of main's for a session slot (as PocketsScreen_CheckUseItem's): -1 when none could
 * be made; func_020436a8 answers 1 done, 2 failed, others pending; func_020431b8 frees one. */
extern int func_02043db4(int slot, s32 *tile, int operation, int arg, u16 item);
extern int func_02043634(int slot, int kind, int item);
extern int func_020436a8(int request);
extern void func_020431b8(int request);
#define TILE_OPERATION 2
#define DROP_KIND 0x18

/* What func_020961a8 gives for a player (4: the one at this console); its position and its
 * angle are read. */
typedef struct PocketsTownPlayer {
    u8 unk_00[0x5c];
    Vec3 position; /* 0x5c */
    u8 unk_68[0x26];
    s16 angle; /* 0x8e */
} PocketsTownPlayer;
static_assert(offsetof(PocketsTownPlayer, angle) == 0x8e, "angle");
#define THIS_PLAYER 4

extern PocketsTownPlayer *func_020961a8(int player);
extern int func_020984e8(void);                               /* the current player's record */
extern u16 *func_02099728(int record);                        /* its item at 0x2406 (record slot 5) */
extern int func_02099020(int record, int bit);                /* a bit of its flags */
extern void *func_0204e414(void);                             /* the town map */
extern int data_021c80bc;                                     /* the town map, for func_0204f658 */
extern void func_0204f818(int *x, int *z, const Vec3 *point); /* a point's tile */
extern void func_0204f794(Vec3 *point, int x, int z);         /* a tile's point */
extern u16 *func_0204f5e0(void *map, int acre_x, int acre_z, int x, int z, int layer);
extern int func_0204f658(int map, int x, int z);
extern int func_0203162c(Vec3 *out, const Vec3 *from, int angle, int distance, int range, int arg);
extern int func_020644cc(int range);                 /* a random number below `range` */
extern void func_020779b8(u8 *packed, int x, int z); /* a point's x and z in 5 bytes */
extern int func_020960f8(int a, int b);

/* The pen (main's bytes, as menu_scene.c reads them), the pad and a close request (state flag
 * 0x80, pockets_screen.c). */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern PadState data_021fbe40;
#define PAD_A 0x0001
#define PAD_B 0x0002
extern int func_0206f56c(void);

/* The session the messages go through; a received record (main/player_messages.h, type 6). */
extern NetSession *data_020ccf94;
extern Heap *data_021c9b28;
extern u8 data_021ee418[0x100];
extern void *func_020900f0(void *record);
extern int func_02066830(void *dst, const void *src); /* copy a letter */
extern void func_02090100(void *record);
extern void func_02090140(void *record, int arg);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
#define LETTER_SIZE 0x100
#define MESSAGE_TO 4 /* where these messages are sent (as PlayerMessages_SetMode answers) */

/* Overlay 3's, for a player number. */
extern int func_ov003_0222780c(int player, int item, Vec3 *point);
extern void func_ov003_0222c3a8(Vec3 *point, int player);
extern int func_ov003_0222c364(int player);
extern int func_ov003_0222ea84(int player);
extern void func_ov003_0222e898(unsigned char kind, int player);
extern void func_ov003_0222eabc(int player, int angle);

/* Overlay 94's answer to whether an item can be used. */
extern int func_ov094_022999e4(unsigned int item);

/* The angles beside the player's that PocketsTown_FindTileAhead looks along: ahead, then
 * 0x1800 to either side. */
extern const s16 data_ov098_022a3240[3];

/* PocketsTown_DirectionStep's table and the bit that says it is filled. */
extern u32 data_ov098_022a3260;
extern PocketsTownStep data_ov098_022a3264[16];

/* func_ov098_022a27c0 (sub state 0x39): the window is kept up until func_020960f8(6, 4)
 * answers 0; then it is undimmed and the action ends. */
void PocketsTown_WaitShowEnd(PocketsScreen *self)
{
    ErrorMessage_UpdateWindow(&self->error);
    if (func_020960f8(6, 4) == 0) {
        ErrorMessage_UndimWindow(&self->error);
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov098_022a27c0, PocketsTown_WaitShowEnd)

/* func_ov098_022a27f0 (sub state 0x38): once the player puts away what it holds up, sub state
 * 0x39. */
void PocketsTown_WaitPutAway(PocketsScreen *self)
{
    ErrorMessage_UpdateWindow(&self->error);
    if (FieldActor_PlayerPutAwayShown()) {
        MenuScene_SetSubState(scene_of(self), SUB_SHOW_END);
    }
}
CLEAN_AS(func_ov098_022a27f0, PocketsTown_WaitPutAway)

/* func_ov098_022a2818 (sub state 0x37): a close request, a touch, A or B hides the window and
 * goes to sub state 0x38. */
void PocketsTown_WaitDismissShow(PocketsScreen *self)
{
    ErrorMessage_UpdateWindow(&self->error);
    if (func_0206f56c() != 0 || (data_021fbdd8 != 0 && data_021fbddc != 0) || (data_021fbe40.pressed & PAD_A) != 0 ||
        (data_021fbe40.pressed & PAD_B) != 0) {
        MenuScene_SetSubState(scene_of(self), SUB_PUT_AWAY);
        ErrorMessage_HideWindow(&self->error);
    }
}
CLEAN_AS(func_ov098_022a2818, PocketsTown_WaitDismissShow)

/* func_ov098_022a2884 (sub state 0x36): once the player holds the item up, sub state 0x37
 * with the window shown. */
void PocketsTown_WaitShowing(PocketsScreen *self)
{
    if (FieldActor_PlayerShowing() != 0) {
        MenuScene_SetSubState(scene_of(self), SUB_SHOWN);
        ErrorMessage_ShowWindow(&self->error);
    }
}
CLEAN_AS(func_ov098_022a2884, PocketsTown_WaitShowing)

/* func_ov098_022a28ac (sub state 0x35): the player asked to hold up the picked item; sub
 * state 0x36 once that is queued. */
void PocketsTown_ShowItem(PocketsScreen *self)
{
    if (FieldActor_PlayerShowItem(PocketsScreen_PlaceItem(self, self->slot)) != 0) {
        MenuScene_SetSubState(scene_of(self), SUB_SHOWING);
    }
}
CLEAN_AS(func_ov098_022a28ac, PocketsTown_ShowItem)

/* func_ov098_022a28d0 (action 33): sub state 0x35, the switch asked off and the cursor sprite
 * hidden. */
void PocketsTown_ActionShowItem(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), SUB_SHOW);
    PocketsScreen_RequestSwitchOff(self);
    PocketsScreen_HideCursorSprite(self);
}
CLEAN_AS(func_ov098_022a28d0, PocketsTown_ActionShowItem)

/* func_ov098_022a28ec: the point ahead is told to the others (message 5) and the picked letter
 * goes to the record at data_021ee418: kept there by this console when it is not linked or is
 * in slot 0, else sent to slot 0 in a message of type 6 (built in a block of the heap at
 * data_021c9b28). REQUIRES: that heap has room for the message (the allocation is not
 * checked). */
void PocketsTown_PassLetter(PocketsScreen *self)
{
    PocketsTown_SendPoint(self, 0, PLAYER_MESSAGE_PLACE);
    const void *letter = (const void *) (uintptr_t) PocketsScreen_PlaceLetter(self, self->slot);
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) == 0 || session->local_slot == 0) {
        u8 *record = data_021ee418;
        func_02066830(func_020900f0(record), letter);
        func_02090100(record);
        func_02090140(record, 0);
        return;
    }
    Heap *heap = data_021c9b28;
    u8 *message = Heap_AllocBack(heap, 1 + LETTER_SIZE);
    message[0] = PLAYER_MESSAGE_RECORD;
    MI_CpuCopy8(letter, message + 1, LETTER_SIZE);
    Session_BeginMessage(data_020ccf94);
    Session_AppendMessage(data_020ccf94, message, 1 + LETTER_SIZE);
    Session_EndMessage(data_020ccf94, PLAYER_MESSAGE_CATEGORY, 0);
    Heap_Free(heap, message);
}
CLEAN_AS(func_ov098_022a28ec, PocketsTown_PassLetter)

/* func_ov098_022a2994 (sub state 0x34): the action ends once func_ov003_0222c364 answers 0 for
 * this console's player. */
void PocketsTown_WaitLetterPlaced(PocketsScreen *self)
{
    if (func_ov003_0222c364(PocketsScreen_LocalSlotIfTaken(self)) == 0) {
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov098_022a2994, PocketsTown_WaitLetterPlaced)

/* func_ov098_022a29b0 (sub state 0x33): sub state 0x34 once func_ov003_0222c364 answers 1. */
void PocketsTown_WaitLetterPlacing(PocketsScreen *self)
{
    if (func_ov003_0222c364(PocketsScreen_LocalSlotIfTaken(self)) == 1) {
        MenuScene_SetSubState(scene_of(self), SUB_LETTER_PLACED);
    }
}
CLEAN_AS(func_ov098_022a29b0, PocketsTown_WaitLetterPlacing)

/* func_ov098_022a29d0 (action 25): the letter passed on (PocketsTown_PassLetter), the player
 * asked for state 0x89, the point ahead given to func_ov003_0222c3a8, the letter taken from
 * its place and sub state 0x33. */
void PocketsTown_ActionPlaceLetter(PocketsScreen *self)
{
    PocketsTown_PassLetter(self);
    FieldActor_PlayerRequestState89();
    func_ov003_0222c3a8(point_of(self), PocketsScreen_LocalSlotIfTaken(self));
    PocketsScreen_RemoveLetterAt(self, self->slot);
    MenuScene_SetSubState(scene_of(self), SUB_LETTER_PLACING);
}
CLEAN_AS(func_ov098_022a29d0, PocketsTown_ActionPlaceLetter)

/* The request at the tile ahead (PocketsTown_FindTileAhead's) for `item`, kept at `unk_c4`. */
static int request_tile(PocketsScreen *self, u16 item)
{
    s32 tile[2] = {(s32) self->unk_2e20, (s32) self->unk_2e24};
    self->unk_c4 = func_02043db4(data_020ccf94->local_slot, tile, TILE_OPERATION, 0, item);
    return self->unk_c4;
}

/* func_ov098_022a2a0c (action 23): with a tile ahead, its request for the picked item, waited
 * for in sub state 0x2d. Without one, or when it cannot be made, a drop request (kind 0x18)
 * waited for in sub state 0x29 with flag 0x1000; error 8 and the refusal's sound when that
 * cannot be made either. */
void PocketsTown_ActionTileOrDrop(PocketsScreen *self)
{
    int item = PocketsScreen_PlaceItem(self, self->slot);
    if (PocketsTown_FindTileAhead(self) != 0 && request_tile(self, (u16) item) != -1) {
        MenuScene_SetSubState(scene_of(self), SUB_TILE_REQUEST);
        return;
    }
    self->unk_c4 = func_02043634(data_020ccf94->local_slot, DROP_KIND, item);
    if (self->unk_c4 == -1) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, ERROR_8, 0xff, 0);
        SoundSys_PlaySe(SOUND_ERROR);
    } else {
        MenuScene_SetSubState(scene_of(self), SUB_USE_REQUEST);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_1000);
    }
}
CLEAN_AS(func_ov098_022a2a0c, PocketsTown_ActionTileOrDrop)

/* func_ov098_022a2ac8 (sub state 0x2e): the player asked for state 0x61 at the tile with the
 * picked item; once queued the place is emptied and sub state 0x2f follows. */
void PocketsTown_StartTileState61(PocketsScreen *self)
{
    Vec3 point;
    func_0204f794(&point, (int) self->unk_2e20, (int) self->unk_2e24);
    u16 item = PocketsScreen_PlaceItem(self, self->slot);
    if (FieldActor_PlayerRequestState61(&point, &item) != 0) {
        PocketsScreen_EmptyPlace(self, self->slot);
        MenuScene_SetSubState(scene_of(self), SUB_TILE_DONE);
    }
}
CLEAN_AS(func_ov098_022a2ac8, PocketsTown_StartTileState61)

/* func_ov098_022a2b1c (sub state 0x2d): the tile request done goes on to sub state 0x2e at
 * once; failed, the action ends with error 3 (flag 1). Either way it is freed (`unk_c4` -1);
 * nothing while it is pending. */
void PocketsTown_WaitTileRequest(PocketsScreen *self)
{
    switch (func_020436a8(self->unk_c4)) {
        case 1:
            MenuScene_SetSubState(scene_of(self), SUB_TILE_STATE);
            PocketsTown_StartTileState61(self);
            break;
        case 2:
            PocketsScreen_EndAction(self);
            PocketsScreen_ShowError(self, ERROR_3, 0xff, 1);
            break;
        default:
            return;
    }
    func_020431b8(self->unk_c4);
    self->unk_c4 = -1;
}
CLEAN_AS(func_ov098_022a2b1c, PocketsTown_WaitTileRequest)

/* func_ov098_022a2b6c (action 22): the request at the tile ahead for the picked item, waited
 * for in sub state 0x2d; error 13 (flag 1) without a tile or when it cannot be made. */
void PocketsTown_ActionTile(PocketsScreen *self)
{
    if (PocketsTown_FindTileAhead(self) != 0) {
        u16 item = PocketsScreen_PlaceItem(self, self->slot);
        if (request_tile(self, item) != -1) {
            MenuScene_SetSubState(scene_of(self), SUB_TILE_REQUEST);
            return;
        }
    }
    PocketsScreen_EndAction(self);
    PocketsScreen_ShowError(self, ERROR_13, 0xff, 1);
}
CLEAN_AS(func_ov098_022a2b6c, PocketsTown_ActionTile)

/* func_ov098_022a2bfc: while the record's slot 5 holds item 0x1369 or 0x136a, looks at the
 * tiles next to the player's, ahead and then 0x1800 to the left and right of its angle, for
 * one whose map object (layer 0) is 0xfc or 0xfd; the first found is kept at 0x2e20 and 0x2e24.
 * Whether one was found. */
int PocketsTown_FindTileAhead(PocketsScreen *self)
{
    u16 held = *func_02099728(func_020984e8());
    if (held != ITEM_TOOL_1369 && held != ITEM_TOOL_136A) {
        return 0;
    }
    PocketsTownPlayer *player = func_020961a8(THIS_PLAYER);
    int x = 0;
    int z = 0;
    void *map = func_0204e414();
    func_0204f818(&x, &z, &player->position);
    int angle = player->angle;
    for (int i = 0; i < 3; i++) {
        const PocketsTownStep *step =
            PocketsTown_DirectionStep((int) (uintptr_t) self, (s16) (angle + data_ov098_022a3240[i]));
        int tile_x = x + step->dx;
        int tile_z = z + step->dz;
        /* The tile's acre and its place in it: x >> 4 rounds down, x & 15 is the rest. */
        u16 *object = func_0204f5e0(map, tile_x >> 4, tile_z >> 4, tile_x & 15, tile_z & 15, 0);
        if (object != NULL && *object >= 0xfc && *object <= 0xfd) {
            self->unk_2e20 = (u32) tile_x;
            self->unk_2e24 = (u32) tile_z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov098_022a2bfc, PocketsTown_FindTileAhead)

/* func_ov098_022a2cd8: the step to the neighbouring tile in the direction of `angle` (16
 * sectors of 0x1000, from its bits 12-15): sector 0 is +z, 4 is +x, 8 is -z, 12 is -x, and each
 * diagonal takes the two sectors around it. The table is a static of the function, filled on
 * the first call (bit 0 of data_ov098_022a3260 says it was). */
PocketsTownStep *PocketsTown_DirectionStep(int unused, int angle)
{
    static const PocketsTownStep steps[16] = {
        {0, 1},  {1, 1},   {1, 1},   {1, 0},  {1, 0},  {1, -1}, {1, -1}, {0, -1},
        {0, -1}, {-1, -1}, {-1, -1}, {-1, 0}, {-1, 0}, {-1, 1}, {-1, 1}, {0, 1},
    };
    (void) unused;
    if ((data_ov098_022a3260 & 1) == 0) {
        for (int i = 0; i < 16; i++) {
            data_ov098_022a3264[i] = steps[i];
        }
        data_ov098_022a3260 |= 1;
    }
    return &data_ov098_022a3264[(angle >> 12) & 0xf];
}
CLEAN_AS(func_ov098_022a2cd8, PocketsTown_DirectionStep)

/* func_ov098_022a2dac: in a linked session, message 1 (PlayerMessages_Turn) with an insect's
 * kind and a turn in degrees plus 30. */
void PocketsTown_SendTurn(PocketsScreen *self, int kind, int turn)
{
    (void) self;
    if (Session_IsLinked(data_020ccf94)) {
        u8 message[3] = {PLAYER_MESSAGE_TURN, (u8) kind, (u8) turn};
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, message, sizeof message);
        Session_EndMessage(session, PLAYER_MESSAGE_CATEGORY, MESSAGE_TO);
    }
}
CLEAN_AS(func_ov098_022a2dac, PocketsTown_SendTurn)

/* func_ov098_022a2df4 (sub state 0x2c): the picked insect let go by this console's player
 * (func_ov003_0222e898 with its kind, func_ov003_0222eabc with an angle 30 degrees either side
 * of the player's, at random), the player looking (FieldActor_PlayerLook without the flag), the
 * others told (PocketsTown_SendTurn) and the place blinking. Nothing while func_ov003_0222ea84
 * answers for the player, which is answered.
 * QUIRK: an item that is not an insect gives the kind 0xff; the angle is kept in 16 bits. */
int PocketsTown_LetInsectGo(PocketsScreen *self)
{
    int player = PocketsScreen_LocalSlotIfTaken(self);
    int busy = func_ov003_0222ea84(player);
    if (busy != 0) {
        return busy;
    }
    u16 item = PocketsScreen_PlaceItem(self, self->slot);
    int kind = item >= ITEM_INSECT_FIRST && item <= ITEM_INSECT_LAST ? item - ITEM_INSECT_FIRST : NO_KIND;
    int turn = (u8) func_020644cc(60);
    s16 angle = (s16) (0xb6 * (turn - 30));
    angle = (s16) (angle + func_020961a8(THIS_PLAYER)->angle);
    func_ov003_0222e898((u8) kind, player);
    func_ov003_0222eabc(player, angle);
    FieldActor_PlayerLook(0);
    PocketsTown_SendTurn(self, (u8) kind, turn);
    return (int) (uintptr_t) PocketsScreen_StartBlinkSlot(self);
}
CLEAN_AS(func_ov098_022a2df4, PocketsTown_LetInsectGo)

/* func_ov098_022a2e9c (action 21): sub state 0x2c, run at once. */
int PocketsTown_ActionInsect(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), SUB_INSECT);
    return PocketsTown_LetInsectGo(self);
}
CLEAN_AS(func_ov098_022a2e9c, PocketsTown_ActionInsect)

/* func_ov098_022a2eb4: message 2 with the point ahead and `id`. */
void PocketsTown_SendPlaceId(PocketsScreen *self, int id)
{
    PocketsTown_SendPoint(self, (char) id, PLAYER_MESSAGE_PLACE_ID);
}
CLEAN_AS(func_ov098_022a2eb4, PocketsTown_SendPlaceId)

/* func_ov098_022a2ec0: in a linked session, a message of `type` (PlayerMessages_Place: 2 or 5)
 * with `id` and the point ahead's x and z packed in 5 bytes. */
void PocketsTown_SendPoint(PocketsScreen *self, char id, char type)
{
    if (Session_IsLinked(data_020ccf94)) {
        u8 message[7];
        u8 packed[5];
        const Vec3 *point = point_of(self);
        message[0] = (u8) type;
        message[1] = (u8) id;
        func_020779b8(packed, point->x, point->z);
        MI_CpuCopy8(packed, message + 2, sizeof packed);
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, message, sizeof message);
        Session_EndMessage(session, PLAYER_MESSAGE_CATEGORY, MESSAGE_TO);
    }
}
CLEAN_AS(func_ov098_022a2ec0, PocketsTown_SendPoint)

/* func_ov098_022a2f2c (sub state 0x30): the picked fish placed at the point ahead by this
 * console's player (func_ov003_0222780c); once it is, the others told with its kind
 * (PocketsTown_SendPlaceId), the player looking (FieldActor_PlayerLook with the flag) and the
 * place blinking. QUIRK: an item that is not a fish gives the kind 0xff. */
void PocketsTown_PlaceFish(PocketsScreen *self)
{
    int player = PocketsScreen_LocalSlotIfTaken(self);
    int item = PocketsScreen_PlaceItem(self, self->slot);
    if (func_ov003_0222780c(player, item, point_of(self)) != 0) {
        u16 code = (u16) item;
        u8 kind = code >= ITEM_FISH_FIRST && code <= ITEM_FISH_LAST ? (u8) (code - ITEM_FISH_FIRST) : NO_KIND;
        PocketsTown_SendPlaceId(self, kind);
        FieldActor_PlayerLook(1);
        PocketsScreen_StartBlinkSlot(self);
    }
}
CLEAN_AS(func_ov098_022a2f2c, PocketsTown_PlaceFish)

/* func_ov098_022a2fa8 (action 24): sub state 0x30, run at once. */
void PocketsTown_ActionFish(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), SUB_FISH);
    PocketsTown_PlaceFish(self);
}
CLEAN_AS(func_ov098_022a2fa8, PocketsTown_ActionFish)

/* func_ov098_022a2fc0: func_0203162c looks for a point ahead of the player (along its angle,
 * from 0x7800, over a range) and keeps it at 0x2e14; whether it found one. The range depends
 * on the town map's bits at the player's position (func_0204f658 at x >> 17, z >> 17): with
 * bits 0x7f000 or 8 it is 0x1b58 for a letter and 0x1810 otherwise, without them 0xde8; a
 * letter is not looked for without them. */
int PocketsTown_FindPointAhead(PocketsScreen *self, int for_letter)
{
    PocketsTownPlayer *player = func_020961a8(THIS_PLAYER);
    int bits = func_0204f658(data_021c80bc, player->position.x >> 17, player->position.z >> 17);
    int marked = (bits & 0x7f000) != 0 || (bits & 8) != 0;
    int range;
    if (for_letter) {
        if (!marked) {
            return 0;
        }
        range = 0x1b58;
    } else {
        range = marked ? 0xa00 + 0xe10 : 0xa00 + 0x3e8;
    }
    return func_0203162c(point_of(self), &player->position, player->angle, 0x7800, range, 0xc);
}
CLEAN_AS(func_ov098_022a2fc0, PocketsTown_FindPointAhead)

/* func_ov098_022a3060: for a letter of kind 4 (PocketsScreen_AddLetterEntries): flag 8 cleared;
 * when not linked and a point ahead is found for a letter, the row of action 25 and flag 8. */
void PocketsTown_AddLetterRows(PocketsScreen *self)
{
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_08);
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    if (PocketsTown_FindPointAhead(self, 1) == 0) {
        return;
    }
    ChoiceEntries_Add(&self->entries, ROW_LETTER, ACTION_LETTER);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_08);
}
CLEAN_AS(func_ov098_022a3060, PocketsTown_AddLetterRows)

static int is_insect(u16 item)
{
    return item >= ITEM_INSECT_FIRST && item <= ITEM_INSECT_LAST;
}

static int is_fish(u16 item)
{
    return item >= ITEM_FISH_FIRST && item <= ITEM_FISH_LAST;
}

/* The items that get the row of action 23. */
static int is_tile_or_drop_item(u16 item)
{
    return item == 0x137c || (item >= 0x1408 && item <= 0x1428) || (item >= 0x1471 && item <= 0x1491) ||
           (item >= 0x14fe && item <= 0x1517) || (item >= 0x151d && item <= 0x151e) || item == 0x1567;
}

/* func_ov098_022a30a4: the rows for a grid item (PocketsScreen_AddGridEntries): an insect or a
 * fish can be shown (action 33); an insect let go (21); a fish placed (24) when a point ahead is
 * found; some items (is_tile_or_drop_item) get action 23; others action 22 when there is a tile
 * ahead (PocketsTown_FindTileAhead). */
void PocketsTown_AddItemRows(PocketsScreen *self, u16 item)
{
    if (is_insect(item) || is_fish(item)) {
        ChoiceEntries_Add(&self->entries, ROW_SHOW, ACTION_SHOW);
    }
    if (is_insect(item)) {
        ChoiceEntries_Add(&self->entries, ROW_LET_GO, ACTION_INSECT);
        return;
    }
    if (is_fish(item)) {
        if (PocketsTown_FindPointAhead(self, 0) != 0) {
            ChoiceEntries_Add(&self->entries, ROW_LET_GO, ACTION_FISH);
        }
        return;
    }
    if (is_tile_or_drop_item(item)) {
        ChoiceEntries_Add(&self->entries, ROW_TILE_OR_DROP, ACTION_TILE_OR_DROP);
        return;
    }
    if (PocketsTown_FindTileAhead(self) != 0) {
        ChoiceEntries_Add(&self->entries, ROW_TILE, ACTION_TILE);
    }
}
CLEAN_AS(func_ov098_022a30a4, PocketsTown_AddItemRows)

/* func_ov098_022a31d8: whether `item` can be used (PocketsScreen_CanUseItem asks this one when
 * data_020e54a8 is 0): items 0x14fe-0x1517 and 0x151d-0x151e not while the current player's
 * record has bit 1 set, others as overlay 94 says. */
int PocketsTown_CanUseItem(PocketsScreen *self, unsigned int item)
{
    (void) self;
    if (func_02099020(func_020984e8(), 1) != 0) {
        if ((item >= 0x14fe && item <= 0x1517) || (item >= 0x151d && item <= 0x151e)) {
            return 0;
        }
    }
    return func_ov094_022999e4(item);
}
CLEAN_AS(func_ov098_022a31d8, PocketsTown_CanUseItem)
