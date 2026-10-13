/* func_0201354c @ 0x0201354c, 0x1ec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int x, y, z;
} UnkStruct_0201354c;
typedef struct {
    u32 x, y;
} UnkStruct_0201354c_2;
typedef struct {
    u32 pad_00[3];
    u32 c;
    u32 d;
} UnkStruct_0201354c_3;

extern UnkStruct_0201354c_3 *data_021c80bc;
extern UnkStruct_0201354c_2 data_021c172c;
extern UnkStruct_0201354c_2 data_021c173c;
extern UnkStruct_0201354c_2 data_021c1734;
extern UnkStruct_0201354c_2 data_021c1744;

extern void func_0204f818(u32 *a, u32 *b, UnkStruct_0201354c *p);
extern int func_0204ed30(UnkStruct_0201354c_3 *o, UnkStruct_0201354c *p);
extern int func_0204f658(UnkStruct_0201354c_3 *o, int a, int b);
extern int func_020137ec(void *p0, UnkStruct_0201354c *arr, u32 *lim, UnkStruct_0201354c_2 *step, int n,
                         UnkStruct_0201354c_2 *lm, int f, UnkStruct_0201354c_3 *o);
extern int func_020ea990(UnkStruct_0201354c *a, UnkStruct_0201354c *b);
extern unsigned int func_02013738(void *p0, UnkStruct_0201354c *out, UnkStruct_0201354c_3 *o);

int func_0201354c(void *p0, u32 *p1, UnkStruct_0201354c *p2)
{
    int ret;
    int t;
    int v;
    int w;
    int off;
    u32 s2c;
    u32 s30;
    UnkStruct_0201354c_2 lim;
    UnkStruct_0201354c out;
    UnkStruct_0201354c arr[4];
    UnkStruct_0201354c_3 *obj;
    unsigned char mask;
    int i;
    int best;
    int d;
    u32 u;
    u32 *q;

    obj = data_021c80bc;
    out.x = p2->x;
    out.y = p2->y;
    out.z = p2->z;
    mask = 0;
    s2c = 0;
    s30 = 0;
    lim.x = 0;
    lim.y = 0;
    ret = 4;
    if (obj == 0) {
        return 4;
    }
    func_0204f818(&s2c, &s30, p2);
    q = (u32 *) ((int) obj + 0xc);
    lim.x = q[0];
    lim.y = q[1];
    if (func_0204ed30(obj, p2) != 0) {
        return 4;
    }
    i = 0;
    do {
        UnkStruct_0201354c *v = &arr[i];
        v->x = p2->x;
        v->y = p2->y;
        v->z = p2->z;
        i++;
    } while (i < 4);
    func_0204f818(&s2c, &s30, p2);
    if ((func_0204f658(obj, p2->x >> 17, p2->z >> 17) & 0x7f000) != 0) {
        d = 1;
    } else {
        d = 0;
    }
    t = s2c;
    t = t & 0xfff0;
    u = s30 & 0xfff0;
    v = t;
    v = v + 0x10;
    w = u;
    w = w + 0x10;
    if (func_020137ec(p0, arr, &s2c, &data_021c172c, s30 - u, &lim, d, obj) != 0) {
        mask |= 1;
    }
    if (func_020137ec(p0, &arr[2], &s2c, &data_021c173c, w - s30, &lim, d, obj) != 0) {
        mask |= 4;
    }
    if (func_020137ec(p0, &arr[1], &s2c, &data_021c1734, s2c - t, &lim, d, obj) != 0) {
        mask |= 2;
    }
    if (func_020137ec(p0, &arr[3], &s2c, &data_021c1744, v - s2c, &lim, d, obj) != 0) {
        mask |= 8;
    }
    if (mask != 0) {
        best = 0xfffff000;
        i = 0;
        do {
            off = i;
            off = 0xc * off;
            d = func_020ea990(p2, &arr[i]);
            if (((mask >> i) & 1) != 0) {
                if (best < 0 || d < best) {
                    out.x = *(int *) ((char *) arr + off);
                    out.y = ((UnkStruct_0201354c *) ((char *) arr + off))->y;
                    out.z = ((UnkStruct_0201354c *) ((char *) arr + off))->z;
                    best = d;
                    ret = i;
                }
            }
            i++;
        } while (i < 4);
    } else {
        i = func_02013738(p0, &out, obj);
        if ((unsigned int) i < 4) {
            ret = i;
        }
    }
    func_0204f818(p1, p1 + 1, &out);
    return ret;
}
