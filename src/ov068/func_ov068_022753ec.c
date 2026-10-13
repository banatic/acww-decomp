/* func_ov068_022753ec @ 0x022753ec, 0x320 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    Vec pos; // 0x5c
    u8 pad_68[0x8e - 0x68];
    short unk_8E; // 0x8e
    u8 pad_90[0x350 - 0x90];
    u8 unk_350[0x508 - 0x350]; // 0x350
    u8 unk_508;                // 0x508
    u8 pad_509[0x564 - 0x509];
    u8 unk_564[0x618 - 0x564]; // 0x564
    u8 unk_618[0x898 - 0x618]; // 0x618
    int unk_898;               // 0x898
    u8 pad_89C[0xa52 - 0x89c];
    u16 unk_A52; // 0xa52
    u8 pad_A54[0xa58 - 0xa54];
    u8 unk_A58; // 0xa58
    u8 unk_A59; // 0xa59
    u8 pad_A5A[0xa5c - 0xa5a];
    u8 unk_A5C; // 0xa5c
    u8 pad_A5D;
    short unk_A5E; // 0xa5e
    u8 unk_A60;    // 0xa60
    u8 pad_A61;
    short unk_A62; // 0xa62
    Vec unk_A64;   // 0xa64
    Vec unk_A70;   // 0xa70
} UnkStruct_022753ec;

extern int data_020ca0ec;
extern u16 data_020c80f8;

extern Vec *func_02095794(int);
extern int func_02014868(void *);
extern void func_0203e0a8(UnkStruct_022753ec *, int);
extern int func_02030818(Vec *);
extern int func_020ea990(void *, void *);
extern int func_020eaa2c(void *, void *);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_ov068_02276458(UnkStruct_022753ec *);
extern int func_ov004_0221e1e0(Vec *, Vec *, int);
extern int func_020644cc(int);
extern int func_0201c194(UnkStruct_022753ec *, Vec *);
extern void func_0201b044(void *, Vec *);

void func_ov068_022753ec(UnkStruct_022753ec *a)
{
    Vec v;
    Vec loc;
    Vec *e;
    int d;
    u8 t;
    short cur;

    e = func_02095794(4);
    if (a->unk_898 == 6 && func_02014868(a->unk_618) == 0) {
        if (a->unk_A5E == 0 || a->unk_A5C == 0) {
            t = a->unk_A60;
            if (t == 0) {
                func_0203e0a8(a, 0);
                a->unk_A58 = 1;
                return;
            }
            if (t != 0) {
                a->unk_A60 = t - 1;
            }
        }
        if (a->unk_A5E > 0) {
            a->unk_A5E--;
        }
    }

    if (a->unk_898 == 6 && e != 0) {
        v.x = e->x;
        v.y = e->y;
        v.z = e->z;
        if (func_02030818(&v) != 0) {
            func_0203e0a8(a, 0);
            a->unk_A59 = 1;
            return;
        }
    }

    d = data_020ca0ec;
    if (e != 0) {
        d = func_020ea990(e, &a->pos);
    }

    if (a->unk_508 != 0 || (a->unk_898 != 6 && d < 0x2334)) {
        if (func_02019e00(a->unk_564) == 1 || a->unk_898 == 3) {
            if (func_02019c6c(a->unk_564, 2, data_020c80f8) != 0) {
                func_ov068_02276458(a);
                return;
            }
        }
    }

    if (func_02019e00(a->unk_564) == 0) {
        if (a->unk_A52 != 0) {
            a->unk_A52--;
        }
        if (a->unk_A52 == 0) {
            a->unk_A62 = (short) func_ov004_0221e1e0(&a->unk_A70, &a->pos, a->unk_8E);
            a->unk_A64.x = a->unk_A70.x;
            a->unk_A64.y = a->unk_A70.y;
            a->unk_A64.z = a->unk_A70.z;
            cur = a->unk_A62;
            if (cur != a->unk_8E) {
                if (func_02019d0c(a->unk_564, 3, 1, 0, 0, 0, cur, 0, 0, data_020c80f8, 0) != 0) {
                    a->unk_A52 = (u16) (func_020644cc(0x46) + 0x14);
                }
                return;
            }
            if (func_02019d0c(a->unk_564, 1, 1, a->unk_A70.x, a->unk_A70.z, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
                a->unk_A52 = (u16) (func_020644cc(0x50) + 0x14);
            }
            return;
        }
        if (func_02019de8(a->unk_564) != 0) {
            func_02019c6c(a->unk_564, 1, data_020c80f8);
        }
        return;
    }

    if (func_02019e00(a->unk_564) == 3) {
        if (func_02019de8(a->unk_564) == 0) {
            return;
        }
        func_02019d0c(a->unk_564, 1, 1, a->unk_A70.x, a->unk_A70.z, 0, 0, 0, 0, data_020c80f8, 0);
        return;
    }

    if (func_02019e00(a->unk_564) != 1) {
        return;
    }

    switch (func_0201c194(a, &loc)) {
        case 1:
            if (func_02019c6c(a->unk_564, 1, data_020c80f8) != 0) {
                func_ov068_02276458(a);
            }
            return;
        case 2:
            a->unk_A64.x = loc.x;
            a->unk_A64.y = loc.y;
            a->unk_A64.z = loc.z;
            func_0201b044(a->unk_350, &a->unk_A64);
            return;
        default:
            if (func_020eaa2c(&a->unk_A64, &a->unk_A70) != 0) {
                a->unk_A64.x = a->unk_A70.x;
                a->unk_A64.y = a->unk_A70.y;
                a->unk_A64.z = a->unk_A70.z;
                func_0201b044(a->unk_350, &a->unk_A70);
                return;
            }
            if (func_020ea990(&a->unk_A70, &a->pos) < 0x200) {
                func_02019c6c(a->unk_564, 1, data_020c80f8);
                func_ov068_02276458(a);
            }
            return;
    }
}
