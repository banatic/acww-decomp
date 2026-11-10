/* Behaviors 0, 1 and 5 of a villager out walking in the town (its behavior member at 0x8b8,
 * outdoor_villager.h), the choice of what it does next, and the walker that takes it about
 * the town's paths (main's path_walker.h, at 0x3c of the behavior member).
 *
 * - 0, walking about on screen: while the villager is within the box of the behavior member's
 *   first four words around the camera's target (OutdoorVillagerWalks_OnScreen; else behavior
 *   1), each frame it may start another behavior (OutdoorVillagerWalks_Choose). Once a motion
 *   ends it stands, now and then (one frame in eight) walks a step of its walker (kind 1, or
 *   kind 2 one time in four when the mood (byte 0x18) of its state entry is clear; kind 4 to turn first
 *   when the step is more than a quarter turn away), but not across the line between this
 *   console's player and the object of an object event (OutdoorVillagerWalks_CrossesEvent).
 *   While it walks it stops when its wait is out, when it walks into that line, or when its
 *   mover's end is more than a quarter turn away; and when its watch has followed an insect or
 *   a fish shadow for more than 15 frames it stops to watch for 160 to 359 frames (at most
 *   once in 1200).
 * - 1, off screen: it stands unseen (no draw hook, no footsteps) and steps its walker every 40
 *   frames without moving visibly; arriving at its house's door it is in at once (behavior 3).
 *   It may catch insects or fish (VillagerErrandCatch_Update) and its record's byte 0x1e rises
 *   every 900 frames. Back on screen, behavior 0.
 * - 5, told its talk started: it talks (to its partner when paired, at its place while the
 *   byte at 0xa04 is set, else turning to the object its talk's motion names); once the
 *   action ends its mood is applied, the object event finished and it is unpaired.
 *
 * The walker's kinds (its `status`): 3 home (when its state entry's flag 1 is set, or at night
 * for its personality unless the current player still works for Nook, flag 1), 6 for a villager whose kind of
 * the moment (byte 0x1c of its state entry) is 6, else one of 0, 2 and 4 at random
 * (data_ov068_022767ac), not the one it had. Walking home, behavior 2 (or 16 first, to put
 * its held item away) starts within 0x800 of its door.
 *
 * The choice (OutdoorVillagerWalks_Choose), in order: home (2 or 16), a marked pitfall seed (0x1566)
 * under it (17), the count at 0xa06 at its limit (21), the byte at 0xa05 (19), behavior 7's
 * call (OutdoorVillagerBehavior_CallsPlayer), a pairing with a villager near and in view (9, one time in five),
 * its effect's countdown (11), a change of its held item (15 or 16), this console's player
 * showing an insect or a fish (23), and a step aside around what blocks it.
 *
 * The held item (OutdoorVillagerWalks_ChangeHeldItem), checked while it stands: every 12000
 * frames (the halfword at 0x34) the activity of the moment is redrawn (OutdoorVillagerRecords_RedrawActivity), and
 * the item it should hold is the kind's (VillagerModeRecord_KindItem), its umbrella (items
 * 0x1380 to 0x139f, TownVillager_Umbrella) when rain falls and the kind has none or item
 * 0x1378; behavior 15 brings an item out, 16 puts one away. The halfword at 0x36 (300 after
 * a change, -1 for none) lets only the weather be looked at while both run. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_WALKS_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_WALKS_H

#include "autoload_2/vector.h"
#include "main/tile_requests.h"
#include "outdoor_villager.h"
#include "types.h"

/* The box around the camera's target within which the villager counts as on screen: the
 * behavior member's first four words (0x10000, 0x10000, 0x1a000 and 0xa000 when it is made). */
typedef struct OutdoorVillagerWalksBox {
    fx32 left;  /* 0x00: along x below the target */
    fx32 right; /* 0x04: along x above it */
    fx32 back;  /* 0x08: along z below it */
    fx32 front; /* 0x0c: along z above it */
} OutdoorVillagerWalksBox;

int OutdoorVillagerWalks_Update5(OutdoorVillagerBehavior *self, u8 *villager);
void OutdoorVillagerWalks_Idle5(OutdoorVillagerBehavior *self, u8 *villager);
void OutdoorVillagerWalks_End5(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_Start5(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_Update1(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_Start1(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_Update0(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_Choose(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_WatchShown(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_PlayerShowsCatch(OutdoorVillagerBehavior *self);
int OutdoorVillagerWalks_WasNetted(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_OnPitfall(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_TileMarked(OutdoorVillagerBehavior *self, TileRequestTile *tile);
int OutdoorVillagerWalks_ChangeHeldItem(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_TryPair(OutdoorVillagerBehavior *self, u8 *villager);
u8 *OutdoorVillagerWalks_FindPartner(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_StepAside(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_StepWalker(OutdoorVillagerBehavior *self, Vec3 *point, u8 *villager);
int OutdoorVillagerWalks_NearEvent(OutdoorVillagerBehavior *self, const Vec3 *point, fx32 range);
int OutdoorVillagerWalks_CrossesEventTo(OutdoorVillagerBehavior *self, const Vec3 *to, const Vec3 *from);
int OutdoorVillagerWalks_CrossesEventAhead(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_CrossesEvent(OutdoorVillagerBehavior *self, const Vec3 *from, const Vec3 *direction);
int OutdoorVillagerWalks_AtHome(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_TimeToGoHome(OutdoorVillagerBehavior *self, u8 *villager);
void OutdoorVillagerWalks_StartWalker(OutdoorVillagerBehavior *self, int state, u8 *villager);
int OutdoorVillagerWalks_DrawWalkKind(OutdoorVillagerBehavior *self);
int OutdoorVillagerWalks_OnScreen(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerWalks_InBox(const OutdoorVillagerWalksBox *box, const Vec3 *center, const Vec3 *point);
int OutdoorVillagerWalks_Start0(OutdoorVillagerBehavior *self, u8 *villager);
void OutdoorVillagerWalks_InitItemCheck(OutdoorVillagerBehavior *self);
int OutdoorVillagerWalks_IsDoing(OutdoorVillagerBehavior *self, int index);
void OutdoorVillagerWalks_StartCooldown(OutdoorVillagerBehavior *self);

#endif
