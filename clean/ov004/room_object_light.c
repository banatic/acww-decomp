/* The lights among the room objects (room_object_light.h). */
#include "room_object_light.h"

#include "clean.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "main/room_sync.h"
#include "main/scene_kinds.h"
#include "main/scene_lights.h"
#include "main/scene_query.h"
#include "room_objects.h"

#define LIGHT_FLASHES 1 /* RoomObject.light_kind whose glow flashes as it comes on */

/* The name of the material that glows. */
extern const char data_ov004_02250010[];

/* Whether a room object is a light (RoomObject_Check0221134c); handed to RoomObjects_CountOn,
 * which counts the lights that are on. */
extern int func_ov004_0221134c(RoomObject *object);

/* func_ov004_0220ecec: when the object goes away (vtable slot 0x14) while it is the only light
 * on: SceneLights_RequestOff(0, 1), and when it vanishes also RoomSync_SetLit with 0. */
void RoomObject_ExitLight(RoomObject *object)
{
    if (RoomObject_Check0221134c(object) && Area_CurrentIs1To5() && Switch_Value(&object->light_switch) &&
        RoomObjects_CountOn(func_ov004_0221134c) == 1) {
        SceneLights_RequestOff(0, 1);
        if (RoomObject_IsVanishing(object)) {
            RoomSync_SetLit(SceneQuery_Current(), 0);
        }
    }
}
CLEAN_AS(func_ov004_0220ecec, RoomObject_ExitLight)

/* func_ov004_0220ed40 (each frame): a light's glow follows its switch (fading, and flashing for
 * light kind 1); when Glow_Switch says it changed, the first light on sets the room's lighting
 * (RoomLight_TurnOn, then RoomSync_SetLit with 1) and the last one off sets it back
 * (SceneLights_RequestOff with 8, then RoomSync_SetLit with 0). The glow is updated for every object. */
void RoomObject_UpdateLight(RoomObject *object)
{
    if (RoomObject_Check0221134c(object) && Area_CurrentIs1To5() &&
        Glow_Switch(&object->glow, Switch_Value(&object->light_switch), 1, object->light_kind == LIGHT_FLASHES)) {
        int lights_on = RoomObjects_CountOn(func_ov004_0221134c);
        if (Switch_Value(&object->light_switch)) {
            if (lights_on == 1) {
                RoomLight_TurnOn(object->light_kind);
                RoomSync_SetLit(SceneQuery_Current(), 1);
            }
        } else if (lights_on == 0) {
            SceneLights_RequestOff(0, 8);
            RoomSync_SetLit(SceneQuery_Current(), 0);
        }
    }
    Glow_Update(&object->glow);
}
CLEAN_AS(func_ov004_0220ed40, RoomObject_UpdateLight)

/* func_ov004_0220ede0 (vtable slot 0x08 with 2): a light binds its glow to the material
 * data_ov004_02250010 of its model, lit by its switch; when it is the only light on, it sets
 * the room's lighting: by its kind (RoomLight_TurnOn and RoomSync_SetLit with 1), or for mode
 * 0 (unk_76C) with SceneLights_RequestOn(0, 1, 0). */
void RoomObject_StartLight(RoomObject *object)
{
    if (!RoomObject_Check0221134c(object)) {
        return;
    }
    G3dModel *model = object->model_resource;
    Glow_Bind(&object->glow, model, data_ov004_02250010, Switch_Value(&object->light_switch));
    if (Area_CurrentIs1To5()) {
        int lights_on = RoomObjects_CountOn(func_ov004_0221134c);
        if (Switch_Value(&object->light_switch) && lights_on == 1) {
            if (object->unk_76C != 0) {
                RoomLight_TurnOn(object->light_kind);
                RoomSync_SetLit(SceneQuery_Current(), 1);
            } else {
                SceneLights_RequestOn(0, 1, 0);
            }
        }
    }
}
CLEAN_AS(func_ov004_0220ede0, RoomObject_StartLight)

/* func_ov004_0220ee74: Area_Is1To5 of the current area (SceneQuery_Current). */
int Area_CurrentIs1To5(void)
{
    return Area_Is1To5(SceneQuery_Current());
}
CLEAN_AS(func_ov004_0220ee74, Area_CurrentIs1To5)

/* func_ov004_0220ee88: whether `area` is one of 1 to 5 (SceneKinds_IsHouseRoom). */
int Area_Is1To5(unsigned int area)
{
    return SceneKinds_IsHouseRoom(area);
}
CLEAN_AS(func_ov004_0220ee88, Area_Is1To5)

/* The room's lighting (index 0 of SceneLights_RequestOn) for a light of kind 2, and for the others. */
#define LIGHTING_KIND_2 8
#define LIGHTING_OTHER 0xc

/* func_ov004_02211414: the room's lighting for the first light switched on, by its kind: 8 for
 * kind 2, else 0xc, flashing for the kind that flashes; then RoomSync_SetLit with 1. */
void RoomLight_TurnOn(int light_kind)
{
    int flashes = LightKind_Flashes(light_kind);
    if (light_kind == 2) {
        SceneLights_RequestOn(0, LIGHTING_KIND_2, flashes);
    } else {
        SceneLights_RequestOn(0, LIGHTING_OTHER, flashes);
    }
    RoomSync_SetLit(SceneQuery_Current(), 1);
}
CLEAN_AS(func_ov004_02211414, RoomLight_TurnOn)

/* func_ov004_02211444: whether a light of this kind flashes as it comes on (kind 1). */
int LightKind_Flashes(int light_kind)
{
    return light_kind == LIGHT_FLASHES;
}
CLEAN_AS(func_ov004_02211444, LightKind_Flashes)
