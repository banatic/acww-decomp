/* The lights of a model: lamps, a window and a door brought up by a fader (building_lights.h). */
#include "building_lights.h"

#include "clean.h"

static_assert(offsetof(BuildingLightsLamps, materials) == 0x04, "lamp materials");
static_assert(offsetof(BuildingLightsLamps, fader) == 0x08, "lamp fader");
static_assert(sizeof(BuildingLightsLamps) == 0x1c, "lamps");
static_assert(offsetof(BuildingLights, door) == 0x14, "door");
static_assert(offsetof(BuildingLights, lamps) == 0x18, "lamps");
static_assert(offsetof(BuildingLights, window) == 0x34, "window");
static_assert(sizeof(BuildingLights) == 0x38, "the member at 0x1f4 of a scene actor");
static_assert(offsetof(BuildingLightsModel, material_count) == 0x18, "material count");

/* NitroSDK's material flag for the emission colour (NNS_G3D_MATFLAG_EMISSION). */
#define BUILDING_LIGHTS_EMISSION 0x400
/* White, as a 5-bit colour component in 20.12 fixed point. */
#define BUILDING_LIGHTS_WHITE_COMPONENT 0x1f000
/* The window's alpha at full level, less the 1 it keeps at level 0, and the door's colour. */
#define BUILDING_LIGHTS_WINDOW_ALPHA 29
#define BUILDING_LIGHTS_DOOR_RED 31
#define BUILDING_LIGHTS_DOOR_GREEN 27
#define BUILDING_LIGHTS_DOOR_BLUE 13

/* The lamps' vtable and its function's buffer and format ("lp_m%d"); the window's and the
 * door's material names ("m_window", "m_door"). */
extern const u8 data_020e50dc[];
extern char data_021f4b58[];
extern const char data_020e50f4[];
extern const char data_020e50fc[];
extern const char data_020e5108[];

/* NitroSDK's G3D global state; the word at 0x18 holds the material colours, the ambient one
 * (5 bits each of red, green and blue) in its high half. */
extern const u32 data_027e0148[];

/* The game's sprintf. */
extern int func_02064328(char *buffer, const char *format, ...);
/* The index of the material `name` of a model, -1 for none. */
extern int func_02057a50(BuildingLightsModel *model, const char *name);

extern void NNSi_G3dModifyMatFlag(BuildingLightsModel *model, int on, int flag);
extern void NNS_G3dMdlSetMdlEmi(BuildingLightsModel *model, int material, int colour);
extern void NNS_G3dMdlSetMdlAlpha(BuildingLightsModel *model, int material, int alpha);
extern void NNS_G3dMdlSetMdlDiff(BuildingLightsModel *model, int material, int colour);

typedef char *BuildingLightsNameLamp(BuildingLightsLamps *lamps, int index);

/* The 5 bits of a colour component that `level` (20.12) holds: bits 12-16. Only these bits
 * reach the colour, so it does not matter how the ARM shifts a negative value. */
static u32 building_lights_component(int level, u32 scale)
{
    return ((u32) level * scale) >> 12;
}

/* The lamps' function that names lamp `index` (the vtable's first slot, func_020b3408). */
static BuildingLightsNameLamp *building_lights_name_lamp(const BuildingLightsLamps *lamps)
{
    u32 function = *(const u32 *) lamps->vtable;
    return (BuildingLightsNameLamp *) (uintptr_t) function;
}

/* func_020b3310: whether the fader's level is above 0 (1 or 0). */
int BuildingLights_IsLit(const BuildingLights *lights)
{
    return Fader_Level(&lights->fader) != 0;
}
CLEAN_AS(func_020b3310, BuildingLights_IsLit)

/* func_020b3328: the lights on or off, faded or at once, flashing when they come on; at the
 * fader's speed 0x800. */
void BuildingLights_Switch(BuildingLights *lights, int on, int fade, int flash)
{
    Fader_Switch(&lights->fader, on, fade, flash, 0x800);
}
CLEAN_AS(func_020b3328, BuildingLights_Switch)

/* func_020b3340: the fader's frame, then, with a model, the lamps, the window and the door
 * shown at its level. */
void BuildingLights_Update(BuildingLights *lights, BuildingLightsModel *model)
{
    Fader_Run(&lights->fader);
    int level = Fader_Level(&lights->fader);
    if (model != NULL) {
        BuildingLights_ShowLamps(&lights->lamps, model, level);
        BuildingLights_ShowWindow(&lights->window, model, level);
        BuildingLights_ShowDoor(&lights->door, model, level);
    }
}
CLEAN_AS(func_020b3340, BuildingLights_Update)

/* func_020b3380: the lights on or off at once, then, with a model, its door, lamps and window
 * found. */
void BuildingLights_Bind(BuildingLights *lights, BuildingLightsModel *model, int on)
{
    Fader_Set(&lights->fader, on);
    if (model != NULL) {
        BuildingLights_BindDoor(&lights->door, model);
        BuildingLights_BindLamps(&lights->lamps, model);
        BuildingLights_BindWindow(&lights->window, model);
    }
}
CLEAN_AS(func_020b3380, BuildingLights_Bind)

/* func_020b33b8: the parts taken down, last built first. */
BuildingLights *BuildingLights_Destruct(BuildingLights *lights)
{
    BuildingLights_DestructWindow(&lights->window);
    BuildingLights_DestructLamps(&lights->lamps);
    BuildingLights_DestructDoor(&lights->door);
    Fader_Destruct(&lights->fader);
    return lights;
}
CLEAN_AS(func_020b33b8, BuildingLights_Destruct)

/* func_020b33e0: the fader off, no door, lamps or window. */
BuildingLights *BuildingLights_Construct(BuildingLights *lights)
{
    Fader_Construct(&lights->fader);
    BuildingLights_ConstructDoor(&lights->door);
    BuildingLights_ConstructLamps(&lights->lamps);
    BuildingLights_ConstructWindow(&lights->window);
    return lights;
}
CLEAN_AS(func_020b33e0, BuildingLights_Construct)

/* func_020b3408 (the lamps' vtable slot 0): the name of lamp `index`, "lp_m<index>", in a
 * buffer shared by every call. */
char *BuildingLights_LampName(BuildingLightsLamps *lamps, int index)
{
    (void) lamps;
    func_02064328(data_021f4b58, data_020e50f4, index);
    return data_021f4b58;
}
CLEAN_AS(func_020b3408, BuildingLights_LampName)

/* func_020b3428: the colour the lamps start from, the scene's ambient material colour. */
int BuildingLights_BaseColour(void)
{
    return (int) (data_027e0148[6] >> 16);
}
CLEAN_AS(func_020b3428, BuildingLights_BaseColour)

/* func_020b3438: while `level` is not 0, the lamps' emission is the base colour brought
 * towards white by the level (blue, red, then green) and the other materials' emission the
 * base colour; at level 0 the emission is turned off. */
void BuildingLights_ShowLamps(BuildingLightsLamps *lamps, BuildingLightsModel *model, int level)
{
    if (level == 0) {
        NNSi_G3dModifyMatFlag(model, 0, BUILDING_LIGHTS_EMISSION);
        return;
    }
    NNSi_G3dModifyMatFlag(model, 1, BUILDING_LIGHTS_EMISSION);
    int base = BuildingLights_BaseColour();
    int blue = Fader_Mix(level, ((base >> 10) & 0x1f) << 12, BUILDING_LIGHTS_WHITE_COMPONENT);
    int red = Fader_Mix(level, (base & 0x1f) << 12, BUILDING_LIGHTS_WHITE_COMPONENT);
    int green = Fader_Mix(level, ((base >> 5) & 0x1f) << 12, BUILDING_LIGHTS_WHITE_COMPONENT);
    /* QUIRK: the components are not clamped; the sum is cut to 16 bits. */
    u32 bits = (((u32) blue >> 12) << 10) | ((u32) red >> 12) | (((u32) green >> 12) << 5);
    int lit = (u16) bits;
    for (int i = 0; i < model->material_count; i++) {
        NNS_G3dMdlSetMdlEmi(model, i, BuildingLights_IsLamp(lamps, i) ? lit : base);
    }
}
CLEAN_AS(func_020b3438, BuildingLights_ShowLamps)

/* func_020b34e0: whether `material` is one of the lamps. */
int BuildingLights_IsLamp(const BuildingLightsLamps *lamps, int material)
{
    for (int i = 0; i < BUILDING_LIGHTS_LAMPS; i++) {
        if (lamps->materials[i] == material) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020b34e0, BuildingLights_IsLamp)

/* func_020b3504: each lamp's material found in the model by the name the vtable gives.
 * QUIRK: the name is asked for twice, once to see that there is one and once to look it up;
 * a lamp without a name keeps its material. */
void BuildingLights_BindLamps(BuildingLightsLamps *lamps, BuildingLightsModel *model)
{
    for (unsigned int i = 0; i < BUILDING_LIGHTS_LAMPS; i++) {
        if (building_lights_name_lamp(lamps)(lamps, (int) i) != NULL) {
            int material = func_02057a50(model, building_lights_name_lamp(lamps)(lamps, (int) i));
            lamps->materials[i] = (s8) material;
        }
    }
}
CLEAN_AS(func_020b3504, BuildingLights_BindLamps)

/* func_020b3550: the lamps taken down: their vtable set back, their fader taken down. */
BuildingLightsLamps *BuildingLights_DestructLamps(BuildingLightsLamps *lamps)
{
    lamps->vtable = data_020e50dc;
    Fader_Destruct(&lamps->fader);
    return lamps;
}
CLEAN_AS(func_020b3550, BuildingLights_DestructLamps)

/* func_020b356c: the lamps built, with no materials. */
BuildingLightsLamps *BuildingLights_ConstructLamps(BuildingLightsLamps *lamps)
{
    lamps->vtable = data_020e50dc;
    Fader_Construct(&lamps->fader);
    for (unsigned int i = 0; i < BUILDING_LIGHTS_LAMPS; i++) {
        lamps->materials[i] = BUILDING_LIGHTS_NO_MATERIAL;
    }
    return lamps;
}
CLEAN_AS(func_020b356c, BuildingLights_ConstructLamps)

/* func_020b3598: the window's alpha, 1 at level 0 up to 30 at 1.0. */
void BuildingLights_ShowWindow(s8 *window, BuildingLightsModel *model, int level)
{
    s8 material = *window;
    if (material == BUILDING_LIGHTS_NO_MATERIAL) {
        return;
    }
    NNS_G3dMdlSetMdlAlpha(model, material, (u8) (building_lights_component(level, BUILDING_LIGHTS_WINDOW_ALPHA) + 1));
}
CLEAN_AS(func_020b3598, BuildingLights_ShowWindow)

/* func_020b35c0: the window's material found in the model. */
void BuildingLights_BindWindow(s8 *window, BuildingLightsModel *model)
{
    *window = (s8) func_02057a50(model, data_020e50fc);
}
CLEAN_AS(func_020b35c0, BuildingLights_BindWindow)

/* func_020b35d8: the window taken down: no material. */
void BuildingLights_DestructWindow(s8 *window)
{
    *window = BUILDING_LIGHTS_NO_MATERIAL;
}
CLEAN_AS(func_020b35d8, BuildingLights_DestructWindow)

/* func_020b35e0: the window built, with no material. */
void BuildingLights_ConstructWindow(s8 *window)
{
    *window = BUILDING_LIGHTS_NO_MATERIAL;
}
CLEAN_AS(func_020b35e0, BuildingLights_ConstructWindow)

/* func_020b35e8: the door's diffuse colour, black at level 0 up to (31, 27, 13) at 1.0. */
void BuildingLights_ShowDoor(s8 *door, BuildingLightsModel *model, int level)
{
    s8 material = *door;
    if (material == BUILDING_LIGHTS_NO_MATERIAL) {
        return;
    }
    u32 red = (u8) building_lights_component(level, BUILDING_LIGHTS_DOOR_RED);
    u32 green = (u8) building_lights_component(level, BUILDING_LIGHTS_DOOR_GREEN);
    u32 blue = (u8) building_lights_component(level, BUILDING_LIGHTS_DOOR_BLUE);
    /* QUIRK: each component is cut to 8 bits, not 5, before it is packed. */
    NNS_G3dMdlSetMdlDiff(model, material, (u16) ((blue << 10) | red | (green << 5)));
}
CLEAN_AS(func_020b35e8, BuildingLights_ShowDoor)

/* func_020b3634: the door's material found in the model. */
void BuildingLights_BindDoor(s8 *door, BuildingLightsModel *model)
{
    *door = (s8) func_02057a50(model, data_020e5108);
}
CLEAN_AS(func_020b3634, BuildingLights_BindDoor)

/* func_020b364c: the door taken down; nothing to do. */
void BuildingLights_DestructDoor(s8 *door)
{
    (void) door;
}
CLEAN_AS(func_020b364c, BuildingLights_DestructDoor)

/* func_020b3650: the door built, with no material. */
void BuildingLights_ConstructDoor(s8 *door)
{
    *door = BUILDING_LIGHTS_NO_MATERIAL;
}
CLEAN_AS(func_020b3650, BuildingLights_ConstructDoor)
