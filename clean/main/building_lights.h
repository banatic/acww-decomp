/* The lights of a model: overlay 9's scene actors (ov009/scene_actor.h, the town's buildings
 * and special characters) keep one at 0x1f4 (0x38 bytes) and turn it on and off with a fader
 * (fader.h). As the fader's level rises from 0 to 1.0:
 *
 * - the lamps, up to three materials named "lp_m0", "lp_m1" and "lp_m2", glow: their emission
 *   colour goes from the scene's ambient material colour towards white, while the model's
 *   other materials take the ambient colour as theirs (at level 0 emission is turned off);
 * - the window, the material "m_window", goes from nearly clear (alpha 1) to opaque (30);
 * - the door, the material "m_door", gets a warm diffuse colour, up to red 31, green 27 and
 *   blue 13.
 *
 * A material the model lacks is -1 and left alone. The lamps are a small C++ object with a
 * vtable (data_020e50dc) whose one function names lamp `index`. */
#ifndef CLEAN_MAIN_BUILDING_LIGHTS_H
#define CLEAN_MAIN_BUILDING_LIGHTS_H

#include "main/fader.h"
#include "types.h"

#define BUILDING_LIGHTS_LAMPS 3
#define BUILDING_LIGHTS_NO_MATERIAL (-1)

/* A model resource (NitroSDK's NNSG3dResMdl): only its material count is read here. */
typedef struct BuildingLightsModel {
    u8 unk_00[0x18];
    u8 material_count;
} BuildingLightsModel;

/* The lamps (0x1c bytes). */
typedef struct BuildingLightsLamps {
    const void *vtable;                  /* data_020e50dc */
    s8 materials[BUILDING_LIGHTS_LAMPS]; /* the materials "lp_m0" to "lp_m2" */
    u8 unk_07;
    Fader fader; /* built and taken down, never run here */
} BuildingLightsLamps;

typedef struct BuildingLights {
    Fader fader; /* 0x00 */
    s8 door;     /* 0x14: the material "m_door" */
    u8 unk_15[3];
    BuildingLightsLamps lamps; /* 0x18 */
    s8 window;                 /* 0x34: the material "m_window" */
    u8 unk_35[3];
} BuildingLights;

int BuildingLights_IsLit(const BuildingLights *lights);
void BuildingLights_Switch(BuildingLights *lights, int on, int fade, int flash);
void BuildingLights_Update(BuildingLights *lights, BuildingLightsModel *model);
void BuildingLights_Bind(BuildingLights *lights, BuildingLightsModel *model, int on);
BuildingLights *BuildingLights_Destruct(BuildingLights *lights);
BuildingLights *BuildingLights_Construct(BuildingLights *lights);
char *BuildingLights_LampName(BuildingLightsLamps *lamps, int index);
int BuildingLights_BaseColour(void);
void BuildingLights_ShowLamps(BuildingLightsLamps *lamps, BuildingLightsModel *model, int level);
int BuildingLights_IsLamp(const BuildingLightsLamps *lamps, int material);
void BuildingLights_BindLamps(BuildingLightsLamps *lamps, BuildingLightsModel *model);
BuildingLightsLamps *BuildingLights_DestructLamps(BuildingLightsLamps *lamps);
BuildingLightsLamps *BuildingLights_ConstructLamps(BuildingLightsLamps *lamps);
void BuildingLights_ShowWindow(s8 *window, BuildingLightsModel *model, int level);
void BuildingLights_BindWindow(s8 *window, BuildingLightsModel *model);
void BuildingLights_DestructWindow(s8 *window);
void BuildingLights_ConstructWindow(s8 *window);
void BuildingLights_ShowDoor(s8 *door, BuildingLightsModel *model, int level);
void BuildingLights_BindDoor(s8 *door, BuildingLightsModel *model);
void BuildingLights_DestructDoor(s8 *door);
void BuildingLights_ConstructDoor(s8 *door);

#endif
