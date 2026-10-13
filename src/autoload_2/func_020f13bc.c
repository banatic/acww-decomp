/* func_020f13bc @ 0x020f13bc, 0x164 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_020f13bc {
    u32 unk_00;
    u8 unk_04[2];
    unsigned short unk_06;
    u8 pad_08[8]; // 0x08..0x10
    u8 unk_10[2];
    unsigned short unk_12;
    u8 pad_14[8]; // 0x14..0x1c
    u8 unk_1C[2];
    unsigned short unk_1E;
    u8 pad_20[12]; // 0x20..0x2c
    void *unk_2C;  // 0x2c
    u8 pad_30[4];  // 0x30..0x34
    u8 unk_34[52]; // 0x34..0x68
    u32 unk_68;
};

extern int func_020f0d50(void *);
extern void func_020f0ddc(void *, int);
extern void func_020f0d98(void *, int, int);
extern void func_020f11d0(void *, int, int);
extern void func_020f1158(void *, int);
extern unsigned int NNS_SndArcStrmGetCurrentPlayingPos(void *);

void func_020f13bc(struct UnkStruct_020f13bc *self)
{
    if (self->unk_2C == 0) {
        return;
    }

    if (((signed char *) self->unk_2C)[4] == 50) {
        unsigned int pos = NNS_SndArcStrmGetCurrentPlayingPos(&self->unk_34);
        int secs = (self->unk_68 - pos) * 20 / 1000;
        if (pos != 0) {
            if (secs > 127) {
                func_020f11d0(self, 0, 0);
            } else if (secs == 127) {
                func_020f0ddc(&self->unk_04, 0);
                func_020f0d98(&self->unk_04, 127, 160);
            }
        }

        if (self->unk_06 != 0) {
            int v = func_020f0d50(&self->unk_04);
            func_020f11d0(self, v, v);
        }
    }

    if (((signed char *) self->unk_2C)[4] == 51) {
        if (self->unk_06 != 0) {
            int v = func_020f0d50(&self->unk_04);
            func_020f11d0(self, v, v);
        }
    }

    if (self->unk_12 != 0) {
        int v1 = func_020f0d50(&self->unk_10);
        int v2 = func_020f0d50(&self->unk_1C);
        func_020f11d0(self, v1, v2);
    } else if (self->unk_1E != 0) {
        int v = func_020f0d50(&self->unk_1C);
        func_020f1158(self, v);
    }
}