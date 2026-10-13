/* func_020fa498 @ 0x020fa498, 0xcc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    unsigned int type : 4;
    unsigned int : 13;
    unsigned int cached : 1;
    unsigned int cacheIndex : 8;
    unsigned int : 6;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
} UnkStruct_020fa498;

typedef struct {
    UnkStruct_020fa498 *p;
    u32 result;
    char pad[0xc];
} Entry;

typedef struct {
    char pad[0x20];
    Entry *entries;
    char pad_24[2];
    u16 count;
} UnkStruct_020fa498_2;

extern void GX_BeginLoadTex(void);
extern void GX_EndLoadTex(void);
extern void GX_LoadTex(const void *pSrc, u32 destSlotAddr, u32 szByte);

int func_020fa498(UnkStruct_020fa498_2 *self, u32 (*callback)(u32, int))
{
    int i;
    u32 zero = 0;
    u32 one = 1;

    GX_BeginLoadTex();

    for (i = 0; i < self->count; i++) {
        Entry *e = &self->entries[i];
        UnkStruct_020fa498 *p = e->p;

        if (p->cached) {
            u32 idx = p->cacheIndex;
            e->result = self->entries[idx].result;
        } else {
            u32 arg = (p->type == 5) ? one : zero;
            u32 dest = callback(p->unk_08, arg);
            GX_LoadTex((char *) e->p + 0x20, dest, p->unk_08);
            e->result = dest;
        }
    }

    GX_EndLoadTex();
    return 1;
}
