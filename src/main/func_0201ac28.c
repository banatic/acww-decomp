/* func_0201ac28 @ 0x0201ac28, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    u8 type; // 0x00
    u8 pad_01[0x5c - 1];
    int unk_5C; // 0x5c
    u8 unk_60;  // 0x60
    u8 pad_61[0x64 - 0x61];
    int unk_64; // 0x64
} UnkStruct_0201ac28;

typedef struct {
    u8 pad_00[0x5c];
    Vec3 pos; // 0x5c
    u8 pad_68[0x8e - 0x68];
    short unk_8E; // 0x8e
} Target;

extern int data_021fbee8[3];

extern void *func_02096190(int);
extern int func_020eaa2c(int *a, int *b);
extern int func_020ea9e4(Vec3 *a, Vec3 *b);
extern int func_0201ac10(void *p1, Vec3 *p2, Vec3 *p3, int p4);
extern int func_0201a814(void *s, int a);

int func_0201ac28(UnkStruct_0201ac28 *self, Target *other)
{
    volatile Vec3 local;
    Vec3 *vec = 0;

    local.x = 0;
    local.y = 0;
    local.z = 0;

    switch (self->type) {
        case 1: {
            void *p = func_02096190(self->unk_64);
            if (p != 0) {
                vec = (Vec3 *) ((char *) p + 0x5c);
            }
            break;
        }
        case 3:
            vec = (Vec3 *) ((char *) self + 8);
            break;
        default:
            break;
    }

    {
        int dist, threshold, tmp;

        if (vec == 0) {
            goto fail;
        }
        if (func_020eaa2c((int *) vec, data_021fbee8) == 0) {
            goto fail;
        }

        dist = func_020ea9e4(vec, &other->pos);
        threshold = self->unk_5C;
        if (threshold != 0) {
            if (dist < 0) {
                dist = -dist;
            }
            if (dist >= threshold) {
                goto fail;
            }
        }

        tmp = func_0201ac10(self, vec, &other->pos, other->unk_8E);
        if (self->unk_60 != 0 && func_0201a814(self, tmp) == 0) {
            goto fail;
        }

        return 1;
    }

fail:
    return 0;
}
