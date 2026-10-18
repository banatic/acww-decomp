/* Overlay 3's tile events: a table of four entries (0xa4 bytes each) per player at
 * data_ov003_0223cfe4, set up by the process of vtable 0x0223bc7c (0x6a70 bytes, made by
 * func_ov003_02227454). func_ov003_022213f8 starts an event in a free entry of a player: a kind
 * (3-14), a tile, a point, an id (an item or object code) and two more values; the
 * func_ov003_0222139c variant first makes the player 0 unless the session is linked.
 *
 * The functions here start the event of one kind each from what the field's players do (the
 * player states of field_actor.c, the tile requests of main), and give that process its
 * destructors. Which effect each kind shows is not read from this code. */
#ifndef CLEAN_OV003_TILE_EVENT_H
#define CLEAN_OV003_TILE_EVENT_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/model_object.h"
#include "main/tile_changes.h" /* TileChangesTile */
#include "types.h"

/* The process of vtable 0x0223bc7c, as far as its destructors read it. */
typedef struct TileEventProcess {
    Process process;                 /* 0x0000 */
    u8 unk_0050[0x174 - 0x50];       /* 0x0050 */
    ModelObject models_0174[0x12];   /* 0x0174 */
    ModelObject models_0c6c[6];      /* 0x0c6c */
    ModelObject models_1014[3];      /* 0x1014 */
    ModelObject models_11e8[6];      /* 0x11e8 */
    ModelObject models_1590[0x28];   /* 0x1590 */
    ModelObject models_2df0[4];      /* 0x2df0 */
    u8 unk_3060[0x3068 - 0x3060];    /* 0x3060 */
    ModelObject models_3068[0x20];   /* 0x3068 */
    ModelObject models_43e8[5];      /* 0x43e8 */
    u8 unk_46f4[0x4708 - 0x46f4];    /* 0x46f4 */
    ModelObject models_4708[2];      /* 0x4708 */
    ModelObject models_4840[2];      /* 0x4840 */
    u8 unk_4978[0x49a8 - 0x4978];    /* 0x4978 */
    ModelObject models_49a8[2];      /* 0x49a8 */
    ModelSet sets[4];                /* 0x4ae0 */
    u8 member_4b20[0x6a70 - 0x4b20]; /* 0x4b20: destroyed by func_ov003_02223b34, and the rest */
} TileEventProcess;

int TileEvent_StartKindE(int player, const Vec3 *position);
void TileEvent_StartKindD(int player, int id, const TileChangesTile *tile, const Vec3 *position);
int TileEvent_FindFreeTileAround(TileChangesTile *tile);
int TileEvent_StartKindC(int variant, int x);
void TileEvent_StartKindB(int player, int id, const TileChangesTile *tile);
int TileEvent_StartKindA(int player, const Vec3 *position);
void TileEvent_StartKind9(int player, int id, const TileChangesTile *tile, const Vec3 *position);
int TileEvent_StartKind8(int player, const Vec3 *position, int angle);
void TileEvent_StartKind7(int player, u32 id, const TileChangesTile *tile, const Vec3 *position);
void TileEvent_StartKind6(int player, int id, const TileChangesTile *tile, const Vec3 *position, int extra);
void TileEvent_StartKind5(int player, int id, const TileChangesTile *tile, const Vec3 *position, short angle, int extra);
int TileEvent_StartKind4(int player, int id, const TileChangesTile *tile);
void TileEvent_StartKind3(int player, const Vec3 *position);
TileEventProcess *TileEvent_DestroyProcess(TileEventProcess *process);
TileEventProcess *TileEvent_DestroyAndFreeProcess(TileEventProcess *process);

struct AcreMap;

/* An entry of the events' table (0xa4 bytes; four per player, twenty in all). An event is
 * started by TileEvent_Begin with a kind 0-14; each frame TileEvent_StepAll runs its kind's
 * step, which ends it (TileEvent_End) when its motion is over, and TileEvent_DrawAll draws `id`
 * at `position` + `offset`, scaled by `scale`. */
typedef struct TileEventEntry {
    int player;           /* 0x00 */
    int active;           /* 0x04 */
    u16 id;               /* 0x08: what is drawn (an item or object code), 0xfff1 for nothing */
    u16 under;            /* 0x0a: the item of the tile change at the tile at the start, or 0xfff1 */
    int kind;             /* 0x0c: 0-14; 15 once ended */
    TileChangesTile tile; /* 0x10 */
    Vec3 position;        /* 0x18 */
    Vec3 offset;          /* 0x24: added to the position when drawn */
    Vec3 velocity;        /* 0x30: added to the position by the kinds that move */
    Vec3 scale;           /* 0x3c */
    s16 angle;            /* 0x48: the start's `angle` (kinds 8 and 11 a direction, 5 and 6 a flag) */
    s16 unk_4a;           /* 0x4a: 0 */
    s16 state;            /* 0x4c: the kind's phase, from 0 */
    u16 frames;           /* 0x4e: frames since the start (kind 6 adds to it) */
    s16 counter;          /* 0x50 */
    s16 countdown;        /* 0x52: 0x1f at the start; also handed to the item drawer */
    Vec3 point;           /* 0x54: the start's point */
    u8 sound[0x40];       /* 0x60: a sound emitter (sound_emitter.h, its first 0x40 bytes) */
    u8 finish_change;     /* 0xa0: the tile change at the tile is finished when the event lets go */
    u8 release_change;    /* 0xa1: else it is released, when this is set */
    u8 pad_a2[2];
} TileEventEntry;

#define TILE_EVENT_PLAYER_ENTRIES 4
#define TILE_EVENT_ENTRIES 20

/* The record TileEvent_DrawAll hands the drawers (func_ov003_022251e8-02225768). */
typedef struct TileEventDraw {
    u16 id;            /* 0x00 */
    u8 pad_02[2];      /* 0x02 */
    Vec3 bent;         /* 0x04: `point` bent over the globe */
    Vec3 point;        /* 0x10 */
    Vec3 scale;        /* 0x1c */
    Vec3 sum;          /* 0x28: the entry's position + offset */
    Vec3 item_point;   /* 0x34 */
    Vec3 item_scale;   /* 0x40 */
    Vec3 growth_point; /* 0x4c */
} TileEventDraw;

int TileEvent_StartUnitKind3(int player, const Vec3 *position);
int TileEvent_StartUnitKind2(int player, const Vec3 *position);
int TileEvent_StartUnitKind1(int player, const Vec3 *position, int extra);
int TileEvent_StartKind0(u32 player, u32 id, const TileChangesTile *tile, const Vec3 *position);
int TileEvent_EndAt(int player, const TileChangesTile *tile);
int TileEvent_StartLocal(TileEventEntry *table, int player, const int *tile, const int *point, int kind, u16 id, s16 angle,
                         int extra);
int TileEvent_Start(TileEventEntry *table, int player, const int *tile, const int *point, int kind, u16 id, s16 angle,
                    int extra);
TileEventEntry *TileEvent_FreeEntry(TileEventEntry *table, int player);
void TileEvent_ReleaseAll(TileEventEntry *entries);
void TileEvent_DrawAll(TileEventEntry *entries);
void TileEvent_StepAll(TileEventEntry *entries);
void TileEvent_InitAll(TileEventEntry *entries);
void TileEvent_InitKind14(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map);
void TileEvent_StepKind12(TileEventEntry *entry);
void TileEvent_InitKind12(TileEventEntry *entry, const Vec3 *point);
void TileEvent_PlaceKind12Effect(int *transform);
void TileEvent_StepKind11(TileEventEntry *entry);
void TileEvent_InitKind11(TileEventEntry *entry, const TileChangesTile *tile);
void TileEvent_StepKind10(TileEventEntry *entry);
void TileEvent_InitKind10(TileEventEntry *entry, const TileChangesTile *tile);
void TileEvent_StepKind9(TileEventEntry *entry);
void TileEvent_InitKind9(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from, u16 id);
void TileEvent_StepKind8(TileEventEntry *entry);
void TileEvent_InitKind8(TileEventEntry *entry, const TileChangesTile *tile, int angle);
void TileEvent_StepKind7(TileEventEntry *entry);
void TileEvent_InitKind7(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from);
void TileEvent_StepKind6(TileEventEntry *entry);
void TileEvent_InitKind6(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from);
void TileEvent_StepKind5(TileEventEntry *entry);
void TileEvent_InitKind5(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from, int extra);
void TileEvent_StepKind4(TileEventEntry *entry);
void TileEvent_InitKind4(TileEventEntry *entry, const TileChangesTile *tile);
void TileEvent_StepKind3(TileEventEntry *entry);
void TileEvent_InitKind3(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map);
void TileEvent_InitKind2(TileEventEntry *entry, const TileChangesTile *tile);
void TileEvent_StepKind1(TileEventEntry *entry);
void TileEvent_InitKind1(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map, int extra);
void TileEvent_StepKind0(TileEventEntry *entry);
void TileEvent_InitKind0(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from);
void TileEvent_Clear(TileEventEntry *entry);
void TileEvent_End(TileEventEntry *entry);
void TileEvent_Begin(TileEventEntry *entry, int player, const int *tile, const int *point, int kind, u16 id,
                     struct AcreMap *map, s16 angle, int extra);
void TileEvent_LetGoChange(TileEventEntry *entry);

void TileEvent_SetTownItem(int x, int z, u16 item, int mark);
void TileEvent_StartFromChanges(const TileChangesTile *tile);

TileEventProcess *TileEvent_NewProcess(void);
void *TileEvent_DestroyEntries(TileEventEntry *entries);
TileEventEntry *TileEvent_DestructEntry(TileEventEntry *entry);
TileEventEntry *TileEvent_ConstructEntry(TileEventEntry *entry);

#endif
