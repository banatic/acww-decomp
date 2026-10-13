/* func_02058528 @ 0x02058528, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad1[0x8e - 0x60];
    s16 unk_8E;
} UnkStruct_02058528;

typedef struct {
    u8 pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    Vec pos;
    u8 pad1[0x90 - 0x78];
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xcc - 0x9c];
    UnkStruct_02058528 *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
} UnkStruct_02058528_2;

extern int data_021c9358;
extern Vec data_021c93b4;
extern int data_021c93a8;
extern void func_020012dc(void);
extern void __register_global_object(void *, void *, void *);
extern int func_020b65c4(void);
extern void func_020ea6e0(Vec *, int);
extern void VEC_Add(Vec *, void *, Vec *);
extern void func_0204f7e0(Vec *, Vec *);
extern int _s32_div_f(int, int);
extern void func_02059674(UnkStruct_02058528_2 *, int);

void func_02058528(UnkStruct_02058528_2 *p)
{
    Vec v;
    int a, b, c;

    if (!(data_021c9358 & 1)) {
        data_021c93b4.x = 0x10000;
        data_021c93b4.y = 0;
        data_021c93b4.z = 0x17000;
        __register_global_object(&data_021c93b4, (void *) &func_020012dc, &data_021c93a8);
        data_021c9358 |= 1;
    }
    v.x = 0;
    v.y = 0;
    v.z = 0x2000;
    if (func_020b65c4() == 0x10) {
        p->pos.x = data_021c93b4.x;
        p->pos.y = data_021c93b4.y;
        p->pos.z = data_021c93b4.z;
    } else {
        func_020ea6e0(&v, p->unk_CC->unk_8E);
        VEC_Add(&v, &p->unk_CC->unk_5C, &v);
        func_0204f7e0(&p->pos, &v);
    }
    p->pos.y += 0x1000;
    c = _s32_div_f(p->pos.z - p->unk_68, 4);
    if (c < 0) {
        c = -c;
    }
    b = _s32_div_f(p->pos.y - p->unk_64, 4);
    if (b < 0) {
        b = -b;
    }
    a = _s32_div_f(p->pos.x - p->unk_60, 4);
    if (a < 0) {
        a = -a;
    }
    p->unk_90 = a;
    p->unk_94 = b;
    p->unk_98 = c;
    p->unk_D6 = 0;
    func_02059674(p, 1);
}
