/* func_0205817c @ 0x0205817c, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0205817c {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

typedef struct UnkStruct_0205817c_2 {
    u8 pad_00[0x60];
    u8 unk_60[0x18];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xa8 - 0x9c];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    u8 pad_B4[0xcc - 0xb4];
    struct UnkStruct_0205817c *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
} UnkStruct_0205817c_2;

extern int data_021c9364;
extern unsigned int data_021c9360;

extern void func_0205967c(UnkStruct_0205817c_2 *, void *);
extern int func_020e895c(void *, int, unsigned int);
extern void func_020ea6e0(void *, int);
extern void VEC_Add(void *, void *, void *);
extern void func_02059674(UnkStruct_0205817c_2 *, int);

void func_0205817c(UnkStruct_0205817c_2 *p)
{
    int tmp;
    int v;

    if (!(data_021c9364 & 1)) {
        data_021c9360 = 0x200;
        data_021c9364 |= 1;
    }
    tmp = p->unk_A8;
    if ((int) p->unk_D6 >= 8) {
        return;
    }

    func_0205967c(p, &p->unk_60[0]);
    func_020e895c(&tmp, 0, data_021c9360);
    v = tmp;
    p->unk_A8 = v;
    p->unk_AC = v;
    p->unk_B0 = v;
    func_020e895c(&p->unk_84, 0, p->unk_90);
    func_020e895c(&p->unk_88, 0, p->unk_94);
    func_020e895c(&p->unk_8C, 0, p->unk_98);
    if (p->unk_CC) {
        p->unk_78 = p->unk_84;
        p->unk_7C = p->unk_88;
        p->unk_80 = p->unk_8C;
        func_020ea6e0(&p->unk_78, p->unk_CC->unk_8E);
    }
    VEC_Add(&p->unk_60[0], &p->unk_78, &p->unk_60[0]);
    p->unk_D6++;
    if ((int) p->unk_D6 >= 8) {
        func_02059674(p, 0);
    }
}
