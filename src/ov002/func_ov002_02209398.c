/* func_ov002_02209398 @ 0x02209398, 0xcc bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209398 {
    u8 pad_00[0x18];
    u8 unk_18;
    u8 pad_19;
    u8 unk_1A;
    u8 pad_1B[6];
    volatile u8 unk_21;
};

extern void func_ov002_0220958c(struct UnkStruct_02209398 *self);
extern void func_02001a7c(void);
extern unsigned char func_02002d50(unsigned int v);
extern unsigned char func_02001a30(unsigned char mask);
extern void func_02001a1c(int v);
extern int func_02002d8c(int v);
extern void func_ov002_02208558(char *p, int a, int b, int c, int d);
extern void func_02002708(int v);
extern void func_ov002_02208a0c(struct UnkStruct_02209398 *self, int bit);
extern void func_ov002_02209464(struct UnkStruct_02209398 *self);
extern int func_ov002_0220866c(char *p, int a);
extern void func_ov002_0220968c(struct UnkStruct_02209398 *self, int v);
extern void func_0208a9e4(char *p, int a);

void func_ov002_02209398(struct UnkStruct_02209398 *self)
{
    int t;

    if (self->unk_18 == 0) {
        func_ov002_0220958c(self);
        func_02001a7c();
        func_02001a30(func_02002d50(self->unk_1A));
        func_02001a1c(-6);
        t = func_02002d8c(self->unk_1A);
        func_ov002_02208558((char *) self + 0x3b0, t, 5, 0, 0x30);
        func_02002708(self->unk_1A);
        func_ov002_02208a0c(self, 1);
        self->unk_21 = 2;
        func_ov002_02209464(self);
        self->unk_18 = self->unk_18 + 1;
    } else {
        if (func_ov002_0220866c((char *) self + 0x3b0, 0)) {
            func_ov002_0220968c(self, 3);
            if (self->unk_21 != 0) {
                self->unk_21 = 1;
            }
        }
        if (self->unk_21 != 0) {
            self->unk_21 = self->unk_21 - 1;
            if (self->unk_21 == 0) {
                func_0208a9e4((char *) self + 0x2e4, 0);
            }
        }
        func_ov002_02209464(self);
    }
}
