/* The particle effects a tile's map object gives off when it is struck or brushed against
 * (func_02090c2c starts an effect by number at a place, with a word holding the function that
 * sets each new emitter up).
 *
 * A code of the families (MapItem_InFamilies) starts two effects at the tile's centre, chosen
 * by the code's category (func_02049ec4), unless the mode is 1 (only the first then). Their
 * set-up functions read what the effects are for from TileEffectsSource (data_021c77a0): the
 * place, the code's category and stage, and the mode; they tint the emitter's colour by the
 * sky's light and, in mode 2, turn its axis by the source's angle.
 *
 * TileEffects_Strike (mode 1) and TileEffects_Brush (mode 1 seven times in eight, else 0) start
 * them for the code on a tile of the town; mode 0 also sends the tile on to the other systems
 * (LinkedMapItems_Set with no item). */
#ifndef CLEAN_MAIN_TILE_EFFECTS_H
#define CLEAN_MAIN_TILE_EFFECTS_H

#include "autoload_2/particle.h"
#include "autoload_2/vector.h"
#include "types.h"

/* TileEffectsSource.mode */
#define TILE_EFFECTS_MODE_BOTH 0  /* both effects; the tile sent on */
#define TILE_EFFECTS_MODE_FIRST 1 /* the first effect only, given off every other frame */
#define TILE_EFFECTS_MODE_TURNED 2

/* data_021c77a0 (data_021c779c + 4): what the effects being started are for. */
typedef struct TileEffectsSource {
    u32 mode;      /* 0x00: TILE_EFFECTS_MODE_* */
    u8 category;   /* 0x04: func_02049ec4's category of the code, 0-6 */
    u8 stage;      /* 0x05: the code's place in its line (func_02049d78), 0 for 0x6e-0xa5 */
    u8 families;   /* 0x06: the code is one of 0x6e-0xa5 (families B and C and after) */
    u8 unk_07;     /* 0x07 */
    Vec3 position; /* 0x08: the tile's centre */
    s16 angle;     /* 0x14: what the axis turns by in mode 2 */
} TileEffectsSource;

/* The tile of a map, as the callers hand it. */
typedef struct TileEffectsTile {
    int x;
    int z;
} TileEffectsTile;

void TileEffects_Strike(const TileEffectsTile *tile);
void TileEffects_Brush(const TileEffectsTile *tile);
void TileEffects_StartAt(const TileEffectsTile *tile, int mode);
void TileEffects_StartFor(u16 *code, const TileEffectsTile *tile, int mode);
void TileEffects_StartE2(const TileEffectsTile *tile);
void TileEffects_Start1f(const u16 *code, const TileEffectsTile *tile);
void TileEffects_StartTurned(u16 *code, const TileEffectsTile *tile, int angle, int mode);
void TileEffects_Start(u16 *code, const TileEffectsTile *tile, int angle, int mode);
void TileEffects_SetUpSecond(ParticleEmitter *emitter);
void TileEffects_SetUpFirst(ParticleEmitter *emitter);
void TileEffects_SetSource(TileEffectsSource *source, int mode, u8 category, u8 stage, u8 families, const Vec3 *position,
                           s16 angle);

#endif
