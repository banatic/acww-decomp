/* The pockets swap scene of overlay 107 (pockets_swap.h): its destructors and flags, the actions
 * that give a pocket item up, the cursor and the choice, the places, the sub states, the states
 * and the vtable's slots. */
#include "pockets_swap.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/cell_layer_sprite.h"
#include "main/collision_query.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/item_form.h"
#include "main/item_record.h"
#include "main/main_random.h"
#include "main/packed_bytes.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/tile_changes.h"
#include "main/tile_requests.h"
#include "ov002/key_repeat.h"
#include "ov003/field_actor.h"
#include "ov003/fish_shadow.h"
#include "ov003/town_insect.h"
#include "ov004/member_pointer.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PocketsSwap, flags) == 0x94, "flags");
static_assert(offsetof(PocketsSwap, grab_dx) == 0x9c && offsetof(PocketsSwap, held_x) == 0xa4, "places");
static_assert(offsetof(PocketsSwap, request) == 0xac && offsetof(PocketsSwap, held_kind) == 0xb5, "request");
static_assert(offsetof(PocketsSwap, cursor) == 0xb8 && offsetof(PocketsSwap, return_state) == 0xbb, "bytes");
static_assert(offsetof(PocketsSwap, delay) == 0xbe && offsetof(PocketsSwap, point) == 0xc0, "bytes");
static_assert(offsetof(PocketsSwap, tile_x) == 0xcc && offsetof(PocketsSwap, task) == 0xd4, "tile");
static_assert(offsetof(PocketsSwap, grid) == 0x10c && offsetof(PocketsSwap, letters) == 0xb6c, "ov094 objects");
static_assert(offsetof(PocketsSwap, wallet) == 0xb94 && offsetof(PocketsSwap, popup) == 0x21cc, "wallet");
static_assert(offsetof(PocketsSwap, glide) == 0x229c && offsetof(PocketsSwap, cursor_sprite) == 0x22b4, "glide");
static_assert(offsetof(PocketsSwap, choice) == 0x2318 && offsetof(PocketsSwap, entries) == 0x2700, "choice");
static_assert(offsetof(PocketsSwap, error) == 0x270c && offsetof(PocketsSwap, panel) == 0x2828, "error");
static_assert(sizeof(PocketsSwap) == 0x29f4, "size (func_ov107_0229e1cc)");

/* The scene's vtable. */
extern const u8 data_ov107_0229e3b8[];

/* The session (main/session.h): this system's slot and player. */
extern NetSession *data_020ccf94;

/* The pen (autoload_2/input.c): its place, down, and gone down or up this frame. */
extern u8 data_021f6c58, data_021f6c54;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define POCKETS_SWAP_PAD_A 0x0001
#define POCKETS_SWAP_PAD_B 0x0002

/* The eight turns tried from the player's facing for water (PocketsSwap_FindWater): 0, then
 * +-0x2000, +-0x4000, +-0x6000 and 0x7fff. */
extern const s16 data_ov107_0229e280[8];
#define POCKETS_SWAP_WATER_TURNS 8

/* What the parent (overlay 92's) is told (func_ov092_02299324): the scene ends; and when the
 * scene closes (func_ov092_0229929c). */
extern void func_ov092_02299324(Process *parent, int code, int flag);
extern void func_ov092_0229929c(Process *parent);
#define POCKETS_SWAP_PARENT_CODE_END 0x44

/* The SDK's byte copy, as the ROM calls it. */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The item ranges (main/creature_table.h, ov003/town_insect.h). */
#define POCKETS_SWAP_INSECT_FIRST 0x12b0 /* 0x12b0 + an insect's kind */
#define POCKETS_SWAP_INSECT_LAST 0x12e7
#define POCKETS_SWAP_FISH_FIRST 0x12e8 /* 0x12e8 + a fish's kind */
#define POCKETS_SWAP_FISH_LAST 0x131f
#define POCKETS_SWAP_NO_ITEM 0xfff1   /* main/item_code.h's ITEM_CODE_NONE */
#define POCKETS_SWAP_NO_STATE 0xf1    /* PocketsSwap_PlaceItemState off the grid */
#define POCKETS_SWAP_ITEM_156B 0x156b /* drawn again by CurrentPockets_DrawFor156B */

/* The game's mode the scene was opened in (GroupParams_Mode). */
#define POCKETS_SWAP_MODE_ITEM_29 0x29
#define POCKETS_SWAP_MODE_ITEM_2A 0x2a
#define POCKETS_SWAP_MODE_INSECT 0x2b
#define POCKETS_SWAP_MODE_FISH 0x2c

/* The session message the scene sends (handler 0x16, kind 4) and their first bytes. */
#define POCKETS_SWAP_MESSAGE_HANDLER 0x16
#define POCKETS_SWAP_MESSAGE_KIND 4
#define POCKETS_SWAP_MESSAGE_INSECT 1       /* the insect's kind and angle */
#define POCKETS_SWAP_MESSAGE_FISH 2         /* the fish's kind and the point it goes to */
#define POCKETS_SWAP_MESSAGE_FREE_TILE 0x17 /* this system's slot */

/* The panel's button that closes the scene without a swap, and the message shown when a tile
 * request cannot be asked or is refused. */
#define POCKETS_SWAP_PANEL_BUTTON 9
#define POCKETS_SWAP_MESSAGE_REFUSED 3
#define POCKETS_SWAP_RETURN_HERE 0xff

/* The display layer the scene scrolls. */
#define POCKETS_SWAP_LAYER 6

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov107_0229e420; /* the actions' guard */
extern u32 data_ov107_0229e424; /* the sub states' guard */
extern u32 data_ov107_0229e428; /* the states' guard */
extern MemberPointer data_ov107_0229e42c[POCKETS_SWAP_ACTION_CANCEL];
extern MemberPointer data_ov107_0229e44c[POCKETS_SWAP_STATES];
extern MemberPointer data_ov107_0229e474[POCKETS_SWAP_SUB_STATES];
extern const MemberPointer data_ov107_0229e2a0, data_ov107_0229e2a8, data_ov107_0229e2b0, data_ov107_0229e2b8,
    data_ov107_0229e2c8, data_ov107_0229e2d0, data_ov107_0229e2d8, data_ov107_0229e2e0, data_ov107_0229e2e8,
    data_ov107_0229e2f0, data_ov107_0229e2f8, data_ov107_0229e300, data_ov107_0229e308, data_ov107_0229e310,
    data_ov107_0229e318, data_ov107_0229e320, data_ov107_0229e328, data_ov107_0229e330, data_ov107_0229e338,
    data_ov107_0229e340, data_ov107_0229e348, data_ov107_0229e350, data_ov107_0229e358, data_ov107_0229e360,
    data_ov107_0229e368, data_ov107_0229e370, data_ov107_0229e378, data_ov107_0229e380, data_ov107_0229e388,
    data_ov107_0229e390, data_ov107_0229e398, data_ov107_0229e3a0, data_ov107_0229e3a8;

static MenuScene *psw_scene(PocketsSwap *self)
{
    return &self->base;
}

static PagedChoice *psw_choice(PocketsSwap *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *psw_cursor_cells(PocketsSwap *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static Process *psw_parent(PocketsSwap *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3). */
static void psw_update_cursor_sprite(PocketsSwap *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}

/* The popup drawn through its class (vtable slot 2). */
static void psw_draw_popup(PocketsSwap *self)
{
    void (*const *vtable)(Popup *) = (void (*const *)(Popup *)) self->popup.vtable;
    vtable[2](&self->popup);
}

/* The pen went down this frame. */
static int psw_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x2705 + row. */
static u8 psw_entry_value(PocketsSwap *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(PocketsSwap, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

static int psw_is_insect(unsigned int item)
{
    return item >= POCKETS_SWAP_INSECT_FIRST && item <= POCKETS_SWAP_INSECT_LAST;
}

static int psw_is_fish(unsigned int item)
{
    return item >= POCKETS_SWAP_FISH_FIRST && item <= POCKETS_SWAP_FISH_LAST;
}

/* A message of `size` bytes to the session, when it is linked. */
static void psw_send(const u8 *message, int size)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, size);
    Session_EndMessage(session, POCKETS_SWAP_MESSAGE_HANDLER, POCKETS_SWAP_MESSAGE_KIND);
}

/* The members' destructors, last member first, then the base's. */
static void psw_destroy_members(PocketsSwap *self)
{
    self->base.vtable = data_ov107_0229e3b8;
    ButtonPanel_Destroy(&self->panel);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(psw_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(psw_scene(self));
}

/* func_ov107_0229c180 (vtable slot 0x40) */
PocketsSwap *PocketsSwap_Destroy(PocketsSwap *self)
{
    psw_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov107_0229c180, PocketsSwap_Destroy)

/* func_ov107_0229c208 (vtable slot 0x44) */
PocketsSwap *PocketsSwap_Delete(PocketsSwap *self)
{
    psw_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov107_0229c208, PocketsSwap_Delete)

/* func_ov107_0229c294 */
void PocketsSwap_ClearFlags(PocketsSwap *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov107_0229c294, PocketsSwap_ClearFlags)

/* func_ov107_0229c2a4 */
void PocketsSwap_SetFlags(PocketsSwap *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov107_0229c2a4, PocketsSwap_SetFlags)

/* func_ov107_0229c2b4: 1 when any of `flags` is set. */
unsigned int PocketsSwap_TestFlags(PocketsSwap *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov107_0229c2b4, PocketsSwap_TestFlags)

/* func_ov107_0229c2c8: what the field holds of the item being got is let go, by the mode: in
 * modes 0x29 and 0x2a with `free_tile`, the tile held for this system's slot is freed and, when
 * the session is linked, its peers are told (message 0x17 with the slot); in mode 0x2b the held
 * insect ends (told to the peers); in mode 0x2c the hooked fish (GroupParams_C80) ends. */
void PocketsSwap_EndGetting(PocketsSwap *self, int free_tile)
{
    unsigned int mode = GroupParams_Mode();
    int slot = PocketsSwap_OwnSlot(self);

    switch (mode) {
        case POCKETS_SWAP_MODE_ITEM_29:
        case POCKETS_SWAP_MODE_ITEM_2A:
            if (free_tile == 0) {
                return;
            }
            TileChanges_FreeHeld(slot);
            if (Session_IsLinked(data_020ccf94) == 0) {
                return;
            }
            {
                u8 message[2] = {POCKETS_SWAP_MESSAGE_FREE_TILE, (u8) slot};
                psw_send(message, sizeof(message));
            }
            break;
        case POCKETS_SWAP_MODE_INSECT:
            TownInsect_EndHeld((u8) slot, 1);
            break;
        case POCKETS_SWAP_MODE_FISH:
            PlayerFish_EndForShadow((FishShadow *) (void *) GroupParams_C80());
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov107_0229c2c8, PocketsSwap_EndGetting)

/* func_ov107_0229c354: this system's slot in the session when the slot is taken, else 0. */
int PocketsSwap_OwnSlot(PocketsSwap *self)
{
    (void) self;
    int slot = data_020ccf94->local_slot;
    if (Session_IsSlotTaken(data_020ccf94, slot) != 0) {
        return (u8) slot;
    }
    return 0;
}
CLEAN_AS(func_ov107_0229c354, PocketsSwap_OwnSlot)

/* func_ov107_0229c378 (sub state 0x17): the player asked to go to the centre of the tile
 * (`tile_x`, `tile_z`) with the item given up (FieldActor_PlayerRequestState61); once accepted,
 * the item got takes its place and sub state 0x14 waits for the player. */
void PocketsSwap_SendPlayerToTile(PocketsSwap *self)
{
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) self->tile_x, (u32) self->tile_z);
    u16 item = (u16) PocketsSwap_PlaceItem(self, self->slot);
    if (FieldActor_PlayerRequestState61(&centre, &item) != 0) {
        PocketsSwap_TakeNewItem(self);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_FINISH_PLAYER);
    }
}
CLEAN_AS(func_ov107_0229c378, PocketsSwap_SendPlayerToTile)

/* func_ov107_0229c3c4 (sub state 0x16): the tile request's answer: 1 sends the player to the
 * tile (sub state 0x17, run at once), 2 refuses (the action ends with message 3); with either
 * the request is released. */
void PocketsSwap_WaitTileAnswer(PocketsSwap *self)
{
    int answer = TileRequests_Answer((u32) self->request);
    if (answer == 1) {
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TILE_PLAYER);
        PocketsSwap_SendPlayerToTile(self);
    } else if (answer == 2) {
        PocketsSwap_EndAction(self);
        PocketsSwap_ShowMessage(self, POCKETS_SWAP_MESSAGE_REFUSED, POCKETS_SWAP_RETURN_HERE);
    } else {
        return;
    }
    TileRequests_Release(self->request);
    self->request = -1;
}
CLEAN_AS(func_ov107_0229c3c4, PocketsSwap_WaitTileAnswer)

/* func_ov107_0229c414 (action 3): tile operation 2 asked for at the player's tile with the item
 * given up. When it cannot be asked the action ends with message 3; else the tile held for this
 * system's player gives `tile_x` (its high byte) and `tile_z` (its low byte), and sub state 0x16
 * waits for the answer. */
void PocketsSwap_RunActionTileOp(PocketsSwap *self)
{
    int item = PocketsSwap_PlaceItem(self, self->slot);
    NetSession *session = data_020ccf94;

    self->request = TileRequests_AskAtActorTileOp(session->local_slot, 2, 0, item);
    if (self->request == -1) {
        PocketsSwap_EndAction(self);
        PocketsSwap_ShowMessage(self, POCKETS_SWAP_MESSAGE_REFUSED, POCKETS_SWAP_RETURN_HERE);
        return;
    }
    u16 tile = *TileChanges_HeldTileOf(session->local_player);
    self->tile_x = tile >> 8;
    self->tile_z = tile & 0xff;
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TILE_ANSWER);
}
CLEAN_AS(func_ov107_0229c414, PocketsSwap_RunActionTileOp)

/* func_ov107_0229c488: when the session is linked, its peers told a fish of `kind` goes to
 * `point` (message 2: the kind's byte and the point's x and z packed in five bytes). */
void PocketsSwap_SendFishPoint(PocketsSwap *self, int kind)
{
    if (Session_IsLinked(data_020ccf94) == 0) {
        return;
    }
    u8 message[7];
    u8 packed[5];
    message[0] = POCKETS_SWAP_MESSAGE_FISH;
    message[1] = (u8) kind;
    PackedBytes_PackPoint(packed, self->point.x, self->point.z);
    MI_CpuCopy8(packed, &message[2], sizeof(packed));
    psw_send(message, sizeof(message));
}
CLEAN_AS(func_ov107_0229c488, PocketsSwap_SendFishPoint)

/* func_ov107_0229c4f0 (sub state 0x11): after `delay` frames, the fish given up placed in the
 * water from the pockets (PlayerFish_PlaceFromPockets at `point`); once it is, the peers are
 * told its kind (0xff for an item that is no fish), 20 frames counted before the scene finishes
 * (sub state 0x13) and the item got takes its place. */
void PocketsSwap_ReleaseFish(PocketsSwap *self)
{
    if (self->delay != 0) {
        self->delay--;
        return;
    }
    int slot = PocketsSwap_OwnSlot(self);
    int item = PocketsSwap_PlaceItem(self, self->slot);
    if (PlayerFish_PlaceFromPockets(slot, item, &self->point) == 0) {
        return;
    }
    u16 code = (u16) item;
    int kind = psw_is_fish(code) ? code - POCKETS_SWAP_FISH_FIRST : -1;
    PocketsSwap_SendFishPoint(self, (u8) kind);
    self->delay = 0x14;
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_FINISH_DELAY);
    PocketsSwap_TakeNewItem(self);
}
CLEAN_AS(func_ov107_0229c4f0, PocketsSwap_ReleaseFish)

/* func_ov107_0229c588 (action 2): what is being got let go (its tile freed), 5 frames, then
 * the fish's release (sub state 0x11, run at once). */
void PocketsSwap_RunActionReleaseFish(PocketsSwap *self)
{
    PocketsSwap_EndGetting(self, 1);
    self->delay = 5;
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_RELEASE_FISH);
    PocketsSwap_ReleaseFish(self);
}
CLEAN_AS(func_ov107_0229c588, PocketsSwap_RunActionReleaseFish)

/* func_ov107_0229c5b0: 1 when there is water a fish can be put in, its point kept in `point`.
 * In mode 0x2c that is where the hooked fish started (PlayerFish_HookedStart); else water found
 * ahead of this system's player within eight turns from its facing. */
int PocketsSwap_FindWater(PocketsSwap *self)
{
    unsigned int mode = GroupParams_Mode();
    int slot = PocketsSwap_OwnSlot(self);
    if (mode == POCKETS_SWAP_MODE_FISH) {
        return PlayerFish_HookedStart(&self->point, slot);
    }

    Actor *player = SessionPlayers_ActorOf(SESSION_PLAYERS_OWN);
    const Vec3 *from = &player->position;
    s16 facing = player->angle[1];
    for (int i = 0; i < POCKETS_SWAP_WATER_TURNS; i++) {
        s16 angle = (s16) (facing + data_ov107_0229e280[i]);
        if (CollisionQuery_FindWaterAhead(&self->point, from, angle, 0x7800, 0xa00, 0xc) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov107_0229c5b0, PocketsSwap_FindWater)

/* func_ov107_0229c628: when the session is linked, its peers told an insect of `kind` was let go
 * `turn` steps of 0xb6 (less 30) from the player's facing (message 1: the two bytes). */
void PocketsSwap_SendInsectRelease(PocketsSwap *self, int kind, int turn)
{
    (void) self;
    if (Session_IsLinked(data_020ccf94) == 0) {
        return;
    }
    u8 message[3] = {POCKETS_SWAP_MESSAGE_INSECT, (u8) kind, (u8) turn};
    psw_send(message, sizeof(message));
}
CLEAN_AS(func_ov107_0229c628, PocketsSwap_SendInsectRelease)

/* func_ov107_0229c670 (sub state 0x10): once this system's player holds no insect, the insect
 * given up is taken in hand (its kind, 0xff for an item that is no insect) and let go at the
 * player's facing turned by a random -30 to 29 steps of 0xb6; the player looks, the peers are
 * told, sub state 0x12 waits for the insect to go and the item got takes its place. */
void PocketsSwap_ReleaseInsect(PocketsSwap *self)
{
    int slot = PocketsSwap_OwnSlot(self);
    if (TownInsect_HeldState(slot) != 0) {
        return;
    }
    u16 item = (u16) PocketsSwap_PlaceItem(self, self->slot);
    int kind = psw_is_insect(item) ? item - POCKETS_SWAP_INSECT_FIRST : -1;
    int turn = (u8) MainRandom_Below(0x3c);
    s16 angle = (s16) (0xb6 * (turn - 0x1e));
    Actor *player = SessionPlayers_ActorOf(SESSION_PLAYERS_OWN);
    angle = (s16) (angle + player->angle[1]);
    TownInsect_TakeHeld((u8) kind, slot);
    TownInsect_LetGo(slot, angle);
    FieldActor_PlayerLook(0);
    PocketsSwap_SendInsectRelease(self, (u8) kind, turn);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_INSECT_GONE);
    PocketsSwap_TakeNewItem(self);
}
CLEAN_AS(func_ov107_0229c670, PocketsSwap_ReleaseInsect)

/* func_ov107_0229c720 (action 0): what is being got let go (its tile freed), then the insect's
 * release (sub state 0x10, run at once). */
void PocketsSwap_RunActionReleaseInsect(PocketsSwap *self)
{
    PocketsSwap_EndGetting(self, 1);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_RELEASE_INSECT);
    PocketsSwap_ReleaseInsect(self);
}
CLEAN_AS(func_ov107_0229c720, PocketsSwap_RunActionReleaseInsect)

/* func_ov107_0229c740 (sub state 0x15): the drop request carried out (TileRequests_Carry): 1
 * lets go what is being got (its tile kept), the item got takes the place and 10 frames are
 * counted before the scene finishes (sub state 0x13); 2 refuses (the action ends with message
 * 3). With either the request is released. */
void PocketsSwap_WaitDropCarried(PocketsSwap *self)
{
    switch (TileRequests_Carry(self->request)) {
        case 1:
            PocketsSwap_EndGetting(self, 0);
            PocketsSwap_TakeNewItem(self);
            TileRequests_Release(self->request);
            self->delay = 10;
            MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_FINISH_DELAY);
            self->request = -1;
            break;
        case 2:
            TileRequests_Release(self->request);
            PocketsSwap_EndAction(self);
            PocketsSwap_ShowMessage(self, POCKETS_SWAP_MESSAGE_REFUSED, POCKETS_SWAP_RETURN_HERE);
            self->request = -1;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov107_0229c740, PocketsSwap_WaitDropCarried)

/* func_ov107_0229c7b0 (action 1): the item given up asked to be dropped, at the player's tile in
 * mode 0x29 (TileRequests_AskAtActorTile), else by TileRequests_AskDrop12. When it cannot be
 * asked the action ends with message 3; else sub state 0x15 waits for it. */
void PocketsSwap_RunActionDrop(PocketsSwap *self)
{
    int item = PocketsSwap_PlaceItem(self, self->slot);
    if (GroupParams_Mode() == POCKETS_SWAP_MODE_ITEM_29) {
        self->request = TileRequests_AskAtActorTile(data_020ccf94->local_slot, item);
    } else {
        self->request = TileRequests_AskDrop12(data_020ccf94->local_slot, item);
    }
    if (self->request == -1) {
        PocketsSwap_EndAction(self);
        PocketsSwap_ShowMessage(self, POCKETS_SWAP_MESSAGE_REFUSED, POCKETS_SWAP_RETURN_HERE);
    } else {
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_DROP_CARRY);
    }
}
CLEAN_AS(func_ov107_0229c7b0, PocketsSwap_RunActionDrop)

/* func_ov107_0229c824: the cursor moved by `keys` (KeyRepeat_Has*): in the grid
 * (PocketsSwap_MoveCursorInGrid), or up from POCKETS_SWAP_BELOW to the grid's last place (the
 * cursor sprite turning to set A). The wrap flags are cleared first. 1 when the cursor changed
 * place; 0 at once when `keys` is 0. */
int PocketsSwap_MoveCursor(PocketsSwap *self, int keys)
{
    u8 before = self->cursor;

    PocketsSwap_ClearFlags(self, POCKETS_SWAP_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (PocketsSwap_IsGridPlace(self, self->cursor) != 0) {
        PocketsSwap_MoveCursorInGrid(self, keys);
    } else if (self->cursor == POCKETS_SWAP_BELOW && KeyRepeat_HasUp(keys) != 0) {
        self->cursor = POCKETS_SWAP_GRID_LAST;
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov107_0229c824, PocketsSwap_MoveCursor)

/* func_ov107_0229c894: the cursor in the grid (3 rows of 5). Left (unless up is also held off
 * the top row) and right (unless down is also held) wrap over the edges within the row, with
 * their flag; when the move did not wrap, up stops at the top row and down from the bottom row
 * goes to POCKETS_SWAP_BELOW, the cursor sprite turning to set B. */
void PocketsSwap_MoveCursorInGrid(PocketsSwap *self, int keys)
{
    int column = self->cursor;
    int row = 0;
    while (column >= POCKETS_SWAP_COLUMNS) {
        column -= POCKETS_SWAP_COLUMNS;
        row++;
    }

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (KeyRepeat_HasUp(keys) == 0 || row == 0) {
            if (column == 0) {
                self->cursor += POCKETS_SWAP_COLUMNS - 1;
                PocketsSwap_SetFlags(self, POCKETS_SWAP_FLAG_WRAPPED_LEFT);
            } else {
                self->cursor -= 1;
            }
        }
    } else if (KeyRepeat_HasRight(keys) != 0 && KeyRepeat_HasDown(keys) == 0) {
        if (column == POCKETS_SWAP_COLUMNS - 1) {
            self->cursor -= POCKETS_SWAP_COLUMNS - 1;
            PocketsSwap_SetFlags(self, POCKETS_SWAP_FLAG_WRAPPED_RIGHT);
        } else {
            self->cursor += 1;
        }
    }

    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= POCKETS_SWAP_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < POCKETS_SWAP_ROWS - 1) {
            self->cursor += POCKETS_SWAP_COLUMNS;
        } else {
            self->cursor = POCKETS_SWAP_BELOW;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}
CLEAN_AS(func_ov107_0229c894, PocketsSwap_MoveCursorInGrid)

/* func_ov107_0229c990: the choice of `place` (the default value 4, cancel): for a grid place its
 * rows added, the cursor sprite hidden, the popup too unless the choice goes above it, and the
 * choice shown. */
void PocketsSwap_OpenChoice(PocketsSwap *self, int place, int above_popup)
{
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, POCKETS_SWAP_ACTION_CANCEL);
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) == 0) {
        return;
    }
    PocketsSwap_AddEntries(self);
    PocketsSwap_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    PocketsSwap_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov107_0229c990, PocketsSwap_OpenChoice)

/* func_ov107_0229c9e4: the rows of the choice of `slot`'s item: text 0x10 releasing an insect
 * (0x12b0-0x12e7) or a fish (0x12e8-0x131f), or for other items in mode 0x2a the tile operation;
 * for an item PocketsItem_CanUse allows, the drop (text 1 in mode 0x2a, else 0x10); text 2 to
 * cancel. (GroupParams_MaskArg is read first and its value left unused.) */
void PocketsSwap_AddEntries(PocketsSwap *self)
{
    GroupParams_MaskArg();
    int item = PocketsSwap_PlaceItem(self, self->slot);
    unsigned int mode = GroupParams_Mode();
    u16 code = (u16) item;

    if (psw_is_insect(code)) {
        ChoiceEntries_Add(&self->entries, 0x10, POCKETS_SWAP_ACTION_RELEASE_INSECT);
    } else if (psw_is_fish(code)) {
        ChoiceEntries_Add(&self->entries, 0x10, POCKETS_SWAP_ACTION_RELEASE_FISH);
    } else if (mode == POCKETS_SWAP_MODE_ITEM_2A) {
        ChoiceEntries_Add(&self->entries, 0x10, POCKETS_SWAP_ACTION_TILE_OP);
    }
    if (PocketsItem_CanUse((unsigned int) item) != 0) {
        if (mode == POCKETS_SWAP_MODE_ITEM_2A) {
            ChoiceEntries_Add(&self->entries, 1, POCKETS_SWAP_ACTION_DROP);
        } else {
            ChoiceEntries_Add(&self->entries, 0x10, POCKETS_SWAP_ACTION_DROP);
        }
    }
    ChoiceEntries_Add(&self->entries, 2, POCKETS_SWAP_ACTION_CANCEL);
}
CLEAN_AS(func_ov107_0229c9e4, PocketsSwap_AddEntries)

/* func_ov107_0229caa8: the item got (GroupParams_ItemC, in its carried form) put at `slot`: the
 * carried form of item 0x156b is drawn again (CurrentPockets_DrawFor156B) and kept in state 1;
 * the carried form is marked in the current player's item record, and the item given up becomes
 * GroupParams_ItemC. */
void PocketsSwap_TakeNewItem(PocketsSwap *self)
{
    u16 got = GroupParams_ItemC();
    u16 carried;
    ItemForm_ToCarried(&carried, &got);
    int item = carried;
    int state = 0;
    if (item == POCKETS_SWAP_ITEM_156B) {
        item = CurrentPockets_DrawFor156B();
        state = 1;
    }
    ItemRecord *record = (ItemRecord *) (void *) PlayerRecord_ItemRecord(PlayerRecords_Current());
    ItemRecord_SetBit(record, &carried, 0, 1);
    GroupParams_SetItemC((u16) PocketsSwap_PlaceItem(self, self->slot));
    PocketsSwap_SetPlaceItem(self, self->slot, item, state);
}
CLEAN_AS(func_ov107_0229caa8, PocketsSwap_TakeNewItem)

/* func_ov107_0229cb14: panel button 9 selected, sub state 0x0f, sound 0x28. */
void PocketsSwap_PressBelow(PocketsSwap *self)
{
    ButtonPanel_Select(&self->panel, POCKETS_SWAP_PANEL_BUTTON);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_PANEL_PRESSED);
    SoundSys_PlaySe(0x28);
}
CLEAN_AS(func_ov107_0229cb14, PocketsSwap_PressBelow)

/* func_ov107_0229cb3c: the swap done: `slot` handed back as GroupParams_SetArg, C4C 1, state 3
 * in phase 1 (the wipe out), the popup and the cursor sprite hidden. */
void PocketsSwap_Finish(PocketsSwap *self)
{
    GroupParams_SetArg(self->slot);
    GroupParams_SetC4C(1);
    self->base.state = POCKETS_SWAP_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(psw_scene(self), POCKETS_SWAP_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    PocketsSwap_HideCursorSprite(self);
}
CLEAN_AS(func_ov107_0229cb3c, PocketsSwap_Finish)

/* func_ov107_0229cb78: the choice cancelled: action 4, the cursor sprite placed at the cursor,
 * the choice asked to close, sub state 0x0d. */
void PocketsSwap_CancelChoice(PocketsSwap *self)
{
    self->action = POCKETS_SWAP_ACTION_CANCEL;
    PocketsSwap_PlaceCursorSprite(self);
    PagedChoice_RequestClose(psw_choice(self), 0);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov107_0229cb78, PocketsSwap_CancelChoice)

/* func_ov107_0229cba4: the entries shown in the choice, placed above the popup or beside
 * `slot`, and opened; sub state 0x0b. */
void PocketsSwap_ShowChoice(PocketsSwap *self, int above_popup)
{
    PagedChoice_ShowEntries(psw_choice(self), &self->entries, 0);
    int x = PocketsSwap_PlaceX(self, self->slot);
    int y = PocketsSwap_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(psw_choice(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(psw_choice(self), x, y);
    }
    PagedChoice_RequestOpen(psw_choice(self), 0);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_OPEN);
}
CLEAN_AS(func_ov107_0229cba4, PocketsSwap_ShowChoice)

/* func_ov107_0229cc14: the action picked (`action`, PocketsSwapAction): cancel ends it, the
 * others run through the table of member functions, filled once from its constants.
 * REQUIRES: `action` is below 5; the game reads past the table for others. */
void PocketsSwap_RunAction(PocketsSwap *self)
{
    static const MemberPointer *const actions[POCKETS_SWAP_ACTION_CANCEL] = {
        &data_ov107_0229e380,
        &data_ov107_0229e2b0,
        &data_ov107_0229e2a0,
        &data_ov107_0229e2c8,
    };
    if (self->action == POCKETS_SWAP_ACTION_CANCEL) {
        PocketsSwap_EndAction(self);
        return;
    }
    MemberTable_InitOnce(&data_ov107_0229e420, data_ov107_0229e42c, actions, POCKETS_SWAP_ACTION_CANCEL);
    MemberPointer_CallVoid(&data_ov107_0229e42c[self->action], self);
}
CLEAN_AS(func_ov107_0229cc14, PocketsSwap_RunAction)

/* func_ov107_0229cca8: the cursor sprite's second set shown, sub state 9. */
void PocketsSwap_ShowCursorSecondOfSet(PocketsSwap *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_BELOW_PRESS);
}
CLEAN_AS(func_ov107_0229cca8, PocketsSwap_ShowCursorSecondOfSet)

/* func_ov107_0229ccc8: the cursor sprite's first set shown and the sprite updated. */
void PocketsSwap_ShowCursorFirstOfSet(PocketsSwap *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    psw_update_cursor_sprite(self);
}
CLEAN_AS(func_ov107_0229ccc8, PocketsSwap_ShowCursorFirstOfSet)

/* func_ov107_0229cce8: the cursor sprite placed at the cursor with animation 1. */
void PocketsSwap_PlaceCursorSprite(PocketsSwap *self)
{
    int x = PocketsSwap_CursorSpriteX(self);
    int y = PocketsSwap_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov107_0229cce8, PocketsSwap_PlaceCursorSprite)

/* func_ov107_0229cd1c: the cursor sprite on the choice's first row, animation 7. */
void PocketsSwap_PointAtFirstRow(PocketsSwap *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(psw_choice(self));
    int y = PagedChoice_RowY(psw_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov107_0229cd1c, PocketsSwap_PointAtFirstRow)

/* func_ov107_0229cd68: the choice cancelled from the keys: action 4, its last row picked (with
 * its sound), the cursor sprite on it running animation 8 from its end, sub state 0x0c. */
void PocketsSwap_PointAtLastRow(PocketsSwap *self)
{
    self->action = POCKETS_SWAP_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(psw_choice(self), 1);
    int x = PagedChoice_TextX(psw_choice(self));
    int y = PagedChoice_RowY(psw_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd(psw_cursor_cells(self), 8);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov107_0229cd68, PocketsSwap_PointAtLastRow)

/* func_ov107_0229cdcc: the cursor sprite moved to `choice_row` in 2 steps; sub state 8, coming
 * back to this one. */
void PocketsSwap_GlideToRow(PocketsSwap *self)
{
    int x = PagedChoice_TextX(psw_choice(self));
    int y = PagedChoice_RowY(psw_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov107_0229cdcc, PocketsSwap_GlideToRow)

/* func_ov107_0229ce1c: the cursor sprite to the cursor: at once with
 * POCKETS_SWAP_FLAG_JUMP_SPRITE (then cleared); else eased there in 3 steps and sub state 8,
 * coming back to this one. */
void PocketsSwap_GlideToCursor(PocketsSwap *self)
{
    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_JUMP_SPRITE) != 0) {
        int x = PocketsSwap_CursorSpriteX(self);
        int y = PocketsSwap_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        PocketsSwap_ClearFlags(self, POCKETS_SWAP_FLAG_JUMP_SPRITE);
    } else {
        int x = PocketsSwap_CursorSpriteX(self);
        int y = PocketsSwap_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_SPRITE_MOVE);
    }
}
CLEAN_AS(func_ov107_0229ce1c, PocketsSwap_GlideToCursor)

/* func_ov107_0229ce90: the cursor sprite hidden (animation 0) and updated. */
void PocketsSwap_HideCursorSprite(PocketsSwap *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    psw_update_cursor_sprite(self);
}
CLEAN_AS(func_ov107_0229ce90, PocketsSwap_HideCursorSprite)

/* func_ov107_0229ceb4 */
int PocketsSwap_CursorSpriteY(PocketsSwap *self)
{
    return PocketsSwap_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov107_0229ceb4, PocketsSwap_CursorSpriteY)

/* func_ov107_0229cec4: the cursor's x plus 8; a wrap over the right edge starts it 0x100
 * further right, one over the left edge 0x100 further left. */
int PocketsSwap_CursorSpriteX(PocketsSwap *self)
{
    int x = PocketsSwap_PlaceX(self, self->cursor);
    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov107_0229cec4, PocketsSwap_CursorSpriteX)

/* func_ov107_0229cf08: the cursor sprite shown at the cursor, with animation 7 below the grid
 * and 1 on it. */
void PocketsSwap_ShowCursorAtCursor(PocketsSwap *self)
{
    int x = PocketsSwap_CursorSpriteX(self);
    int y = PocketsSwap_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == POCKETS_SWAP_BELOW) {
        Glider_SetAnim(&self->cursor_sprite, 7);
    } else {
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    PocketsSwap_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov107_0229cf08, PocketsSwap_ShowCursorAtCursor)

/* func_ov107_0229cf58: a held item drawn at `held_x`, `held_y` unless hidden. */
void PocketsSwap_DrawHeld(PocketsSwap *self)
{
    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == POCKETS_SWAP_HELD_ITEM) {
        PocketsGrid_DrawHeld(&self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov107_0229cf58, PocketsSwap_DrawHeld)

/* func_ov107_0229cf90: the popup queued for the cursor's place when it is a grid place with an
 * item (`popup_place`); else its queue cleared. */
void PocketsSwap_UpdatePopup(PocketsSwap *self)
{
    if (PocketsSwap_IsGridPlace(self, self->cursor) != 0 && PocketsSwap_PlaceIsEmpty(self, self->cursor) == 0) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov107_0229cf90, PocketsSwap_UpdatePopup)

/* func_ov107_0229cfe4: the popup placed above `popup_place` (8 pixels higher with state flag 2),
 * with the item's text for a grid place. */
void PocketsSwap_PlacePopup(PocketsSwap *self)
{
    int x = PocketsSwap_PlaceX(self, self->popup_place) - 0x6d;
    int y = PocketsSwap_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (PocketsSwap_IsGridPlace(self, self->popup_place) != 0) {
        int index = PocketsSwap_GridIndex(self, self->popup_place);
        PocketsGrid_ShowItemText(&self->grid, &self->popup, index);
    }
}
CLEAN_AS(func_ov107_0229cfe4, PocketsSwap_PlacePopup)

/* func_ov107_0229d054: `place` lifted in the grid (the letters' lift cleared), or no lift when
 * it is not a grid place. */
void PocketsSwap_SelectPlace(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        PocketsGrid_Lift(&self->grid, PocketsSwap_GridIndex(self, place));
        PocketsLetters_Unlift(&self->letters);
    } else {
        PocketsSwap_ClearSelection(self);
    }
}
CLEAN_AS(func_ov107_0229d054, PocketsSwap_SelectPlace)

/* func_ov107_0229d098 */
void PocketsSwap_ClearSelection(PocketsSwap *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov107_0229d098, PocketsSwap_ClearSelection)

/* func_ov107_0229d0bc: the state of the place's item; 0xf1 off the grid. */
int PocketsSwap_PlaceItemState(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_ItemState(&self->grid, PocketsSwap_GridIndex(self, place));
    }
    return POCKETS_SWAP_NO_STATE;
}
CLEAN_AS(func_ov107_0229d0bc, PocketsSwap_PlaceItemState)

/* func_ov107_0229d0f0: the place's item; 0xfff1 (no item) off the grid. */
int PocketsSwap_PlaceItem(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_Item(&self->grid, PocketsSwap_GridIndex(self, place));
    }
    return POCKETS_SWAP_NO_ITEM;
}
CLEAN_AS(func_ov107_0229d0f0, PocketsSwap_PlaceItem)

/* func_ov107_0229d128: the place holds no item; 1 off the grid. */
int PocketsSwap_PlaceIsEmpty(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_IsEmpty(&self->grid, PocketsSwap_GridIndex(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov107_0229d128, PocketsSwap_PlaceIsEmpty)

/* func_ov107_0229d15c: the place is dimmed in the grid; 0 off the grid. */
int PocketsSwap_PlaceIsDimmed(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_IsDimmed(&self->grid, PocketsSwap_GridIndex(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov107_0229d15c, PocketsSwap_PlaceIsDimmed)

/* func_ov107_0229d190: the place's item cannot be given up (it is dimmed): an item in a state
 * other than 0, item 0x137c, the items 0x1408-0x1428 and 0x1471-0x1491, and a fish when the setup
 * found no water. An empty place is not. */
int PocketsSwap_PlaceIsKept(PocketsSwap *self, int place)
{
    if (PocketsSwap_PlaceIsEmpty(self, place) != 0) {
        return 0;
    }
    if (PocketsSwap_PlaceItemState(self, place) != 0) {
        return 1;
    }
    unsigned int item = (unsigned int) PocketsSwap_PlaceItem(self, place);
    if (item == 0x137c || (item >= 0x1408 && item <= 0x1428) || (item >= 0x1471 && item <= 0x1491)) {
        return 1;
    }
    if (psw_is_fish(item) && PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_WATER) == 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov107_0229d190, PocketsSwap_PlaceIsKept)

/* func_ov107_0229d224: every grid place whose item cannot be given up dimmed. */
void PocketsSwap_DimKeptPlaces(PocketsSwap *self)
{
    for (int place = POCKETS_SWAP_GRID_FIRST; place <= POCKETS_SWAP_GRID_LAST; place++) {
        if (PocketsSwap_PlaceIsKept(self, place) != 0) {
            PocketsGrid_DimPlace(&self->grid, PocketsSwap_GridIndex(self, place));
        }
    }
}
CLEAN_AS(func_ov107_0229d224, PocketsSwap_DimKeptPlaces)

/* func_ov107_0229d260: the place's y: the grid's less 16; 0xb6 below the grid; else 0. */
int PocketsSwap_PlaceY(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_PlaceY(&self->grid, PocketsSwap_GridIndex(self, place)) - 0x10;
    }
    return place == POCKETS_SWAP_BELOW ? 0xb6 : 0;
}
CLEAN_AS(func_ov107_0229d260, PocketsSwap_PlaceY)

/* func_ov107_0229d29c: the place's x: the grid's; 0xbc below the grid; else 0. */
int PocketsSwap_PlaceX(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_PlaceX(&self->grid, PocketsSwap_GridIndex(self, place));
    }
    return place == POCKETS_SWAP_BELOW ? 0xbc : 0;
}
CLEAN_AS(func_ov107_0229d29c, PocketsSwap_PlaceX)

/* func_ov107_0229d2d8: a grid place's item and state set (and the pocket slot) and redrawn. */
void PocketsSwap_SetPlaceItem(PocketsSwap *self, int place, int item, int state)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) == 0) {
        return;
    }
    int index = PocketsSwap_GridIndex(self, place);
    PocketsGrid_SetItem(&self->grid, index, item, state);
    PocketsGrid_RefreshPlace(&self->grid, (unsigned int) index);
}
CLEAN_AS(func_ov107_0229d2d8, PocketsSwap_SetPlaceItem)

/* func_ov107_0229d31c: the grid place at the touch (x, y), POCKETS_SWAP_NO_PLACE for none (the
 * grid's 0x23) or, with `with_item`, for an empty one. */
int PocketsSwap_PlaceAtTouch(PocketsSwap *self, int x, int y, int with_item)
{
    int index = PocketsGrid_PocketPlaceAtTouch(&self->grid, x, y);
    if (index == 0x23) {
        return POCKETS_SWAP_NO_PLACE;
    }
    if (with_item != 0 && PocketsGrid_IsEmpty(&self->grid, index) != 0) {
        return POCKETS_SWAP_NO_PLACE;
    }
    return PocketsSwap_GridPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov107_0229d31c, PocketsSwap_PlaceAtTouch)

/* func_ov107_0229d35c: the place of grid index `index`; POCKETS_SWAP_NO_PLACE past the grid. */
u8 PocketsSwap_GridPlace(PocketsSwap *self, unsigned int index)
{
    (void) self;
    return index <= POCKETS_SWAP_GRID_LAST ? (u8) index : POCKETS_SWAP_NO_PLACE;
}
CLEAN_AS(func_ov107_0229d35c, PocketsSwap_GridPlace)

/* func_ov107_0229d36c: the grid index of a grid place (its low byte); 0 for other places. */
int PocketsSwap_GridIndex(PocketsSwap *self, int place)
{
    if (PocketsSwap_IsGridPlace(self, (unsigned int) place) != 0) {
        return (u8) place;
    }
    return 0;
}
CLEAN_AS(func_ov107_0229d36c, PocketsSwap_GridIndex)

/* func_ov107_0229d388 */
int PocketsSwap_IsGridPlace(PocketsSwap *self, unsigned int place)
{
    (void) self;
    return place <= POCKETS_SWAP_GRID_LAST;
}
CLEAN_AS(func_ov107_0229d388, PocketsSwap_IsGridPlace)

/* func_ov107_0229d394 */
void PocketsSwap_EndLayerTask(PocketsSwap *self)
{
    LayerTask_End(&self->task.first);
}
CLEAN_AS(func_ov107_0229d394, PocketsSwap_EndLayerTask)

/* func_ov107_0229d3a0: error message `message` opened (sub state 0x0e), going back to
 * `return_state` after it (0xff: the current sub state); the cursor sprite's window cleared.
 * (The ROM first copies data_021f43ec into the message's byte, then overwrites it.) */
void PocketsSwap_ShowMessage(PocketsSwap *self, u8 message, u8 return_state)
{
    if (return_state == POCKETS_SWAP_RETURN_HERE) {
        self->return_state = self->base.sub_state;
    } else {
        self->return_state = return_state;
    }
    u8 text = message;
    ErrorMessage_Open(&self->error, &text, 1, 0);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_ERROR);
    CellLayerSprite_ClearWindow(psw_cursor_cells(self));
}
CLEAN_AS(func_ov107_0229d3a0, PocketsSwap_ShowMessage)

/* func_ov107_0229d3f8: `place` touched (sub state 1): the offset from the touch to it kept, the
 * popup queued for it and shown, two frames before its choice may open, and sound 0x0c unless
 * the place is dimmed. */
void PocketsSwap_TouchPlace(PocketsSwap *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = PocketsSwap_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = PocketsSwap_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    if (PocketsSwap_PlaceIsDimmed(self, place) == 0) {
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov107_0229d3f8, PocketsSwap_TouchPlace)

/* func_ov107_0229d480: the action over, back to the touch's idle or the keys' browsing as state
 * flag 2 says. */
void PocketsSwap_EndAction(PocketsSwap *self)
{
    if (StateFlags_IsClear2() != 0) {
        PocketsSwap_EndActionHidden(self);
    } else {
        PocketsSwap_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov107_0229d480, PocketsSwap_EndAction)

/* func_ov107_0229d4a0: back to the keys: no popup place, the cursor sprite shown at the cursor,
 * the key repeat reset, the popup's queue set by the cursor, sub state 5 and the cursor's place
 * lifted. */
void PocketsSwap_EndActionAtCursor(PocketsSwap *self)
{
    self->popup_place = POCKETS_SWAP_NO_PLACE;
    PocketsSwap_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(psw_scene(self));
    PocketsSwap_UpdatePopup(self);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_BROWSE);
    PocketsSwap_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov107_0229d4a0, PocketsSwap_EndActionAtCursor)

/* func_ov107_0229d4d4: back to the touch: the cursor sprite hidden, no lift, sub state 0. */
void PocketsSwap_EndActionHidden(PocketsSwap *self)
{
    PocketsSwap_HideCursorSprite(self);
    PocketsSwap_ClearSelection(self);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov107_0229d4d4, PocketsSwap_EndActionHidden)

/* func_ov107_0229d4f0 (sub state 0x14): the scene finishes once the player's actor is in state
 * 0x90 (PlayerActorOps_InState90). */
void PocketsSwap_FinishWithPlayer(PocketsSwap *self)
{
    if (PlayerActorOps_InState90() != 0) {
        PocketsSwap_Finish(self);
    }
}
CLEAN_AS(func_ov107_0229d4f0, PocketsSwap_FinishWithPlayer)

/* func_ov107_0229d508 (sub state 0x13): the scene finishes once `delay` has counted down. */
void PocketsSwap_FinishAfterDelay(PocketsSwap *self)
{
    if (self->delay != 0) {
        self->delay--;
    } else {
        PocketsSwap_Finish(self);
    }
}
CLEAN_AS(func_ov107_0229d508, PocketsSwap_FinishAfterDelay)

/* func_ov107_0229d530 (sub state 0x12): once the held insect's state is not 3 any more, 5 frames
 * before the scene finishes (sub state 0x13). */
void PocketsSwap_WaitInsectGone(PocketsSwap *self)
{
    if (TownInsect_HeldState(PocketsSwap_OwnSlot(self)) != 3) {
        self->delay = 5;
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_FINISH_DELAY);
    }
}
CLEAN_AS(func_ov107_0229d530, PocketsSwap_WaitInsectGone)

/* func_ov107_0229d558 (sub state 0x0f): while the selected panel button's press runs, the cursor
 * sprite (when shown) follows the button by its press frame. Once over: C4C 0, state 3 in
 * phase 1 (the wipe out), the popup and the cursor sprite hidden. */
void PocketsSwap_FollowPanelPress(PocketsSwap *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(psw_cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
        return;
    }
    GroupParams_SetC4C(0);
    self->base.state = POCKETS_SWAP_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(psw_scene(self), POCKETS_SWAP_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    PocketsSwap_HideCursorSprite(self);
}
CLEAN_AS(func_ov107_0229d558, PocketsSwap_FollowPanelPress)

/* func_ov107_0229d5e0 (sub state 0x0e): once the error message is done, back to `return_state`
 * with the cursor sprite's window set. */
void PocketsSwap_WaitError(PocketsSwap *self)
{
    if (ErrorMessage_Update(&self->error, 0) != 0) {
        MenuScene_SetSubState(psw_scene(self), self->return_state);
        CellLayerSprite_SetWindow(psw_cursor_cells(self));
    }
}
CLEAN_AS(func_ov107_0229d5e0, PocketsSwap_WaitError)

/* func_ov107_0229d614 (sub state 0x0d): the action run once the choice is idle. */
void PocketsSwap_RunActionWhenIdle(PocketsSwap *self)
{
    if (PagedChoice_IsIdle(psw_choice(self)) != 0) {
        PocketsSwap_RunAction(self);
    }
}
CLEAN_AS(func_ov107_0229d614, PocketsSwap_RunActionWhenIdle)

/* func_ov107_0229d634 (sub state 0x0c): once the choice's count is down, it is asked to close,
 * the popup hidden, the cursor sprite (when shown) placed at the cursor, sub state 0x0d. */
void PocketsSwap_CloseChoice(PocketsSwap *self)
{
    if (PagedChoice_CountDown(psw_choice(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(psw_choice(self), 0);
    Popup_Hide(&self->popup, 1);
    if (CellLayerSprite_AnimNumber(psw_cursor_cells(self)) != 0) {
        PocketsSwap_PlaceCursorSprite(self);
    }
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov107_0229d634, PocketsSwap_CloseChoice)

/* func_ov107_0229d684 (sub state 0x0b): once the choice is shown, the keys' choice (the cursor
 * sprite on its first row, sub state 6) with state flag 2, else the touch's (sub state 4). */
void PocketsSwap_WaitChoiceShown(PocketsSwap *self)
{
    if (PagedChoice_IsShown(psw_choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2() != 0) {
        PocketsSwap_PointAtFirstRow(self);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_BY_KEYS);
    } else {
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov107_0229d684, PocketsSwap_WaitChoiceShown)

/* func_ov107_0229d6c0 (sub state 0x0a): once the cursor sprite's animation is done, its first
 * set shown and back to browsing (sub state 5). */
void PocketsSwap_WaitSpriteAnim(PocketsSwap *self)
{
    if (CellLayerSprite_IsDone(psw_cursor_cells(self)) != 0) {
        PocketsSwap_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov107_0229d6c0, PocketsSwap_WaitSpriteAnim)

/* func_ov107_0229d6e8 (sub state 9): once the cursor sprite's animation is done, panel button 9
 * pressed (PocketsSwap_PressBelow). */
void PocketsSwap_WaitBelowPress(PocketsSwap *self)
{
    if (CellLayerSprite_IsDone(psw_cursor_cells(self)) != 0) {
        ButtonPanel_Select(&self->panel, POCKETS_SWAP_PANEL_BUTTON);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_PANEL_PRESSED);
        SoundSys_PlaySe(0x28);
    }
}
CLEAN_AS(func_ov107_0229d6e8, PocketsSwap_WaitBelowPress)

/* func_ov107_0229d720 (sub state 8): once the cursor sprite stops, back to `return_state`
 * (browsing lifts the cursor's place) and that sub state run at once. */
void PocketsSwap_WaitCursorSprite(PocketsSwap *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) != 0) {
        return;
    }
    MenuScene_SetSubState(psw_scene(self), self->return_state);
    if (self->return_state == POCKETS_SWAP_SUB_BROWSE) {
        PocketsSwap_SelectPlace(self, self->cursor);
    }
    PocketsSwap_RunSubState(self);
}
CLEAN_AS(func_ov107_0229d720, PocketsSwap_WaitCursorSprite)

/* func_ov107_0229d764 (sub state 7): once the cursor sprite's animation is done, `choice_row`
 * picked (with its sound), its value the action, sub state 0x0c. */
void PocketsSwap_PickChoiceRow(PocketsSwap *self)
{
    if (CellLayerSprite_IsDone(psw_cursor_cells(self)) == 0) {
        return;
    }
    PagedChoice_PickRowWithSound(psw_choice(self), self->choice_row, 1);
    self->action = psw_entry_value(self, self->choice_row);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov107_0229d764, PocketsSwap_PickChoiceRow)

/* func_ov107_0229d7b0 (sub state 6): the choice by the keys. A touch cancels it; a move of its
 * cursor glides the sprite to the row; A shows the sprite's second set (sub state 7, the row is
 * picked); B picks the last row (cancel). */
void PocketsSwap_ChooseByKeys(PocketsSwap *self)
{
    if (MenuScene_TakeTouch(psw_scene(self)) != 0) {
        PocketsSwap_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(psw_scene(self));
    if (PagedChoice_MoveCursor(psw_choice(self), keys, &self->choice_row, 0) != 0) {
        PocketsSwap_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & POCKETS_SWAP_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_PICK);
        return;
    }
    if (pressed & POCKETS_SWAP_PAD_B) {
        PocketsSwap_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov107_0229d7b0, PocketsSwap_ChooseByKeys)

/* func_ov107_0229d828 (sub state 5): browsing by the keys. A touch goes back to the touch (the
 * popup hidden). A move updates the popup and eases the sprite to the cursor (the popup hidden,
 * its queue kept). A on a grid place that is not dimmed and holds an item opens its choice; A
 * below the grid shows the sprite's second set (sub state 9, panel button 9). B hides the sprite
 * and presses panel button 9 (the popup hidden, its queue kept); otherwise a queued popup is
 * shown. */
void PocketsSwap_BrowseByKeys(PocketsSwap *self)
{
    if (MenuScene_TakeTouch(psw_scene(self)) != 0) {
        PocketsSwap_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(psw_scene(self));
    if (PocketsSwap_MoveCursor(self, keys) != 0) {
        PocketsSwap_UpdatePopup(self);
        PocketsSwap_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (PocketsSwap_PlaceIsDimmed(self, self->cursor) == 0 && (data_021fbe40.pressed & POCKETS_SWAP_PAD_A) != 0) {
        if (PocketsSwap_IsGridPlace(self, self->cursor) != 0) {
            if (PocketsSwap_PlaceIsEmpty(self, self->cursor) == 0) {
                PocketsSwap_OpenChoice(self, self->cursor, 0);
            }
        } else if (self->cursor == POCKETS_SWAP_BELOW) {
            PocketsSwap_ShowCursorSecondOfSet(self);
        }
        return;
    }
    if (data_021fbe40.pressed & POCKETS_SWAP_PAD_B) {
        PocketsSwap_HideCursorSprite(self);
        PocketsSwap_PressBelow(self);
        Popup_Hide(&self->popup, 0);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov107_0229d828, PocketsSwap_BrowseByKeys)

/* func_ov107_0229d908 (sub state 4): the choice by the touch, once shown. A button cancels it;
 * a touch on a row picks it (with its sound), its value the action, sub state 0x0c. */
void PocketsSwap_ChooseByTouch(PocketsSwap *self)
{
    if (PagedChoice_IsShown(psw_choice(self)) == 0) {
        return;
    }
    if (MenuScene_TakeButtons(psw_scene(self), 1) != 0) {
        PocketsSwap_CancelChoice(self);
        return;
    }
    if (!psw_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(psw_choice(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    PagedChoice_PickRowWithSound(psw_choice(self), row, 1);
    self->action = psw_entry_value(self, row);
    MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov107_0229d908, PocketsSwap_ChooseByTouch)

/* func_ov107_0229d9a0 (sub state 3): once the popup is up and `open_delay` more frames have
 * passed, the touched place's choice opened above the popup (sub state 2). */
void PocketsSwap_OpenTouchedChoice(PocketsSwap *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
    } else {
        PocketsSwap_OpenChoice(self, self->touch_place, 1);
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TOUCH_RELEASE);
    }
}
CLEAN_AS(func_ov107_0229d9a0, PocketsSwap_OpenTouchedChoice)

/* func_ov107_0229d9e8 (sub state 2): once the pen is up, the touch's choice (sub state 4). */
void PocketsSwap_WaitTouchRelease(PocketsSwap *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov107_0229d9e8, PocketsSwap_WaitTouchRelease)

/* func_ov107_0229da04 (sub state 1): a place is touched. Let go: a dimmed place goes back to
 * sub state 0 with the popup's timer at 60 frames; another has its choice opened (sub state 3,
 * run at once). Held down on a place that is not dimmed, once the popup is up and `open_delay`
 * more frames have passed, its choice opens above the popup (sub state 2); otherwise a queued
 * popup is shown. */
void PocketsSwap_HoldTouchOnPlace(PocketsSwap *self)
{
    if (data_021fbdd8 == 0) {
        if (PocketsSwap_PlaceIsDimmed(self, self->touch_place) != 0) {
            MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TOUCH_IDLE);
            Popup_SetTimer(&self->popup, 0x3c);
        } else {
            MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_OPEN_TOUCHED);
            PocketsSwap_RunSubState(self);
        }
        return;
    }
    if (PocketsSwap_PlaceIsDimmed(self, self->touch_place) == 0 && Popup_IsUp(&self->popup) != 0) {
        if (self->open_delay != 0) {
            self->open_delay--;
        } else {
            PocketsSwap_OpenChoice(self, self->touch_place, 1);
            MenuScene_SetSubState(psw_scene(self), POCKETS_SWAP_SUB_TOUCH_RELEASE);
        }
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov107_0229da04, PocketsSwap_HoldTouchOnPlace)

/* func_ov107_0229daa4 (sub state 0): idle by the touch. A button goes to the keys; a pen going
 * down on a grid place with an item touches it (16 pixels lower in the grid's view), on panel
 * button 9 presses it. */
void PocketsSwap_IdleByTouch(PocketsSwap *self)
{
    if (MenuScene_TakeButtons(psw_scene(self), 1) != 0) {
        PocketsSwap_EndActionAtCursor(self);
        return;
    }
    if (!psw_pen_pressed()) {
        return;
    }
    int place = PocketsSwap_PlaceAtTouch(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (place != POCKETS_SWAP_NO_PLACE) {
        PocketsSwap_TouchPlace(self, place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, POCKETS_SWAP_PANEL_BUTTON) != 0) {
        PocketsSwap_PressBelow(self);
    }
}
CLEAN_AS(func_ov107_0229daa4, PocketsSwap_IdleByTouch)

/* func_ov107_0229db24: the wallet's object files and the panel's text colours loaded. */
void PocketsSwap_LoadObjFiles(PocketsSwap *self)
{
    PocketsWallet_LoadObjFiles(&self->wallet);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov107_0229db24, PocketsSwap_LoadObjFiles)

/* func_ov107_0229db48: the wallet's display started with 0 and prepared. */
void PocketsSwap_PrepareWallet(PocketsSwap *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov107_0229db48, PocketsSwap_PrepareWallet)

/* func_ov107_0229db5c: layer 6 at priority 2 with its plain background settings. */
void PocketsSwap_SetUpLayer6(void)
{
    DisplayLayer_SetPriority(POCKETS_SWAP_LAYER, 2);
    DisplayLayer_SetBgControl(POCKETS_SWAP_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov107_0229db5c, PocketsSwap_SetUpLayer6)

/* func_ov107_0229db7c: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void PocketsSwap_EndFrame(PocketsSwap *self)
{
    PagedChoice_Update(psw_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        PocketsSwap_PlacePopup(self);
    }
}
CLEAN_AS(func_ov107_0229db7c, PocketsSwap_EndFrame)

/* func_ov107_0229dbb4: the start of a frame: the layer task ended, the three objects of ov094's
 * updated and the panel's texts closed. */
void PocketsSwap_BeginFrame(PocketsSwap *self)
{
    PocketsSwap_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov107_0229dbb4, PocketsSwap_BeginFrame)

/* func_ov107_0229dbf4 */
void PocketsSwap_EndInteractiveFrame(PocketsSwap *self)
{
    PocketsSwap_EndFrame(self);
}
CLEAN_AS(func_ov107_0229dbf4, PocketsSwap_EndInteractiveFrame)

/* func_ov107_0229dbfc: the start of a frame, then the cursor sprite's update. */
void PocketsSwap_BeginInteractiveFrame(PocketsSwap *self)
{
    PocketsSwap_BeginFrame(self);
    psw_update_cursor_sprite(self);
}
CLEAN_AS(func_ov107_0229dbfc, PocketsSwap_BeginInteractiveFrame)

/* func_ov107_0229dc18: the members' teardown before the scene closes. */
void PocketsSwap_Teardown(PocketsSwap *self)
{
    PocketsSwap_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(psw_choice(self));
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov107_0229dc18, PocketsSwap_Teardown)

/* func_ov107_0229dc58: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor on the first place, the choice on
 * layer 3; POCKETS_SWAP_FLAG_WATER when water is found for a fish; no open delay. */
void PocketsSwap_Setup(PocketsSwap *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = POCKETS_SWAP_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = POCKETS_SWAP_HELD_NONE;
    self->cursor = POCKETS_SWAP_GRID_FIRST;
    PagedChoice_Init(psw_choice(self), 3, 1, NULL);
    if (PocketsSwap_FindWater(self) != 0) {
        PocketsSwap_SetFlags(self, POCKETS_SWAP_FLAG_WATER);
    }
    self->open_delay = 0;
}
CLEAN_AS(func_ov107_0229dc58, PocketsSwap_Setup)

/* func_ov107_0229dcdc (state 4): the wipe out stepped; once over, layer 6 hidden and the scene
 * deleted (phase 5) and no longer drawn; else layer 6 scrolled 16 up. The objects follow the
 * wipe. */
void PocketsSwap_WipeOut(PocketsSwap *self)
{
    if (MenuScene_StepWipe(psw_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(POCKETS_SWAP_LAYER);
        MenuScene_SetPhase(psw_scene(self), POCKETS_SWAP_PHASE_DELETE);
        PocketsSwap_ClearFlags(self, POCKETS_SWAP_FLAG_DRAWN);
        PocketsSwap_ClearFlags(self, POCKETS_SWAP_FLAG_OBJECTS_DRAWN);
    } else {
        MenuScene_ScrollWipe(psw_scene(self), POCKETS_SWAP_LAYER, 0, -16);
    }
    self->objects_y = MenuScene_WipeOffsetY(psw_scene(self));
}
CLEAN_AS(func_ov107_0229dcdc, PocketsSwap_WipeOut)

/* func_ov107_0229dd28 (state 3): the popup and the cursor sprite hidden, the parent told the
 * scene ends, the wipe out started (8 frames on window 2, margin 0x30), state 4. */
void PocketsSwap_StartWipeOut(PocketsSwap *self)
{
    Popup_Hide(&self->popup, 1);
    PocketsSwap_HideCursorSprite(self);
    func_ov092_02299324(psw_parent(self), POCKETS_SWAP_PARENT_CODE_END, 1);
    MenuScene_StartWipeOnWindow2(psw_scene(self), 8, 0, 0, 0x30);
    MenuScene_ScrollWipe(psw_scene(self), POCKETS_SWAP_LAYER, 0, -16);
    MenuScene_SetState(psw_scene(self), POCKETS_SWAP_STATE_WIPE_OUT);
    self->objects_y = MenuScene_WipeOffsetY(psw_scene(self));
}
CLEAN_AS(func_ov107_0229dd28, PocketsSwap_StartWipeOut)

/* func_ov107_0229dd88 (state 2): the wipe in stepped back; once over, the interactive phase (2)
 * with the action ended (PocketsSwap_EndAction). Layer 6 scrolled 16 up, the objects following
 * the wipe. */
void PocketsSwap_WipeIn(PocketsSwap *self)
{
    if (MenuScene_StepWipeBack(psw_scene(self), 0) != 0) {
        MenuScene_SetPhase(psw_scene(self), POCKETS_SWAP_PHASE_INTERACTIVE);
        PocketsSwap_EndAction(self);
    }
    MenuScene_ScrollWipe(psw_scene(self), POCKETS_SWAP_LAYER, 0, -16);
    self->objects_y = MenuScene_WipeOffsetY(psw_scene(self));
}
CLEAN_AS(func_ov107_0229dd88, PocketsSwap_WipeIn)

/* func_ov107_0229ddc4 (state 1): the object files loaded, the panel in layout 5 with message
 * 0x65, the pockets loaded into the grid (the places that cannot be given up dimmed) and the
 * letters (states 0-3 dimmed), the wipe in started covered (8 frames on window 2, margin 0x30),
 * layer 6 shown and scrolled 16 up, state 2, the scene and its objects drawn. */
void PocketsSwap_StartWipeIn(PocketsSwap *self)
{
    PocketsSwap_LoadObjFiles(self);
    ButtonPanel_SetLayout5(&self->panel, 0x65);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsSwap_DimKeptPlaces(self);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_DimByState(&self->letters, 0xf);
    MenuScene_StartWipeCoveredOnWindow2(psw_scene(self), 8, 0, 0, 0x30);
    DisplayLayer_Show(POCKETS_SWAP_LAYER);
    MenuScene_ScrollWipe(psw_scene(self), POCKETS_SWAP_LAYER, 0, -16);
    MenuScene_SetState(psw_scene(self), POCKETS_SWAP_STATE_WIPE_IN);
    PocketsSwap_SetFlags(self, POCKETS_SWAP_FLAG_DRAWN);
    PocketsSwap_SetFlags(self, POCKETS_SWAP_FLAG_OBJECTS_DRAWN);
    self->objects_y = MenuScene_WipeOffsetY(psw_scene(self));
}
CLEAN_AS(func_ov107_0229ddc4, PocketsSwap_StartWipeIn)

/* func_ov107_0229de54 (state 0): layer 6 set up, the wallet prepared, state 1. */
void PocketsSwap_StartSetup(PocketsSwap *self)
{
    PocketsSwap_SetUpLayer6();
    PocketsSwap_PrepareWallet(self);
    MenuScene_SetState(psw_scene(self), POCKETS_SWAP_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov107_0229de54, PocketsSwap_StartSetup)

/* func_ov107_0229de70 (vtable slot 0x5c, phase 5): the scene's deletion asked for. Answers 1. */
int PocketsSwap_RequestDelete(PocketsSwap *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov107_0229de70, PocketsSwap_RequestDelete)

/* func_ov107_0229de80 (vtable slot 0x58): nothing. */
int PocketsSwap_Phase1Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov107_0229de80, PocketsSwap_Phase1Idle)

/* func_ov107_0229de84 (vtable slot 0x54): nothing. */
int PocketsSwap_Phase0Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov107_0229de84, PocketsSwap_Phase0Idle)

/* func_ov107_0229de88 (vtable slot 0x50, phase 2): a frame of the scene in use: the frame's
 * start, its sub state and its end. Answers 1. */
int PocketsSwap_RunInteractive(PocketsSwap *self)
{
    PocketsSwap_BeginInteractiveFrame(self);
    PocketsSwap_RunSubState(self);
    PocketsSwap_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov107_0229de88, PocketsSwap_RunInteractive)

/* func_ov107_0229dea4: the sub state's function (PocketsSwapSubState) through the table of
 * member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x18; the game reads past the table for others. */
void PocketsSwap_RunSubState(PocketsSwap *self)
{
    static const MemberPointer *const sub_states[POCKETS_SWAP_SUB_STATES] = {
        &data_ov107_0229e388, &data_ov107_0229e300, &data_ov107_0229e338, &data_ov107_0229e370, &data_ov107_0229e368,
        &data_ov107_0229e360, &data_ov107_0229e358, &data_ov107_0229e350, &data_ov107_0229e348, &data_ov107_0229e340,
        &data_ov107_0229e2d8, &data_ov107_0229e330, &data_ov107_0229e328, &data_ov107_0229e320, &data_ov107_0229e318,
        &data_ov107_0229e310, &data_ov107_0229e308, &data_ov107_0229e2f8, &data_ov107_0229e378, &data_ov107_0229e2f0,
        &data_ov107_0229e2e8, &data_ov107_0229e2e0, &data_ov107_0229e2a8, &data_ov107_0229e2d0,
    };
    MemberTable_InitOnce(&data_ov107_0229e424, data_ov107_0229e474, sub_states, POCKETS_SWAP_SUB_STATES);
    MemberPointer_CallVoid(&data_ov107_0229e474[self->base.sub_state], self);
}
CLEAN_AS(func_ov107_0229dea4, PocketsSwap_RunSubState)

/* Obj_ov107_0229e3b8::func_ov107_0229e048 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (PocketsSwapState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int PocketsSwap_RunState(PocketsSwap *self)
{
    static const MemberPointer *const states[POCKETS_SWAP_STATES] = {
        &data_ov107_0229e390, &data_ov107_0229e2b8, &data_ov107_0229e398, &data_ov107_0229e3a8, &data_ov107_0229e3a0,
    };
    MemberTable_InitOnce(&data_ov107_0229e428, data_ov107_0229e44c, states, POCKETS_SWAP_STATES);
    PocketsSwap_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov107_0229e44c[self->base.state], self);
    PocketsSwap_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov107_0229e3b819func_ov107_0229e048Ev, PocketsSwap_RunState)

/* func_ov107_0229e0e8 (vtable slot 0x24): the scene's draw: the choice; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use) and a
 * held item; with the objects drawn, the panel at the wipe's y, and the grid, the letters and the
 * wallet 16 pixels above it. Answers 1. */
int PocketsSwap_Draw(PocketsSwap *self)
{
    PagedChoice_Draw(psw_choice(self));
    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_DRAWN) == 0) {
        return 1;
    }
    psw_draw_popup(self);
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    PocketsSwap_DrawHeld(self);
    if (PocketsSwap_TestFlags(self, POCKETS_SWAP_FLAG_OBJECTS_DRAWN) != 0) {
        ButtonPanel_Draw(&self->panel, self->objects_y);
        int y = (int) ((u32) self->objects_y - 0x10);
        PocketsGrid_DrawPockets(&self->grid, 0, y);
        PocketsLetters_DrawPockets(&self->letters, 0, y);
        PocketsWallet_Draw(&self->wallet, y);
    }
    return 1;
}
CLEAN_AS(func_ov107_0229e0e8, PocketsSwap_Draw)

/* func_ov107_0229e190 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int PocketsSwap_Close(PocketsSwap *self)
{
    func_ov092_0229929c(psw_parent(self));
    PocketsSwap_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov107_0229e190, PocketsSwap_Close)

/* func_ov107_0229e1ac (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int PocketsSwap_Start(PocketsSwap *self)
{
    PocketsSwap_Setup(self);
    MenuScene_SetState(psw_scene(self), POCKETS_SWAP_STATE_START_SETUP);
    MenuScene_SetPhase(psw_scene(self), POCKETS_SWAP_PHASE_START);
    return 1;
}
CLEAN_AS(func_ov107_0229e1ac, PocketsSwap_Start)

/* func_ov107_0229e1cc: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable, the tile cleared and the members constructed in order. */
PocketsSwap *PocketsSwap_New(void)
{
    PocketsSwap *self = MenuScene_Alloc(sizeof(PocketsSwap));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov107_0229e3b8;
    self->tile_x = 0;
    self->tile_z = 0;
    LayerTask_ConstructPair(&self->task);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(psw_choice(self));
    ErrorMessage_Construct(&self->error);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov107_0229e1cc, PocketsSwap_New)
