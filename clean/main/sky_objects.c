/* The objects of the town's sky (sky_objects.h). */
#include "sky_objects.h"

#include "clean.h"
#include "scene_kinds.h"
#include "scene_query.h"

static_assert(sizeof(SkyObject) == 0x74, "an object");
static_assert(offsetof(SkyObject, anim) == 0x10, "the animation");
static_assert(offsetof(SkyObject, hidden) == 0x31, "hidden");
static_assert(offsetof(SkyObject, position) == 0x34, "the position");
static_assert(offsetof(SkyObject, scale_x) == 0x4c, "the scale");
static_assert(offsetof(SkyObject, radius) == 0x5c, "the radius");
static_assert(offsetof(SkyObject, param) == 0x60, "the parameter");
static_assert(offsetof(SkyObjects, slots) == 0x1b30, "the slots");
static_assert(offsetof(SkyObjects, unk_2eb8) == 0x2eb8, "0x2eb8");
static_assert(offsetof(SkyObjects, thunder_timer) == 0x2f10, "the thunder");
static_assert(offsetof(SkyObjects, time) == 0x2f18, "the time");
static_assert(offsetof(SkyObjects, program) == 0x2f2c, "the program");
static_assert(offsetof(SkyObjects, launch_timers) == 0x2f38, "the launch timers");
static_assert(offsetof(SkyObjects, blend_alpha) == 0x2f51, "the blending");
static_assert(offsetof(SkyObjects, unk_2fa8) == 0x2fa8, "0x2fa8");
static_assert(offsetof(SkyObjects, unk_2fcc) == 0x2fcc, "0x2fcc");

#define SKY_OBJECTS_ENGINE_MAIN 0
#define SKY_OBJECTS_ENGINE_SUB 1
#define SKY_OBJECTS_LAST_LINE 0xbf
#define SKY_OBJECTS_MAIN_TOP 0x100 /* where the main screen starts below the sub screen */
#define SKY_OBJECTS_SCENE_2C 0x2c  /* a scene without four of the weather's calls */
#define SKY_OBJECTS_BLEND_LINES 0x77
#define SKY_OBJECTS_BLEND_FADE_LINES 0x20
#define SKY_OBJECTS_BLEND_BACKDROP 0x1000 /* BLDALPHA: the backdrop's weight 16 */

extern int func_0208a1d0(const CellAnim *anim);            /* the cells shown, 0: none */
extern s16 func_0208a1b0(const CellAnim *anim, int frame); /* a frame's x, the current one for -1 */
extern s16 func_0208a198(const CellAnim *anim, int frame); /* a frame's y, the current one for -1 */
extern void func_0208a0c8(CellAnim *anim);                 /* the animation advanced */
extern void func_02088df8(int engine, const void *cells, int x, int y, int palette, int priority, int scale_x, int scale_y,
                          int rotation, int arg9, int arg10, int arg11);
extern void func_020bde24(SkyObjects *objects);
extern void func_020be388(SkyObjects *objects);
extern void func_020bf5b8(SkyObject *object);
extern void func_020bf700(SkyObject *object);
extern void func_020bf5f0(SkyObject *object);
extern void func_020be348(SkyObjects *objects);
extern void func_020bea1c(void *part);
extern void func_020be568(void *part);
extern void func_020bda88(SkyObjects *objects); /* the thunder */
extern void func_020bd3b4(SkyObjects *objects); /* the show's program (sky_show.h) */
extern void func_020bd938(SkyObjects *objects);
extern void func_020bd7a4(SkyObjects *objects);
extern void func_020bceb4(SkyObjects *objects);
extern void func_020bd688(SkyObjects *objects);
extern void func_020bd054(SkyObjects *objects);
extern void func_020bd6d0(SkyObjects *objects);
extern void func_020bd2d0(SkyObjects *objects);
extern void func_020bd1c4(SkyObjects *objects);
extern void func_020bd124(SkyObjects *objects);
extern void func_020bcfbc(SkyObjects *objects);
extern void func_020be600(void *part);
extern void func_020be0a0(SkyObjects *objects);
extern void func_020be0a8(SkyObjects *objects);
extern void func_020be628(void *part);
extern int func_020be0d4(SkyObjects *objects, int kind); /* the first entry of `kind`, 60: none */
extern void *func_020bdc50(SkyObjects *objects, int kind, int limit, const Vec3 *position, u32 param);

/* An object drawn by `engine` at (x, y) unless it is out of view; one of radius 0 never is. */
static void draw_object(int engine, const SkyObject *object, const void *cells, int x, int y)
{
    int radius = object->radius;
    if (radius != 0 && (y + radius < 0 || y - radius > SKY_OBJECTS_LAST_LINE)) {
        return;
    }
    func_02088df8(engine, cells, x, y, object->palette, object->priority, object->scale_x, object->scale_y, object->rotation,
                  -1, object->unk_56, object->unk_57);
}

/* func_020bc1bc: the running objects drawn (but the kind never drawn and the hidden ones) at their
 * position plus their frame's offset, raised by the shift of the set of lines not shown. With
 * the sky on the main screen they are drawn there; with it on the sub screen those above line
 * 0xc0 are drawn on the sub screen, those below line 0x100 on the main one (the gap between the
 * screens in between).
 * REQUIRES: Sky.shift_index is 0 or 1. */
void SkyObjects_Draw(SkyObjects *objects)
{
    s32 shift = data_021f75b0.shift[data_021f75b0.shift_index ^ 1];
    for (SkyObject *object = objects->entries; object < objects->entries + SKY_OBJECT_COUNT; object++) {
        if (object->kind == SKY_OBJECT_UNDRAWN || object->state != SKY_OBJECT_RUNNING || object->hidden != 0) {
            continue;
        }
        int cells = func_0208a1d0(&object->anim);
        if (cells == 0) {
            continue;
        }
        int x = func_0208a1b0(&object->anim, -1);
        int y = func_0208a198(&object->anim, -1);
        const void *cell_data = (const void *) (uintptr_t) (u32) cells;
        x += (object->position.x + 0x800) >> 12;
        y += (object->position.y + 0x800) >> 12;
        int line = y - shift;
        if (data_021f75b0.screen == SKY_SCREEN_MAIN) {
            draw_object(SKY_OBJECTS_ENGINE_MAIN, object, cell_data, x, line);
        } else if (y < SCREEN_LINES) {
            draw_object(SKY_OBJECTS_ENGINE_SUB, object, cell_data, x, line);
        } else if (y > SKY_OBJECTS_MAIN_TOP) {
            draw_object(SKY_OBJECTS_ENGINE_MAIN, object, cell_data, x, line - SKY_OBJECTS_MAIN_TOP);
        }
    }
}
CLEAN_AS(func_020bc1bc, SkyObjects_Draw)

/* func_020bc380: a frame without the sky drawn: the thunder and the show only. */
void SkyObjects_FrameHidden(SkyObjects *objects)
{
    SkyObjects_RunEvents(objects);
}
CLEAN_AS(func_020bc380, SkyObjects_FrameHidden)

/* func_020bc388: a frame: the clock taken, the weather's and the show's objects added, each
 * entry in use stepped (a new one set up and running, a running one animated, a finished one
 * taken down), then the slots and the two parts at 0x2fa8 and 0x2fcc run. */
void SkyObjects_Frame(SkyObjects *objects)
{
    func_020bde24(objects);
    SkyObjects_FrameHook(objects);
    SkyObjects_RunWeather(objects);

    for (SkyObject *object = objects->entries; object < objects->entries + SKY_OBJECT_COUNT; object++) {
        if (object->resource == SKY_OBJECT_NO_RESOURCE) {
            continue;
        }
        switch (object->state) {
            case SKY_OBJECT_NEW:
                if (object->slot != SKY_OBJECT_NO_SLOT) {
                    func_020be388(objects);
                }
                func_020bf5b8(object);
                object->state = SKY_OBJECT_RUNNING;
                break;
            case SKY_OBJECT_RUNNING:
                func_0208a0c8(&object->anim);
                func_020bf700(object);
                break;
            case SKY_OBJECT_DONE:
                func_020bf5f0(object);
                objects->count--;
                break;
            default:
                break;
        }
    }

    func_020be348(objects);
    func_020bea1c(objects->unk_2fa8);
    func_020be568(objects->unk_2fcc);
}
CLEAN_AS(func_020bc388, SkyObjects_Frame)

/* func_020bc428: called each frame; does nothing. */
void SkyObjects_FrameHook(SkyObjects *objects)
{
    (void) objects;
}
CLEAN_AS(func_020bc428, SkyObjects_FrameHook)

/* func_020bc42c: in a scene of sound kind other than 0 and 3 (SceneKinds_SoundKind), the
 * thunder while heavy rain falls, and the show. */
void SkyObjects_RunEvents(SkyObjects *objects)
{
    int kind = SceneKinds_SoundKind(0);
    if (kind == 0 || kind == 3) {
        return;
    }
    if (data_021f75b0.precipitation == SKY_FALLING_RAIN && data_021f75b0.weather == SKY_WEATHER_HEAVY_RAIN) {
        func_020bda88(objects);
    }
    func_020bd3b4(objects);
}
CLEAN_AS(func_020bc42c, SkyObjects_RunEvents)

/* func_020bc464: the rain's or the snow's objects (with neither, their two words cleared), then
 * the other objects of the weather and the time, the show, and outside scene 0x2c four more. */
void SkyObjects_RunWeather(SkyObjects *objects)
{
    switch (data_021f75b0.precipitation) {
        case SKY_FALLING_RAIN:
            func_020bd938(objects);
            break;
        case SKY_FALLING_SNOW:
            func_020bd7a4(objects);
            break;
        default:
            objects->unk_2f08 = 0;
            objects->unk_2f0c = 0;
            break;
    }
    func_020bceb4(objects);
    func_020bd688(objects);
    func_020bd054(objects);
    func_020bd6d0(objects);
    func_020bd3b4(objects);
    if (SceneQuery_Current() != SKY_OBJECTS_SCENE_2C) {
        func_020bd2d0(objects);
        func_020bd1c4(objects);
        func_020bd124(objects);
        func_020bcfbc(objects);
    }
}
CLEAN_AS(func_020bc464, SkyObjects_RunWeather)

/* func_020bc4dc: taken down: the part at 0x2fcc, then the objects. */
void SkyObjects_Delete(SkyObjects *objects)
{
    func_020be600(objects->unk_2fcc);
    func_020be0a0(objects);
}
CLEAN_AS(func_020bc4dc, SkyObjects_Delete)

/* func_020bc4f8: started: the objects, then the part at 0x2fcc. */
void SkyObjects_Start(SkyObjects *objects)
{
    func_020be0a8(objects);
    func_020be628(objects->unk_2fcc);
}
CLEAN_AS(func_020bc4f8, SkyObjects_Start)

/* func_020bc514: an object of kind 2 added (parameter 1), and the first of kind 3, found before,
 * marked (its parameter 1).
 * QUIRK: with no object of kind 3 the mark lands 0x60 bytes past the entries (in the slots and
 * the part after them); the game also checks that address, which is never null. */
void SkyObjects_Add2Mark3(SkyObjects *objects)
{
    int index = func_020be0d4(objects, SKY_OBJECT_KIND_3);
    uintptr_t marked = (uintptr_t) objects + (u32) index * (u32) sizeof(SkyObject);
    if (marked != 0) {
        func_020bdc50(objects, SKY_OBJECT_KIND_2, SKY_OBJECT_COUNT, NULL, 1);
        ((SkyObject *) marked)->param = 1;
    }
}
CLEAN_AS(func_020bc514, SkyObjects_Add2Mark3)

/* func_020bc548: the clouds' blending of the set of lines shown: `blend_alpha` down to line
 * 0x76, then fading out over 32 lines (rounded); the lines below are left as they were.
 * The table's address is computed as the ARM does, whatever Sky.shown. */
void SkyObjects_SetBlend(SkyObjects *objects)
{
    u16 *line =
        (u16 *) ((uintptr_t) data_021f75b0.blend_alpha + data_021f75b0.shown * (u32) sizeof(data_021f75b0.blend_alpha[0]));
    int alpha = objects->blend_alpha;
    for (int i = 0; i < SKY_OBJECTS_BLEND_LINES; i++) {
        *line++ = (u16) (alpha | SKY_OBJECTS_BLEND_BACKDROP);
    }
    int step = -(alpha << 12) / SKY_OBJECTS_BLEND_FADE_LINES;
    for (int i = 0; i < SKY_OBJECTS_BLEND_FADE_LINES; i++) {
        *line++ = (u16) ((((step * i + 0x800) >> 12) + alpha) | SKY_OBJECTS_BLEND_BACKDROP);
    }
}
CLEAN_AS(func_020bc548, SkyObjects_SetBlend)
