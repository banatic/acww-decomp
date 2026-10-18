/* The cockroaches of the player's house (house_roaches.h). */
#include "house_roaches.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/house_record.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/scene_kinds.h"
#include "main/session.h"
#include "main/session_players.h"
#include "house_roach.h"

/* The cockroaches out now, the count still in the house (out ones included), the process
 * (their parent), and the cockroaches out by slot. */
extern u8 data_ov004_02259a08;
extern u8 data_ov004_02259a0c;
extern Process *data_ov004_02259a10;
extern HouseRoach *data_ov004_02259a18[HOUSE_ROACHES_MAX];

/* The class's vtable and the process base's. */
extern const u32 data_ov004_022561dc[];
extern const u32 data_020da13c[];

extern HouseRecord data_021ebcd4; /* the house */
extern AcreMap *data_021c80bc;    /* the room's map */
extern NetSession *data_020ccf94; /* the link with other players */

#define HOUSE_ROACH_PROFILE 0xc0
#define HOUSE_ROACH_FLOOR_GROUP 0x1f
#define HOUSE_ROACH_GONE 0xffff
#define HOUSE_ROACH_HEIGHT 0x200 /* above the floor cell's centre */
#define HOUSE_ROACHES_NO_ITEM 0xfff1
#define HOUSE_ROACHES_PLAYER 4 /* the own player's actor */
#define HOUSE_ROACHES_MAX_ROWS 33
#define HOUSE_ROACHES_FAR 0x0fffffff

/* A cockroach as the process it is. */
static Process *roach_process(HouseRoach *roach)
{
    return (Process *) (void *) roach;
}

/* Slot `index` read the way the ROM's code does, also before the table (the words before it
 * are the process pointer and data_ov004_02259a14). */
static HouseRoach *roach_slot_any(int index)
{
    return *(HouseRoach **) ((uintptr_t) data_ov004_02259a18 + (uintptr_t) (index * 4));
}

/* The ARM's shifts by a register: 32 and more give 0. */
static u32 bit(int n)
{
    return n < 32 ? 1u << n : 0;
}

static u32 shift_right(u32 value, int n)
{
    return n < 32 ? value >> n : 0;
}

/* func_ov004_0223e5f0: the count read from the house's record; whether there are any. */
int HouseRoaches_ReadCount(Process *self)
{
    (void) self;
    data_ov004_02259a0c = HouseRecord_Absence(&data_021ebcd4);
    return data_ov004_02259a0c != 0;
}
CLEAN_AS(func_ov004_0223e5f0, HouseRoaches_ReadCount)

/* Whether the floor cell (x, z) of the room's map is empty: a cell whose unit allows it, with
 * no item (its variant's item compared, for an item with variants). */
static int floor_cell_empty(AcreMap *map, int x, int z)
{
    if (AcreTile_UnitByte04(map, x, z) == 0) {
        return 0;
    }
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    u16 *item = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - (acre_x << 4), z - (acre_z << 4), 0);
    if (item == NULL) {
        return 0;
    }
    if (ItemCode_HasVariant(item)) {
        u16 none = HOUSE_ROACHES_NO_ITEM;
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(&none);
    }
    return *item == HOUSE_ROACHES_NO_ITEM;
}

/* func_ov004_0223e618: the empty floor cells of the room are noted, row by row, then up to
 * three cockroaches (while fewer are out than the count) let out on cells picked at random
 * among them, each cell once, 0x200 above its centre, the process their parent.
 * QUIRK: the number of empty cells is counted in a byte; a cockroach with no cell left (none
 * picked) is let out at the origin.
 * REQUIRES: the room's map exists and is at most 33 cells high (the ROM's code tests the map
 * for null only after reading its height). */
int HouseRoaches_SpawnOnFloor(Process *self)
{
    AcreMap *map = data_021c80bc;
    u32 empty[HOUSE_ROACHES_MAX_ROWS];
    u8 count = 0;
    for (int z = 0; z < map->tiles_high; z++) {
        empty[z] = 0;
        for (int x = 0; x < map->tiles_wide; x++) {
            if (floor_cell_empty(map, x, z)) {
                count++;
                empty[z] |= bit(x);
            }
        }
    }
    for (u8 slot = 0; slot < HOUSE_ROACHES_MAX && data_ov004_02259a08 < data_ov004_02259a0c; slot++) {
        if (count == 0) {
            break;
        }
        Vec3 position = {0, 0, 0};
        u8 pick = (u8) (MainRandom_Below(count) + 1);
        count--;
        for (int z = 0; z < map->tiles_high; z++) {
            int found = 0;
            for (int x = 0; x < map->tiles_wide; x++) {
                if (shift_right(empty[z], x) & 1) {
                    pick--;
                }
                if (pick == 0) {
                    empty[z] -= bit(x);
                    AcreTile_TileCentre(&position, (u32) x, (u32) z);
                    position.y = HOUSE_ROACH_HEIGHT;
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        data_ov004_02259a18[slot] =
            (HouseRoach *) (intptr_t) Actor_Spawn(HOUSE_ROACH_PROFILE, HOUSE_ROACH_FLOOR_GROUP, &position, NULL, self);
        data_ov004_02259a08++;
    }
    return 1;
}
CLEAN_AS(func_ov004_0223e618, HouseRoaches_SpawnOnFloor)

/* func_ov004_0223e7b4: one more cockroach at `point` turned by `angle`, in the first free slot,
 * when no link is up, fewer than three are out and more are in the house; whether it was
 * made. */
int HouseRoaches_SpawnAt(const Vec3 *point, const s16 *angle)
{
    if (Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    if (data_ov004_02259a08 >= HOUSE_ROACHES_MAX || (int) data_ov004_02259a0c - (int) data_ov004_02259a08 <= 0) {
        return 0;
    }
    for (int i = 0; i < HOUSE_ROACHES_MAX; i++) {
        if (data_ov004_02259a18[i] == NULL) {
            data_ov004_02259a18[i] =
                (HouseRoach *) (intptr_t) Actor_Spawn(HOUSE_ROACH_PROFILE, 0, point, angle, data_ov004_02259a10);
            data_ov004_02259a08++;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223e7b4, HouseRoaches_SpawnAt)

/* Whether the process has anything to do: in a room of the house, outside a link. */
static int HouseRoaches_active(void)
{
    return SceneKinds_CurrentIsHouseRoom() && !Session_IsLinked(data_020ccf94);
}

/* func_ov004_0223e834 (vtable slot 0, the creation): the process noted, the count read, and
 * the first cockroaches let out when there are any. */
int HouseRoaches_Init(Process *self)
{
    if (!HouseRoaches_active()) {
        return 1;
    }
    data_ov004_02259a10 = self;
    if (HouseRoaches_ReadCount(self)) {
        HouseRoaches_SpawnOnFloor(self);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223e834, HouseRoaches_Init)

/* func_ov004_0223e878 (vtable slot 6, the frame): a cockroach made away with is quieted,
 * deleted and its slot freed, and the count goes down with the number out; of those asking to
 * make their sound, the only one, or else the one nearest the player, is chosen to - unless
 * one already makes it.
 * BUG: with no player, or with more than one asking and none nearer than 0x0fffffff, the
 * index chosen stays negative and a word before the slots is taken for a cockroach and set
 * (data_ov004_02259a14 for one asking, the process for two, the word before it for three).
 * QUIRK: the count goes down only while some are out (it is a byte, so it never wraps from
 * this). */
int HouseRoaches_Update(Process *self)
{
    (void) self;
    if (!HouseRoaches_active()) {
        return 1;
    }
    u8 asking = 0; /* by bit of the slot; 0xff when one sounds already */
    s8 chosen = 0; /* minus the number asking, until one is chosen */
    for (int i = 0; i < HOUSE_ROACHES_MAX; i++) {
        HouseRoach *roach = data_ov004_02259a18[i];
        if (roach == NULL) {
            continue;
        }
        if (roach_process(roach)->param == HOUSE_ROACH_GONE) {
            roach_process(roach)->param = 0;
            HouseRoach_SetSoundState(roach, HOUSE_ROACH_QUIET);
            Process_RequestDelete(roach_process(roach));
            data_ov004_02259a18[i] = NULL;
            if (data_ov004_02259a08 != 0) {
                data_ov004_02259a08--;
                data_ov004_02259a0c--;
            }
        } else if (HouseRoach_SoundState(roach) == HOUSE_ROACH_ASKING) {
            asking |= (u8) (1 << i);
            chosen--;
        } else if (HouseRoach_SoundState(roach) == HOUSE_ROACH_SOUNDING) {
            asking = 0xff;
        }
    }
    if (asking == 0xff || asking == 0) {
        return 1;
    }
    Actor *player = SessionPlayers_ActorOf(HOUSE_ROACHES_PLAYER);
    fx32 nearest = HOUSE_ROACHES_FAR;
    if (player != NULL) {
        for (int j = 0; j < HOUSE_ROACHES_MAX; j++) {
            HouseRoach *roach = data_ov004_02259a18[j];
            if (roach == NULL || ((asking >> j) & 1) == 0) {
                continue;
            }
            if (chosen == -1) {
                chosen = (s8) j;
                break;
            }
            fx32 distance = Vec_DistanceXZ(&player->position, &roach->actor.position);
            if (nearest > distance) {
                nearest = distance;
                chosen = (s8) j;
            }
        }
    }
    HouseRoach_SetSoundState(roach_slot_any(chosen), HOUSE_ROACH_SOUNDING);
    return 1;
}
CLEAN_AS(func_ov004_0223e878, HouseRoaches_Update)

/* func_ov004_0223e998 (vtable slot 3, the deletion): the count left written back to the house's
 * record, and the process forgotten. */
int HouseRoaches_Release(void)
{
    if (!HouseRoaches_active()) {
        return 1;
    }
    HouseRecord_SetAbsence(&data_021ebcd4, data_ov004_02259a0c);
    data_ov004_02259a10 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0223e998, HouseRoaches_Release)

/* func_ov004_0223e9dc (the deleting destructor) */
Process *HouseRoaches_Delete(Process *self)
{
    self->vtable = data_ov004_022561dc;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0223e9dc, HouseRoaches_Delete)

/* func_ov004_0223ea04 (the destructor) */
Process *HouseRoaches_Destruct(Process *self)
{
    self->vtable = data_ov004_022561dc;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_ov004_0223ea04, HouseRoaches_Destruct)

/* func_ov004_0223ea24 (the constructor): the base's vtable set before the class's. */
Process *HouseRoaches_Construct(Process *self)
{
    Process_Construct(self);
    self->vtable = data_020da13c;
    self->vtable = data_ov004_022561dc;
    return self;
}
CLEAN_AS(func_ov004_0223ea24, HouseRoaches_Construct)

/* func_ov004_0223ea44 (the cockroach's profile maker): a new cockroach from the room's heap. */
void HouseRoaches_NewRoach(void)
{
    void *roach = Heap_AllocAuxZeroed(sizeof(HouseRoach));
    if (roach != NULL) {
        HouseRoach_Construct(roach);
    }
}
CLEAN_AS(func_ov004_0223ea44, HouseRoaches_NewRoach)

/* func_ov004_0223ea60 (the process's profile maker) */
void HouseRoaches_New(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));
    if (self != NULL) {
        HouseRoaches_Construct(self);
    }
}
CLEAN_AS(func_ov004_0223ea60, HouseRoaches_New)
