/* The night sky's twinkling ("menu/star"): the palettes of the sky's background (data_021f7280)
 * changed lane by lane at random times.
 *
 * The object builds on a palette transfer object (func_020b9cfc constructs it, func_020b9ccc
 * takes it off its list, func_020b9b14 asks for a transfer). It holds the sky's four palettes
 * as shown and five versions of them loaded from files: "a_bg.bpl" (phase 0, the resting
 * look) and "b_bg1.bpl" to "b_bg4.bpl" (phases 1-4). Each of the four palettes (a lane) waits
 * a number of frames, then switches between rest and a random twinkle phase. */
#ifndef CLEAN_MAIN_STAR_PALETTE_H
#define CLEAN_MAIN_STAR_PALETTE_H

#include "types.h"

#define STAR_PALETTE_LANES 4
#define STAR_PALETTE_PHASES 5
#define STAR_PALETTE_LANE_SIZE 0x20
#define STAR_PALETTE_SIZE (STAR_PALETTE_LANES * STAR_PALETTE_LANE_SIZE)

typedef struct StarPalette {
    u8 transfer[0x24];                                 /* 0x000: the palette transfer object */
    u8 shown[STAR_PALETTE_SIZE];                       /* 0x024 */
    u8 phases[STAR_PALETTE_PHASES][STAR_PALETTE_SIZE]; /* 0x0a4 */
    u8 wait[STAR_PALETTE_LANES];                       /* 0x324: frames until the lane changes */
    u8 phase[STAR_PALETTE_LANES];                      /* 0x328: the lane's phase */
    u8 layer;                                          /* 0x32c: the background layer */
} StarPalette;

void StarPalette_Cancel(StarPalette *palette);
void StarPalette_Start(StarPalette *palette, int layer);
void StarPalette_Update(StarPalette *palette);
void StarPalette_Destruct(void *palette);
StarPalette *StarPalette_Construct(StarPalette *palette);

#endif
