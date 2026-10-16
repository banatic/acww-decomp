/* The town's objects of codes 0x5000-0x5021 (town_objects.h). */
#include "town_objects.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/block_020b220c.h"
#include "main/session.h"
#include "main/villager_roster.h"

#define TOWN_OBJECTS_VISITORS 0x0f /* the low four bits of a visit record */
#define TOWN_OBJECTS_ANSWER_SHIFT 4

/* The messages: a scene actor's mode, a request to visit or its answer, a visitor gone. */
#define TOWN_OBJECTS_MESSAGE_MODE 0x22
#define TOWN_OBJECTS_MESSAGE_VISIT 0x23
#define TOWN_OBJECTS_MESSAGE_LEFT 0x24
/* The kind message 0x22 is sent with. */
#define TOWN_OBJECTS_MODE_KIND 4
/* A visit message's byte: the answer (0 for a request) in bits 0-1, the index in bits 2-7. */
#define TOWN_OBJECTS_VISIT_ANSWER 3
#define TOWN_OBJECTS_VISIT_INDEX_SHIFT 2
/* A mode message's halfword: the object's index in bits 0-5, the mode in bits 6-11. */
#define TOWN_OBJECTS_MODE_INDEX 0x3f
#define TOWN_OBJECTS_MODE_SHIFT 6
#define TOWN_OBJECTS_MODE_MASK 0x3f
/* A scene actor's vtable slot that sets its mode, and answers whether it took it. */
#define TOWN_OBJECTS_SET_MODE_SLOT 0x6c

/* The villagers' houses, 0x5001-0x5008 for villagers 0-7. */
#define TOWN_OBJECTS_FIRST_HOUSE 0x5001
#define TOWN_OBJECTS_LAST_HOUSE 0x5008
#define TOWN_OBJECTS_VILLAGER_STATE_2 2

/* The empty item code, written over the tiles TownObjects_MarkFootprints marks. */
#define TOWN_OBJECTS_ITEM_NONE 0xfff1
#define TOWN_OBJECTS_ACRE_TILES 16

/* The flags of an acre's model (func_02037bd8) that make room for the objects. */
#define TOWN_OBJECTS_MODEL_5014 0x001  /* codes 0x5014-0x501a */
#define TOWN_OBJECTS_MODEL_STORE 0x002 /* codes 0x500d-0x5010 (the store) and 0x500c */
#define TOWN_OBJECTS_MODEL_5000 0x200
#define TOWN_OBJECTS_MODEL_5011 0x800

extern u8 data_020e54a8; /* 0 or 1, a mode many scenes test */
extern NetSession *data_020ccf94;
extern u8 data_021f4bac[TOWN_OBJECTS_COUNT]; /* the visit records */
extern u8 data_021f4b14;                     /* see TownObjects_VisitorsInScene */
extern u32 data_021f4b50;                    /* TownObjects_AtKeptTile's last answer */
extern const u16 data_020d1ebc[];            /* each scene's object code */
extern const SceneActorRecord data_020d1f24[TOWN_OBJECTS_COUNT];
extern u8 data_021e5a2c[];  /* the town's villagers (VillagerTown) */
extern void *data_021c80bc; /* the map being played on (AcreMap), or 0 */
extern s8 data_021f69b8[];  /* a tile at bytes 0x13 and 0x14 */
/* The function-local static item code of TownObjects_MarkFootprints: its guard, the code
 * and its destruction record. */
extern u32 data_021f4b40;
extern u16 data_021f4b28;
extern u8 data_021f4ba0[];

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *item); /* the item code's destructor (does nothing) */

extern u8 func_020b65c4(void);                /* the scene */
extern int func_020b67e8(unsigned int scene); /* whether 1 <= scene <= 5 */
/* An object's index (-1 outside the codes), and the code of an index (0x5000 past them). */
extern int func_020b3f58(u16 code);
extern u16 func_0204bbd4(unsigned int index);
/* The number of bits set among the low four. */
extern int func_020b3fc0(int bits);
/* A record of data_020d1f24 copied out, its byte 9, and the copy's (empty) destructor; the
 * record's code with a tile's x and z packed below it. */
extern void func_020b2a68(SceneActorRecord *dst, const SceneActorRecord *src);
extern unsigned int func_020b2a3c(SceneActorRecord *record);
extern void func_020b2a64(SceneActorRecord *record);
extern unsigned int func_020b2a20(SceneActorRecord *record, int x, int z);
/* A villager's state (2 is the one TownObjects_HouseState2 asks about). */
extern int func_0207f1d8(void *villager);
/* Overlay 3's scene actor of a code, or 0; the mode recorded for an object without one. */
extern void *func_ov003_02220174(u16 code);
extern int func_020b30e8(unsigned int code, u8 mode);
/* main's table at data_021f69d0 (its address), whether the map's mode applies, and the two
 * bytes of the kept tile. */
extern int func_020b5e10(void);
extern int func_020b6660(void);
extern s8 func_020b64d4(s8 *tile);
extern s8 func_020b64cc(s8 *tile);
/* Acre records: the model number, its flags, the code of tile (x, z) in a layer (or 0). */
extern int func_02037e84(u8 *acre);
extern int func_02037bd8(unsigned int model);
extern u16 *func_02037e0c(u8 *acre, int x, int z, u8 layer);
/* Item codes: 0x5014-0x501a, 0x500d-0x5010, a code with a variant, a code's item. */
extern int func_0204bb00(u16 *code);
extern int func_0204bba8(u16 *code);
extern int func_0204bcdc(u16 *code);
extern int func_0204bc64(u16 *code);
/* An object's shape: the tiles it covers, as offsets from its own tile. */
extern void *func_020b3b50(u16 *object);
extern unsigned int func_020b3eb8(void *shape);
extern int func_020b3e08(void *shape, int *x, int *z, unsigned int index);

typedef int TownObjectsSetMode(void *actor, unsigned int mode);

/* The visit record of index `index`, as the ARM addresses it (an index of -1 is the byte
 * before the table). */
static u8 *town_objects_record(u32 index)
{
    return (u8 *) (uintptr_t) ((u32) (uintptr_t) data_021f4bac + index);
}

static u32 town_objects_visitors(const u8 *record)
{
    return *record & TOWN_OBJECTS_VISITORS;
}

static void town_objects_set_visitors(u8 *record, u32 visitors)
{
    *record = (u8) ((*record & ~TOWN_OBJECTS_VISITORS) | (visitors & TOWN_OBJECTS_VISITORS));
}

static u32 town_objects_answer(const u8 *record)
{
    return *record >> TOWN_OBJECTS_ANSWER_SHIFT;
}

static void town_objects_set_answer(u8 *record, u32 answer)
{
    *record = (u8) ((*record & TOWN_OBJECTS_VISITORS) | ((answer & 0xf) << TOWN_OBJECTS_ANSWER_SHIFT));
}

/* One bit, shifted as the ARM shifts by a register: by the low byte, nothing left past 31. */
static u32 town_objects_bit(int shift)
{
    u32 amount = (u32) shift & 0xffu;
    return amount < 32 ? 1u << amount : 0;
}

/* The record of data_020d1f24 for an index; the first for one past them. */
static const SceneActorRecord *town_objects_info(u32 index)
{
    return index < TOWN_OBJECTS_COUNT ? &data_020d1f24[index] : &data_020d1f24[0];
}

/* Rounding down as the ARM's arithmetic shift does. */
static int town_objects_acre_of(int tile)
{
    return tile >= 0 ? tile / TOWN_OBJECTS_ACRE_TILES : -1 - (-1 - tile) / TOWN_OBJECTS_ACRE_TILES;
}

/* The scene actor's function that sets its mode. */
static TownObjectsSetMode *town_objects_set_mode(const void *actor)
{
    u32 vtable = *(const u32 *) actor;
    u32 function = *(const u32 *) (uintptr_t) (vtable + TOWN_OBJECTS_SET_MODE_SLOT);
    return (TownObjectsSetMode *) (uintptr_t) function;
}

/* ---- The objects' footprints on the town's map */

/* Whether the object `item` is the one of code `code`; for a code with a variant, whether
 * their items are the same. */
static int town_objects_is(u16 *item, u16 code)
{
    if (func_0204bcdc(item)) {
        u16 wanted = code;
        int own = func_0204bc64(item);
        return own == func_0204bc64(&wanted);
    }
    return *item == code;
}

/* Whether an object at tile (x, z) of its acre is out of the place the acre's model makes for
 * it: always when the model lacks the object's flag; else unless it is off the acre's first
 * column and, for the models that name one, on the row `row` (-1: any row). */
static int town_objects_out_of_place(int has_flag, int row, int x, int z)
{
    if (!has_flag) {
        return 1;
    }
    if (row < 0) {
        row = z;
    }
    return !(x != 0 && row == z);
}

static int town_objects_5014_row(int model)
{
    return model >= 0x1d && model <= 0x1f ? 5 : -1;
}

static int town_objects_store_row(int model)
{
    switch (model) {
        case 0x23:
            return 9;
        case 0x24:
            return 8;
        case 0x25:
            return 4;
    }
    return -1;
}

static int town_objects_500c_row(int model)
{
    switch (model) {
        case 0x23:
            return 8;
        case 0x24:
            return 9;
        case 0x25:
            return 6;
    }
    return -1;
}

static int town_objects_5011_row(int model)
{
    switch (model) {
        case 0x20:
            return 6;
        case 0x21:
            return 0xa;
        case 0x22:
            return 5;
    }
    return -1;
}

static int town_objects_5000_row(int model)
{
    return model >= 0x26 && model <= 0x28 ? 4 : -1;
}

/* func_020b1e54: on the town's map, outside its first row and column of acres, every tile
 * under an object out of the place its acre's model makes for it (town_objects_out_of_place)
 * gets the empty item code.
 * QUIRK: the first call builds a function-local static item code (0xfff1) and registers it
 * for destruction (func_020051b0, which does nothing); it is what is written. Without acre
 * records the model is still asked of address 0, once per acre. Each of the five tests runs
 * whatever the others answered. */
void TownObjects_MarkFootprints(void)
{
    if ((data_021f4b40 & 1) == 0) {
        data_021f4b28 = TOWN_OBJECTS_ITEM_NONE;
        __register_global_object(&data_021f4b28, (void *) func_020051b0, data_021f4ba0);
        data_021f4b40 |= 1;
    }

    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return;
    }
    for (int acre_z = 1; acre_z < town->acres_high; acre_z++) {
        for (int acre_x = 1; acre_x < town->acres_wide; acre_x++) {
            u8 *acre = NULL;
            if ((u32) acre_x < (u32) town->acres_wide && (u32) acre_z < (u32) town->acres_high && town->acres != NULL) {
                acre = town->acres + ACRE_MAP_ACRE_SIZE * (acre_x + acre_z * town->acres_wide);
            }
            int model = func_02037e84(acre);
            int flags = func_02037bd8((unsigned int) model);

            for (int z = 0; z < TOWN_OBJECTS_ACRE_TILES; z++) {
                for (int x = 0; x < TOWN_OBJECTS_ACRE_TILES; x++) {
                    u16 *object = acre != NULL ? func_02037e0c(acre, x, z, 0) : NULL;
                    if (object == NULL) {
                        continue;
                    }
                    int mark = 0;
                    if (func_0204bb00(object) &&
                        town_objects_out_of_place(flags & TOWN_OBJECTS_MODEL_5014, town_objects_5014_row(model), x, z)) {
                        mark = 1;
                    }
                    if (func_0204bba8(object) &&
                        town_objects_out_of_place(flags & TOWN_OBJECTS_MODEL_STORE, town_objects_store_row(model), x, z)) {
                        mark = 1;
                    }
                    if (town_objects_is(object, 0x500c) &&
                        town_objects_out_of_place(flags & TOWN_OBJECTS_MODEL_STORE, town_objects_500c_row(model), x, z)) {
                        mark = 1;
                    }
                    if (town_objects_is(object, 0x5011) &&
                        town_objects_out_of_place(flags & TOWN_OBJECTS_MODEL_5011, town_objects_5011_row(model), x, z)) {
                        mark = 1;
                    }
                    if (town_objects_is(object, 0x5000) &&
                        town_objects_out_of_place(flags & TOWN_OBJECTS_MODEL_5000, town_objects_5000_row(model), x, z)) {
                        mark = 1;
                    }
                    if (!mark) {
                        continue;
                    }

                    int tile_x;
                    int tile_z;
                    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
                    void *shape = func_020b3b50(object);
                    if (shape == NULL) {
                        continue;
                    }
                    unsigned int count = func_020b3eb8(shape);
                    for (unsigned int i = 0; i < count; i++) {
                        int dx = 0;
                        int dz = 0;
                        if (func_020b3e08(shape, &dx, &dz, i)) {
                            AcreTile_SetItem(town, &data_021f4b28, tile_x + dx, tile_z + dz, 0);
                        }
                    }
                }
            }
        }
    }
}
CLEAN_AS(func_020b1e54, TownObjects_MarkFootprints)

/* ---- Visits */

/* func_020b2300: the players in the current scene's object, in mode 1; 0 in mode 0. */
int TownObjects_VisitorsHere(void)
{
    if (data_020e54a8 == 1) {
        return TownObjects_VisitorsInScene(func_020b65c4());
    }
    return 0;
}
CLEAN_AS(func_020b2300, TownObjects_VisitorsHere)

/* func_020b232c: the players visiting scene `scene`'s object, and two more in scenes 1-5 while
 * TownObjects_ExtraVisitors is set. */
int TownObjects_VisitorsInScene(int scene)
{
    int count = func_020b3fc0(TownObjects_VisitorMask(scene));
    if (func_020b67e8((unsigned int) scene) != 0 && TownObjects_ExtraVisitors() != 0) {
        return count + 2;
    }
    return count;
}
CLEAN_AS(func_020b232c, TownObjects_VisitorsInScene)

/* func_020b235c: the slots visiting scene `scene`'s object; 0 on a linked system other than
 * slot 0's, or when the scene's code is not an object's. */
int TownObjects_VisitorMask(int scene)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && !Session_IsLocalSlot(session, 0)) {
        return 0;
    }
    u16 code = *(const u16 *) (uintptr_t) ((u32) (uintptr_t) data_020d1ebc + (u32) scene * 2u);
    if (code < TOWN_OBJECTS_FIRST || code > TOWN_OBJECTS_LAST) {
        return 0;
    }
    return (int) town_objects_visitors(town_objects_record((u32) func_020b3f58(code)));
}
CLEAN_AS(func_020b235c, TownObjects_VisitorMask)

/* func_020b23c8 */
void TownObjects_ClearExtraVisitors(void)
{
    data_021f4b14 = 0;
}
CLEAN_AS(func_020b23c8, TownObjects_ClearExtraVisitors)

/* func_020b23d4: set by overlay 4. */
void TownObjects_SetExtraVisitors(void)
{
    data_021f4b14 = 1;
}
CLEAN_AS(func_020b23d4, TownObjects_SetExtraVisitors)

/* func_020b23e0 */
u8 TownObjects_ExtraVisitors(void)
{
    return data_021f4b14;
}
CLEAN_AS(func_020b23e0, TownObjects_ExtraVisitors)

/* func_020b23ec: the player of slot `slot` leaves object `code`: slot 0's system, a system
 * playing alone or one without a slot (slot SESSION_SLOTS) clears its bit; the others tell slot 0's (message 0x24).
 * QUIRK: a code that is not an object's gives index -1: the byte before the records is
 * changed, or index 0xff sent. */
void TownObjects_Leave(int code, int slot)
{
    int index = func_020b3f58((u16) code);
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session) || Session_IsLocalSlot(session, 0) || Session_IsLocalSlot(session, SESSION_SLOTS)) {
        u8 *record = town_objects_record((u32) index);
        town_objects_set_visitors(record, town_objects_visitors(record) & ~town_objects_bit(slot));
    } else {
        u8 message = (u8) index;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &message, 1);
        Session_EndMessage(session, TOWN_OBJECTS_MESSAGE_LEFT, 0);
    }
}
CLEAN_AS(func_020b23ec, TownObjects_Leave)

/* func_020b2470: the answer to the last request to visit object `code`, 0 while none came. */
int TownObjects_VisitAnswer(u16 code)
{
    return (int) town_objects_answer(town_objects_record((u32) func_020b3f58(code)));
}
CLEAN_AS(func_020b2470, TownObjects_VisitAnswer)

/* func_020b248c: this system's player asks to visit object `code`. Slot 0's system or one
 * playing alone answers at once for slot 0 (town_objects.h); the others clear the answer and
 * ask slot 0's (message 0x23).
 * QUIRK: letting the player in asks TownObjects_HouseState2 a second time, its answer
 * dropped. */
void TownObjects_RequestVisit(u32 code)
{
    u32 index = (u32) func_020b3f58((u16) code);
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session) || Session_IsLocalSlot(session, 0)) {
        u8 *record = town_objects_record(index);
        u32 visitors = town_objects_visitors(record);
        u32 before = (u32) func_020b3fc0((int) visitors);
        visitors |= 1;
        u32 after = (u32) func_020b3fc0((int) visitors);
        SceneActorRecord info;
        func_020b2a68(&info, town_objects_info(index));
        if (after > func_020b2a3c(&info)) {
            town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_FULL);
        } else if (TownObjects_HouseState2((int) code) && before == 0) {
            town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_HOUSE);
        } else {
            town_objects_set_visitors(record, visitors);
            town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_LET_IN);
            TownObjects_HouseState2((int) code);
        }
        func_020b2a64(&info);
    } else {
        town_objects_set_answer(town_objects_record(index), 0);
        u8 request = (u8) ((index & TOWN_OBJECTS_MODE_INDEX) << TOWN_OBJECTS_VISIT_INDEX_SHIFT);
        Session_BeginMessage(session);
        Session_AppendMessage(session, &request, 1);
        Session_EndMessage(session, TOWN_OBJECTS_MESSAGE_VISIT, 0);
    }
}
CLEAN_AS(func_020b248c, TownObjects_RequestVisit)

/* func_020b25a8: no visitors and no answers; TownObjects_ExtraVisitors cleared. */
void TownObjects_ResetVisits(void)
{
    for (int i = 0; i < TOWN_OBJECTS_COUNT; i++) {
        data_021f4bac[i] = 0;
    }
    data_021f4b14 = 0;
}
CLEAN_AS(func_020b25a8, TownObjects_ResetVisits)

/* func_020b25e0 (message 0x24): the player of slot `slot` left object `*index`. */
void TownObjects_OnLeftMessage(const u8 *index, u32 slot)
{
    u8 *record = town_objects_record(*index);
    town_objects_set_visitors(record, town_objects_visitors(record) & ~town_objects_bit((int) slot));
}
CLEAN_AS(func_020b25e0, TownObjects_OnLeftMessage)

/* func_020b260c (message 0x23) from slot `slot`: an answer is kept; a request is answered as
 * TownObjects_RequestVisit answers this system's (with the sender's bit), and the answer sent
 * back with the sender's slot as the message's kind.
 * QUIRK: letting the player in asks TownObjects_HouseState2 a second time, its answer
 * dropped; an index past 0x21 (six bits allow 63) reaches past the records. */
void TownObjects_OnVisitMessage(u8 *payload, int slot)
{
    u32 answer = *payload & TOWN_OBJECTS_VISIT_ANSWER;
    u32 index = *payload >> TOWN_OBJECTS_VISIT_INDEX_SHIFT;
    u8 *record = town_objects_record(index);
    if (answer != 0) {
        town_objects_set_answer(record, answer);
        return;
    }

    u32 visitors = town_objects_visitors(record);
    u32 before = (u32) func_020b3fc0((int) visitors);
    visitors = (u8) (visitors | town_objects_bit(slot));
    u32 after = (u32) func_020b3fc0((int) visitors);
    SceneActorRecord info;
    func_020b2a68(&info, town_objects_info(index));
    if (after > func_020b2a3c(&info)) {
        town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_FULL);
    } else {
        int code = func_0204bbd4(index);
        if (TownObjects_HouseState2(code) && before == 0) {
            town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_HOUSE);
        } else {
            town_objects_set_visitors(record, visitors);
            town_objects_set_answer(record, TOWN_OBJECTS_ANSWER_LET_IN);
            TownObjects_HouseState2(code);
        }
    }

    u8 reply = (u8) ((*payload & ~TOWN_OBJECTS_VISIT_ANSWER) | (town_objects_answer(record) & TOWN_OBJECTS_VISIT_ANSWER));
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &reply, 1);
    Session_EndMessage(session, TOWN_OBJECTS_MESSAGE_VISIT, (u32) slot);
    func_020b2a64(&info);
}
CLEAN_AS(func_020b260c, TownObjects_OnVisitMessage)

/* func_020b2734 (message 0x22): in mode 0, overlay 3's scene actor of the object takes the
 * mode; without one, or in mode 1, the mode is recorded (func_020b30e8). */
void TownObjects_OnModeMessage(const u16 *payload)
{
    u16 code = func_0204bbd4(*payload & TOWN_OBJECTS_MODE_INDEX);
    u8 mode = (u8) ((*payload >> TOWN_OBJECTS_MODE_SHIFT) & TOWN_OBJECTS_MODE_MASK);
    if (data_020e54a8 == 0) {
        void *actor = func_ov003_02220174(code);
        if (actor != NULL) {
            town_objects_set_mode(actor)(actor, mode);
            return;
        }
    }
    func_020b30e8(code, mode);
}
CLEAN_AS(func_020b2734, TownObjects_OnModeMessage)

/* func_020b278c: for a villager's house (0x5001-0x5008), whether its villager is in state 2;
 * else 0. */
int TownObjects_HouseState2(int code)
{
    u16 house = (u16) code;
    if (house < TOWN_OBJECTS_FIRST_HOUSE || house > TOWN_OBJECTS_LAST_HOUSE) {
        return 0;
    }
    return TownObjects_VillagerState2(house - TOWN_OBJECTS_FIRST_HOUSE);
}
CLEAN_AS(func_020b278c, TownObjects_HouseState2)

/* func_020b27d4: whether the town has villager `villager` and it is in state 2. */
int TownObjects_VillagerState2(int villager)
{
    u8 *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
    if (record == NULL) {
        return 0;
    }
    return func_0207f1d8(record) == TOWN_OBJECTS_VILLAGER_STATE_2;
}
CLEAN_AS(func_020b27d4, TownObjects_VillagerState2)

/* func_020b2800: in mode 0, the scene actor is given `mode` (its vtable's slot 0x6c); when it
 * takes it on a linked system, the others are told (message 0x22). Whether it took it; 0 in
 * mode 1. */
int TownObjects_SetActorMode(SceneActor *actor, unsigned int mode)
{
    if (data_020e54a8 != 0 || town_objects_set_mode(actor)(actor, mode) == 0) {
        return 0;
    }
    if (Session_IsLinked(data_020ccf94)) {
        const u16 *code = (const u16 *) (uintptr_t) (u32) SceneActor_CodeAddress(actor);
        u16 message = (u16) ((*code & TOWN_OBJECTS_MODE_INDEX) | ((mode & TOWN_OBJECTS_MODE_MASK) << TOWN_OBJECTS_MODE_SHIFT));
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &message, 2);
        Session_EndMessage(session, TOWN_OBJECTS_MESSAGE_MODE, TOWN_OBJECTS_MODE_KIND);
    }
    return 1;
}
CLEAN_AS(func_020b2800, TownObjects_SetActorMode)

/* func_020b289c: where func_020b6660 agrees, func_020b22b8 is 0 and in mode 0: the object on
 * the kept tile (bytes 0x13 and 0x14 of data_021f69b8) of the map being played on, as its
 * record's code with the tile's x and z packed below it (func_020b2a20); else 0. */
int TownObjects_AtKeptTile(void)
{
    if (func_020b6660() == 0 || Block020b220c_Flag4b18() != 0) {
        return 0;
    }
    if (data_020e54a8 != 0) {
        return 0;
    }
    func_020b5e10();
    int x = func_020b64d4(data_021f69b8);
    func_020b5e10();
    int z = func_020b64cc(data_021f69b8);
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int acre_x = town_objects_acre_of(x);
    int acre_z = town_objects_acre_of(z);
    u16 *object = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * TOWN_OBJECTS_ACRE_TILES,
                                      z - acre_z * TOWN_OBJECTS_ACRE_TILES, 0);
    if (object == NULL || *object < TOWN_OBJECTS_FIRST || *object > TOWN_OBJECTS_LAST) {
        return 0;
    }
    SceneActorRecord info;
    func_020b2a68(&info, town_objects_info(*object & 0xfffu));
    int packed = (int) func_020b2a20(&info, x, z);
    func_020b2a64(&info);
    return packed;
}
CLEAN_AS(func_020b289c, TownObjects_AtKeptTile)

/* func_020b2980 */
void TownObjects_KeepAtKeptTile(void)
{
    data_021f4b50 = (u32) TownObjects_AtKeptTile();
}
CLEAN_AS(func_020b2980, TownObjects_KeepAtKeptTile)
