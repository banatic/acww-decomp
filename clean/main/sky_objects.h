/* The objects of the town's sky (data_021f8b48, constructed by func_020be400 and run by the sky's
 * process, block_020ba298.h): 60 entries of sprites drawn over the sky by their cell animations
 * (SkyObject), the five slots of resources they share (SkyObjectSlot, sky.h), and the state of
 * what puts them there: the rain and snow (by Sky.precipitation), the thunder of heavy rain, the
 * time of day and the show of kind-9 objects launched from four places (sky_show.h).
 *
 * Without the sky drawn (Sky's data_021f6cd8 0) only the thunder and the show run, and the show
 * is then heard rather than seen (SkyShow_Launch). */
#ifndef CLEAN_MAIN_SKY_OBJECTS_H
#define CLEAN_MAIN_SKY_OBJECTS_H

#include "autoload_2/vector.h"
#include "screen_icon.h" /* CellAnim */
#include "sky.h"
#include "types.h"

#define SKY_OBJECT_COUNT 60
#define SKY_OBJECT_NO_RESOURCE 0x34 /* SkyObject.resource: none */
#define SKY_OBJECT_NO_SLOT 6        /* SkyObject.slot: needs none */

/* SkyObject.state. */
enum SkyObjectState {
    SKY_OBJECT_FREE = 0,
    SKY_OBJECT_NEW = 1,     /* set up at the next frame */
    SKY_OBJECT_RUNNING = 2, /* animated and drawn */
    SKY_OBJECT_DONE = 3,    /* taken down at the next frame */
};

/* SkyObject.kind (func_020bdc50's second argument): the ones these functions know. */
enum SkyObjectKind {
    SKY_OBJECT_KIND_2 = 2,
    SKY_OBJECT_KIND_3 = 3,
    SKY_OBJECT_SHOW = 9,     /* sky_show.h */
    SKY_OBJECT_UNDRAWN = 0xd /* never drawn by SkyObjects_Draw */
};

/* An object (0x74 bytes). */
typedef struct SkyObject {
    s32 kind;      /* 0x00: SkyObjectKind */
    s32 state;     /* 0x04: SkyObjectState */
    s32 resource;  /* 0x08: SKY_OBJECT_NO_RESOURCE: the entry is unused */
    u8 unk_0c[4];  /* 0x0c */
    CellAnim anim; /* 0x10 */
    s32 slot;      /* 0x24: its resource slot, SKY_OBJECT_NO_SLOT for none */
    u8 unk_28[9];  /* 0x28 */
    u8 hidden;     /* 0x31 */
    u8 unk_32[2];  /* 0x32 */
    Vec3 position; /* 0x34: x and y in screen pixels (fx32) */
    u8 unk_40[12]; /* 0x40 */
    s32 scale_x;   /* 0x4c */
    s32 scale_y;   /* 0x50 */
    u16 rotation;  /* 0x54 */
    u8 unk_56;     /* 0x56: func_02088df8's 11th argument */
    u8 unk_57;     /* 0x57: and its 12th */
    s32 priority;  /* 0x58 */
    u8 radius;     /* 0x5c: its half height, 0: never culled */
    s8 palette;    /* 0x5d */
    u8 unk_5e[2];  /* 0x5e */
    u32 param;     /* 0x60: func_020bdc50's last argument */
    u8 unk_64[16]; /* 0x64 */
} SkyObject;

/* data_021f8b48. */
typedef struct SkyObjects {
    SkyObject entries[SKY_OBJECT_COUNT]; /* 0x0000 */
    SkyObjectSlot slots[5];              /* 0x1b30 */
    u8 files[0x2eb8 - 0x1b6c];           /* 0x1b6c */
    u8 unk_2eb8[0x2f00 - 0x2eb8];        /* 0x2eb8 */
    s32 unk_2f00;                        /* 0x2f00 */
    s32 unk_2f04;                        /* 0x2f04 */
    s32 unk_2f08;                        /* 0x2f08: of the rain or snow */
    s32 unk_2f0c;                        /* 0x2f0c: of the rain or snow */
    s32 thunder_timer;                   /* 0x2f10: func_020bda88 */
    s32 count;                           /* 0x2f14: the entries in use */
    Time time;                           /* 0x2f18: the clock at this frame */
    Time last_time;                      /* 0x2f1a: and at the one before */
    u32 unk_2f1c;                        /* 0x2f1c */
    u32 unk_2f20;                        /* 0x2f20 */
    u8 unk_2f24[8];                      /* 0x2f24 */
    s32 program;                         /* 0x2f2c: the show's program, 0: none (sky_show.h) */
    s32 program_timer;                   /* 0x2f30 */
    s32 countdown;                       /* 0x2f34 */
    s32 launch_timers[4];                /* 0x2f38: per launch place */
    s32 launch_delay;                    /* 0x2f48 */
    s32 unk_2f4c;                        /* 0x2f4c */
    u8 unk_2f50;                         /* 0x2f50 */
    u8 blend_alpha;                      /* 0x2f51: the clouds' blending (SkyObjects_SetBlend) */
    u8 unk_2f52[2];                      /* 0x2f52 */
    s32 unk_2f54;                        /* 0x2f54 */
    u8 unk_2f58[0x2fa8 - 0x2f58];        /* 0x2f58: four of 0x14 bytes */
    u8 unk_2fa8[0x2fcc - 0x2fa8];        /* 0x2fa8 */
    u8 unk_2fcc[4];                      /* 0x2fcc */
} SkyObjects;

void SkyObjects_Draw(SkyObjects *objects);
void SkyObjects_FrameHidden(SkyObjects *objects);
void SkyObjects_Frame(SkyObjects *objects);
void SkyObjects_FrameHook(SkyObjects *objects);
void SkyObjects_RunEvents(SkyObjects *objects);
void SkyObjects_RunWeather(SkyObjects *objects);
void SkyObjects_Delete(SkyObjects *objects);
void SkyObjects_Start(SkyObjects *objects);
void SkyObjects_Add2Mark3(SkyObjects *objects);
void SkyObjects_SetBlend(SkyObjects *objects);

#endif
