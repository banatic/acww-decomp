/* field_actor_27: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221292c @ 0x0221292c, 0x3c bytes, Thumb
 * func_ov003_02212884 @ 0x02212884, 0xa8 bytes, Thumb
 * func_ov003_02212878 @ 0x02212878, 0xa bytes, Thumb
 */

#include "types.h"

struct FuncOv003Struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C[0x32];
    unsigned char unk_8E[0x0a];
    int unk_98;
    unsigned char pad_9C[0x800 - 0x9c];
    int unk_800;
} SelfType;

struct UnkStruct_02212878 {
    int a;
    int b;
};

extern int func_02008258(void *, int);
extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);
extern int func_020113a4(int, int, int);
extern void func_0201107c(void *, int *);
extern int func_02073908(void *, int);
extern void func_ov003_02212a54(void *);
extern void func_02010f5c(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern void func_ov003_02212968(void *);
extern void func_ov003_02212a14(void *);
extern int func_0200f554(void *);
extern int func_020912d4(int, void *, void *, int);
extern void *data_020ccf94;

void func_ov003_0221292c(struct FuncOv003Struct *self)
{
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_020109fc(self, 0x4a, 3, 0);
    }
}

void func_ov003_02212884(SelfType *self)
{
    int tmp;
    int orig;
    orig = self->unk_98;
    tmp = func_020113a4(orig, 0, 0x171);
    func_0201107c(self, &tmp);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02212a54(self);
        func_02010f5c(self);
        func_0201100c(self);
        func_02010d64(self);
        func_ov003_02212968(self);
        func_ov003_02212a14(self);
    } else {
        func_02010f5c(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        func_ov003_0221292c((struct FuncOv003Struct *) self);
    }
    if (orig != 0 && self->unk_98 == 0) {
        func_020912d4(0x2a, &self->unk_5C, &self->unk_8E, 0);
    }
}

void func_ov003_02212878(u8 *d, struct UnkStruct_02212878 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
