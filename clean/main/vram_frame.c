/* The game's texture and palette VRAM allocators (vram_frame.h). */
#include "vram_frame.h"

#include "clean.h"

/* The banks GX_GetBankForTex reports: A, B and C, or A to D. */
#define VRAM_FRAME_BANKS_ABC 7
#define VRAM_FRAME_BANKS_ABCD 15
/* A 4x4 texture's texels in the high pair end here (the indexes for slot 3 do not exist). */
#define VRAM_FRAME_HIGH_4X4_END 0x60000
/* What a failed 4x4 allocation gives. */
#define VRAM_FRAME_FAILED_INDEXES 0x20000

extern void OS_Terminate(void);
extern void NNS_GfdInitFrmTexVramManager(int slots, int use_as_default);
extern void NNS_GfdInitFrmPlttVramManager(int size, int use_as_default);
extern int GX_GetSizeOfTexPltt(void);
extern int GX_GetBankForTex(void);
/* NitroSystem's default allocators, which the game replaces with its own. */
extern u32 NNS_GfdDefaultFuncAllocTexVram;
extern u32 NNS_GfdDefaultFuncAllocPlttVram;
/* The game's allocators, as handed to NitroSystem. */
extern u32 func_020b95b4(u32 size, u32 is_4x4);
extern u32 func_020b958c(u32 size);

extern u32 data_021f6c70; /* palette VRAM taken */
extern u32 data_021f6c94; /* palette VRAM's size */

/* The four areas of texture VRAM (vram_frame.h): bottoms and tops. */
extern u32 data_021f6c90; /* low texels */
extern u32 data_021f6c80;
extern u32 data_021f6c8c; /* low indexes */
extern u32 data_021f6c7c;
extern u32 data_021f6c84; /* high texels */
extern u32 data_021f6c74;
extern u32 data_021f6c88; /* high indexes */
extern u32 data_021f6c78;

/* func_020b947c: NitroSystem's frame VRAM managers set up (4 texture slots, 32 KB of palettes)
 * with the game's allocators in place of their defaults; nothing taken; the texture areas laid
 * out for the banks given to textures. Banks other than A-C or A-D stop the game. */
void VramFrame_Init(void)
{
    NNS_GfdInitFrmTexVramManager(4, 1);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    NNS_GfdDefaultFuncAllocTexVram = (u32) (uintptr_t) func_020b95b4;
    NNS_GfdDefaultFuncAllocPlttVram = (u32) (uintptr_t) func_020b958c;

    data_021f6c70 = 0;
    data_021f6c94 = (u32) GX_GetSizeOfTexPltt();
    data_021f6c84 = 0;
    data_021f6c88 = 0;
    data_021f6c8c = 0;
    data_021f6c90 = 0;
    data_021f6c74 = 0;
    data_021f6c78 = 0;
    data_021f6c7c = 0;
    data_021f6c80 = 0;

    int banks = GX_GetBankForTex();
    if (banks == VRAM_FRAME_BANKS_ABC || banks == VRAM_FRAME_BANKS_ABCD) {
        data_021f6c90 = 0x00000;
        data_021f6c8c = 0x20000;
        data_021f6c88 = 0x30000;
        data_021f6c84 = 0x40000;
        data_021f6c80 = 0x20000;
        data_021f6c7c = 0x30000;
        data_021f6c78 = 0x40000;
        data_021f6c74 = banks == VRAM_FRAME_BANKS_ABCD ? 0x80000 : 0x60000;
    } else {
        OS_Terminate();
    }
}
CLEAN_AS(func_020b947c, VramFrame_Init)

/* func_020b9478: called when VRAM runs out, before the game stops; does nothing. */
void VramFrame_ReportFull(void) {}
CLEAN_AS(func_020b9478, VramFrame_ReportFull)

/* func_020b958c (NitroSystem's palette allocator): `size` rounded up to 8 bytes, taken; the
 * key (the size / 8 in the top half, the address / 8 in the bottom one). */
VramKey VramFrame_AllocPltt(u32 size)
{
    size = (size + 7) & ~7u;
    u32 address = VramFrame_TakePltt(size);

    return ((size >> 3) << 16) | ((address >> 3) & 0xffff);
}
CLEAN_AS(func_020b958c, VramFrame_AllocPltt)

/* func_020b95b4 (NitroSystem's texture allocator): `size` bytes taken, as a 4x4 texture when
 * `is_4x4` (only the texels' address goes in the key); the key (bit 31 for 4x4, the size / 16
 * from bit 16, the address / 8 in the bottom half).
 * QUIRK: `is_4x4` is shifted to bit 31 as it is, and the size / 16 is not masked: a size of
 * 1 MB or more runs into bit 31. */
VramKey VramFrame_AllocTex(u32 size, u32 is_4x4)
{
    u32 address;
    u32 indexes;

    if (is_4x4) {
        VramFrame_TakeTex4x4(&address, &indexes, size);
    } else {
        VramFrame_TakeTex(&address, size);
    }
    return (is_4x4 << 31) | ((size >> 4) << 16) | ((address >> 3) & 0xffff);
}
CLEAN_AS(func_020b95b4, VramFrame_AllocTex)

/* func_020b95f4: `size` bytes (rounded up to 16) of palette VRAM taken from the bottom up; their
 * address. When they do not fit the game stops (and 0 is returned).
 * QUIRK: the rounded size keeps only its low 16 bits, and an allocation may not end exactly at
 * the end of palette VRAM (its end must stay under the size), so the last 16 bytes stay
 * unused. */
u32 VramFrame_TakePltt(u32 size)
{
    u32 address = data_021f6c70;
    u32 end = address + ((size + 0xf) & 0xfff0);

    data_021f6c70 = end;
    if (end >= data_021f6c94) {
        data_021f6c70 = address;
        OS_Terminate();
        return 0;
    }
    return address;
}
CLEAN_AS(func_020b95f4, VramFrame_TakePltt)

/* From the top of a pair of areas (texels and indexes) whose free bytes are `texels_free` and
 * `indexes_free`: the indexes' top when both fit and what the indexes would keep, doubled, is
 * more than what the texels would; else the texels' top when they fit; else the indexes' top
 * when they fit. Returns 0 when neither fits. */
static int take_from_top(u32 *address, u32 size, u32 *texels_top, u32 texels_free, u32 *indexes_top, u32 indexes_free)
{
    u32 *top;

    if (texels_free >= size) {
        top = indexes_free >= size && (indexes_free - size) * 2 > texels_free - size ? indexes_top : texels_top;
    } else if (indexes_free >= size) {
        top = indexes_top;
    } else {
        return 0;
    }
    *address = *top - size;
    *top = *address;
    return 1;
}

/* func_020b962c: `size` bytes for a texture that is not 4x4, from the tops of the high pair,
 * else of the low pair (vram_frame.h); when neither has room VRAM is reported full, the game
 * stops and the address is 0. */
void VramFrame_TakeTex(u32 *address, u32 size)
{
    if (take_from_top(address, size, &data_021f6c74, data_021f6c74 - data_021f6c84, &data_021f6c78,
                      data_021f6c78 - data_021f6c88)) {
        return;
    }
    if (take_from_top(address, size, &data_021f6c80, data_021f6c80 - data_021f6c90, &data_021f6c7c,
                      data_021f6c7c - data_021f6c8c)) {
        return;
    }
    VramFrame_ReportFull();
    OS_Terminate();
    *address = 0;
}
CLEAN_AS(func_020b962c, VramFrame_TakeTex)

/* func_020b96f8: a 4x4 texture of `size` bytes of texels (and half as many of indexes) from the
 * bottoms of the low pair, else of the high pair below 0x60000; when neither has room VRAM is
 * reported full, the game stops and the addresses are 0 and 0x20000. */
void VramFrame_TakeTex4x4(u32 *texels, u32 *indexes, u32 size)
{
    u32 index_size = size >> 1;

    if (data_021f6c90 + size <= data_021f6c80 && data_021f6c8c + index_size <= data_021f6c7c) {
        *texels = data_021f6c90;
        *indexes = data_021f6c8c;
        data_021f6c90 += size;
        data_021f6c8c += index_size;
    } else if (data_021f6c84 + size <= data_021f6c74 && data_021f6c84 + size <= VRAM_FRAME_HIGH_4X4_END &&
               data_021f6c88 + index_size <= data_021f6c78) {
        *texels = data_021f6c84;
        *indexes = data_021f6c88;
        data_021f6c84 += size;
        data_021f6c88 += index_size;
    } else {
        VramFrame_ReportFull();
        OS_Terminate();
        *texels = 0;
        *indexes = VRAM_FRAME_FAILED_INDEXES;
    }
}
CLEAN_AS(func_020b96f8, VramFrame_TakeTex4x4)
