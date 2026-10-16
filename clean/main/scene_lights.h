/* The 3D scene's lights: a process (0x17c bytes, vtable data_020de710, profile data_020de6c0:
 * execute order 7, draw order 5) that data_021cd864 points to while it exists. It sets the
 * hardware's lights each frame:
 *
 * - up to three lights of the scene (SceneLight), set up from the scene's set (func_02065a7c):
 *   lights of kinds 0-2 turn with the time of day (SceneLight_SunAngle), lights of kinds 3 and
 *   4 are lamps whose colour goes from an unlit to a lit colour as their fader rises, and
 *   kind 5 is a warm glow that brightens with its fader. The lamps are switched by requests
 *   (SceneLights_RequestOn, SceneLights_RequestOff): request 0 for kinds 3 and 4, request 1
 *   for kind 5. Other kinds take a colour of the sky's light of now (Sky_LightColor);
 * - a flash on light 2 (SceneFlash): a thunderbolt's white flash, with its thunder heard about
 *   45 frames later, or a firework's coloured one (SceneLights_StartFlash);
 * - the ambient colour (from Sky_LightColor(3), brighter or white in some rooms) and the
 *   materials' emission colour (SceneLights_EmissionColour).
 *
 * The scene's light kind (data_020ccc48, by scene) decides the rest: kind 0 has every light
 * follow the camera with the sky's colour, kinds 2 and 3 mix the emission colour with the
 * lamp's fader and light their materials with light 0 only. */
#ifndef CLEAN_MAIN_SCENE_LIGHTS_H
#define CLEAN_MAIN_SCENE_LIGHTS_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/calendar.h"
#include "main/fader.h"
#include "types.h"

#define SCENE_LIGHTS_MAX 3
#define SCENE_FLASH_TIMERS 4

/* The scene's light kind (data_020ccc48). */
enum SceneLightsKind {
    SCENE_LIGHTS_FOLLOW_CAMERA = 0,
    SCENE_LIGHTS_LAMP_ROOM = 2,
    SCENE_LIGHTS_LAMP_ROOM_B = 3,
};

/* A light's kind (SceneLight.kind). */
enum SceneLightKind {
    SCENE_LIGHT_SUN_A = 0, /* kinds 0-2 turn about Y with the time of day */
    SCENE_LIGHT_SUN_B = 1,
    SCENE_LIGHT_SUN_C = 2,
    SCENE_LIGHT_SWITCHED_LAMP = 3, /* a lamp whose colour the switch's mode can override */
    SCENE_LIGHT_LAMP = 4,
    SCENE_LIGHT_GLOW = 5,
};

/* How a lamp is switched (SceneLightSwitch.mode). */
enum SceneLightMode {
    SCENE_LIGHT_FADE = 0,  /* over `duration` frames */
    SCENE_LIGHT_FLASH = 1, /* on: flashes first */
    SCENE_LIGHT_FADE_B = 3,
};

/* A lamp's switch: whether it is on, as last taken from its request, and its fader. */
typedef struct SceneLightSwitch {
    u8 on;
    u8 unk_01[3];
    s32 mode; /* 0x04: SceneLightMode */
    Fader fader;
    s32 duration; /* 0x1c: the frames of a fade */
} SceneLightSwitch;

/* A light of the scene (0x44 bytes). */
typedef struct SceneLight {
    s32 kind;         /* SceneLightKind */
    s32 light;        /* 0x04: the hardware light (0-3) */
    Time time_offset; /* 0x08: added to the clock for a sun light's angle */
    u16 unk_0a;
    s32 colour_index;    /* 0x0c: Sky_LightColor's index for the colour of other kinds */
    s16 angle_x;         /* 0x10: the turn about X */
    s16 angle_y;         /* 0x12: the turn about Y of the kinds that do not follow the time */
    SceneLightSwitch sw; /* 0x14 */
    u16 colour;          /* 0x34 */
    u16 unk_36;
    Vec3 direction; /* 0x38 */
} SceneLight;

/* A pending sound of the flash: counting down, then played. */
typedef struct SceneFlashTimer {
    s32 state; /* SceneFlashTimerState */
    s32 count;
} SceneFlashTimer;

enum SceneFlashTimerState {
    SCENE_FLASH_TIMER_COUNTING = 0,
    SCENE_FLASH_TIMER_IDLE = 2,
};

/* The flash, on light 2 (0x44 bytes). */
typedef struct SceneFlash {
    s32 kind; /* SceneFlashKind */
    u16 colour;
    u16 unk_06;
    Vec3 direction;                             /* 0x08 */
    s32 state;                                  /* 0x14: SceneFlashState */
    s32 phase;                                  /* 0x18: 0 brightening, 1 dimming */
    fx32 level;                                 /* 0x1c */
    fx32 step;                                  /* 0x20: added to the level each frame */
    SceneFlashTimer timers[SCENE_FLASH_TIMERS]; /* 0x24 */
} SceneFlash;

/* The flash's kind: thunder, a firework's colour (1-8) or none. */
enum SceneFlashKind {
    SCENE_FLASH_THUNDER = 0,
    SCENE_FLASH_FIREWORK_FIRST = 1,
    SCENE_FLASH_FIREWORK_LAST = 8,
    SCENE_FLASH_NONE = 9,
};

enum SceneFlashState {
    SCENE_FLASH_IDLE = 0,
    SCENE_FLASH_STARTING = 1,
    SCENE_FLASH_RUNNING = 2,
};

typedef struct SceneLights {
    Process process;
    s32 kind;                            /* 0x50: SceneLightsKind */
    s32 count;                           /* 0x54: the lights in use */
    SceneLight lights[SCENE_LIGHTS_MAX]; /* 0x58 */
    SceneFlash flash;                    /* 0x124 */
    u16 ambient;                         /* 0x168 */
    u16 lamp_lit;                        /* 0x16a: the lamps' colours */
    u16 lamp_unlit;                      /* 0x16c */
    u16 emission_lit;                    /* 0x16e: the materials' emission colours */
    u16 emission_unlit;                  /* 0x170 */
    u16 unk_172;
    const Fader *fader; /* 0x174: the lamp's fader the emission follows */
    u8 level;           /* 0x178: light level 0 in a room */
    u8 unk_179[3];
} SceneLights;

/* What a lamp is asked to do (data_021cd87c): request 0 for kinds 3 and 4, 1 for kind 5. */
typedef struct SceneLightRequests {
    u8 on[2];
    u8 unk_02[2];
    s32 mode[2];
    s32 duration[2];
} SceneLightRequests;

/* A scene's preset (data_020ccc7c, by scene; 10 bytes). */
typedef struct SceneLightsPreset {
    u16 lamp_lit;
    u16 emission_lit;
    s16 angle_x; /* the lamps' turns (func_02065a7c) */
    s16 angle_y;
    u8 level;
    u8 unk_09;
} SceneLightsPreset;

/* Three rows of a rotation (a 3x3 matrix, 0x24 bytes). */
typedef struct SceneLightsRotation {
    Vec3 rows[3];
} SceneLightsRotation;

SceneLights *SceneLights_Destruct(SceneLights *self);
SceneLights *SceneLights_DestructFree(SceneLights *self);
SceneLight *SceneLight_Destruct(SceneLight *light);
void SceneLights_RequestOff(u32 index, u32 duration);
void SceneLights_RequestOn(int index, int duration, int mode);
void SceneLight_Draw(SceneLight *light, const SceneLightsRotation *rotation);
void SceneLight_Run(SceneLight *light);
void SceneLight_Update(SceneLight *light);
void SceneLight_GlowColour(SceneLight *light);
void SceneLight_LampColour(SceneLight *light);
void SceneLight_SwitchedLampColour(SceneLight *light);
void SceneLight_FollowCamera(SceneLight *light);
void SceneLight_Rotate(SceneLight *light, Vec3 *v);
void SceneLights_ClampDirection(Vec3 *v, Vec3 *out);
short SceneLight_SunAngle(SceneLight *light);
void SceneLight_Init(SceneLight *light);
int SceneLight_TakeRequest(SceneLightSwitch *sw, int kind);
void SceneLights_StartFlash(int kind);
void SceneFlash_RunFirework(SceneFlash *flash);
void SceneFlash_StartFirework(SceneFlash *flash);
void SceneFlash_Firework(SceneFlash *flash);
void SceneFlash_RunThunder(SceneFlash *flash);
void SceneFlash_StartThunder(SceneFlash *flash);
void SceneFlash_Thunder(SceneFlash *flash);
void SceneFlash_Delete(SceneFlash *flash);
void SceneFlash_Draw(SceneFlash *flash, const SceneLightsRotation *rotation);
void SceneFlash_Run(SceneFlash *flash);
void SceneFlash_Reset(SceneFlash *flash);
void SceneFlash_StartTimers(SceneFlashTimer *timers, int state, int count);
void SceneFlash_DeleteTimers(SceneFlashTimer *timers);
void SceneFlash_RunTimers(SceneFlashTimer *timers);
void SceneFlash_ClearTimers(SceneFlashTimer *timers);
void SceneFlashTimer_Set(SceneFlashTimer *timer, int state, int count);
void SceneFlashTimer_Delete(SceneFlashTimer *timer);
void SceneFlashTimer_Run(SceneFlashTimer *timer);
void SceneFlashTimer_Clear(SceneFlashTimer *timer);
unsigned int SceneLights_LightLevel(unsigned int index);
short SceneLights_EmissionColour(void);
void SceneLights_UpdateAmbient(SceneLights *self);
short SceneLights_AmbientColour(void);
short SceneLights_FlashColour(void);
int SceneLights_RoomMaterialLights(void);
int SceneLights_MaterialLights(void);
void SceneLights_NormalizeRows(const SceneLightsRotation *src, SceneLightsRotation *dst);
int SceneLights_Delete(SceneLights *self);
int SceneLights_Draw(SceneLights *self);
int SceneLights_Execute(SceneLights *self);
int SceneLights_Create(SceneLights *self);

#endif
