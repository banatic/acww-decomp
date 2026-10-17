/* The museum's insect rooms: a process of overlay 4 (vtable 0x022562c0 on the Process base:
 * InsectRoom_Init, InsectRoom_Release, InsectRoom_Update, InsectRoom_Draw) that shows the
 * insects the museum's record has been given (main/museum_record.h, items 0x12b0 + kind) in one
 * of its two rooms, the process's parameter saying which (InsectRoom_RoomOf gives each kind's).
 *
 * There are 56 kinds (0-55) and a 57th, 56, shown with kind 35 when that one is (its own model
 * and animation, bug62 beside kind 35's bug61). Each shown insect takes one of 32 entries of a
 * static table (data_ov004_02259a34, MuseumInsect), made by the overlay's static initialiser:
 * off, loading (InsectRoom_LoadInsect, the next frame: the model "/insect/<tens>1/bug<kind>"
 * from an entry of the room's model pool and its animation, joints or visibility by the table
 * data_ov004_02256308) and shown (InsectRoom_UpdateInsect: its kind's own frame function, then
 * its body on the field, its sound and its matrix). Each kind has an initialiser and a frame
 * function in the table data_ov004_022563ec; those of this file are the InsectKind_* ones.
 *
 * Each insect is placed at its kind's spot (InsectRoom_PlaceInsect) and is "awake" or not by
 * the hour (InsectRoom_HourBand). A few fixed bodies (two or four by the room) are entered on
 * the field each frame, and boxes of the collision map stand for the room's cases while the
 * insects move. */
#ifndef CLEAN_OV004_MUSEUM_INSECTS_H
#define CLEAN_OV004_MUSEUM_INSECTS_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/model_pool.h"
#include "main/sound_emitter.h"
#include "rmo_object.h"
#include "types.h"

/* The kinds, and the two pairs shown together. */
#define MUSEUM_INSECT_KINDS 57
#define MUSEUM_INSECT_GIVEN_KINDS 56
#define MUSEUM_INSECT_WITH_PARTNER 35 /* its partner, kind 56, is shown with it */
#define MUSEUM_INSECT_PARTNER 56
#define MUSEUM_INSECT_PAIR_FIRST 54 /* kinds 54 and 55 keep together */
#define MUSEUM_INSECT_PAIR_SECOND 55

/* The entries of the static table. */
#define MUSEUM_INSECT_ENTRIES 32

/* MuseumInsect.state */
enum {
    MUSEUM_INSECT_OFF = 0,
    MUSEUM_INSECT_LOADING = 1, /* its model is loaded on the next frame */
    MUSEUM_INSECT_SHOWN = 2,
};

/* MuseumInsect.mode, as far as set here. */
#define MUSEUM_INSECT_MODE_REST 0x19
#define MUSEUM_INSECT_MODE_4 4

/* What the table data_ov004_02256308 says of each kind (4 bytes). */
typedef struct InsectKindInfo {
    u8 visibility_anim; /* 0x00: its animation is a visibility one (.nsbva), else joints (.nsbca) */
    u8 pad_01;
    s16 size; /* 0x02: its body's radius and height, and its shadow's size */
} InsectKindInfo;

struct MuseumInsect;

/* The functions of each kind (the table data_ov004_022563ec): the game's. */
typedef struct InsectKindCode {
    void (*init)(struct MuseumInsect *insect);  /* when it is loaded */
    void (*frame)(struct MuseumInsect *insect); /* each frame it is shown */
} InsectKindCode;

/* An insect (0x2d8 bytes). Its base is an animation (vtable 0x022562b0, InsectAnim_*) that
 * only kind 24 plays (a texture animation). */
typedef struct MuseumInsect {
    ModelAnim anim; /* 0x000 */
    u8 unk_20;      /* 0x020: set when its body touches one of flags 0x80 (or 0x40, for kind 23) */
    u8 paired;      /* 0x021: kinds 54 and 55 when both are shown */
    u8 awake;       /* 0x022: its kind's hour bands that the hour now is in */
    u8 pad_23;
    SoundSource sound; /* 0x024: the class's vtable data_0213f020 */
    u8 unk_30[4];      /* 0x030 */
    Vec3 kept;         /* 0x034: a position kept (its body touched one of flags 0x40) */
    Vec3 anchor;       /* 0x040 */
    int unk_4c;        /* 0x04c */
    u8 unk_50;         /* 0x050 */
    u8 unk_51[3];
    fx32 unk_54;                /* 0x054: a height, set with unk_a8 */
    fx32 low[2];                /* 0x058: the x and z it is kept within (InsectRoom_KeepInBounds) */
    fx32 high[2];               /* 0x060 */
    CollisionContacts contacts; /* 0x068 */
    s16 unk_98;                 /* 0x098: frames; 0x098-0x0af are its motion's (func_ov004_02240f2c) */
    u8 unk_9a;                  /* 0x09a */
    u8 pad_9b;                  /* 0x09b */
    s16 unk_9c;                 /* 0x09c */
    s16 unk_9e;                 /* 0x09e */
    fx32 unk_a0;                /* 0x0a0 */
    u8 distance;                /* 0x0a4: a distance it moves, in whole units */
    u8 pad_a5[3];               /* 0x0a5 */
    fx32 unk_a8;                /* 0x0a8: the height it moves at */
    s16 unk_ac;                 /* 0x0ac */
    u8 unk_ae;                  /* 0x0ae */
    u8 pad_af;                  /* 0x0af */
    RmoAnimatedModel model;     /* 0x0b0 */
    s16 unk_168;                /* 0x168 */
    s16 unk_16a;                /* 0x16a */
    int unk_16c;                /* 0x16c */
    u8 unk_170;                 /* 0x170 */
    u8 pad_171;
    s16 mode;        /* 0x172: MUSEUM_INSECT_MODE_* */
    int timer;       /* 0x174: frames */
    Vec3 unk_178[2]; /* 0x178 */
    s16 pitch;       /* 0x190 */
    s16 yaw;         /* 0x192 */
    s16 roll;        /* 0x194 */
    s8 kind;         /* 0x196: -1 for none */
    u8 pad_197;
    int state;           /* 0x198: MUSEUM_INSECT_* */
    FieldPointBody body; /* 0x19c */
    ModelObject unk_1e8; /* 0x1e8 */
    u16 pool_slot;       /* 0x284: its entry of the room's model pool */
    u8 pad_286[2];
    ModelPoolFiles files;                       /* 0x288 */
    Vec3 position;                              /* 0x2c8 */
    void (*frame)(struct MuseumInsect *insect); /* 0x2d4: its kind's, NULL until loaded */
} MuseumInsect;

/* The fixed bodies entered each frame. */
#define INSECT_ROOM_BODIES 4

typedef struct InsectRoom {
    Process base;                              /* 0x000: param is the room, 0 or 1 */
    FieldPointBody bodies[INSECT_ROOM_BODIES]; /* 0x050 */
    ModelPool pool;                            /* 0x180 */
    u8 *with_partner_anim;                     /* 0x198: kind 35's animation file */
    u8 *partner_anim;                          /* 0x19c: kind 56's */
} InsectRoom;

int InsectRoom_HourBand(void);
ModelAnim *InsectAnim_Delete(ModelAnim *self);
ModelAnim *InsectAnim_Destruct(ModelAnim *self);
ModelAnim *InsectAnim_Construct(ModelAnim *self);
InsectRoom *InsectRoom_Delete(InsectRoom *self);
InsectRoom *InsectRoom_Destruct(InsectRoom *self);
InsectRoom *InsectRoom_Construct(InsectRoom *self);
void InsectRoom_ReleaseInsect(InsectRoom *self, int index);
MuseumInsect *MuseumInsect_Destruct(MuseumInsect *self);
MuseumInsect *MuseumInsect_Construct(MuseumInsect *self);
MuseumInsect *InsectRoom_FindPartner(void);
MuseumInsect *InsectRoom_FindPairSecond(void);
int InsectRoom_RoomOf(InsectRoom *self, unsigned int kind);
void InsectRoom_AddGivenInsects(InsectRoom *self);
int InsectRoom_Release(InsectRoom *self);
int InsectRoom_CastsShadow(InsectRoom *self, MuseumInsect *insect);
int InsectRoom_Draw(InsectRoom *self);
void InsectRoom_EnterBodies(InsectRoom *self);
int InsectRoom_Update(InsectRoom *self);
int InsectRoom_IsSolid(InsectRoom *self, int kind, int mode);
void InsectRoom_UpdateInsect(InsectRoom *self, MuseumInsect *insect);
void InsectRoom_KeepInBounds(InsectRoom *self, MuseumInsect *insect, const Vec3 *fallback);
void InsectRoom_LoadInsect(InsectRoom *self, MuseumInsect *insect);
int InsectRoom_Init(InsectRoom *self);
int InsectRoom_AddInsect(InsectRoom *self, int kind);
int InsectRoom_FreeEntry(void);
void InsectRoom_New(void);
void InsectRoom_PlaceInsect(InsectRoom *self, MuseumInsect *insect);

#endif
