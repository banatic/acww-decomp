/* The cockroaches of the player's house: a process of overlay 4 (vtable 0x022561dc on the
 * Process base: HouseRoaches_Init, HouseRoaches_Release, HouseRoaches_Update) that, in a room of
 * the house and outside a link with other players, lets out the cockroaches the house's record
 * counts (HouseRecord_Absence: a long absence leaves them) on its empty floor cells, up to
 * three at once (scene object 0xc0, whose class names its model "GOKI" and loads it from
 * /insect/51/bug52). A cockroach made away with (its process's param becomes 0xffff) leaves the count one smaller, which is written back to the record when the process ends.
 *
 * Each frame, of the cockroaches asking to make their sound (state 1, set by their class), the
 * one nearest the player is chosen to make it (state 2). Other code makes one more at a point
 * (HouseRoaches_SpawnAt) while fewer than three are out and the count allows it. */
#ifndef CLEAN_OV004_HOUSE_ROACHES_H
#define CLEAN_OV004_HOUSE_ROACHES_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "types.h"

/* The most out at once. */
#define HOUSE_ROACHES_MAX 3

int HouseRoaches_ReadCount(Process *self);
int HouseRoaches_SpawnOnFloor(Process *self);
int HouseRoaches_SpawnAt(const Vec3 *point, const s16 *angle);
int HouseRoaches_Init(Process *self);
int HouseRoaches_Update(Process *self);
int HouseRoaches_Release(void);
Process *HouseRoaches_Delete(Process *self);
Process *HouseRoaches_Destruct(Process *self);
Process *HouseRoaches_Construct(Process *self);
void HouseRoaches_NewRoach(void);
void HouseRoaches_New(void);

#endif
