/* The museum's aquarium: a process of overlay 4 (vtable 0x02255ebc: Aquarium_Init,
 * Aquarium_Release, Aquarium_Update, Aquarium_Draw) that shows the fish the museum's record
 * has been given (main/museum_record.h, items 0x12e8 + kind) swimming in the tanks of one of
 * its two rooms, the process's parameter saying which (data_ov004_022593a0):
 *
 *   0  the river room: kinds 0-34, in two tanks (centres data_ov004_022593dc and
 *      data_ov004_022593c4, 17.75 by 5.75); kinds below 17 and kind 25 in the first; five
 *      rocks the fish swim round;
 *   1  the sea room: kinds 35-55, in one tank (centre data_ov004_022593dc, 38.0 by 4.86; each
 *      fish keeps to 26.0, 38.0 or 42.0 of its width); four rocks, and a body of another
 *      kind.
 *
 * The fish (aquarium_fish.h) are made when the process starts, one object per kind in the
 * table data_ov004_022594d4 (the room's kinds data_ov004_022593a4 to data_ov004_02255c30 - 1),
 * and placed when the record has them. Each frame a fish runs its state through the member
 * pointers data_ov004_0225940c: off (nothing), loading (Aquarium_FishStateLoad) and shown
 * (Aquarium_SwimFish). Their models share a model pool of 0x38 entries (0x7f8). The glass
 * of each tank is a box the stylus can touch (TouchPick_SetBoxAndAdd), offered each frame. */
#ifndef CLEAN_OV004_MUSEUM_AQUARIUM_H
#define CLEAN_OV004_MUSEUM_AQUARIUM_H

#include "aquarium_fish.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/field_body.h"
#include "main/model_pool.h"
#include "main/touch_pick_shapes.h"
#include "types.h"

/* The rooms (data_ov004_022593a0). */
enum {
    AQUARIUM_RIVER_ROOM = 0,
    AQUARIUM_SEA_ROOM = 1,
};

/* A rock the fish swim round: a body at a point, fixed. */
typedef struct AquariumRock {
    FieldPointBody body; /* 0x00 */
    u8 unk_4c[4];
    Vec3 point;  /* 0x50 */
    fx32 radius; /* 0x5c */
    fx32 height; /* 0x60 */
} AquariumRock;

/* The rocks (data_ov004_02255c34 of them are entered) and the sea room's extra body. */
#define AQUARIUM_ROCKS 5
#define AQUARIUM_EXTRA_ROCK 5

/* The triangles of a tank's touch box. */
#define AQUARIUM_GLASS_FACES 10

typedef struct MuseumAquarium {
    Process base;                                 /* 0x000: param is the room */
    AquariumRock rocks[AQUARIUM_ROCKS + 1];       /* 0x050 */
    TouchPickFace glass[2][AQUARIUM_GLASS_FACES]; /* 0x2a8 */
    ModelPool pool;                               /* 0x7f8 */
} MuseumAquarium;

void Aquarium_ApplyLargerShift(MuseumAquarium *self, fx32 *coordinate, fx32 head_before, fx32 head_after, fx32 tail_before,
                               fx32 tail_after);
void Aquarium_KeepInTank(MuseumAquarium *self, AquariumFish **slot, int kind);
void Aquarium_PlaceSeaFish(MuseumAquarium *self);
void Aquarium_PlaceRiverFish(MuseumAquarium *self);
int Aquarium_Release(MuseumAquarium *self);
int Aquarium_Draw(MuseumAquarium *self);
void Aquarium_SetFishMatrix(MuseumAquarium *self, AquariumFish **slot);
int Aquarium_LoadFish(MuseumAquarium *self, AquariumFish **slot, int kind);
void Aquarium_EnterRocks(MuseumAquarium *self, int count);
int Aquarium_Update(MuseumAquarium *self);
void Aquarium_SwimFish(MuseumAquarium *self, AquariumFish **slot, int kind);
void Aquarium_FishStateLoad(MuseumAquarium *self, AquariumFish **slot, int kind);
void Aquarium_FishStateOff(void);
void Aquarium_RunFishState(MuseumAquarium *self, AquariumFish **slot, int kind);
int Aquarium_LoadFishAnims(MuseumAquarium *self, AquariumFish **slot, int kind, int count);
int Aquarium_CreateSeaFish(MuseumAquarium *self);
int Aquarium_CreateRiverFish(MuseumAquarium *self);
int Aquarium_Init(MuseumAquarium *self);
void Aquarium_ReleaseFish(MuseumAquarium *self, int kind);
int Aquarium_ActivateFish(MuseumAquarium *self, int kind);

#endif
