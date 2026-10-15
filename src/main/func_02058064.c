/* func_02058064 @ 0x02058064, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps &self->unk_78 computed before self->unk_CC is loaded for the func_020ea6e0 call; the plain call loads the pointer first */

#include "types.h"

typedef struct PtrStruct {
    u8 pad_00[0x8e];
    s16 unk_8E;
} PtrStruct;
typedef struct UnkStruct_02058064 UnkStruct_02058064;
extern unsigned char data_020cbaf4;
extern unsigned char data_021c9340;
extern int data_021c9390[3];
extern void func_0205967c(UnkStruct_02058064 *self, int *p);
extern void func_020ea6e0(void *dst, short val);
extern void VEC_Add(void *a, void *b, void *c);
struct UnkStruct_02058064 {
    u8 pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7C;
    int unk_80;
    u8 pad_84[0x90 - 0x84];
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xcc - 0x9c];
    PtrStruct *unk_CC;
    u8 pad_D0[0xd4 - 0xd0];
    u8 unk_D4;
    u8 pad_D5;
    u16 unk_D6;
};
void func_02058064(UnkStruct_02058064 *self)
{
    int b;
    int c;
    int a;
    void *dst;
    PtrStruct *p;
    if (self->unk_D6 >= data_020cbaf4) {
        return;
    }
    self->unk_D6++;
    if (self->unk_D6 < data_020cbaf4) {
        return;
    }
    func_0205967c(self, &self->unk_6C);
    if (self->unk_CC != 0) {
        self->unk_78 = data_021c9390[0];
        self->unk_7C = data_021c9390[1];
        self->unk_80 = data_021c9390[2];
        dst = &self->unk_78;
        if (self && self) {
        }
        p = self->unk_CC;
        func_020ea6e0(dst, p->unk_8E);
    }
    VEC_Add(&self->unk_6C, &self->unk_78, &self->unk_6C);
    c = (self->unk_74 - self->unk_68) / ((int) data_021c9340);
    if (c < 0) {
        c = -c;
    }
    b = (self->unk_70 - self->unk_64) / ((int) data_021c9340);
    if (b < 0) {
        b = -b;
    }
    a = (self->unk_6C - self->unk_60) / ((int) data_021c9340);
    if (a < 0) {
        a = -a;
    }
    self->unk_90 = a;
    self->unk_94 = b;
    self->unk_98 = c;
    self->unk_D4 = 1;
}
