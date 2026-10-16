/* The game's own allocation of texture and palette VRAM, put in place of NitroSystem's default
 * allocators (VramFrame_Init); nothing is ever given back but all at once.
 *
 * Palettes are taken from the bottom of palette VRAM up, in 16-byte steps.
 *
 * Texture VRAM is four 128 KB slots (three when bank D is not texture VRAM). A 4x4 compressed
 * texture needs its texels in slot 0 or 2 and its palette indexes, half as many bytes, at the
 * matching place in slot 1 (slot 0's in its first half, slot 2's in its second). So four areas
 * are kept, each with a bottom and a top:
 *
 *   low texels      slot 0                  0x00000-0x20000
 *   low indexes     slot 1, first half      0x20000-0x30000
 *   high texels     slot 2 (and 3)          0x40000-0x60000 (0x80000 with bank D)
 *   high indexes    slot 1, second half     0x30000-0x40000
 *
 * 4x4 textures are taken from the bottoms of an area pair (the low pair first; in the high pair
 * no further than 0x60000), others from the tops (the high areas first). Running out stops the
 * game (OS_Terminate). */
#ifndef CLEAN_MAIN_VRAM_FRAME_H
#define CLEAN_MAIN_VRAM_FRAME_H

#include "types.h"
#include "vram_region.h" /* VramKey */

void VramFrame_Init(void);
void VramFrame_ReportFull(void);
VramKey VramFrame_AllocPltt(u32 size);
VramKey VramFrame_AllocTex(u32 size, u32 is_4x4);
u32 VramFrame_TakePltt(u32 size);
void VramFrame_TakeTex(u32 *address, u32 size);
void VramFrame_TakeTex4x4(u32 *texels, u32 *indexes, u32 size);

#endif
