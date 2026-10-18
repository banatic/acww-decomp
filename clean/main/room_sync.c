/* The rooms kept the same on every system of the session (room_sync.h). */
#include "room_sync.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "item_footprint.h"
#include "ov004/room_object.h"
#include "ov004/room_object_body.h"
#include "ov004/room_object_methods.h"
#include "ov004/room_object_parts.h"
#include "room_cells.h"
#include "session.h"
#include "actor_table.h"
#include "furniture_info.h"
#include "house_record.h"
#include "item_code.h"
#include "link_global.h"
#include "ov004/room_objects.h"
#include "scene_map.h"
#include "scene_query.h"

extern NetSession *data_020ccf94; /* the session */
extern u8 data_020e54a8;          /* 1 while overlay 4 shows a room */
extern AcreMap *data_021c80bc;    /* the map of the scene shown */
extern u8 data_021ebcd4[];        /* the house rooms' records */

#define HOST_SLOT 0
#define LAYER_FLOOR 0
#define LAYER_ON_TOP 1
#define ACRE_CELLS_SHIFT 4 /* 16 x 16 cells to an acre */
#define ACRE_CELL_MASK 0xf
#define LIGHTS_ON_MAX 4 /* lamps of kind 0x18 on before switching one more turns one off */

extern int func_ov004_02211280(const RoomObject *object); /* RoomObject_TestUnk780Is18 */

static int room_shown(void)
{
    return data_020e54a8 == 1;
}

/* The map of `scene`: the one shown when overlay 4 shows that scene. */
static AcreMap *scene_map(int scene)
{
    if (room_shown() && SceneQuery_Current() == scene) {
        return data_021c80bc;
    }
    return (AcreMap *) (uintptr_t) SceneMap_OfScene(scene);
}

static RoomObject *object_at(int x, int y, int layer)
{
    return RoomObjects_GridObjectAt(RoomObjects_Grid(), x, y, layer);
}

/* The item code on cell (x, y) of `layer` of a map. */
static u16 *map_item(AcreMap *map, int x, int y, u8 layer)
{
    int acre_x = x >> ACRE_CELLS_SHIFT;
    int acre_y = y >> ACRE_CELLS_SHIFT;
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_y, x & ACRE_CELL_MASK, y & ACRE_CELL_MASK, layer);
}

static int is_step_item(u16 code)
{
    return code >= ROOM_SYNC_STEP_ITEM_FIRST && code <= ROOM_SYNC_STEP_ITEM_LAST;
}

/* Vtable slot 0x74: whether `state` shows the object on. */
static int shows_on(RoomObject *object, int state)
{
    int (*fn)(RoomObject *, int) = (int (*)(RoomObject *, int)) object->vtable->unk_74;
    return fn(object, state);
}

static void send_message(int handler, const void *payload, int size, int kind)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, payload, size);
    Session_EndMessage(session, (u32) handler, (u32) kind);
}

/* func_02051d30 is in text_string.c. */

/* func_02051d40: nothing (an empty function next to this code; OverlayTask_Init, func_02070390, calls it). */
void RoomSync_Nothing(void) {}
CLEAN_AS(func_02051d40, RoomSync_Nothing)

/* func_02051d44: whether, in the room shown, an object stands on cell (x, y) of the floor
 * whose furniture's data says 1 at byte 0x1a, with nothing on top of it on the map. */
int RoomSync_IsFreeTopAt(int x, int y)
{
    if (!room_shown()) {
        return 0;
    }
    AcreMap *map = data_021c80bc;
    RoomObject *object = object_at(x, y, LAYER_FLOOR);
    if (map == NULL || object == NULL) {
        return 0;
    }
    u16 *top = map_item(map, x, y, LAYER_ON_TOP);
    if (FurnitureInfo_DmaUnk1A(RoomObject_Number(object)) != 1 || top == NULL) {
        return 0;
    }
    if (ItemCode_HasVariant(top)) {
        u16 none = ACRE_MAP_ITEM_NONE;
        int number = ItemCode_VariantItem(top);
        return number == ItemCode_VariantItem(&none);
    }
    return *top == ACRE_MAP_ITEM_NONE;
}
CLEAN_AS(func_02051d44, RoomSync_IsFreeTopAt)

/* func_02051f4c: RoomSync_ToggleSwitchAt for the cell `point` is on. */
void RoomSync_ToggleSwitchAtPoint(int scene, const Vec3 *point, int layer)
{
    int x;
    int y;
    Position_Tile(&x, &y, (const Position *) point);
    RoomSync_ToggleSwitchAt((u32) scene, (u32) x, (u32) y, (u32) layer);
}
CLEAN_AS(func_02051f4c, RoomSync_ToggleSwitchAtPoint)

/* func_02051f74: toggles the switch of the object at cell (x, y) of `layer`: at once
 * (RoomSync_ToggleAt) unless the session is linked and func_020a7278 says 0; then the object
 * there, if any, is held still (unk_77D) and message 29 goes to the systems in this scene.
 * BUG: the message's halfword is built in an uninitialised stack slot and its bit 15 is never
 * set, so the ROM sends what it held; here it is 0. The receiver does not read it. */
void RoomSync_ToggleSwitchAt(u32 scene, u32 x, u32 y, u32 layer)
{
    if (!Session_IsLinked(data_020ccf94) || LinkGlobal_HoldsScene()) {
        RoomSync_ToggleAt((int) scene, (int) x, (int) y, (int) layer, 1);
        return;
    }
    RoomObject *object = object_at((int) x, (int) y, (int) layer);
    if (object != NULL) {
        object->unk_77D = 1;
    }
    u16 message = (u16) ((scene & 0x3f) | (layer & 1) << ROOM_SYNC_TOGGLE_LAYER_SHIFT | (x & 0xf) << ROOM_SYNC_TOGGLE_X_SHIFT |
                         (y & 0xf) << ROOM_SYNC_TOGGLE_Y_SHIFT);
    send_message(ROOM_SYNC_MSG_TOGGLE, &message, sizeof(message), ROOM_SYNC_TO_SCENE);
}
CLEAN_AS(func_02051f74, RoomSync_ToggleSwitchAt)

/* func_02052038: the house room `scene` lit or not: at once where the session is not linked or
 * this system is the host, else asked of the host. */
void RoomSync_SetLit(int scene, int lit)
{
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session) || Session_IsLocalSlot(session, HOST_SLOT)) {
        RoomSync_ApplyLit(scene, lit);
    } else {
        RoomSync_SendLit(scene, lit, ROOM_SYNC_TO_HOST);
    }
}
CLEAN_AS(func_02052038, RoomSync_SetLit)

/* func_02052078: sets the house room's lit bit and tells everyone. */
void RoomSync_ApplyLit(int scene, int lit)
{
    HouseRecord_SetLit((HouseRecord *) (void *) data_021ebcd4, scene, lit);
    RoomSync_SendLit(scene, lit, ROOM_SYNC_TO_ALL);
}
CLEAN_AS(func_02052078, RoomSync_ApplyLit)

/* func_020520a0: message 25, when the session is linked; sent to anyone but everyone, it asks
 * to be relayed. */
void RoomSync_SendLit(int scene, int lit, int kind)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 message = (u8) ((scene & ROOM_SYNC_LIT_SCENE) | ((lit & 1) ? ROOM_SYNC_LIT_ON : 0) |
                       (kind != ROOM_SYNC_TO_ALL ? ROOM_SYNC_LIT_RELAY : 0));
    send_message(ROOM_SYNC_MSG_LIT, &message, sizeof(message), kind);
}
CLEAN_AS(func_020520a0, RoomSync_SendLit)

/* func_02052118: puts the item `code` on top at cell (x, y) of the scene's map and, with
 * `send` on a linked session, sends it as message 26.
 * BUG: the message's word is built in an uninitialised stack slot and its bits 24-31 are never
 * set, so the ROM sends what they held; here they are 0. The receiver does not read them. */
void RoomSync_PutItem(int scene, int x, int y, u16 *code, u8 send_it)
{
    AcreMap *map = scene_map(scene);
    if (map == NULL || !AcreTile_SetItem(map, code, x, y, LAYER_ON_TOP) || !send_it || !Session_IsLinked(data_020ccf94)) {
        return;
    }
    u32 message =
        ((u32) x & 0xf) | ((u32) y & 0xf) << ROOM_SYNC_PUT_ITEM_Y_SHIFT | (u32) *code << ROOM_SYNC_PUT_ITEM_CODE_SHIFT;
    send_message(ROOM_SYNC_MSG_PUT_ITEM, &message, sizeof(message), ROOM_SYNC_TO_ALL);
}
CLEAN_AS(func_02052118, RoomSync_PutItem)

/* func_020521d8: takes the furniture `code` at cell (x, y) of `layer` off the scene's map:
 * each cell of its footprint is emptied (with `with_top` on the floor, layer 1 too), its switch
 * set to `on` in the scene's RoomCells, and for a step item that is on its step forgotten. The
 * first cell that cannot be emptied ends it. With `send` on a linked session it goes out as
 * message 27.
 * BUG: the message's word is built in an uninitialised stack slot and its bits 27-31 are never
 * set, so the ROM sends what they held; here they are 0. The receiver does not read them. */
void RoomSync_TakeFurniture(int scene, int x, int y, int layer, int on, u16 *code, int with_top, u8 send_it)
{
    u16 first = *code;
    AcreMap *map = scene_map(scene);
    if (map == NULL) {
        return;
    }
    ItemFootprint footprint;
    ItemFootprint_Construct(&footprint, code);
    int step_item = is_step_item(*code);
    int both = with_top && layer == LAYER_FLOOR;

    for (u32 i = 0; i < ItemFootprint_Count(&footprint); i++) {
        int cell_x = x + ItemFootprint_Cell(&footprint, i)->x;
        int cell_y = y + ItemFootprint_Cell(&footprint, i)->y;
        u16 none = ACRE_MAP_ITEM_NONE;
        if (!AcreTile_SetItem(map, &none, cell_x, cell_y, (u8) layer)) {
            ItemFootprint_Destruct(&footprint);
            return;
        }
        if (both) {
            u16 none_on_top = ACRE_MAP_ITEM_NONE;
            if (!AcreTile_SetItem(map, &none_on_top, cell_x, cell_y, LAYER_ON_TOP)) {
                ItemFootprint_Destruct(&footprint);
                return;
            }
        }
        RoomCells_SetSwitch(cell_x, cell_y, layer, on, (u8) scene);
        if (both) {
            RoomCells_SetSwitch(cell_x, cell_y, LAYER_ON_TOP, on, (u8) scene);
        }
        if (step_item && on) {
            RoomCells_ClearStep(cell_x, cell_y, scene);
        }
    }
    if (Session_IsLinked(data_020ccf94) && send_it) {
        u32 message = ((u32) layer & 1) | ((u32) x & 0xf) << ROOM_SYNC_TAKE_X_SHIFT |
                      ((u32) y & 0xf) << ROOM_SYNC_TAKE_Y_SHIFT | ((u32) with_top & 1) << ROOM_SYNC_TAKE_WITH_TOP_SHIFT |
                      ((u32) on & 1) << ROOM_SYNC_TAKE_ON_SHIFT | (u32) first << ROOM_SYNC_TAKE_CODE_SHIFT;
        send_message(ROOM_SYNC_MSG_TAKE_FURNITURE, &message, sizeof(message), ROOM_SYNC_TO_ALL);
    }
    ItemFootprint_Destruct(&footprint);
}
CLEAN_AS(func_020521d8, RoomSync_TakeFurniture)

/* func_020523e4: puts the furniture `code` on the scene's map at cell (x, y) of `layer`: its
 * code at its own cell and ROOM_SYNC_ITEM_COVERED at the others of its footprint, each cell's
 * switch set to `on` in the scene's RoomCells, and with `keeps_step` while on, `step` kept at
 * its own cell. The first cell that cannot be set ends it. With `send` on a linked session it
 * goes out as message 28.
 * BUG: the message's word is built in an uninitialised stack slot and its bit 31 is never set,
 * so the ROM sends what it held; here it is 0. The receiver does not read it. */
void RoomSync_PutFurniture(int scene, int x, int y, int layer, int on, int keeps_step, int step, u16 *code, u8 send_it)
{
    u16 first = *code;
    AcreMap *map = scene_map(scene);
    if (map == NULL) {
        return;
    }
    ItemFootprint footprint;
    ItemFootprint_Construct(&footprint, code);

    for (int i = 0; i < ItemFootprint_Count(&footprint); i++) {
        int cell_x = x + ItemFootprint_Cell(&footprint, (u32) i)->x;
        int cell_y = y + ItemFootprint_Cell(&footprint, (u32) i)->y;
        u16 put = i == 0 ? first : ROOM_SYNC_ITEM_COVERED;
        if (!AcreTile_SetItem(map, &put, cell_x, cell_y, (u8) layer)) {
            ItemFootprint_Destruct(&footprint);
            return;
        }
        RoomCells_SetSwitch(cell_x, cell_y, layer, on, (u8) scene);
        if (keeps_step && on && i == 0) {
            RoomCells_SetStep(cell_x, cell_y, step, scene);
        }
    }
    if (Session_IsLinked(data_020ccf94) && send_it) {
        u32 message = ((u32) x & 0xf) | ((u32) y & 0xf) << ROOM_SYNC_PUT_Y_SHIFT |
                      ((u32) step & 0xf) << ROOM_SYNC_PUT_STEP_SHIFT | ((u32) layer & 1) << ROOM_SYNC_PUT_LAYER_SHIFT |
                      ((u32) on & 1) << ROOM_SYNC_PUT_ON_SHIFT | ((u32) keeps_step & 1) << ROOM_SYNC_PUT_KEEPS_STEP_SHIFT |
                      (u32) first << ROOM_SYNC_PUT_CODE_SHIFT;
        send_message(ROOM_SYNC_MSG_PUT_FURNITURE, &message, sizeof(message), ROOM_SYNC_TO_ALL);
    }
    ItemFootprint_Destruct(&footprint);
}
CLEAN_AS(func_020523e4, RoomSync_PutFurniture)

/* func_020525a4: asks for `state` (with `value`) of the object at cell (x, y) of `layer`. Where
 * the session is not linked or this system is the host it is set at once (RoomSync_SetStateAt).
 * Otherwise, in the room shown with an object there and `send`, the host is asked (message 24
 * with the relay bit) and the object held still (unk_77D) until the answer; 1 when asked. */
int RoomSync_RequestStateAt(int x, int y, int layer, int state, u8 value, u8 flag, u8 send_it)
{
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session) || Session_IsLocalSlot(session, HOST_SLOT)) {
        return RoomSync_SetStateAt(x, y, layer, state, value, flag, send_it);
    }
    if (!room_shown()) {
        return 0;
    }
    RoomObject *object = object_at(x, y, layer);
    if (object == NULL || !send_it) {
        return 0;
    }
    if (RoomSync_SendState(x, y, layer, state, value, flag, ROOM_SYNC_TO_HOST)) {
        object->unk_77D = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020525a4, RoomSync_RequestStateAt)

/* func_0205265c: RoomSync_RequestStateAt at the object's cell (RoomObject_FindVariantCell) and
 * layer, sent; 0 outside the room shown or without a cell. */
int RoomSync_RequestState(RoomObject *object, int state, int value, int flag)
{
    if (!room_shown()) {
        return 0;
    }
    int x;
    int y;
    if (!RoomObject_FindVariantCell(object, &x, &y, NULL, 0)) {
        return 0;
    }
    return RoomSync_RequestStateAt(x, y, RoomObject_Layer(object), state, (u8) value, (u8) flag, 1);
}
CLEAN_AS(func_0205265c, RoomSync_RequestState)

/* func_020526b8: sets `state` with `value` on the object at cell (x, y) of `layer` of the room
 * shown (vtable slot 0x70) and, with `send`, tells everyone with the value the object keeps
 * (vtable slot 0x78). 0 without such an object. */
int RoomSync_SetStateAt(int x, int y, int layer, int state, u8 value, u8 flag, u8 send_it)
{
    if (!room_shown()) {
        return 0;
    }
    RoomObject *object = object_at(x, y, layer);
    if (object == NULL) {
        return 0;
    }
    object->vtable->vfunc_70(object, state, value);
    if (send_it) {
        int kept = object->vtable->vfunc_78(object);
        return RoomSync_SendState(x, y, layer, state, (u8) kept, flag, ROOM_SYNC_TO_ALL);
    }
    return 1;
}
CLEAN_AS(func_020526b8, RoomSync_SetStateAt)

/* func_02052738: RoomSync_SetStateAt at the object's cell and layer, sent; 0 outside the room
 * shown or without a cell. */
int RoomSync_SetState(RoomObject *object, int state, int value, int flag)
{
    if (!room_shown()) {
        return 0;
    }
    int x;
    int y;
    if (!RoomObject_FindVariantCell(object, &x, &y, NULL, 0)) {
        return 0;
    }
    return RoomSync_SetStateAt(x, y, RoomObject_Layer(object), state, (u8) value, (u8) flag, 1);
}
CLEAN_AS(func_02052738, RoomSync_SetState)

/* func_02052794: message 24 for the object at cell (x, y) of `layer`, sent with `kind` when the
 * session is linked and the object is not a preview (RoomObject_Unk76CIs2); sent to anyone but
 * everyone it asks to be relayed. 0 without an object there, else 1 (sent or not). */
int RoomSync_SendState(int x, int y, int layer, int state, u8 value, u8 flag, int kind)
{
    u32 relay = kind != ROOM_SYNC_TO_ALL;
    RoomObject *object = object_at(x, y, layer);
    if (object == NULL) {
        return 0;
    }
    if (Session_IsLinked(data_020ccf94) && !RoomObject_Unk76CIs2(object)) {
        u32 on = (u32) shows_on(object, state);
        u32 scene = SceneQuery_Current();
        u32 music = (u32) RoomObject_Unk00CIs3A(object);
        u32 message = (scene & ROOM_SYNC_STATE_SCENE) | ((u32) layer & 1) << ROOM_SYNC_STATE_LAYER_SHIFT |
                      (on & 1) << ROOM_SYNC_STATE_ON_SHIFT | ((u32) x & 0xf) << ROOM_SYNC_STATE_X_SHIFT |
                      ((u32) y & 0xf) << ROOM_SYNC_STATE_Y_SHIFT | ((u32) state & 0x1f) << ROOM_SYNC_STATE_STATE_SHIFT |
                      (u32) value << ROOM_SYNC_STATE_VALUE_SHIFT | relay << ROOM_SYNC_STATE_RELAY_SHIFT |
                      (music & 1) << ROOM_SYNC_STATE_MUSIC_SHIFT | ((u32) flag & 1) << ROOM_SYNC_STATE_FLAG_SHIFT;
        send_message(ROOM_SYNC_MSG_STATE, &message, sizeof(message), kind);
    }
    return 1;
}
CLEAN_AS(func_02052794, RoomSync_SendState)

/* func_02052960 (message 29): RoomSync_ToggleAt for the cell it names. */
void RoomSync_ReceiveToggle(const u16 *payload)
{
    u32 message = *payload;
    RoomSync_ToggleAt((int) (message & 0x3f), (int) (message >> ROOM_SYNC_TOGGLE_X_SHIFT & 0xf),
                      (int) (message >> ROOM_SYNC_TOGGLE_Y_SHIFT & 0xf), (int) (message >> ROOM_SYNC_TOGGLE_LAYER_SHIFT & 1),
                      1);
}
CLEAN_AS(func_02052960, RoomSync_ReceiveToggle)

/* func_0205298c: in the room shown, when it is `scene`, toggles the object at cell (x, y) of
 * `layer`: state 1 when its switch is off, else state 0, set and sent (RoomSync_SetStateAt). When
 * it goes on while LIGHTS_ON_MAX or more of the objects of kind 0x18 (RoomObject_TestUnk780Is18)
 * are on, one of those picked at random is switched off and set to state 0 first. */
void RoomSync_ToggleAt(int scene, int x, int y, int layer, u8 flag)
{
    if (SceneQuery_Current() != scene || !room_shown()) {
        return;
    }
    RoomObject *object = object_at(x, y, layer);
    if (object == NULL) {
        return;
    }
    if (Switch_Value(&object->light_switch) == 0) {
        if (RoomObjects_CountOn((RoomObjectsTest) func_ov004_02211280) >= LIGHTS_ON_MAX) {
            RoomObject *other = RoomObjects_PickOn((RoomObjectsTest) func_ov004_02211280, 0);
            if (other != NULL) {
                RoomSync_SetState(other, 0, ROOM_SYNC_NO_VALUE, flag);
            }
        }
        RoomSync_SetStateAt(x, y, layer, 1, ROOM_SYNC_NO_VALUE, flag, 1);
    } else {
        RoomSync_SetStateAt(x, y, layer, 0, ROOM_SYNC_NO_VALUE, flag, 1);
    }
}
CLEAN_AS(func_0205298c, RoomSync_ToggleAt)

/* func_02052a3c (message 26, from `scene`): puts the item on top, not sent on. */
void RoomSync_ReceivePutItem(int scene, const u32 *payload)
{
    u32 message = *payload;
    u16 code = (u16) (message >> ROOM_SYNC_PUT_ITEM_CODE_SHIFT);
    RoomSync_PutItem(scene, (int) (message & 0xf), (int) (message >> ROOM_SYNC_PUT_ITEM_Y_SHIFT & 0xf), &code, 0);
}
CLEAN_AS(func_02052a3c, RoomSync_ReceivePutItem)

/* func_02052a64 (message 28, from `scene`): puts the furniture on the map, not sent on. */
void RoomSync_ReceivePutFurniture(int scene, const u32 *payload)
{
    u32 message = *payload;
    u16 code = (u16) (message >> ROOM_SYNC_PUT_CODE_SHIFT);
    RoomSync_PutFurniture(scene, (int) (message & 0xf), (int) (message >> ROOM_SYNC_PUT_Y_SHIFT & 0xf),
                          (int) (message >> ROOM_SYNC_PUT_LAYER_SHIFT & 1), (int) (message >> ROOM_SYNC_PUT_ON_SHIFT & 1),
                          (int) (message >> ROOM_SYNC_PUT_KEEPS_STEP_SHIFT & 1),
                          (int) (message >> ROOM_SYNC_PUT_STEP_SHIFT & 0xf), &code, 0);
}
CLEAN_AS(func_02052a64, RoomSync_ReceivePutFurniture)

/* func_02052ac8 (message 27, from `scene`): takes the furniture off the map, not sent on. */
void RoomSync_ReceiveTakeFurniture(int scene, const u32 *payload)
{
    u32 message = *payload;
    u16 code = (u16) (message >> ROOM_SYNC_TAKE_CODE_SHIFT);
    RoomSync_TakeFurniture(scene, (int) (message >> ROOM_SYNC_TAKE_X_SHIFT & 0xf),
                           (int) (message >> ROOM_SYNC_TAKE_Y_SHIFT & 0xf), (int) (message & 1),
                           (int) (message >> ROOM_SYNC_TAKE_ON_SHIFT & 1), &code,
                           (int) (message >> ROOM_SYNC_TAKE_WITH_TOP_SHIFT & 1), 0);
}
CLEAN_AS(func_02052ac8, RoomSync_ReceiveTakeFurniture)

/* func_02052b20 (message 25): sets the house room's lit bit and, when asked to relay it (on the
 * host), sends it on to everyone without the relay bit. */
void RoomSync_ReceiveLit(const u8 *payload)
{
    u8 message = *payload;
    int scene = message & ROOM_SYNC_LIT_SCENE;
    int lit = (message & ROOM_SYNC_LIT_ON) != 0;
    HouseRecord_SetLit((HouseRecord *) (void *) data_021ebcd4, scene, lit);
    if (message & ROOM_SYNC_LIT_RELAY) {
        u8 relayed = (u8) (message & ~ROOM_SYNC_LIT_RELAY);
        send_message(ROOM_SYNC_MSG_LIT, &relayed, sizeof(relayed), ROOM_SYNC_TO_ALL);
    }
}
CLEAN_AS(func_02052b20, RoomSync_ReceiveLit)

/* func_02052b90 (message 24): applies the state (RoomSync_ApplyState) and, when asked to relay
 * it (on the host), sends it on to everyone without the relay bit. */
void RoomSync_ReceiveState(const u32 *payload)
{
    u32 message = *payload;
    RoomSync_ApplyState((int) (message & ROOM_SYNC_STATE_SCENE), (int) (message >> ROOM_SYNC_STATE_X_SHIFT & 0xf),
                        (int) (message >> ROOM_SYNC_STATE_Y_SHIFT & 0xf), (int) (message >> ROOM_SYNC_STATE_LAYER_SHIFT & 1),
                        (u8) (message >> ROOM_SYNC_STATE_STATE_SHIFT & 0x1f), (u8) (message >> ROOM_SYNC_STATE_ON_SHIFT & 1),
                        (u8) (message >> ROOM_SYNC_STATE_MUSIC_SHIFT & 1), (u8) (message >> ROOM_SYNC_STATE_FLAG_SHIFT & 1),
                        (u8) (message >> ROOM_SYNC_STATE_VALUE_SHIFT));
    if (message >> ROOM_SYNC_STATE_RELAY_SHIFT & 1) {
        u32 relayed = message & ~(1u << ROOM_SYNC_STATE_RELAY_SHIFT);
        send_message(ROOM_SYNC_MSG_STATE, &relayed, sizeof(relayed), ROOM_SYNC_TO_ALL);
    }
}
CLEAN_AS(func_02052b90, RoomSync_ReceiveState)

/* func_02052cac: applies a state from message 24. In the room shown, when it is `scene`, the
 * object at the cell takes it (vtable slot 0x70) and its answer is the result. Otherwise the
 * scene's records follow: a step item on the floor of its map gets `value`'s low 4 bits as
 * its step when on and loses it when off; the cell's switch becomes `on`; and for a music
 * player the house room gets the song `value` (song 0 past the last) as its music item when on,
 * or no music item when off unless `flag` is set. The result is then 1. */
int RoomSync_ApplyState(int scene, int x, int y, int layer, u8 state, u8 on, u8 music, u8 flag, u8 value)
{
    if (room_shown() && SceneQuery_Current() == scene) {
        RoomObject *object = object_at(x, y, layer);
        if (object != NULL) {
            return object->vtable->vfunc_70(object, state, value);
        }
    }
    AcreMap *map = (AcreMap *) (uintptr_t) SceneMap_OfScene(scene);
    if (map != NULL) {
        u16 *item = map_item(map, x, y, LAYER_FLOOR);
        if (item != NULL && is_step_item(*item)) {
            if (on) {
                RoomCells_SetStep(x, y, value & 0xf, scene);
            } else {
                RoomCells_ClearStep(x, y, scene);
            }
        }
    }
    RoomCells_SetSwitch(x, y, layer, on, (u8) scene);
    if (music) {
        if (on) {
            u16 song = (u16) (ROOM_SYNC_SONG_ITEM_FIRST + (value < ROOM_SYNC_SONGS ? value : 0));
            HouseRecord_SetSong(scene, &song);
        } else if (!flag) {
            HouseRecord_StopSong(scene);
        }
    }
    return 1;
}
CLEAN_AS(func_02052cac, RoomSync_ApplyState)
