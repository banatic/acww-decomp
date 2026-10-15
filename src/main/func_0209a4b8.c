/* func_0209a4b8 @ 0x0209a4b8, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0209a4b8 {
    u16 id;
    u8 key[0xc];
    u8 rest[0x10];
} UnkStruct_0209a4b8;

typedef struct EntB {
    u8 pre[0x1c];
    u16 id;
} EntB;

typedef struct UnkStruct_0209a4b8_2 {
    u8 head[0x1c];
    UnkStruct_0209a4b8 ents[5];
} UnkStruct_0209a4b8_2;

extern int func_0209a654(void *self);
extern void MI_CpuFill8(void *d, int c, int n);
extern int func_020951bc(UnkStruct_0209a4b8 *e);
extern int memcmp(const void *a, const void *b, int n);
extern int func_0209518c(UnkStruct_0209a4b8 *a, UnkStruct_0209a4b8 *b);

UnkStruct_0209a4b8 *func_0209a4b8(UnkStruct_0209a4b8_2 *self)
{
    // DECLS
    u8 *p;
    int best;
    u8 grp;
    int f1;
    u32 bestIdx;
    u8 cnt[5];
    int f2;
    u8 mask;
    int i;
    int k;
    u8 *pc;
    EntB *ri;
    UnkStruct_0209a4b8 *ei;
    int j;
    // ENDDECLS

    if (func_0209a654(self) == 0) {
        goto zero;
    }
    mask = 0;
    MI_CpuFill8(cnt, 0, 5);
    for (i = 0; i < 5; i++) {
        if (((mask >> i) & 1) != 0) {
            continue;
        }
        ei = &self->ents[i];
        if (func_020951bc(ei) == 0) {
            continue;
        }
        grp = 0;
        mask |= (1 << i);
        pc = &cnt[i];
        cnt[i] = 1;
        j = i + 1;
        ri = (EntB *) ((u8 *) self + i * 0x1e);
        for (; j < 5; j++) {
            f1 = 0;
            f2 = 0;
            if (ri->id == ((EntB *) self)[j].id) {
                if (memcmp((u8 *) ei + 2, (u8 *) &self->ents[j] + 2, 0xc) == 0) {
                    f2 = 1;
                }
            }
            if (f2 != 0) {
                if (func_0209518c(ei, &self->ents[j]) != 0) {
                    f1 = 1;
                }
            }
            if (f1 != 0) {
                grp |= (1 << j);
                mask |= (1 << j);
                (*pc)++;
            }
        }
        if (grp == 0) {
            continue;
        }
        for (k = i + 1; k < 5; k++) {
            if (((grp >> k) & 1) != 0) {
                cnt[k] = *pc;
            }
        }
    }
    if (mask == 0) {
        goto zero;
    }
    p = cnt;
    best = 0;
    bestIdx = (u32) -1;
    for (j = 0; j < 5; j++) {
        int v = *p;
        if (v > best) {
            best = v;
            bestIdx = j;
        } else if (v != 0 && v == best) {
            bestIdx = j;
        }
        p++;
    }
    if (bestIdx >= 5) {
        goto zero;
    }
    return &self->ents[bestIdx];
zero:
    return 0;
}
