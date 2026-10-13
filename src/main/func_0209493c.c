/* func_0209493c @ 0x0209493c, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};

struct Node {
    struct Node *next;
    u8 pad_04[4];
    int x, y, z;
    u8 pad_14[0x10];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x10];
    int dx, dy, dz;
};

struct Head {
    u8 pad_00[8];
    struct Node *list;
};

struct Iter {
    u8 pad_00[0x30];
    int flag;
    u8 pad_34[0x10];
};

extern struct Vec data_021fbee8;

extern void func_02034270(struct Iter *, struct Vec *, int, int);
extern int func_0203419c(struct Iter *);
extern void func_02094cf8(int, int, struct Vec *, int, int, int);
extern void func_0203423c(struct Iter *);

int func_0209493c(struct Head *h, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    struct Node *n;
    int ret;
    struct Vec v;
    struct Iter it;
    int t;

    n = h->list;
    v.x = data_021fbee8.x;
    v.y = data_021fbee8.y;
    v.z = data_021fbee8.z;
    ret = 0;
    if (n) {
        ret = 1;
        while (n) {
            v.x = n->x + n->dx;
            v.y = n->y + n->dy;
            v.z = n->z + n->dz;
            func_02034270(&it, &v, 0, 0);
            if (it.flag) {
                t = func_0203419c(&it);
                if (v.y <= t) {
                    v.y = t;
                    if (a1 != -1) {
                        func_02094cf8(a1, 0x64, &v, 0, 0, a2);
                    }
                    if (a3 != -1) {
                        func_02094cf8(a3, 0x64, &v, 0, 0, a4);
                    }
                    n->unk_26 = n->unk_24;
                }
            } else {
                if (v.y <= 0) {
                    if (a5 != -1) {
                        v.y = 0;
                        func_02094cf8(a5, 0x64, &v, 0, 0, a6);
                    }
                    if (a7 != -1) {
                        v.y = 0;
                        func_02094cf8(a7, 0x64, &v, 0, 0, a8);
                    }
                    n->unk_26 = n->unk_24;
                }
            }
            n = n->next;
            func_0203423c(&it);
        }
    }
    return ret;
}
