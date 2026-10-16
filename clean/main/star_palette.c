/* The night sky's twinkling (star_palette.h). */
#include "star_palette.h"

#include "clean.h"
#include "main/display_layers.h"

static_assert(offsetof(StarPalette, shown) == 0x24, "star palette");
static_assert(offsetof(StarPalette, phases) == 0xa4, "star palette");
static_assert(offsetof(StarPalette, wait) == 0x324, "star palette");
static_assert(offsetof(StarPalette, phase) == 0x328, "star palette");
static_assert(offsetof(StarPalette, layer) == 0x32c, "star palette");

/* The five versions' files, phase by phase. */
extern const char *const data_020e4220[STAR_PALETTE_PHASES];

extern u32 func_020644cc(int range);                             /* a random number below `range` */
extern int func_02064af4(const char *path, void *dst, int size); /* a file read into `dst` */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The palette transfer object's: constructor, taking it off its list (and its vtable slot 1),
 * and a transfer of `data` to a background layer's palettes asked for. */
extern void *func_020b9cfc(void *transfer);
extern void func_020b9ccc(void *transfer);
extern int func_020b9b14(void *transfer, u8 *data, unsigned int layer, int first, u8 last);

/* The palettes the sky's twinkling changes: 4 to 7 of the layer. */
#define STAR_PALETTE_FIRST 4
#define STAR_PALETTE_LAST 7

/* func_020b1774 */
void StarPalette_Cancel(StarPalette *palette)
{
    func_020b9ccc(palette);
}
CLEAN_AS(func_020b1774, StarPalette_Cancel)

/* func_020b177c: started on background layer `layer`: each lane resting, waiting 10-99 frames,
 * the five versions loaded and the resting one shown.
 * BUG: the lanes are set up five times over four lanes: the fifth sets lane 0's phase to 10-99
 * (as a wait) and clears the layer before it is set. A lane in no valid phase only goes back to
 * rest when its wait ends, so this only starts lane 0 one change late. */
void StarPalette_Start(StarPalette *palette, int layer)
{
    func_020b9ccc(palette);
    for (int lane = 0; lane < STAR_PALETTE_LANES; lane++) {
        palette->wait[lane] = (u8) (func_020644cc(90) + 10);
        palette->phase[lane] = 0;
    }
#ifndef BUGFIX
    palette->phase[0] = (u8) (func_020644cc(90) + 10);
    palette->layer = 0;
#endif
    palette->layer = (u8) layer;
    for (int phase = 0; phase < STAR_PALETTE_PHASES; phase++) {
        func_02064af4(data_020e4220[phase], palette->phases[phase], STAR_PALETTE_SIZE);
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
    func_020b9ccc(palette);
    for (int lane = 0; lane < STAR_PALETTE_LANES; lane++) {
        if (palette->wait[lane] != 0) {
            palette->wait[lane]--;
            continue;
        }
        if (palette->phase[lane] == 0) {
            palette->phase[lane] = (u8) (func_020644cc(4) + 1);
            palette->wait[lane] = (u8) (func_020644cc(15) + 5);
        } else {
            palette->phase[lane] = 0;
            palette->wait[lane] = (u8) (func_020644cc(30) + 10);
        }
        changed = 1;
        MI_CpuCopy8(&palette->phases[palette->phase[lane]][lane * STAR_PALETTE_LANE_SIZE],
                    &palette->shown[lane * STAR_PALETTE_LANE_SIZE], STAR_PALETTE_LANE_SIZE);
    }
    if (changed != 0) {
        func_020b9b14(palette, palette->shown, palette->layer, STAR_PALETTE_FIRST, STAR_PALETTE_LAST);
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
    func_020b9cfc(palette);
    return palette;
}
CLEAN_AS(func_020b18ac, StarPalette_Construct)
