/* villager_move_record: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209a6fc @ 0x0209a6fc, 0x12 bytes, Thumb
 * func_0209a6ec @ 0x0209a6ec, 0x10 bytes, Thumb
 * func_0209a69c @ 0x0209a69c, 0x50 bytes, Thumb
 * func_0209a67c @ 0x0209a67c, 0x20 bytes, Thumb
 * func_0209a664 @ 0x0209a664, 0x18 bytes, Thumb
 * func_0209a654 @ 0x0209a654, 0x10 bytes, Thumb
 * func_0209a610 @ 0x0209a610, 0x42 bytes, Thumb
 * func_0209a4b8 @ 0x0209a4b8, 0x158 bytes, Thumb
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

extern int func_020951bc(void *p);
extern int memcmp(void *dst, void *src, unsigned int n);
extern int func_0209518c(void *a, void *b);
extern void func_0209525c(int, int);
extern void func_0209df64(void *p);
extern int func_0209dcdc(const void *p, const void *q);
extern void MI_CpuFill8(void *d, int c, int n);

void *func_0209a6fc(void *base, unsigned int idx)
{
    if (idx < 5) {
        return (char *) base + 0x1c + idx * 0x1e;
    } else {
        return 0;
    }
}

int func_0209a6ec(void *p)
{
    return (int) func_0209a6fc(p, (unsigned char) (*((unsigned char *) p + 0xBA)));
}

int func_0209a69c(char *a, char *b)
{
    char *p;
    int i;

    if (func_020951bc(b) != 0) {
        p = a + 0x1c;
        for (i = 0; i < 5; i++) {
            if (*(unsigned short *) b == *(unsigned short *) p && memcmp(b + 2, p + 2, 12) == 0 && func_0209518c(b, p) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

int func_0209a67c(void *argument0)
{
    int forwarded_value;

    int result;

    if ((forwarded_value = (int) func_0209a6ec((void *) argument0)) != 0 && func_020951bc((void *) forwarded_value) != 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}

void func_0209a664(int a, int b)
{
    int ret;
    ret = func_0209a6ec((void *) a);
    if (ret) {
        func_0209525c(ret, b);
    }
}

int func_0209a654(unsigned char *ptr)
{
    if (ptr[0xBA] == 5) {
        return 1;
    } else {
        return 0;
    }
}

int func_0209a610(unsigned char *a, unsigned char *b)
{
    unsigned int local;
    unsigned char *p = b;

    if (p == 0) {
        func_0209df64(&local);
        p = (unsigned char *) &local;
    }

    if (func_0209a654((unsigned char *) a) != 0) {
        int res = func_0209dcdc(p, a + 0xb6);
        if (res >= 0 && res < 3) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

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

    if (func_0209a654((unsigned char *) self) == 0) {
        goto zero;
    }
    mask = 0;
    MI_CpuFill8(cnt, 0, 5);
    for (i = 0; i < 5; i++) {
        if (((mask >> i) & 1) != 0) {
            continue;
        }
        ei = &self->ents[i];
        if (func_020951bc((void *) ei) == 0) {
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
                if (memcmp((void *) ((u8 *) ei + 2), (void *) ((u8 *) &self->ents[j] + 2), 0xc) == 0) {
                    f2 = 1;
                }
            }
            if (f2 != 0) {
                if (func_0209518c((void *) ei, (void *) (&self->ents[j])) != 0) {
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
