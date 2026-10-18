/* The objects of the town's sky (sky_objects.h). */
#include "sky_objects.h"

#include "clean.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "cell_anim.h"
#include "main_random.h"
#include "oam_buffer.h"
#include "sky_object_kinds.h"
#include "sky_resources.h"
#include "sky_shots.h"
#include "sky_show.h"
#include "sky_events.h"
#include "sky_object_sounds.h"

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

/* An object drawn by `engine` at (x, y) unless it is out of view; one of radius 0 never is. */
static void draw_object(int engine, const SkyObject *object, const void *cells, int x, int y)
{
    int radius = object->radius;
    if (radius != 0 && (y + radius < 0 || y - radius > SKY_OBJECTS_LAST_LINE)) {
        return;
    }
    OamBuffer_DrawCell(engine, cells, x, y, object->palette, object->priority, object->scale_x, object->scale_y,
                       object->rotation, -1, object->unk_56, object->unk_57);
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
        int cells = (int) (uintptr_t) CellAnim_Cell(&object->anim);
        if (cells == 0) {
            continue;
        }
        int x = CellAnim_FrameX(&object->anim, -1);
        int y = CellAnim_FrameY(&object->anim, -1);
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
    SkyObjects_TakeTime(objects);
    SkyObjects_FrameHook(objects);
    SkyObjects_RunWeather(objects);

    for (SkyObject *object = objects->entries; object < objects->entries + SKY_OBJECT_COUNT; object++) {
        if (object->resource == SKY_OBJECT_NO_RESOURCE) {
            continue;
        }
        switch (object->state) {
            case SKY_OBJECT_NEW:
                if (object->slot != SKY_OBJECT_NO_SLOT) {
                    SkyObjects_LoadSlots(objects);
                }
                SkyObjectKinds_StartAnimation(object);
                object->state = SKY_OBJECT_RUNNING;
                break;
            case SKY_OBJECT_RUNNING:
                CellAnim_Advance(&object->anim);
                SkyObjectKinds_Run(object);
                break;
            case SKY_OBJECT_DONE:
                SkyObjectKinds_TakeDown(object);
                objects->count--;
                break;
            default:
                break;
        }
    }

    SkyObjects_ReadSlotFiles(objects);
    SkyShots_RunHit((SkyShotsHit *) (void *) objects->unk_2fa8);
    SkyObjectSounds_Update((SkyObjectSounds *) (void *) objects->unk_2fcc);
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
        SkyEvents_Thunder(objects);
    }
    SkyShow_Run(objects);
}
CLEAN_AS(func_020bc42c, SkyObjects_RunEvents)

/* func_020bc464: the rain's or the snow's objects (with neither, their two words cleared), then
 * the other objects of the weather and the time, the show, and outside scene 0x2c four more. */
void SkyObjects_RunWeather(SkyObjects *objects)
{
    switch (data_021f75b0.precipitation) {
        case SKY_FALLING_RAIN:
            SkyEvents_Rain(objects);
            break;
        case SKY_FALLING_SNOW:
            SkyEvents_Snow(objects);
            break;
        default:
            objects->unk_2f08 = 0;
            objects->unk_2f0c = 0;
            break;
    }
    SkyEvents_AddKind12(objects);
    SkyEvents_UpdateMoon(objects);
    SkyEvents_UpdateKind10(objects);
    SkyEvents_AddKind3(objects);
    SkyShow_Run(objects);
    if (SceneQuery_Current() != SKY_OBJECTS_SCENE_2C) {
        SkyEvents_AddKind5(objects);
        SkyEvents_AddKind6(objects);
        SkyEvents_AddKind7(objects);
        SkyShots_Launch(objects);
    }
}
CLEAN_AS(func_020bc464, SkyObjects_RunWeather)

/* func_020bc4dc: taken down: the part at 0x2fcc, then the objects. */
void SkyObjects_Delete(SkyObjects *objects)
{
    SkyObjectSounds_Release((SkyObjectSounds *) (void *) objects->unk_2fcc);
    SkyObjects_DeleteObjects(objects);
}
CLEAN_AS(func_020bc4dc, SkyObjects_Delete)

/* func_020bc4f8: started: the objects, then the part at 0x2fcc. */
void SkyObjects_Start(SkyObjects *objects)
{
    SkyObjects_StartObjects(objects);
    SkyObjectSounds_Init((SkyObjectSounds *) (void *) objects->unk_2fcc);
}
CLEAN_AS(func_020bc4f8, SkyObjects_Start)

/* func_020bc514: an object of kind 2 added (parameter 1), and the first of kind 3, found before,
 * marked (its parameter 1).
 * QUIRK: with no object of kind 3 the mark lands 0x60 bytes past the entries (in the slots and
 * the part after them); the game also checks that address, which is never null. */
void SkyObjects_Add2Mark3(SkyObjects *objects)
{
    int index = SkyObjects_FindKind(objects, SKY_OBJECT_KIND_3);
    uintptr_t marked = (uintptr_t) objects + (u32) index * (u32) sizeof(SkyObject);
    if (marked != 0) {
        SkyObjects_Add(objects, SKY_OBJECT_KIND_2, SKY_OBJECT_COUNT, NULL, 1);
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

/* ---- The entries, the resource slots and the clock */

#include <string.h>

#include "calendar.h"
#include "clock.h"

static_assert(sizeof(SkyObjectSlot) == 12, "a slot");
static_assert(sizeof(SkyResource) == 16, "a resource");
static_assert(offsetof(SkyObjects, files) == 0x1b6c, "the files");
static_assert(offsetof(SkyObjects, unk_2f24) == 0x2f24, "the events' bytes");
static_assert(offsetof(SkyObjects, unk_2f50) == 0x2f50, "0x2f50");
static_assert(offsetof(SkyObjects, unk_2f54) == 0x2f54, "0x2f54");
static_assert(offsetof(SkyObjects, unk_2f58) == 0x2f58, "the shots' requests");

#define SKY_OBJECTS_EVENT_BYTES 6 /* unk_2f24 to 0x2f29, cleared by the constructor */
#define SKY_OBJECTS_NOON 12
#define SKY_OBJECTS_MOON_FIRST 3      /* the moon's first resource, of 28 */
#define SKY_OBJECTS_MOON_LAST 27      /* its last, from the first */
#define SKY_OBJECTS_MOON_DAYS 0x1d87b /* the cycle: 29.53 days (fx32) */
#define SKY_OBJECTS_MOON_HUNDREDTHS 2953
#define SKY_OBJECTS_MOON_OFFSET 2420 /* hundredths of a day into the cycle on 2000-01-01 */

extern const s32 data_020d266c[];         /* per kind: its resource */
extern const SkyResource data_020d2bb4[]; /* per resource */
extern void func_020bf9ac(void *object);  /* an object's constructor */
extern void func_020be554(void *object);  /* and destructor (SkyObject_Destruct) */
extern void func_020bec04(void *request); /* a shot's request's constructor (sky_shots.h) */
extern void func_020be550(void *request); /* and destructor */
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* An entry or a slot by an index the game computes, at the address the ARM would use. */
static SkyObject *sky_objects_entry_at(SkyObjects *objects, int index)
{
    return (SkyObject *) ((uintptr_t) objects->entries + (u32) index * (u32) sizeof(SkyObject));
}

static SkyObjectSlot *sky_objects_slot_at(SkyObjects *objects, int index)
{
    return (SkyObjectSlot *) ((uintptr_t) objects->slots + (u32) index * (u32) sizeof(SkyObjectSlot));
}

/* The objects drawing from a slot's resource (its word at 0x04, counted up by func_020bee74). */
static s32 sky_objects_slot_users(const SkyObjectSlot *slot)
{
    s32 users;
    memcpy(&users, slot->unk_04, sizeof(users));
    return users;
}

/* func_020bdbe0: every object taken down (func_020bf5f0), its entry no longer counted. */
void SkyObjects_RemoveAll(SkyObjects *objects)
{
    for (SkyObject *object = objects->entries; object < objects->entries + SKY_OBJECT_COUNT; object++) {
        if (object->kind != SKY_OBJECT_UNDRAWN) {
            SkyObjectKinds_TakeDown(object);
            objects->count--;
        }
    }
}
CLEAN_AS(func_020bdbe0, SkyObjects_RemoveAll)

/* func_020bdc14: every object of `kind` taken down. */
void SkyObjects_RemoveKind(SkyObjects *objects, int kind)
{
    for (SkyObject *object = objects->entries; object < objects->entries + SKY_OBJECT_COUNT; object++) {
        if (object->kind == kind) {
            SkyObjectKinds_TakeDown(object);
            objects->count--;
        }
    }
}
CLEAN_AS(func_020bdc14, SkyObjects_RemoveKind)

/* func_020bdc50: an object of `kind` added in `entry` (SKY_ENTRY_ANY: the first free one its
 * kind may take), at `position` when given, set up by its kind with `param`; NULL when its
 * resource cannot be shown now or there is no free entry. Its resource's slot is taken (the
 * slots it overlaps released) and the object starts at the next frame (SKY_OBJECT_NEW). */
SkyObject *SkyObjects_Add(SkyObjects *objects, int kind, int entry, const Vec3 *position, int param)
{
    int resource = SkyObjects_ResourceFor(objects, kind, param);
    int slot = SkyObjects_SlotFor(objects, resource);
    if (slot == SKY_SLOT_BUSY) {
        return NULL;
    }
    int index = SkyObjects_FreeEntry(objects, kind, entry);
    if (index == SKY_OBJECT_COUNT) {
        return NULL;
    }
    if (slot != SKY_OBJECT_NO_SLOT) {
        SkySlot_Use(sky_objects_slot_at(objects, slot), resource, (SkyPalettes *) (void *) objects->unk_2eb8);
        SkyObjects_ReleaseOverlapping(objects, slot);
    }
    SkyObject *object = sky_objects_entry_at(objects, index);
    SkyObjectKinds_Reset(object);
    object->kind = kind;
    object->state = SKY_OBJECT_NEW;
    object->slot = slot;
    object->resource = resource;
    object->palette = data_020d2bb4[resource].palette;
    if (position != NULL) {
        object->position.x = position->x;
        object->position.y = position->y;
        object->position.z = position->z;
    }
    SkyObjectKinds_SetUp(object, param);
    objects->count++;
    return object;
}
CLEAN_AS(func_020bdc50, SkyObjects_Add)

/* func_020bdd10: the resource an object of `kind` draws from: the kind's own (data_020d266c),
 * but the moon's picture of the day; for kind 7 resource 40 half the time; for kind 5
 * resource 33 when bit 0 of `param` is set; the show's by its look (param bits 0-3: 45 for
 * looks 0 and 1, 43 for 4, 7, 10 and 13, else 44); kind 2's by its look (47 for 0, 49 for 1,
 * else 48). */
int SkyObjects_ResourceFor(SkyObjects *objects, int kind, int param)
{
    (void) objects;
    int look = param & 0xf;
    switch (kind) {
        case SKY_OBJECT_MOON:
            return SkyObjects_MoonResource();
        case SKY_OBJECT_KIND_7:
            if (MainRandom_Below(2) != 0) {
                return 40;
            }
            return data_020d266c[kind];
        case SKY_OBJECT_KIND_5:
            return (param & 1) != 0 ? 33 : data_020d266c[kind];
        case SKY_OBJECT_SHOW:
            if (look <= 1) {
                return 45;
            }
            if (look == 4 || look == 7 || look == 10 || look == 13) {
                return 43;
            }
            return 44;
        case SKY_OBJECT_KIND_2:
            return look == 0 ? 47 : look == 1 ? 49 : 48;
        default:
            return data_020d266c[kind];
    }
}
CLEAN_AS(func_020bdd10, SkyObjects_ResourceFor)

/* func_020bdd9c: the moon's resource for now, 3 to 30: its picture through a cycle of 29.53
 * days counted from 2000-01-01, 24.2 days into a cycle that day; a day counts from noon.
 * QUIRK: in the first 1/56 of the cycle the rounding gives the last picture, not the first. */
int SkyObjects_MoonResource(void)
{
    Date origin = {1, 1, 0, 0};
    Date today;
    Time now;
    Calendar_Today(&today);
    Calendar_Now(&now);
    int days = Calendar_DaysFrom(&today, &origin);
    if (now.hour < SKY_OBJECTS_NOON) {
        days--;
    }
    if (days < 0) {
        days = 0;
    }
    int hundredths = (days * 100 + SKY_OBJECTS_MOON_OFFSET) % SKY_OBJECTS_MOON_HUNDREDTHS;
    fx32 cycle = FX_Div((hundredths << 12) / 100, SKY_OBJECTS_MOON_DAYS);
    int picture = (cycle * (SKY_OBJECTS_MOON_LAST + 1) - 0x800) >> 12;
    if (picture < 0 || picture > SKY_OBJECTS_MOON_LAST) {
        picture = SKY_OBJECTS_MOON_LAST;
    }
    return picture + SKY_OBJECTS_MOON_FIRST;
}
CLEAN_AS(func_020bdd9c, SkyObjects_MoonResource)

/* func_020bde24: the clock taken for this frame (time and second), the last frame's kept. */
void SkyObjects_TakeTime(SkyObjects *objects)
{
    objects->last_time = objects->time;
    objects->unk_2f20 = objects->unk_2f1c;
    Calendar_Now(&objects->time);
    objects->unk_2f1c = (u32) Clock_Second();
}
CLEAN_AS(func_020bde24, SkyObjects_TakeTime)

/* func_020bde5c: the clock taken, as this frame's and the last frame's. */
void SkyObjects_ResetTime(SkyObjects *objects)
{
    Calendar_Now(&objects->time);
    objects->unk_2f1c = (u32) Clock_Second();
    objects->last_time = objects->time;
    objects->unk_2f20 = objects->unk_2f1c;
}
CLEAN_AS(func_020bde5c, SkyObjects_ResetTime)

/* func_020be0a0: every object taken down. */
void SkyObjects_DeleteObjects(SkyObjects *objects)
{
    SkyObjects_RemoveAll(objects);
}
CLEAN_AS(func_020be0a0, SkyObjects_DeleteObjects)

/* func_020be0a8: the objects of the moment added: the calendar's events read, the rain or snow
 * already falling, the moon and kind 10; kind 5's odds to be drawn again. */
void SkyObjects_StartObjects(SkyObjects *objects)
{
    SkyEvents_ReadCalendar(objects);
    SkyEvents_StartFalling(objects);
    SkyEvents_UpdateMoon(objects);
    SkyEvents_UpdateKind10(objects);
    objects->unk_2f24[SKY_EVENT_ODDS_5] = 0;
}
CLEAN_AS(func_020be0a8, SkyObjects_StartObjects)

/* func_020be0d4: the first entry of `kind`, SKY_OBJECT_COUNT when there is none. */
int SkyObjects_FindKind(SkyObjects *objects, int kind)
{
    for (int i = 0; i < SKY_OBJECT_COUNT; i++) {
        if (objects->entries[i].kind == kind) {
            return i;
        }
    }
    return SKY_OBJECT_COUNT;
}
CLEAN_AS(func_020be0d4, SkyObjects_FindKind)

/* func_020be0f8: the entry a new object of `kind` takes: `entry` when it is free, else (for
 * SKY_ENTRY_ANY) the show's first free one of entries 46 to 58, another kind's first free one
 * of entries 0 to 29 while fewer than 30 are in use; SKY_OBJECT_COUNT when there is none.
 * A given entry is looked at where the ARM would, whatever its index. */
int SkyObjects_FreeEntry(SkyObjects *objects, int kind, int entry)
{
    if (entry != SKY_ENTRY_ANY) {
        return sky_objects_entry_at(objects, entry)->kind == SKY_OBJECT_UNDRAWN ? entry : SKY_OBJECT_COUNT;
    }
    if (kind == SKY_OBJECT_SHOW) {
        for (int i = SKY_ENTRY_SHOW_FIRST; i <= SKY_ENTRY_SHOW_LAST; i++) {
            if (objects->entries[i].kind == SKY_OBJECT_UNDRAWN) {
                return i;
            }
        }
    } else if (objects->count < SKY_ENTRY_OTHERS) {
        for (int i = 0; i < SKY_ENTRY_OTHERS; i++) {
            if (objects->entries[i].kind == SKY_OBJECT_UNDRAWN) {
                return i;
            }
        }
    }
    return SKY_OBJECT_COUNT;
}
CLEAN_AS(func_020be0f8, SkyObjects_FreeEntry)

/* func_020be160: the slots `slot` overlaps emptied: 0 overlaps 3; 1 overlaps 4; 2 overlaps 3
 * and 4; 3 overlaps 0, 2 and 4; 4 overlaps 1, 2 and 3. */
void SkyObjects_ReleaseOverlapping(SkyObjects *objects, int slot)
{
    SkyObjectSlot *slots = objects->slots;
    switch (slot) {
        case 0:
            slots[3].kind = SKY_OBJECT_NO_RESOURCE;
            break;
        case 1:
            slots[4].kind = SKY_OBJECT_NO_RESOURCE;
            break;
        case 2:
            slots[3].kind = SKY_OBJECT_NO_RESOURCE;
            slots[4].kind = SKY_OBJECT_NO_RESOURCE;
            break;
        case 3:
            slots[0].kind = SKY_OBJECT_NO_RESOURCE;
            slots[2].kind = SKY_OBJECT_NO_RESOURCE;
            slots[4].kind = SKY_OBJECT_NO_RESOURCE;
            break;
        case 4:
            slots[1].kind = SKY_OBJECT_NO_RESOURCE;
            slots[2].kind = SKY_OBJECT_NO_RESOURCE;
            slots[3].kind = SKY_OBJECT_NO_RESOURCE;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020be160, SkyObjects_ReleaseOverlapping)

/* func_020be1c4: the slot `resource` is shown from: its own (SKY_OBJECT_NO_SLOT when it needs
 * none) when that slot holds it already, or when neither it nor a slot it overlaps is in use;
 * else SKY_SLOT_BUSY. A slot other than 0 to 4 and SKY_OBJECT_NO_SLOT is busy unless it holds
 * the resource (read where the ARM would). */
int SkyObjects_SlotFor(SkyObjects *objects, int resource)
{
    int slot = data_020d2bb4[resource].slot;
    if (slot == SKY_OBJECT_NO_SLOT || sky_objects_slot_at(objects, slot)->kind == resource) {
        return slot;
    }
    int used[SKY_SLOTS];
    for (int i = 0; i < SKY_SLOTS; i++) {
        used[i] = sky_objects_slot_users(&objects->slots[i]) > 0;
    }
    int free;
    switch (slot) {
        case 0:
            free = !used[0] && !used[3];
            break;
        case 1:
            free = !used[1] && !used[4];
            break;
        case 2:
            free = !used[2] && !used[3] && !used[4];
            break;
        case 3:
            free = !used[3] && !used[0] && !used[2] && !used[4];
            break;
        case 4:
            free = !used[4] && !used[1] && !used[2] && !used[3];
            break;
        default:
            free = 0;
            break;
    }
    return free ? slot : SKY_SLOT_BUSY;
}
CLEAN_AS(func_020be1c4, SkyObjects_SlotFor)

/* A slot's resource shown: with `read_files` its files read first; its cells loaded unless
 * they are (then marked loaded, and with `read_files` no longer changed), its palette loaded
 * unless it is. */
static void sky_objects_show_slot(SkyObjects *objects, SkyObjectSlot *slot, int read_files)
{
    int resource = slot->kind;
    int loaded = slot->loaded;
    int palette_loaded = SkyPalettes_IsLoaded((SkyPalettes *) (void *) objects->unk_2eb8, resource);
    if (!loaded) {
        if (read_files) {
            SkyFiles_ReadCells((SkyFiles *) (void *) objects->files, resource);
        }
        SkySlot_LoadCells(slot, (SkyFiles *) (void *) objects->files);
        slot->loaded = 1;
        if (read_files) {
            slot->changed = 0;
        }
    }
    if (!palette_loaded) {
        SkyPalettes_Load((SkyPalettes *) (void *) objects->unk_2eb8, (SkyFiles *) (void *) objects->files, resource);
    }
}

/* func_020be2d4: each changed slot's resource shown (its files read before,
 * SkyObjects_ReadSlotFiles), and the slot no longer changed. */
void SkyObjects_ReloadChangedSlots(SkyObjects *objects, void *unused)
{
    (void) unused;
    for (SkyObjectSlot *slot = objects->slots; slot < objects->slots + SKY_SLOTS; slot++) {
        if (slot->changed == 0) {
            continue;
        }
        if (slot->kind != SKY_OBJECT_NO_RESOURCE) {
            sky_objects_show_slot(objects, slot, 0);
        }
        slot->changed = 0;
    }
}
CLEAN_AS(func_020be2d4, SkyObjects_ReloadChangedSlots)

/* func_020be348: the files of each changed slot not loaded yet read; an empty changed slot no
 * longer changed. */
void SkyObjects_ReadSlotFiles(SkyObjects *objects)
{
    for (SkyObjectSlot *slot = objects->slots; slot < objects->slots + SKY_SLOTS; slot++) {
        if (slot->changed == 0) {
            continue;
        }
        if (slot->kind == SKY_OBJECT_NO_RESOURCE) {
            slot->changed = 0;
        } else if (slot->loaded == 0) {
            SkyFiles_ReadCells((SkyFiles *) (void *) objects->files, slot->kind);
        }
    }
}
CLEAN_AS(func_020be348, SkyObjects_ReadSlotFiles)

/* func_020be388: each slot's resource shown at once: its files read and its cells loaded
 * unless they are (the slot then no longer changed), its palette loaded unless it is. */
void SkyObjects_LoadSlots(SkyObjects *objects)
{
    for (SkyObjectSlot *slot = objects->slots; slot < objects->slots + SKY_SLOTS; slot++) {
        if (slot->kind != SKY_OBJECT_NO_RESOURCE) {
            sky_objects_show_slot(objects, slot, 1);
        }
    }
}
CLEAN_AS(func_020be388, SkyObjects_LoadSlots)

/* func_020be400: the constructor: the 60 entries, the slots, the palettes (0x2eb8), the shots'
 * requests and their hit (sky_shots.h), the sounds (sky_object_sounds.h), the counters and
 * flags cleared and the files' buffers (0x1b6c) set up. The clock is left alone. */
SkyObjects *SkyObjects_Construct(SkyObjects *objects)
{
    __cxa_vec_ctor(objects->entries, SKY_OBJECT_COUNT, sizeof(SkyObject), func_020bf9ac, func_020be554);
    for (SkyObjectSlot *slot = objects->slots; slot != objects->slots + SKY_SLOTS; slot++) {
        SkySlot_Construct(slot);
    }
    SkyPalettes_Construct((SkyPalettes *) (void *) objects->unk_2eb8);
    __cxa_vec_ctor(objects->unk_2f58, 4, 0x14, func_020bec04, func_020be550);
    SkyShots_ConstructHit((SkyShotsHit *) (void *) objects->unk_2fa8);
    SkyObjectSounds_Construct((SkyObjectSounds *) (void *) objects->unk_2fcc);

    objects->unk_2f00 = 0;
    objects->unk_2f04 = 0;
    objects->unk_2f08 = 0;
    objects->unk_2f0c = 0;
    objects->thunder_timer = 0;
    objects->count = 0;
    for (int i = 0; i < SKY_OBJECTS_EVENT_BYTES; i++) {
        objects->unk_2f24[i] = 0;
    }
    objects->program = 0;
    objects->program_timer = 0;
    objects->countdown = 0;
    for (int i = 0; i < 4; i++) {
        objects->launch_timers[i] = 0;
    }
    objects->launch_delay = 0;
    objects->unk_2f4c = 0;
    objects->unk_2f50 = 0;
    objects->blend_alpha = 0;
    objects->unk_2f54 = 0;

    SkyFiles_Init((SkyFiles *) (void *) objects->files);
    return objects;
}
CLEAN_AS(func_020be400, SkyObjects_Construct)

/* func_020be554: an entry's destructor: its animation's. */
SkyObject *SkyObject_Destruct(SkyObject *object)
{
    CellAnim_Destruct(&object->anim);
    return object;
}
CLEAN_AS(func_020be554, SkyObject_Destruct)

#define SKY_OBJECTS_PART_302C 0x302c /* eight parts of 12 bytes, destroyed as trivial objects */
#define SKY_OBJECTS_PARTS_302C 8
#define SKY_OBJECTS_REQUESTS 0x2f58 /* the shots' four requests, 0x14 bytes each */
#define SKY_OBJECTS_REQUEST_COUNT 4
#define SKY_OBJECTS_REQUEST_SIZE 0x14

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_020012dc(void *object); /* a trivial object's destructor */
extern void func_020be550(void *request);
extern void func_020be554(void *object);

/* func_020c1574: the objects destroyed: the eight parts at 0x302c, the shots' requests, then
 * the entries, each array from its last element by the game's own destructors. */
SkyObjects *SkyObjects_Destruct(SkyObjects *objects)
{
    __cxa_vec_cleanup((u8 *) objects + SKY_OBJECTS_PART_302C, SKY_OBJECTS_PARTS_302C, 0xc, func_020012dc);
    __cxa_vec_cleanup((u8 *) objects + SKY_OBJECTS_REQUESTS, SKY_OBJECTS_REQUEST_COUNT, SKY_OBJECTS_REQUEST_SIZE,
                      func_020be550);
    __cxa_vec_cleanup(objects->entries, SKY_OBJECT_COUNT, (int) sizeof(SkyObject), func_020be554);
    return objects;
}
CLEAN_AS(func_020c1574, SkyObjects_Destruct)
