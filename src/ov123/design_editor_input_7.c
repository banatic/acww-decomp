/* design_editor_input_7: 7 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229bc70 @ 0x0229bc70, 0xb0 bytes, Thumb
 * func_ov123_0229bb74 @ 0x0229bb74, 0xfc bytes, Thumb
 * func_ov123_0229baa4 @ 0x0229baa4, 0xd0 bytes, Thumb
 * func_ov123_0229b9bc @ 0x0229b9bc, 0xe8 bytes, Thumb
 * func_ov123_0229b8ec @ 0x0229b8ec, 0xd0 bytes, Thumb
 * func_ov123_0229b89c @ 0x0229b89c, 0x50 bytes, Thumb
 * func_ov123_0229b7e4 @ 0x0229b7e4, 0xb8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 pad_A4[6];
    u8 unk_AA;
    u8 unk_AB;
    u8 unk_AC;
} UnkStruct_0229bb74;

typedef struct {
    unsigned char pad_00[0xaa];
    unsigned char unk_AA;
    unsigned char unk_AB;
    unsigned char unk_AC;
} ThisType;

typedef struct {
    unsigned char pad_00[2];
    unsigned short u16_at_2;
} UnkStruct_0229baa4;

typedef struct UnkStruct_0229b9bc {
    unsigned char pad_00[0xa2];
    unsigned char a2;
    unsigned char pad_A3[0xa4 - 0xa3];
    unsigned char a4;
    unsigned char pad_A5[0xaf - 0xa5];
    unsigned char af;
    unsigned char b0;
    unsigned char pad_B1[0xb3 - 0xb1];
    unsigned char b3;
} UnkStruct_0229b9bc;

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char a8;
    unsigned char a9;
    unsigned char pad_AA[2];
    unsigned char ac;
    unsigned char pad_AD[2];
    unsigned char af;
    unsigned char b0;
} UnkStruct_0229b8ec;

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov123_02299650(void *, int);
extern void func_ov123_02299630(void *, int);
extern void func_ov123_02299640(void *, int);
extern void func_ov123_022996dc(void *);
extern void func_ov123_02299ea8(void *);
extern void func_02004644(int, int);
extern void func_02004658(int);
extern int func_ov002_02208014(void *receiver);
extern void func_ov123_0229b6d0(UnkStruct_0229bb74 *self);
extern int func_ov123_02299adc(UnkStruct_0229bb74 *self, int arg);
extern void func_ov123_02299c04(UnkStruct_0229bb74 *self);
extern void func_ov123_02299cc0(UnkStruct_0229bb74 *self);
extern int func_ov123_022998c0(UnkStruct_0229bb74 *self);
extern void func_ov123_02299980(UnkStruct_0229bb74 *self);
extern void func_ov123_0229b598(UnkStruct_0229bb74 *self);
extern void func_ov123_0229b5cc(UnkStruct_0229bb74 *self);
extern int func_ov002_02208008(void *);
extern int func_ov123_022999b0(void *, int, int);
extern void func_ov123_0229a438(void *);
extern void func_ov123_0229a340(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov123_0229b65c(void *);
extern void func_ov123_02299d00(void *);
extern int func_ov123_0229ac80(UnkStruct_0229b9bc *self, int a, int b, int c, int d, int e);
extern void func_0200467c(int cmd);
extern void func_ov123_02299ec4(UnkStruct_0229b8ec *self);
extern unsigned short data_021fbe40[2];
extern void func_ov123_0229b644(void *self);
extern int func_ov002_02207fe4(void *self);
extern int func_ov002_02207fd8(void *self);
extern void func_ov123_0229ae84(void *self);

void func_ov123_0229bc70(unsigned char *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov123_02299650(self, 0x80000)) {
            func_ov123_02299630(self, 0x80000);
            func_02004644(0x862, 1);
        }
        func_ov123_02299ea8(self);
    } else {
        func_ov123_02299630(self, 0x100000);
        func_ov123_022996dc(self);
        self[0xb4] = data_021f6c58;
        self[0xb5] = data_021f6c54;

        if (func_ov123_02299650(self, 0x100000)) {
            if (func_ov123_02299650(self, 0x80000) == 0) {
                func_ov123_02299640(self, 0x80000);
                func_02004658(0x862);
            }
        } else {
            if (func_ov123_02299650(self, 0x80000)) {
                func_ov123_02299630(self, 0x80000);
                func_02004644(0x862, 1);
            }
        }
    }
}

void func_ov123_0229bb74(UnkStruct_0229bb74 *self)
{
    if (func_ov002_02208014(self)) {
        func_ov123_0229b6d0(self);
        return;
    }
    if (func_ov123_02299adc(self, func_ov002_02208008((void *) self))) {
        if (self->unk_AC == 0) {
            self->unk_AB = self->unk_AA;
        }
        func_ov123_02299c04(self);
        return;
    } else {
        u16 flags = (*(struct {
                        u8 pad[2];
                        u16 flags;
                    } *) data_021fbe40)
                        .flags;
        if (flags & 1) {
            func_ov123_02299cc0(self);
            return;
        }
        if (flags & 0x800) {
            func_0200467c(0x864);
            if (self->unk_AC == 0) {
                self->unk_AC = 1;
                self->unk_AA = self->unk_A2 + 13;
            } else {
                self->unk_AC = 2;
            }
            func_ov123_0229b65c((void *) self);
            return;
        }
        if (func_ov123_022998c0(self) != 0) {
            return;
        }
        flags = (*(struct {
                    u8 pad[2];
                    u16 flags;
                } *) data_021fbe40)
                    .flags;
        if (flags & 0x400) {
            func_ov123_02299980(self);
            return;
        }
        if (flags & 2) {
            func_ov123_02299d00((void *) self);
            func_ov123_0229b598(self);
            return;
        }
        if (flags & 8) {
            func_ov123_02299d00((void *) self);
            func_ov123_0229b5cc(self);
            return;
        }
        return;
    }
}

void func_ov123_0229baa4(ThisType *this)
{
    unsigned short flags;

    if (func_ov002_02208014(this) != 0) {
        func_ov123_0229b6d0((UnkStruct_0229bb74 *) this);
        return;
    }

    func_ov123_022999b0(this, func_ov002_02208008(this), 0);

    flags = (*(UnkStruct_0229baa4 *) data_021fbe40).u16_at_2;
    if (flags & 0x1) {
        func_ov123_0229a438(this);
        return;
    }
    if (flags & 0x2) {
        func_ov123_02299640(this, 0x800);
        func_ov123_0229a340(this);
        func_ov002_02208098(this, 7);
        return;
    }
    if (flags & 0x800) {
        func_0200467c(0x864);
        this->unk_AC = 0;
        this->unk_AA = this->unk_AB;
        func_ov123_0229b65c(this);
        return;
    }

    if (func_ov123_022998c0((UnkStruct_0229bb74 *) this)) {
        return;
    }

    flags = (*(UnkStruct_0229baa4 *) data_021fbe40).u16_at_2;
    if (flags & 0x400) {
        func_ov123_02299980((UnkStruct_0229bb74 *) this);
        return;
    }
    if (flags & 0x8) {
        func_ov123_02299d00(this);
        func_ov123_0229b5cc((UnkStruct_0229bb74 *) this);
    }
}

void func_ov123_0229b9bc(UnkStruct_0229b9bc *self)
{
    int tmp;
    int flag;

    if (((*(unsigned short *) data_021fbe40) & 1) == 0) {
        func_ov123_0229b65c((void *) self);
        if (func_ov123_02299650((void *) self, 0x40000) != 0) {
            func_ov123_02299630((void *) self, 0x40000);
            func_02004644(0x863, 1);
        }
        return;
    }

    tmp = func_ov002_02208008((void *) self);
    flag = 0;

    if (func_ov123_022999b0((void *) self, tmp, 1) != 0) {
        func_ov123_0229ac80(self, self->af, self->b0, self->a2, self->a4, 1);
        func_ov123_02299640((void *) self, 0x40);
        func_0200467c(0x861);

        if (self->b3 == 0) {
            flag = 1;
        } else {
            func_0200467c(0x860);
        }
    }

    if (flag) {
        if (func_ov123_02299650((void *) self, 0x40000) == 0) {
            func_ov123_02299640((void *) self, 0x40000);
            func_02004658(0x863);
        }
    } else {
        if (func_ov123_02299650((void *) self, 0x40000) != 0) {
            func_ov123_02299630((void *) self, 0x40000);
            func_02004644(0x863, 1);
        }
    }
}

void func_ov123_0229b8ec(UnkStruct_0229b8ec *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_0200467c(0x86e);
        func_ov123_02299ec4(self);
        func_ov123_0229b6d0((UnkStruct_0229bb74 *) self);
        return;
    }
    {
        int r = func_ov002_02208008((void *) self);
        if (func_ov123_022999b0((void *) self, r, 0) != 0) {
            self->a8 = self->af;
            self->a9 = self->b0;
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40[1];
        if (flags & 1) {
            func_ov123_02299ea8((void *) self);
            return;
        }
        if (flags & 2) {
            func_0200467c(0x86e);
            func_ov123_02299ec4(self);
            func_ov123_0229b65c((void *) self);
            return;
        }
        if (flags & 0x800) {
            func_0200467c(0x864);
            func_ov123_02299ec4(self);
            self->ac = 0;
            func_ov123_0229b65c((void *) self);
            return;
        }
        if (flags & 0x400) {
            func_ov123_02299980((UnkStruct_0229bb74 *) self);
        }
    }
}

void func_ov123_0229b89c(void *arg)
{
    if (((*(volatile unsigned short *) data_021fbe40) & 2) == 0) {
        func_ov123_02299630(arg, 0x800);
        func_ov123_0229b65c(arg);
        func_0200467c(0x86d);
    } else {
        int ret = func_ov002_02208008(arg);
        if (func_ov123_022999b0(arg, ret, 0) != 0) {
            func_ov123_0229a340(arg);
        }
    }
}

void func_ov123_0229b7e4(void *self)
{
    if (func_ov002_02208014(self)) {
        func_ov123_0229b644(self);
        return;
    } else {
        unsigned char orig = ((unsigned char *) self)[0xaa];
        func_ov002_02208008(self);
        if (func_ov002_02207fe4(self)) {
            ((unsigned char *) self)[0xaa] = 0x1f;
        } else if (func_ov002_02207fd8(self)) {
            ((unsigned char *) self)[0xaa] = 0x20;
        }
        if (orig != ((unsigned char *) self)[0xaa]) {
            func_ov123_02299c04((UnkStruct_0229bb74 *) self);
            return;
        } else {
            unsigned short v = data_021fbe40[1];
            if (v & 1) {
                func_ov123_02299cc0((UnkStruct_0229bb74 *) self);
            } else if (v & 2) {
                func_ov123_02299d00(self);
                ((unsigned char *) self)[0xa5] = 0x20;
                func_ov123_0229ae84(self);
            } else if (v & 8) {
                func_ov123_02299d00(self);
                ((unsigned char *) self)[0xa5] = 0x1f;
                func_ov123_0229ae84(self);
            }
        }
    }
}
