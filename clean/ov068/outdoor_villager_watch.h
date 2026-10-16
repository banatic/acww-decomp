/* What a villager out walking in the town looks at while free (its member at 0x898,
 * outdoor_villager.h): this console's player, or something near it in the town's field
 * (overlay 3): one of the eight insects (func_ov003_0222f458) or one of the six fish shadows
 * (clean/ov003/fish_shadow.h) whose state is 3 or 4.
 *
 * Each look is a request of the villager's look (main's scene_look.h, at 0x3b0), whose kind
 * the watch keeps. Looking at the player and failing to see it, the villager looks for an
 * insect within 0x5000 of it, then a fish shadow; it follows that thing's point while the
 * thing is still there (its kind unchanged) and within its look's range, else it looks at the
 * player again. When something else takes the look (its kind changes) or a behaviour holds the
 * watch (OutdoorVillagerWatch_Hold), the watch stops until OutdoorVillagerWatch_LookAtPlayer. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_WATCH_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_WATCH_H

#include "autoload_2/vector.h"
#include "types.h"

/* What it looks at (OutdoorVillagerWatch.mode). */
#define OUTDOOR_VILLAGER_WATCH_INSECT 0
#define OUTDOOR_VILLAGER_WATCH_FISH 1
#define OUTDOOR_VILLAGER_WATCH_PLAYER 2
#define OUTDOOR_VILLAGER_WATCH_HELD 3

typedef struct OutdoorVillagerWatch {
    u32 held; /* 0x00: 1 while it does not choose (held, or the look taken) */
    u32 mode; /* 0x04: OUTDOOR_VILLAGER_WATCH_* */
    u8 kind;  /* 0x08: the kind of the last look it requested */
    u8 unk_09[3];
    s32 slot;  /* 0x0c: the insect's or the fish shadow's slot, -1 for none */
    s32 thing; /* 0x10: its kind, -1 for none */
    u16 seen;  /* 0x14: frames its point was in sight, up to 2400 */
    u8 unk_16[2];
} OutdoorVillagerWatch;

void OutdoorVillagerWatch_Update(OutdoorVillagerWatch *watch, u8 *villager);
void OutdoorVillagerWatch_FollowFish(OutdoorVillagerWatch *watch, u8 *villager);
void OutdoorVillagerWatch_LookAtFish(OutdoorVillagerWatch *watch, u8 *villager, int slot, int kind, const Vec3 *point);
int OutdoorVillagerWatch_FishStill(OutdoorVillagerWatch *watch, int slot, int kind);
int OutdoorVillagerWatch_FindFish(OutdoorVillagerWatch *watch, Vec3 *point, int *slot, const Vec3 *from, fx32 range);
int OutdoorVillagerWatch_FishNear(OutdoorVillagerWatch *watch, Vec3 *point, int slot, const Vec3 *from, fx32 range);
void OutdoorVillagerWatch_FollowInsect(OutdoorVillagerWatch *watch, u8 *villager);
void OutdoorVillagerWatch_LookAtInsect(OutdoorVillagerWatch *watch, u8 *villager, int slot, int kind, const Vec3 *point);
int OutdoorVillagerWatch_InsectStill(OutdoorVillagerWatch *watch, int slot, int kind);
int OutdoorVillagerWatch_FindInsect(OutdoorVillagerWatch *watch, Vec3 *point, int *slot, const Vec3 *from, fx32 range);
int OutdoorVillagerWatch_InsectNear(OutdoorVillagerWatch *watch, Vec3 *point, int slot, const Vec3 *from, fx32 range);
void OutdoorVillagerWatch_Request(OutdoorVillagerWatch *watch, u8 *villager, u8 kind, int priority, int target,
                                  const Vec3 *point, int actor, fx32 range, u8 in_view_only);
void OutdoorVillagerWatch_CountSeen(OutdoorVillagerWatch *watch);
void OutdoorVillagerWatch_Hold(OutdoorVillagerWatch *watch, u8 *villager, int kind, int priority, int target,
                               const Vec3 *point, int actor, fx32 range, u8 in_view_only);
void OutdoorVillagerWatch_LookAtPlayer(OutdoorVillagerWatch *watch, u8 *villager);
void OutdoorVillagerWatch_HoldOnPlayer(OutdoorVillagerWatch *watch, u8 *villager);
void OutdoorVillagerWatch_Destruct(OutdoorVillagerWatch *watch);
void OutdoorVillagerWatch_Construct(OutdoorVillagerWatch *watch);

#endif
