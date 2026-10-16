/* The lights among the room objects (room_object_light.h). */
#include "room_object_light.h"

#include "clean.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

#define LIGHT_FLASHES 1 /* RoomObject.light_kind whose glow flashes as it comes on */

/* The name of the material that glows. */
extern const char data_ov004_02250010[];

/* Whether a room object is a light (RoomObject_Check0221134c); handed to func_ov004_0223c264,
 * which counts the lights that are on. */
extern int func_ov004_0221134c(RoomObject *object);
extern int func_ov004_0223c264(int (*is_light)(RoomObject *object));
extern unsigned char func_020b65c4(void);
extern int func_020b67e8(unsigned int area);
extern void func_02064da0(unsigned int index, unsigned int value);
extern void func_02064db8(int index, int value1, int value2);
extern void func_02052038(int area, int on);
extern void func_ov004_02211414(int light_kind);

/* func_ov004_0220ecec: when the object goes away (vtable slot 0x14) while it is the only light
 * on: func_02064da0(0, 1), and when it vanishes also func_02052038 with 0. */
void RoomObject_ExitLight(RoomObject *object)
{
    if (RoomObject_Check0221134c(object) && Area_CurrentIs1To5() && Switch_Value(&object->light_switch) &&
        func_ov004_0223c264(func_ov004_0221134c) == 1) {
        func_02064da0(0, 1);
        if (RoomObject_IsVanishing(object)) {
            func_02052038(func_020b65c4(), 0);
        }
    }
}
CLEAN_AS(func_ov004_0220ecec, RoomObject_ExitLight)

/* func_ov004_0220ed40 (each frame): a light's glow follows its switch (fading, and flashing for
 * light kind 1); when Glow_Switch says it changed, the first light on sets the room's lighting
 * (func_ov004_02211414, then func_02052038 with 1) and the last one off sets it back
 * (func_02064da0 with 8, then func_02052038 with 0). The glow is updated for every object. */
void RoomObject_UpdateLight(RoomObject *object)
{
    if (RoomObject_Check0221134c(object) && Area_CurrentIs1To5() &&
        Glow_Switch(&object->glow, Switch_Value(&object->light_switch), 1, object->light_kind == LIGHT_FLASHES)) {
        int lights_on = func_ov004_0223c264(func_ov004_0221134c);
        if (Switch_Value(&object->light_switch)) {
            if (lights_on == 1) {
                func_ov004_02211414(object->light_kind);
                func_02052038(func_020b65c4(), 1);
            }
        } else if (lights_on == 0) {
            func_02064da0(0, 8);
            func_02052038(func_020b65c4(), 0);
        }
    }
    Glow_Update(&object->glow);
}
CLEAN_AS(func_ov004_0220ed40, RoomObject_UpdateLight)

/* func_ov004_0220ede0 (vtable slot 0x08 with 2): a light binds its glow to the material
 * data_ov004_02250010 of its model, lit by its switch; when it is the only light on, it sets
 * the room's lighting: by its kind (func_ov004_02211414 and func_02052038 with 1), or for mode
 * 0 (unk_76C) with func_02064db8(0, 1, 0). */
void RoomObject_StartLight(RoomObject *object)
{
    if (!RoomObject_Check0221134c(object)) {
        return;
    }
    G3dModel *model = object->model_resource;
    Glow_Bind(&object->glow, model, data_ov004_02250010, Switch_Value(&object->light_switch));
    if (Area_CurrentIs1To5()) {
        int lights_on = func_ov004_0223c264(func_ov004_0221134c);
        if (Switch_Value(&object->light_switch) && lights_on == 1) {
            if (object->unk_76C != 0) {
                func_ov004_02211414(object->light_kind);
                func_02052038(func_020b65c4(), 1);
            } else {
                func_02064db8(0, 1, 0);
            }
        }
    }
}
CLEAN_AS(func_ov004_0220ede0, RoomObject_StartLight)

/* func_ov004_0220ee74: Area_Is1To5 of the current area (func_020b65c4). */
int Area_CurrentIs1To5(void)
{
    return Area_Is1To5(func_020b65c4());
}
CLEAN_AS(func_ov004_0220ee74, Area_CurrentIs1To5)

/* func_ov004_0220ee88: whether `area` is one of 1 to 5 (func_020b67e8). */
int Area_Is1To5(unsigned int area)
{
    return func_020b67e8(area);
}
CLEAN_AS(func_ov004_0220ee88, Area_Is1To5)
