/* Nook's store seen from outside, a scene object of overlay 3 (class Obj_ov003_02239754, vtable
 * 0x02239754, receiver part 0x02239818, 0x2b8 bytes). Its code is the store's map code (0x500d
 * plus the store's level, map_code.h), and set up (vtable slot 0x70) it keeps that level, or -1
 * for a code that is not the store's. It is derived from overlay 9's scene actor
 * (ov009/scene_actor.h), which runs the rest; the paths of its files (slots 0xa4, 0xa8 and 0xac)
 * are overlay 9's.
 *
 * Whether the player may go in (slot 0x8c: a talk asks main for a visit record, which lets the
 * player in, only when it says so; main/nook_store.h for the store's days):
 *
 *   - with no level: from 8:00 to 22:59;
 *   - never while a start kind is set (start_kind.h) or the player of this console has flag
 *     0x23; always when that player has flag 1;
 *   - otherwise not on the day the store is closed for its upgrade, only from 8:00 to 22:59, and
 *     not once the planned upgrade is due.
 *
 * When the player may not go in, the talk (slot 0x78) mostly reads the receiver
 * "obj_etc_closed": its message is the store's level (0 to 3), or 7 when it is closed (on the
 * day of the upgrade, once it is due, or after 12:59 on the day before), or 4 with no level.
 * "sp_etc_sequence4" message 0x15 and "obj_etc_error" message 0 (the visit record said 2,
 * SCENE_ACTOR_FLAG_VISIT_2: more visitors than the store takes) are the other two
 * (StoreFront_PrepareTalk). */
#ifndef CLEAN_OV003_STORE_FRONT_H
#define CLEAN_OV003_STORE_FRONT_H

#include "ov009/scene_actor.h"
#include "types.h"

#define STORE_FRONT_NO_LEVEL (-1)

typedef struct StoreFront {
    SceneActor actor;
    int level; /* 0x2b4: the store's level, STORE_FRONT_NO_LEVEL for another code */
} StoreFront;

int StoreFront_Slot98(void);
int StoreFront_IsClosedForUpgrade(StoreFront *store);
int StoreFront_LetsIn(StoreFront *store);
void StoreFront_PrepareTalk(StoreFront *store);
void StoreFront_LightTexturePath(StoreFront *store);
void StoreFront_TexturePath(StoreFront *store);
void StoreFront_ArchivePath(StoreFront *store);
int StoreFront_SetUp(StoreFront *store);
StoreFront *StoreFront_DestroyAndFree(StoreFront *store);
StoreFront *StoreFront_Destroy(StoreFront *store);
StoreFront *StoreFront_Construct(StoreFront *store);
void StoreFront_New(void);
StoreFront *StoreFront_ReceiverDestroyAndFree(void *receiver);
StoreFront *StoreFront_ReceiverDestroy(void *receiver);

#endif
