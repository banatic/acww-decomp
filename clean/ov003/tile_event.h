/* Overlay 3's tile events: a table of four entries (0xa0 bytes each) per player at
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

#endif
