/* func_0201c6d0 @ 0x0201c6d0, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201c6d0 {
    u8 pad_00[0x40];
    u8 unk_40;
    u8 pad1[0x54 - 0x41];
    u8 unk_54;
    u8 pad_55;
    u16 unk_56;
    u8 unk_58;
};

struct Other {
    u8 pad_00[0x2a0];
    u8 unk_2A0[0x334 - 0x2a0];
    u8 unk_334[0x564 - 0x334];
    u8 unk_564[0x578 - 0x564];
    void *unk_578;
    u8 pad1[0x618 - 0x57c];
    u8 unk_618[0x830 - 0x618];
    void *unk_830;
};

struct UnkStruct_0201c6d0_2 {
    u8 pad_00[0x64];
    void *unk_64;
};

extern struct UnkStruct_0201c6d0_2 *data_020ccf94;
extern u16 data_020c80f8;

extern void *func_0207f270(void *);
extern int func_020794c4(unsigned char *);
extern int func_0201cd2c(struct UnkStruct_0201c6d0 *);
extern int func_02073dd4(void *, void *);
extern int func_02014868(void *);
extern void func_0201ccd0(struct UnkStruct_0201c6d0 *, struct Other *, int);
extern void func_020794a8(void *, u16);
extern void func_020794a4(void *, u16);
extern void func_020794c0(void *, int);
extern void func_02079494(void *);
extern int func_020794a0(void *);
extern void func_0201ccc0(struct UnkStruct_0201c6d0 *);
extern void *func_020164a0(void *, int);
extern void *func_020168ac(void *, int, void *);
extern int func_0201c9a4(struct UnkStruct_0201c6d0 *, struct Other *);
extern int func_02019d0c(void *, int, void *, int, int, int, int, int, int, u16, int);
extern void func_0201c828(struct UnkStruct_0201c6d0 *, struct Other *, int);
extern void func_0201cbcc(struct UnkStruct_0201c6d0 *, struct Other *);

void func_0201c6d0(struct UnkStruct_0201c6d0 *self, struct Other *other)
{
    void *r7;
    int r6;

    r7 = func_0207f270(other->unk_830);
    r6 = func_020794c4(r7);

    if (func_0201cd2c(self) == 0) {
        return;
    }

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    if (func_02014868(other->unk_618) != 0) {
        r6 = 0;
        func_0201ccd0(self, other, r6);
    } else {
        if (self->unk_58 != 0) {
            if (self->unk_54 < 5) {
                if (r6 != 0 && r6 == self->unk_54) {
                    func_020794a8(r7, self->unk_56);
                } else {
                    func_020794a4(r7, self->unk_56);
                }
                func_020794c0(r7, self->unk_54);
                r6 = self->unk_54;
            }
            self->unk_58 = 0;
            func_0201ccc0(self);
        }

        func_02079494(r7);
        if (r6 != 0) {
            if (func_020794a0(r7) == 0) {
                r6 = 0;
                func_020794c0(r7, r6);
            }
        }
        func_0201ccd0(self, other, r6);
    }

    r7 = func_020164a0(other->unk_334, 0);
    if (r7 != func_020168ac(other->unk_334, 0, other->unk_2A0)) {
        if (func_0201c9a4(self, other) != 0) {
            func_02019d0c(other->unk_564, 0, other->unk_578, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201c828(self, other, r6);
    self->unk_40 = (u8) r6;
    func_0201cbcc(self, other);
}
