/* The 3D scene's lights, the flash and the ambient colour (scene_lights.h). */
#include "scene_lights.h"

#include "clean.h"
#include "main/camera_view.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "main/sky.h"
#include "main/sound.h"

static_assert(offsetof(SceneLightSwitch, fader) == 0x08 && sizeof(SceneLightSwitch) == 0x20, "switch");
static_assert(offsetof(SceneLight, sw) == 0x14 && offsetof(SceneLight, direction) == 0x38 && sizeof(SceneLight) == 0x44,
              "light");
static_assert(offsetof(SceneFlash, timers) == 0x24 && sizeof(SceneFlash) == 0x44, "flash");
static_assert(offsetof(SceneLights, kind) == 0x50 && offsetof(SceneLights, flash) == 0x124 &&
                  offsetof(SceneLights, fader) == 0x174 && sizeof(SceneLights) == 0x17c,
              "scene lights");
static_assert(offsetof(SceneLightRequests, duration) == 0x0c, "requests");
static_assert(sizeof(SceneLightsPreset) == 10, "preset");

/* The process while it exists. */
extern SceneLights *data_021cd864;
extern SceneLightRequests data_021cd87c;
/* The scene's light kind and preset, by scene. */
extern const u8 data_020ccc48[];
extern const SceneLightsPreset data_020ccc7c[];
/* The fireworks' colours, by kind - 1. */
extern const u16 data_020ccb98[];
/* The thunder's sound, by the timer's state (only state 0 is read): in scenes 0 and 31, and in
 * the others. */
extern const u16 data_020ccb6c[];
extern const u16 data_020ccb68[];
/* 0 outdoors, 1 in a room. */
extern u8 data_020e54a8;
/* The field camera. */
extern CameraControl *data_021c67a4;
/* The view matrix, whose rotation the lights are turned by. */
extern const SceneLightsRotation data_0213fee4;
/* Vtables: the process's and its base class's. */
extern const u32 data_020de710[];
extern const u32 data_020da13c[];

/* The vector helper is handed the game's destructor of a light, declared as the helper calls it. */
extern void func_02064d8c(void *light);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

extern fx32 VEC_Mag(const Vec3 *v);
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void G3_MultMtx33(const SceneLightsRotation *m);
extern void NNS_G3dGlbLightVector(int light, s16 x, s16 y, s16 z);
extern void NNS_G3dGlbLightColor(int light, u16 colour);

#define REG32(address) (*(volatile u32 *) (uintptr_t) (address))
#define REG_MTX_MODE 0x04000440u
#define REG_MTX_IDENTITY 0x04000454u
#define MTX_MODE_POSITION_VECTOR 2

#define SCENE_LIGHTS_ONE 0x1000          /* 1.0 */
#define SCENE_LIGHTS_DIRECTION_MAX 0xff0 /* a direction is kept just under 1.0 */
#define SCENE_LIGHTS_SET_SPEED 0x800     /* a lamp switched at once, or flashing */
#define SCENE_LIGHTS_SPECIAL_SCENE 0x21
#define SCENE_LIGHTS_BRIGHT_ROOM 0x0b
#define SCENE_LIGHTS_ROOM_AS_SKY_A 0x27
#define SCENE_LIGHTS_ROOM_AS_SKY_B 0x28
#define SCENE_LIGHTS_IN_A_ROOM 1
#define SCENE_LIGHTS_ROOM_LEVEL 0 /* the light level a room has of its own */
#define SCENE_LIGHTS_SKY_AMBIENT 3
#define SCENE_LIGHTS_SKY_EMISSION 2
#define SCENE_LIGHTS_LIGHT_0 1 /* the material light masks */
#define SCENE_LIGHTS_ALL_LIGHTS 0xf
#define SCENE_FLASH_LIGHT 2
#define SCENE_FLASH_FIREWORK_STEP 0x548
#define SCENE_FLASH_FIREWORK_FALL (-614)
#define SCENE_FLASH_THUNDER_STEP 0x800
#define SCENE_FLASH_THUNDER_FALL (-0x333)
#define SCENE_FLASH_THUNDER_DELAY 180 /* counted down four times a frame (SceneFlash_RunTimers) */
#define SCENE_FLASH_THUNDER_GREY 9    /* the thunder's grey at full level, per channel */

/* --- Colours (GXRgb: red in bits 0-4, green 5-9, blue 10-14) --- */

#define CHANNEL_MAX 0x1f
#define COLOUR_ALPHA 0x8000

static int channel(u16 colour, int shift)
{
    return (colour >> shift) & CHANNEL_MAX;
}

/* The channels put together; like the game's, a channel outside 0-31 spills into the others. */
static u16 rgb(int red, int green, int blue)
{
    return (u16) (((u32) blue << 10) | (u32) red | ((u32) green << 5));
}

/* `from` brought towards `to` by `t` (0 to 1.0), channel by channel. */
static u16 mix_colour(u16 from, u16 to, int t)
{
    int red = channel(from, 0) + (((channel(to, 0) - channel(from, 0)) * t) >> 12);
    int green = channel(from, 5) + (((channel(to, 5) - channel(from, 5)) * t) >> 12);
    int blue = channel(from, 10) + (((channel(to, 10) - channel(from, 10)) * t) >> 12);
    return rgb(red, green, blue);
}

/* Each channel scaled by `level` (0 to 1.0). */
static u16 scale_colour(u16 colour, int level)
{
    return rgb((channel(colour, 0) * level) >> 12, (channel(colour, 5) * level) >> 12, (channel(colour, 10) * level) >> 12);
}

static int brighter(int value)
{
    return value > CHANNEL_MAX ? CHANNEL_MAX : value;
}

/* Red and green up by 10 and blue by 7, at most 31 each; the top bit is kept. */
static u16 brighten(u16 colour)
{
    return (u16) ((colour & COLOUR_ALPHA) | rgb(brighter(channel(colour, 0) + 10), brighter(channel(colour, 5) + 10),
                                                brighter(channel(colour, 10) + 7)));
}

static int shl(int value, int count)
{
    return (int) ((u32) value << count);
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back. */
static int div_s32(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    return numerator / divisor;
}

static void set_vec(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* --- The process --- */

/* func_02064d1c (vtable slot 16): the destructor: the lights destructed (the game's
 * func_02064d8c), then the base. */
SceneLights *SceneLights_Destruct(SceneLights *self)
{
    self->process.vtable = data_020de710;
    __cxa_vec_cleanup(self->lights, SCENE_LIGHTS_MAX, sizeof(SceneLight), func_02064d8c);
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    return self;
}
CLEAN_AS(func_02064d1c, SceneLights_Destruct)

/* func_02064d50 (vtable slot 17): the destructor, then the object freed. */
SceneLights *SceneLights_DestructFree(SceneLights *self)
{
    self->process.vtable = data_020de710;
    __cxa_vec_cleanup(self->lights, SCENE_LIGHTS_MAX, sizeof(SceneLight), func_02064d8c);
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02064d50, SceneLights_DestructFree)

/* func_02064d8c: a light's destructor: its fader taken down. */
SceneLight *SceneLight_Destruct(SceneLight *light)
{
    Fader_Destruct(&light->sw.fader);
    return light;
}
CLEAN_AS(func_02064d8c, SceneLight_Destruct)

/* func_02064da0: request `index` (0 or 1) asks its lamps off, a fade taking `duration` frames.
 * The addresses are computed as the ARM does, whatever the index. */
void SceneLights_RequestOff(u32 index, u32 duration)
{
    *(u8 *) ((uintptr_t) data_021cd87c.on + index) = 0;
    *(s32 *) ((uintptr_t) data_021cd87c.duration + index * 4) = (s32) duration;
}
CLEAN_AS(func_02064da0, SceneLights_RequestOff)

/* func_02064db8: request `index` (0 or 1) asks its lamps on in `mode` (SceneLightMode), a fade
 * taking `duration` frames. The addresses are computed as the ARM does, whatever the index. */
void SceneLights_RequestOn(int index, int duration, int mode)
{
    *(u8 *) ((uintptr_t) data_021cd87c.on + (u32) index) = 1;
    *(s32 *) ((uintptr_t) data_021cd87c.duration + (u32) index * 4) = duration;
    *(s32 *) ((uintptr_t) data_021cd87c.mode + (u32) index * 4) = mode;
}
CLEAN_AS(func_02064db8, SceneLights_RequestOn)

/* func_02064ddc: the light set on the hardware: its direction turned by `rotation` (the
 * position and vector matrices made the rotation) and its colour.
 * HW: the matrix mode is set before the identity is loaded and the rotation multiplied. */
void SceneLight_Draw(SceneLight *light, const SceneLightsRotation *rotation)
{
    int id = light->light;
    REG32(REG_MTX_MODE) = MTX_MODE_POSITION_VECTOR;
    REG32(REG_MTX_IDENTITY) = 0;
    G3_MultMtx33(rotation);
    NNS_G3dGlbLightVector(id, (s16) light->direction.x, (s16) light->direction.y, (s16) light->direction.z);
    NNS_G3dGlbLightColor(id, light->colour);
}
CLEAN_AS(func_02064ddc, SceneLight_Draw)

/* func_02064e28: a frame of a light. In a scene whose lights follow the camera, only that
 * (SceneLight_FollowCamera). Else a lamp whose request changed is switched: a fade over its
 * duration (modes 0 and 3), a flash on (mode 1) or at once (the others, and mode 1 off); then
 * its fader runs and its colour and direction are updated. */
void SceneLight_Run(SceneLight *light)
{
    if (data_021cd864->kind == SCENE_LIGHTS_FOLLOW_CAMERA) {
        SceneLight_FollowCamera(light);
        return;
    }

    SceneLightSwitch *sw = &light->sw;
    if (SceneLight_TakeRequest(sw, light->kind) != 0) {
        if (sw->on != 0) {
            switch (sw->mode) {
                case SCENE_LIGHT_FADE:
                case SCENE_LIGHT_FADE_B:
                    Fader_Switch(&sw->fader, 1, 1, 0, div_s32(SCENE_LIGHTS_ONE, sw->duration));
                    break;
                case SCENE_LIGHT_FLASH:
                    Fader_Switch(&sw->fader, 1, 1, 1, SCENE_LIGHTS_SET_SPEED);
                    break;
                default:
                    Fader_Switch(&sw->fader, 1, 0, 0, SCENE_LIGHTS_SET_SPEED);
                    break;
            }
        } else {
            switch (sw->mode) {
                case SCENE_LIGHT_FADE:
                case SCENE_LIGHT_FADE_B:
                    Fader_Switch(&sw->fader, 0, 1, 0, div_s32(SCENE_LIGHTS_ONE, sw->duration));
                    break;
                default:
                    Fader_Switch(&sw->fader, 0, 0, 0, SCENE_LIGHTS_SET_SPEED);
                    break;
            }
        }
    }
    Fader_Run(&sw->fader);
    SceneLight_Update(light);
}
CLEAN_AS(func_02064e28, SceneLight_Run)

/* func_02064ef8: the light's colour and direction: a lamp or glow shines down (its colour from
 * its fader), any other light along -Z with a colour of the sky's light of now; then the
 * direction is turned (SceneLight_Rotate) and kept under 1.0. */
void SceneLight_Update(SceneLight *light)
{
    Vec3 direction;

    switch (light->kind) {
        case SCENE_LIGHT_SWITCHED_LAMP:
            SceneLight_SwitchedLampColour(light);
            set_vec(&direction, 0, -SCENE_LIGHTS_ONE, 0);
            break;
        case SCENE_LIGHT_LAMP:
            SceneLight_LampColour(light);
            set_vec(&direction, 0, -SCENE_LIGHTS_ONE, 0);
            break;
        case SCENE_LIGHT_GLOW:
            SceneLight_GlowColour(light);
            set_vec(&direction, 0, -SCENE_LIGHTS_ONE, 0);
            break;
        default:
            light->colour = (u16) Sky_LightColor(light->colour_index);
            set_vec(&direction, 0, 0, -SCENE_LIGHTS_ONE);
            break;
    }
    SceneLight_Rotate(light, &direction);
    SceneLights_ClampDirection(&direction, &light->direction);
}
CLEAN_AS(func_02064ef8, SceneLight_Update)

/* func_02064f84: a glow's colour by its fader's level: red 25, green 20 and blue 15 at level 0,
 * up by 4, 9 and 16 at 1.0. */
void SceneLight_GlowColour(SceneLight *light)
{
    int level = Fader_Level(&light->sw.fader);
    int blue = (shl(level, 4) >> 12) + 15;
    int red = (shl(level, 2) >> 12) + 25;
    int green = ((9 * level) >> 12) + 20;
    light->colour = rgb(red, green, blue);
}
CLEAN_AS(func_02064f84, SceneLight_GlowColour)

/* func_02064fb4: a lamp's colour: the scene's unlit lamp colour brought towards the lit one by
 * its fader's level. */
void SceneLight_LampColour(SceneLight *light)
{
    int level = Fader_Level(&light->sw.fader);
    SceneLights *lights = data_021cd864;
    light->colour = mix_colour(lights->lamp_unlit, lights->lamp_lit, level);
}
CLEAN_AS(func_02064fb4, SceneLight_LampColour)

/* func_02065020: as SceneLight_LampColour, but an unlit lamp in a mode other than 0 is black
 * and a lit one in mode 2 is red 16, green 16 and blue 13. */
void SceneLight_SwitchedLampColour(SceneLight *light)
{
    int level = Fader_Level(&light->sw.fader);
    SceneLights *lights = data_021cd864;
    u16 colour = mix_colour(lights->lamp_unlit, lights->lamp_lit, level);
    if (light->sw.on == 0) {
        if (light->sw.mode != 0) {
            colour = 0;
        }
    } else if (light->sw.mode == 2) {
        colour = rgb(16, 16, 13);
    }
    light->colour = colour;
}
CLEAN_AS(func_02065020, SceneLight_SwitchedLampColour)

/* func_020650ac: a light that follows the camera: along -Z turned as usual, then about X by
 * the camera's angle over the ground (when there is a camera), with a colour of the sky's
 * light of now. */
void SceneLight_FollowCamera(SceneLight *light)
{
    Vec3 direction;

    set_vec(&direction, 0, 0, -SCENE_LIGHTS_ONE);
    SceneLight_Rotate(light, &direction);
    if (data_021c67a4 != NULL) {
        Vec_RotateX(&direction, CameraControl_GroundAngle(data_021c67a4));
    }
    light->colour = (u16) Sky_LightColor(light->colour_index);
    SceneLights_ClampDirection(&direction, &light->direction);
}
CLEAN_AS(func_020650ac, SceneLight_FollowCamera)

/* func_02065110: `v` turned about X by the light's angle, then about Y by the time of day
 * (kinds 0-2, SceneLight_SunAngle) or by the light's own angle. */
void SceneLight_Rotate(SceneLight *light, Vec3 *v)
{
    switch (light->kind) {
        case SCENE_LIGHT_SUN_A:
        case SCENE_LIGHT_SUN_B:
        case SCENE_LIGHT_SUN_C:
            Vec_RotateX(v, light->angle_x);
            Vec_RotateY(v, SceneLight_SunAngle(light));
            break;
        default:
            Vec_RotateX(v, light->angle_x);
            Vec_RotateY(v, light->angle_y);
            break;
    }
}
CLEAN_AS(func_02065110, SceneLight_Rotate)

/* func_0206515c: `v` normalized and, when that leaves it 0xff0 long or longer, scaled by
 * 0xff0 so a light's direction stays under 1.0; copied to `out` when it is not NULL. */
void SceneLights_ClampDirection(Vec3 *v, Vec3 *out)
{
    if (Vec_NormalizeNonZero(v) != 0 && VEC_Mag(v) >= SCENE_LIGHTS_DIRECTION_MAX) {
        v->x = FX_MulFunc(v->x, SCENE_LIGHTS_DIRECTION_MAX);
        v->y = FX_MulFunc(v->y, SCENE_LIGHTS_DIRECTION_MAX);
        v->z = FX_MulFunc(v->z, SCENE_LIGHTS_DIRECTION_MAX);
    }
    if (out != NULL) {
        out->x = v->x;
        out->y = v->y;
        out->z = v->z;
    }
}
CLEAN_AS(func_0206515c, SceneLights_ClampDirection)

#define MINUTES_PER_DAY 1440
#define HALF_TURN 0x8000
#define QUARTER_TURN 0x4000

/* func_020651b0: the angle about Y of a sun light: the clock's time plus the light's offset
 * as a fraction of the day, half a turn over the day, from a quarter turn at midnight down
 * to a quarter turn the other way. */
short SceneLight_SunAngle(SceneLight *light)
{
    Time offset = light->time_offset;
    Time now;
    Time time;

    Calendar_Now(&now);
    Calendar_AddTime(now, offset, &time);
    int minutes = time.minute + time.hour * 60;
    return (short) -(minutes * HALF_TURN / MINUTES_PER_DAY - QUARTER_TURN);
}
CLEAN_AS(func_020651b0, SceneLight_SunAngle)

/* func_02065218: a light set up at the creation; nothing to do. */
void SceneLight_Init(SceneLight *light)
{
    (void) light;
}
CLEAN_AS(func_02065218, SceneLight_Init)

/* func_0206521c: a lamp (kinds 3 and 4: request 0, kind 5: request 1) takes its request when
 * it is not on as the request asks: its on, mode and duration; whether it took it. Other kinds
 * take none. */
int SceneLight_TakeRequest(SceneLightSwitch *sw, int kind)
{
    int index;

    switch (kind) {
        case SCENE_LIGHT_SWITCHED_LAMP:
        case SCENE_LIGHT_LAMP:
            index = 0;
            break;
        case SCENE_LIGHT_GLOW:
            index = 1;
            break;
        default:
            return 0;
    }
    if (sw->on == data_021cd87c.on[index]) {
        return 0;
    }
    sw->on = data_021cd87c.on[index];
    sw->mode = data_021cd87c.mode[index];
    sw->duration = data_021cd87c.duration[index];
    return 1;
}
CLEAN_AS(func_0206521c, SceneLight_TakeRequest)

/* --- The flash --- */

/* func_02065268: a flash of `kind` (SceneFlashKind) started, when the process exists. */
void SceneLights_StartFlash(int kind)
{
    SceneLights *lights = data_021cd864;
    if (lights != NULL) {
        lights->flash.kind = kind;
        lights->flash.state = SCENE_FLASH_STARTING;
    }
}
CLEAN_AS(func_02065268, SceneLights_StartFlash)

/* func_02065284: a frame of a firework's flash, shining down: the level rises to 1.0, then
 * falls back to 0, where the flash ends (kind none, idle); the colour is the firework's
 * (data_020ccb98) scaled by the level. The table's address is computed as the ARM does,
 * whatever the kind. */
void SceneFlash_RunFirework(SceneFlash *flash)
{
    set_vec(&flash->direction, 0, -SCENE_LIGHTS_ONE, 0);
    flash->level += flash->step;
    if (flash->phase == 0) {
        if (flash->level >= SCENE_LIGHTS_ONE) {
            flash->level = SCENE_LIGHTS_ONE;
            flash->step = SCENE_FLASH_FIREWORK_FALL;
            flash->phase = 1;
        }
    } else if (flash->level < 0) {
        flash->level = 0;
        flash->kind = SCENE_FLASH_NONE;
        flash->state = SCENE_FLASH_IDLE;
    }

    if (flash->kind != SCENE_FLASH_NONE) {
        u16 colour = *(const u16 *) ((uintptr_t) data_020ccb98 + (u32) (flash->kind - 1) * 2);
        flash->colour = scale_colour(colour, flash->level);
    }
}
CLEAN_AS(func_02065284, SceneFlash_RunFirework)

/* func_0206531c: a firework's flash started: black, rising from 0. */
void SceneFlash_StartFirework(SceneFlash *flash)
{
    flash->colour = 0;
    flash->state = SCENE_FLASH_RUNNING;
    flash->level = 0;
    flash->step = SCENE_FLASH_FIREWORK_STEP;
    flash->phase = 0;
}
CLEAN_AS(func_0206531c, SceneFlash_StartFirework)

/* func_02065334: a frame of a firework's flash by its state. */
void SceneFlash_Firework(SceneFlash *flash)
{
    switch (flash->state) {
        case SCENE_FLASH_STARTING:
            SceneFlash_StartFirework(flash);
            break;
        case SCENE_FLASH_RUNNING:
            SceneFlash_RunFirework(flash);
            break;
    }
}
CLEAN_AS(func_02065334, SceneFlash_Firework)

/* func_02065354: a frame of a thunderbolt's flash, shining down: as a firework's, but faster
 * (the step is cleared at the end) and grey, up to 9 in each channel. */
void SceneFlash_RunThunder(SceneFlash *flash)
{
    set_vec(&flash->direction, 0, -SCENE_LIGHTS_ONE, 0);
    flash->level += flash->step;
    if (flash->phase == 0) {
        if (flash->level >= SCENE_LIGHTS_ONE) {
            flash->level = SCENE_LIGHTS_ONE;
            flash->step = SCENE_FLASH_THUNDER_FALL;
            flash->phase = 1;
        }
    } else if (flash->level < 0) {
        flash->level = 0;
        flash->step = 0;
        flash->kind = SCENE_FLASH_NONE;
        flash->state = SCENE_FLASH_IDLE;
    }

    int grey = (SCENE_FLASH_THUNDER_GREY * flash->level) >> 12;
    flash->colour = rgb(grey, grey, grey);
}
CLEAN_AS(func_02065354, SceneFlash_RunThunder)

/* func_020653b0: a thunderbolt's flash started, black and rising from 0, and its thunder set
 * to be heard after a delay. */
void SceneFlash_StartThunder(SceneFlash *flash)
{
    flash->colour = 0;
    flash->state = SCENE_FLASH_RUNNING;
    flash->level = 0;
    flash->step = SCENE_FLASH_THUNDER_STEP;
    flash->phase = 0;
    SceneFlash_StartTimers(flash->timers, SCENE_FLASH_TIMER_COUNTING, SCENE_FLASH_THUNDER_DELAY);
}
CLEAN_AS(func_020653b0, SceneFlash_StartThunder)

/* func_020653d0: a frame of a thunderbolt's flash by its state. */
void SceneFlash_Thunder(SceneFlash *flash)
{
    switch (flash->state) {
        case SCENE_FLASH_STARTING:
            SceneFlash_StartThunder(flash);
            break;
        case SCENE_FLASH_RUNNING:
            SceneFlash_RunThunder(flash);
            break;
    }
}
CLEAN_AS(func_020653d0, SceneFlash_Thunder)

/* func_020653f0: the flash's part of the deletion. */
void SceneFlash_Delete(SceneFlash *flash)
{
    SceneFlash_DeleteTimers(flash->timers);
}
CLEAN_AS(func_020653f0, SceneFlash_Delete)

/* func_020653fc: the flash set on light 2, as SceneLight_Draw; with no flash, light 2 black.
 * HW: the matrix mode is set before the identity is loaded and the rotation multiplied. */
void SceneFlash_Draw(SceneFlash *flash, const SceneLightsRotation *rotation)
{
    if (flash->kind != SCENE_FLASH_NONE) {
        REG32(REG_MTX_MODE) = MTX_MODE_POSITION_VECTOR;
        REG32(REG_MTX_IDENTITY) = 0;
        G3_MultMtx33(rotation);
        NNS_G3dGlbLightVector(SCENE_FLASH_LIGHT, (s16) flash->direction.x, (s16) flash->direction.y, (s16) flash->direction.z);
        NNS_G3dGlbLightColor(SCENE_FLASH_LIGHT, flash->colour);
    } else {
        NNS_G3dGlbLightColor(SCENE_FLASH_LIGHT, 0);
    }
}
CLEAN_AS(func_020653fc, SceneFlash_Draw)

/* func_02065450: a frame of the flash: thunder or firework, its direction turned about X by
 * the camera's angle over the ground (when there is a camera) and kept under 1.0, then the
 * timers. */
void SceneFlash_Run(SceneFlash *flash)
{
    switch (flash->kind) {
        case SCENE_FLASH_THUNDER:
            SceneFlash_Thunder(flash);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case SCENE_FLASH_FIREWORK_LAST:
            SceneFlash_Firework(flash);
            break;
    }
    if (data_021c67a4 != NULL) {
        Vec_RotateX(&flash->direction, CameraControl_GroundAngle(data_021c67a4));
    }
    Vec3 direction = flash->direction;
    SceneLights_ClampDirection(&direction, &flash->direction);
    SceneFlash_RunTimers(flash->timers);
}
CLEAN_AS(func_02065450, SceneFlash_Run)

/* func_020654c8: no flash, and the timers cleared. */
void SceneFlash_Reset(SceneFlash *flash)
{
    flash->kind = SCENE_FLASH_NONE;
    SceneFlash_ClearTimers(flash->timers);
}
CLEAN_AS(func_020654c8, SceneFlash_Reset)

/* The four timer loops below each go over one timer four times.
 * BUG: they never move to the next timer, so only the first of the four is used. */

/* func_020654d8: an idle timer set to `state` and `count`. */
void SceneFlash_StartTimers(SceneFlashTimer *timers, int state, int count)
{
    for (int i = 0; i < SCENE_FLASH_TIMERS; i++) {
        if (timers->state == SCENE_FLASH_TIMER_IDLE) {
            SceneFlashTimer_Set(timers, state, count);
        }
    }
}
CLEAN_AS(func_020654d8, SceneFlash_StartTimers)

/* func_02065504: the timers' part of the deletion. */
void SceneFlash_DeleteTimers(SceneFlashTimer *timers)
{
    for (int i = 0; i < SCENE_FLASH_TIMERS; i++) {
        SceneFlashTimer_Delete(timers);
    }
}
CLEAN_AS(func_02065504, SceneFlash_DeleteTimers)

/* func_02065520: a frame of the timers (so the first counts down four times a frame). */
void SceneFlash_RunTimers(SceneFlashTimer *timers)
{
    for (int i = 0; i < SCENE_FLASH_TIMERS; i++) {
        SceneFlashTimer_Run(timers);
    }
}
CLEAN_AS(func_02065520, SceneFlash_RunTimers)

/* func_0206553c: the timers made idle. */
void SceneFlash_ClearTimers(SceneFlashTimer *timers)
{
    for (int i = 0; i < SCENE_FLASH_TIMERS; i++) {
        SceneFlashTimer_Clear(timers);
    }
}
CLEAN_AS(func_0206553c, SceneFlash_ClearTimers)

/* func_02065558 */
void SceneFlashTimer_Set(SceneFlashTimer *timer, int state, int count)
{
    timer->state = state;
    timer->count = count;
}
CLEAN_AS(func_02065558, SceneFlashTimer_Set)

/* func_02065560: a timer's part of the deletion; nothing to do. */
void SceneFlashTimer_Delete(SceneFlashTimer *timer)
{
    (void) timer;
}
CLEAN_AS(func_02065560, SceneFlashTimer_Delete)

/* func_02065564: a frame of a timer: counting, it counts down and, once below 0, plays the
 * thunder (sound 0x7f3 in scenes 0 and 31, else 0x4cf) and goes idle.
 * QUIRK: a timer in any other state is made idle. */
void SceneFlashTimer_Run(SceneFlashTimer *timer)
{
    if (timer->state != SCENE_FLASH_TIMER_COUNTING) {
        timer->state = SCENE_FLASH_TIMER_IDLE;
        return;
    }
    timer->count--;
    if (timer->count < 0) {
        int sound;
        if (SceneQuery_CurrentIs0() != 0 || SceneQuery_CurrentIs31() != 0) {
            sound = data_020ccb6c[SCENE_FLASH_TIMER_COUNTING];
        } else {
            sound = data_020ccb68[SCENE_FLASH_TIMER_COUNTING];
        }
        SoundSys_PlaySe(sound);
        timer->state = SCENE_FLASH_TIMER_IDLE;
    }
}
CLEAN_AS(func_02065564, SceneFlashTimer_Run)

/* func_020655b8 */
void SceneFlashTimer_Clear(SceneFlashTimer *timer)
{
    timer->state = SCENE_FLASH_TIMER_IDLE;
    timer->count = 0;
}
CLEAN_AS(func_020655b8, SceneFlashTimer_Clear)

/* --- What the rest of the game asks --- */

/* func_020655c4: a light level of now (Sky_LightLevel); in a room, level 0 is the room's own. */
unsigned int SceneLights_LightLevel(unsigned int index)
{
    if (data_020e54a8 == SCENE_LIGHTS_IN_A_ROOM && index == SCENE_LIGHTS_ROOM_LEVEL) {
        return data_021cd864->level;
    }
    return Sky_LightLevel((int) index);
}
CLEAN_AS(func_020655c4, SceneLights_LightLevel)

/* func_02065604: the materials' emission colour: in a lamp-lit room the unlit colour brought
 * towards the lit one by the lamp's fader, elsewhere the sky's (Sky_LightColor(2)); 0 without
 * the process. */
short SceneLights_EmissionColour(void)
{
    SceneLights *lights = data_021cd864;
    if (lights == NULL) {
        return 0;
    }
    switch (lights->kind) {
        case SCENE_LIGHTS_LAMP_ROOM:
        case SCENE_LIGHTS_LAMP_ROOM_B: {
            int level = Fader_Level(lights->fader);
            return (short) mix_colour(lights->emission_unlit, lights->emission_lit, level);
        }
        default:
            return Sky_LightColor(SCENE_LIGHTS_SKY_EMISSION);
    }
}
CLEAN_AS(func_02065604, SceneLights_EmissionColour)

/* func_020656ac: the ambient colour: the sky's (Sky_LightColor(3)), brighter in a house's room
 * while its third light is on; in another room brighter in scene 0x0b, as it is in scenes 0x27
 * and 0x28, white in the others. */
void SceneLights_UpdateAmbient(SceneLights *self)
{
    u16 colour = (u16) Sky_LightColor(SCENE_LIGHTS_SKY_AMBIENT);

    if (SceneKinds_CurrentIsHouseRoom() != 0) {
        if (self->lights[2].sw.on != 0) {
            colour = brighten(colour);
        }
    } else if (data_020e54a8 == SCENE_LIGHTS_IN_A_ROOM) {
        switch (SceneQuery_Current()) {
            case SCENE_LIGHTS_BRIGHT_ROOM:
                colour = brighten(colour);
                break;
            case SCENE_LIGHTS_ROOM_AS_SKY_A:
            case SCENE_LIGHTS_ROOM_AS_SKY_B:
                break;
            default:
                colour = (u16) ((colour & COLOUR_ALPHA) | rgb(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MAX));
                break;
        }
    }
    self->ambient = colour;
}
CLEAN_AS(func_020656ac, SceneLights_UpdateAmbient)

/* func_02065858: the ambient colour.
 * REQUIRES: the process exists. */
short SceneLights_AmbientColour(void)
{
    return (short) data_021cd864->ambient;
}
CLEAN_AS(func_02065858, SceneLights_AmbientColour)

/* func_0206586c: the flash's colour; 0 with no flash or without the process. */
short SceneLights_FlashColour(void)
{
    SceneLights *lights = data_021cd864;
    if (lights != NULL && lights->flash.kind != SCENE_FLASH_NONE) {
        return (short) lights->flash.colour;
    }
    return 0;
}
CLEAN_AS(func_0206586c, SceneLights_FlashColour)

/* The lights a lit material uses in the current scene: light 0 only in a lamp-lit room, else
 * all four. */
static int material_lights(void)
{
    switch (data_020ccc48[SceneQuery_Current()]) {
        case SCENE_LIGHTS_LAMP_ROOM:
        case SCENE_LIGHTS_LAMP_ROOM_B:
            return SCENE_LIGHTS_LIGHT_0;
        default:
            return SCENE_LIGHTS_ALL_LIGHTS;
    }
}

/* func_020658a0: the lights a lit material uses (overlay 4's rooms). */
int SceneLights_RoomMaterialLights(void)
{
    return material_lights();
}
CLEAN_AS(func_020658a0, SceneLights_RoomMaterialLights)

/* func_020658c4: the lights a lit material uses (main's models); the same as
 * SceneLights_RoomMaterialLights. */
int SceneLights_MaterialLights(void)
{
    return material_lights();
}
CLEAN_AS(func_020658c4, SceneLights_MaterialLights)

/* func_020658e8: each row of `src` normalized into `dst`. */
void SceneLights_NormalizeRows(const SceneLightsRotation *src, SceneLightsRotation *dst)
{
    VEC_Normalize(&src->rows[0], &dst->rows[0]);
    VEC_Normalize(&src->rows[1], &dst->rows[1]);
    VEC_Normalize(&src->rows[2], &dst->rows[2]);
}
CLEAN_AS(func_020658e8, SceneLights_NormalizeRows)

/* func_02065914 (vtable slot 3): the deletion: the flash's part, and the process forgotten. */
int SceneLights_Delete(SceneLights *self)
{
    SceneFlash_Delete(&self->flash);
    data_021cd864 = NULL;
    return 1;
}
CLEAN_AS(func_02065914, SceneLights_Delete)

/* func_02065938 (vtable slot 9): the drawing: each light and the flash set on the hardware,
 * turned by the view matrix's rotation with its rows normalized. */
int SceneLights_Draw(SceneLights *self)
{
    SceneLightsRotation rotation;

    SceneLights_NormalizeRows(&data_0213fee4, &rotation);
    for (int i = 0; i < self->count; i++) {
        SceneLight_Draw(&self->lights[i], &rotation);
    }
    SceneFlash_Draw(&self->flash, &rotation);
    return 1;
}
CLEAN_AS(func_02065938, SceneLights_Draw)

/* func_02065980 (vtable slot 6): a frame: each light, the flash and the ambient colour. */
int SceneLights_Execute(SceneLights *self)
{
    for (int i = 0; i < self->count; i++) {
        SceneLight_Run(&self->lights[i]);
    }
    SceneFlash_Run(&self->flash);
    SceneLights_UpdateAmbient(self);
    return 1;
}
CLEAN_AS(func_02065980, SceneLights_Execute)

/* func_020659b8 (vtable slot 0): the creation: the process made data_021cd864, the scene's
 * light kind and preset taken (scene 0x21 has colours of its own, with unlit colours; the
 * others' unlit colours are black), the lights set up and run once, and no flash. */
int SceneLights_Create(SceneLights *self)
{
    data_021cd864 = self;
    int scene = SceneQuery_Current();
    self->kind = data_020ccc48[scene];

    if (scene == SCENE_LIGHTS_SPECIAL_SCENE) {
        self->lamp_lit = 0x3e99;
        self->lamp_unlit = 0x3caa;
        self->emission_lit = 0x494a;
        self->emission_unlit = 0x518c;
        self->level = 0x0b;
    } else {
        const SceneLightsPreset *preset = &data_020ccc7c[scene];
        self->lamp_lit = preset->lamp_lit;
        self->lamp_unlit = 0;
        self->emission_lit = preset->emission_lit;
        self->emission_unlit = 0;
        self->level = preset->level;
    }

    SceneLights_SetUp(self);
    for (int i = 0; i < self->count; i++) {
        SceneLight_Init(&self->lights[i]);
        SceneLight_Run(&self->lights[i]);
    }
    SceneFlash_Reset(&self->flash);
    return 1;
}
CLEAN_AS(func_020659b8, SceneLights_Create)

/* --- The set-up and the construction --- */

/* The light sets, by the scene's light kind. */
extern const SceneLightSet *const data_020de6f4[];
/* A light's constructor, handed to the vector helper with the game's destructor. */
extern void func_02065bec(void *light);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

static_assert(sizeof(SceneLightDef) == 0x14, "light def");

/* func_02065a7c: the lights set up from the set of the scene's light kind. First the lamps'
 * requests: in a room that is not a house's, request 0 asks its lamps on (a fade of 2 frames),
 * else off (1 frame); request 1 asks its glow off. Then each light of the set is copied (all
 * but its halfword 0x0a); a lamp (kinds 3 to 5) takes the turns of the scene's preset, starts
 * off with its fader set to 0, and the emission follows the fader of the last lamp. */
void SceneLights_SetUp(SceneLights *self)
{
    int scene = SceneQuery_Current();
    if (data_020e54a8 == SCENE_LIGHTS_IN_A_ROOM && SceneKinds_CurrentIsHouseRoom() == 0) {
        SceneLights_RequestOn(0, 2, SCENE_LIGHT_FADE);
    } else {
        SceneLights_RequestOff(0, 1);
    }
    SceneLights_RequestOff(1, 1);

    const SceneLightSet *set = data_020de6f4[self->kind];
    const SceneLightsPreset *preset = &data_020ccc7c[scene];
    int count = set->count;
    self->count = count;
    for (int i = 0; i < count; i++) {
        const SceneLightDef *def = set->lights[i];
        SceneLight *light = &self->lights[i];
        light->kind = def->kind;
        light->light = def->light;
        light->time_offset = def->time_offset;
        light->colour_index = def->colour_index;
        light->angle_x = def->angle_x;
        light->angle_y = def->angle_y;
        switch (def->kind) {
            case SCENE_LIGHT_SWITCHED_LAMP:
            case SCENE_LIGHT_LAMP:
            case SCENE_LIGHT_GLOW:
                light->angle_x = preset->angle_x;
                light->angle_y = preset->angle_y;
                light->sw.on = 0;
                Fader_Set(&light->sw.fader, 0);
                self->fader = &light->sw.fader;
                break;
        }
    }
}
CLEAN_AS(func_02065a7c, SceneLights_SetUp)

/* func_02065ba0: the process allocated (zeroed) and constructed: the base process, then the
 * three lights (the game's func_02065bec, destructed by func_02064d8c if one fails). Returns it
 * as an address, 0 when the allocation failed. */
int SceneLights_New(void)
{
    SceneLights *self = Heap_AllocAuxZeroed(sizeof(SceneLights));
    if (self != NULL) {
        Process_Construct(&self->process);
        self->process.vtable = data_020da13c;
        self->process.vtable = data_020de710;
        __cxa_vec_ctor(self->lights, SCENE_LIGHTS_MAX, sizeof(SceneLight), func_02065bec, func_02064d8c);
    }
    return (int) (uintptr_t) self;
}
CLEAN_AS(func_02065ba0, SceneLights_New)

/* func_02065bec: a light's constructor: its fader built. */
SceneLight *SceneLight_Construct(SceneLight *light)
{
    Fader_Construct(&light->sw.fader);
    return light;
}
CLEAN_AS(func_02065bec, SceneLight_Construct)
