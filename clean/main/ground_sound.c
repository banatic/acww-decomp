/* The sound of the ground under a point (ground_sound.h). */
#include "ground_sound.h"

#include "clean.h"
#include "main/field_collision.h"
#include "collision_map.h"
#include "item_info.h"
#include "ov004/room_shell.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "unit_type_info.h"

/* No object on the point (func_02030890). */
#define GROUND_SOUND_NO_OBJECT (-1)
/* The attributes the scenes sound as, and the one mode 1 replaces. */
#define GROUND_SOUND_ATTR_5 5
#define GROUND_SOUND_ATTR_6 6
#define GROUND_SOUND_ATTR_REPLACED 0x1a
/* A row without a sound of its own. */
#define GROUND_SOUND_NONE 0xffff
/* The sounds Lookup falls back on: in mode 0, and in mode 1 outside the scenes it knows. */
#define GROUND_SOUND_MODE_0 0xc8
#define GROUND_SOUND_OTHER 0x4a6
/* Sound 0xc0 becomes 0x877 while func_020b6598 agrees: in mode 0, or in scenes 11-14 and
 * 0x2f. */
#define GROUND_SOUND_SWAPPED 0xc0
#define GROUND_SOUND_SWAP 0x877
#define GROUND_SOUND_SWAP_SCENE_FIRST 11
#define GROUND_SOUND_SWAP_SCENES 4
#define GROUND_SOUND_SWAP_SCENE_OTHER 0x2f

extern u8 data_020e54a8; /* 0 or 1, a mode many scenes test */

static int ground_sound_scene_as_attr(int scene)
{
    if (SceneQuery_InNook((unsigned int) scene) != 0) {
        return GROUND_SOUND_ATTR_5;
    }
    if (SceneKinds_IsHouseRoom((unsigned int) scene) != 0 || SceneKinds_In6To8(scene) != 0) {
        return GROUND_SOUND_ATTR_6;
    }
    if (SceneQuery_In20((unsigned int) scene) != 0) {
        return GROUND_SOUND_ATTR_5;
    }
    return -1;
}

/* func_020b1cb0: the sound of the ground under `point`. On an object of the map the scene
 * decides when it is one it knows; otherwise the ground's attribute does.
 * QUIRK: the ground's attribute is resolved twice (GroundSound_GroundAttr, then
 * GroundSound_OfAttr). */
int GroundSound_AtPoint(const Vec3 *point)
{
    if (CollisionMap_UnclaimedObjectAtPoint(point) != GROUND_SOUND_NO_OBJECT) {
        int attr = ground_sound_scene_as_attr(SceneQuery_Current());
        if (attr >= 0) {
            return GroundSound_OfAttr(attr);
        }
    }
    return GroundSound_OfAttr(GroundSound_GroundAttr(point));
}
CLEAN_AS(func_020b1cb0, GroundSound_AtPoint)

/* func_020b1d18 */
int GroundSound_OfAttr(int attr)
{
    return GroundSound_Lookup(GroundSound_ResolveAttr(attr));
}
CLEAN_AS(func_020b1d18, GroundSound_OfAttr)

/* func_020b1d2c: the attribute of the ground at `point`, resolved. */
int GroundSound_GroundAttr(const Vec3 *point)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, point, 0, 0);
    int attr = GroundSound_ResolveAttr(ground.attr);
    CollisionGround_Destroy(&ground);
    return attr;
}
CLEAN_AS(func_020b1d2c, GroundSound_GroundAttr)

/* func_020b1d54: in mode 1, attribute GROUND_SOUND_ATTR_REPLACED becomes byte 1 of the record
 * of the item overlay 4 gives; any other attribute stays. */
int GroundSound_ResolveAttr(int attr)
{
    if (attr != GROUND_SOUND_ATTR_REPLACED || data_020e54a8 != 1) {
        return attr;
    }
    u16 code = *RoomShell_CarpetCode2();
    return ItemInfo_IndoorUnk01(&code);
}
CLEAN_AS(func_020b1d54, GroundSound_ResolveAttr)

/* func_020b1d88: the sound of attribute `attr`. A row without one sounds, in mode 0, as
 * GROUND_SOUND_MODE_0; in mode 1 as its scene does (ground_sound.h), else GROUND_SOUND_OTHER. */
int GroundSound_Lookup(int attr)
{
    int scene = SceneQuery_Current();
    int sound = UnitTypeInfo_Sound(attr);
    if (sound == GROUND_SOUND_NONE) {
        if (data_020e54a8 == 0) {
            sound = GROUND_SOUND_MODE_0;
        } else {
            int as_attr = ground_sound_scene_as_attr(scene);
            sound = as_attr >= 0 ? GroundSound_OfAttr(as_attr) : GROUND_SOUND_OTHER;
        }
    }
    if (sound == GROUND_SOUND_SWAPPED && SceneQuery_IsSnowSeason() != 0) {
        if (data_020e54a8 == 0 || (u8) (scene - GROUND_SOUND_SWAP_SCENE_FIRST) < GROUND_SOUND_SWAP_SCENES ||
            scene == GROUND_SOUND_SWAP_SCENE_OTHER) {
            sound = GROUND_SOUND_SWAP;
        }
    }
    return sound;
}
CLEAN_AS(func_020b1d88, GroundSound_Lookup)
