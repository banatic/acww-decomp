/* The night sky's twinkling (star_palette.h). */
#include "star_palette.h"

#include "clean.h"
#include "main/display_layers.h"
#include "layer_load_task.h"
#include "main_random.h"
#include "rom_file.h"

static_assert(offsetof(StarPalette, shown) == 0x24, "star palette");
static_assert(offsetof(StarPalette, phases) == 0xa4, "star palette");
static_assert(offsetof(StarPalette, wait) == 0x324, "star palette");
static_assert(offsetof(StarPalette, phase) == 0x328, "star palette");
static_assert(offsetof(StarPalette, layer) == 0x32c, "star palette");

/* The five versions' files, phase by phase. */
extern const char *const data_020e4220[STAR_PALETTE_PHASES];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The palettes the sky's twinkling changes: 4 to 7 of the layer. */
#define STAR_PALETTE_FIRST 4
#define STAR_PALETTE_LAST 7

/* func_020b1774 */
void StarPalette_Cancel(StarPalette *palette)
{
    LayerTask_End((LayerTask *) palette);
}
CLEAN_AS(func_020b1774, StarPalette_Cancel)

/* func_020b177c: started on background layer `layer`: each lane resting, waiting 10-99 frames,
 * the five versions loaded and the resting one shown.
 * BUG: the lanes are set up five times over four lanes: the fifth sets lane 0's phase to 10-99
 * (as a wait) and clears the layer before it is set. A lane in no valid phase only goes back to
 * rest when its wait ends, so this only starts lane 0 one change late. */
void StarPalette_Start(StarPalette *palette, int layer)
{
    LayerTask_End((LayerTask *) palette);
    for (int lane = 0; lane < STAR_PALETTE_LANES; lane++) {
        palette->wait[lane] = (u8) (MainRandom_Below(90) + 10);
        palette->phase[lane] = 0;
    }
#ifndef BUGFIX
    palette->phase[0] = (u8) (MainRandom_Below(90) + 10);
    palette->layer = 0;
#endif
    palette->layer = (u8) layer;
    for (int phase = 0; phase < STAR_PALETTE_PHASES; phase++) {
        RomFile_Read(data_020e4220[phase], palette->phases[phase], STAR_PALETTE_SIZE);
    }
    MI_CpuCopy8(palette->phases[0], palette->shown, STAR_PALETTE_SIZE);
    DisplayLayer_LoadPalettes(palette->shown, (unsigned int) layer, STAR_PALETTE_FIRST, STAR_PALETTE_FIRST, STAR_PALETTE_LAST);
}
CLEAN_AS(func_020b177c, StarPalette_Start)

/* func_020b1800: the frame's step: each lane's wait counts down; when it has ended, a resting
 * lane twinkles in phase 1-4 for 5-19 frames and a twinkling one rests for 10-39, its palette
 * shown in the new phase. A transfer is asked for when any lane changed. */
void StarPalette_Update(StarPalette *palette)
{
    int changed = 0;
    LayerTask_End((LayerTask *) palette);
    for (int lane = 0; lane < STAR_PALETTE_LANES; lane++) {
        if (palette->wait[lane] != 0) {
            palette->wait[lane]--;
            continue;
        }
        if (palette->phase[lane] == 0) {
            palette->phase[lane] = (u8) (MainRandom_Below(4) + 1);
            palette->wait[lane] = (u8) (MainRandom_Below(15) + 5);
        } else {
            palette->phase[lane] = 0;
            palette->wait[lane] = (u8) (MainRandom_Below(30) + 10);
        }
        changed = 1;
        MI_CpuCopy8(&palette->phases[palette->phase[lane]][lane * STAR_PALETTE_LANE_SIZE],
                    &palette->shown[lane * STAR_PALETTE_LANE_SIZE], STAR_PALETTE_LANE_SIZE);
    }
    if (changed != 0) {
        LayerTask_QueuePalettes((LayerTask *) palette, (int) (uintptr_t) palette->shown, palette->layer, STAR_PALETTE_FIRST,
                                STAR_PALETTE_LAST);
    }
}
CLEAN_AS(func_020b1800, StarPalette_Update)

/* func_020b18a8: the destructor (registered for data_021f7280), which does nothing. */
void StarPalette_Destruct(void *palette)
{
    (void) palette;
}
CLEAN_AS(func_020b18a8, StarPalette_Destruct)

/* func_020b18ac: the constructor: the palette transfer object's. */
StarPalette *StarPalette_Construct(StarPalette *palette)
{
    LayerTask_Construct((LayerTask *) palette);
    return palette;
}
CLEAN_AS(func_020b18ac, StarPalette_Construct)
