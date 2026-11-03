/* menu_dispatch: 12 functions, module ov092
 * mwccarm 1.2/base -O4,s
 * func_ov092_02299394 @ 0x02299394, 0x4 bytes, Thumb
 * func_ov092_02299390 @ 0x02299390, 0x4 bytes, Thumb
 * func_ov092_02299380 @ 0x02299380, 0x10 bytes, Thumb
 * func_ov092_02299324 @ 0x02299324, 0x5c bytes, Thumb
 * func_ov092_0229929c @ 0x0229929c, 0x86 bytes, Thumb
 * func_ov092_02299298 @ 0x02299298, 0x2 bytes, Thumb
 * func_ov092_02299084 @ 0x02299084, 0x212 bytes, Thumb
 * func_ov092_0229906c @ 0x0229906c, 0x18 bytes, Thumb
 * func_ov092_02298f5c @ 0x02298f5c, 0x110 bytes, Thumb
 * func_ov092_02298f58 @ 0x02298f58, 0x2 bytes, Thumb
 * func_ov092_02298f38 @ 0x02298f38, 0x20 bytes, Thumb
 * func_ov092_02298f20 @ 0x02298f20, 0x18 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02299324 {
    u8 pad_00[0x91];
    u8 unk_91;
};

struct UnkStruct_0229929c {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
};

struct UnkStruct_02299084 {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
};

typedef struct UnkStruct_02298f5c {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
} UnkStruct_02298f5c;

struct UnkStruct_02298f38 {
    void *unk_00;
};

extern void func_020ee470(void *argument0);
extern void func_0206efc0(void);
extern void func_0200467c(int cmd);
extern void func_02036468(void *p);
extern char *data_021c526c;
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_02001c08(int on);
extern void func_0206ef8c(void);
extern void func_0206ef98(void);
extern void func_0206fc98(int code);
extern void func_0206f55c(void);
extern int func_0207000c(int id);
extern int func_0206fca4(void);
extern void func_0206ead8(int arg);
extern void func_020045ac(int arg);
extern void func_02036470(void *p, int arg);
extern void *func_ov002_0220826c(void *ptr);
extern void func_ov002_02207f6c(void *ptr);
extern unsigned char data_ov092_02299508[];

int func_ov092_02299394(void)
{
    return 1;
}

int func_ov092_02299390(void)
{
    return 1;
}

int func_ov092_02299380(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov092_02299324(struct UnkStruct_02299324 *self, int i, int flag)
{
    self->unk_91 = (u8) i;
    switch (i) {
        case 0:
        case 1:
        case 0x43:
            break;
        case 0x44:
            func_0206efc0();
            break;
    }
    switch (i) {
        case 0x43:
        case 0x44:
            if (flag) {
                func_0200467c(2);
            }
            func_02036468(data_021c526c + 0x1c4);
            break;
    }
}

void func_ov092_0229929c(struct UnkStruct_0229929c *self)
{
    switch (self->unk_91) {
        case 0x43:
            func_ov002_022080a0((void *) (self), 5);
            break;
        case 0x44:
            func_ov002_022080a0((void *) (self), 0);
            func_02001c08(1);
            func_0206ef8c();
            break;
        case 0:
        case 1:
            func_0206ef98();
            self->unk_8D = 1;
            break;
        case 2:
        case 0x23:
        case 0x35:
        case 0x36:
        case 0x40:
            self->unk_8D = 1;
            func_0206fc98(self->unk_91);
            break;
    }
}

void func_ov092_02299298(void) {}

void func_ov092_02299084(struct UnkStruct_02299084 *self)
{
    switch (self->unk_91) {
        case 0:
        case 1:
        case 0x18:
        case 0x1a:
        case 0x20:
        case 0x22:
        case 0x23:
        case 0x27:
        case 0x40:
            func_0206f55c();
            break;
    }
    switch (self->unk_91) {
        case 0x0:
            func_0207000c(0xb);
            break;
        case 0x1:
            func_0207000c(0xa);
            break;
        case 0x2:
        case 0x3:
            func_0207000c(0xd);
            break;
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xa:
            func_0207000c(0xe);
            break;
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            func_0207000c(0xf);
            break;
        case 0x1c:
            func_0207000c(0x10);
            break;
        case 0x1d:
        case 0x1e:
            func_0207000c(0x11);
            break;
        case 0x1f:
        case 0x20:
            func_0207000c(0x2c);
            break;
        case 0x21:
            func_0207000c(0x12);
            break;
        case 0x22:
            func_0207000c(0x13);
            break;
        case 0x24:
            func_0207000c(0x14);
            break;
        case 0x25:
            func_0207000c(0x15);
            break;
        case 0x26:
            func_0207000c(0x16);
            break;
        case 0x27:
            func_0207000c(0x17);
            break;
        case 0x28:
            func_0207000c(0x28);
            break;
        case 0x23:
            func_0207000c(0x29);
            break;
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_0207000c(0x18);
            break;
        case 0x2d:
            func_0207000c(0x19);
            break;
        case 0x2e:
            func_0207000c(0x1a);
            break;
        case 0x2f:
            func_0207000c(0x1b);
            break;
        case 0x30:
            func_0207000c(0x1c);
            break;
        case 0x31:
            func_0207000c(0x1d);
            break;
        case 0x32:
            func_0207000c(0x1e);
            break;
        case 0x33:
            func_0207000c(0x2a);
            break;
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3a:
            func_0207000c(0x1f);
            break;
        case 0x3b:
            func_0207000c(0x20);
            break;
        case 0x3c:
            func_0207000c(0x2d);
            break;
        case 0x3d:
            func_0207000c(0x22);
            break;
        case 0x3e:
            func_0207000c(0x23);
            break;
        case 0x3f:
            func_0207000c(0x25);
            break;
        case 0x40:
            func_0207000c(0x26);
            break;
        case 0x41:
            func_0207000c(0x27);
            break;
        case 0x42:
            func_0207000c(0x2d);
            break;
    }
    self->unk_8D = 0;
}

void func_ov092_0229906c(int param)
{
    func_02001c08(0);
    func_ov002_022080a0((void *) (param), 2);
}

void func_ov092_02298f5c(UnkStruct_02298f5c *self)
{
    u8 *p;

    self->unk_91 = func_0206fca4();
    self->unk_8D = 1;

    if (self->unk_91 == 0) {
        func_ov002_022080a0((void *) (self), 2);
    } else {
        self->unk_8C = 0;
        func_ov002_022080a0((void *) (self), 0);
        func_0206ef98();
    }

    switch (self->unk_91) {
        case 0x2d:
        case 0x2e:
            func_0206ead8(3);
            break;
        case 0xf:
            func_0206ead8(1);
            break;
        case 0x10:
            func_0206ead8(2);
            break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
            func_0206ead8(0);
            break;
        default:
            break;
    }

    switch (self->unk_91) {
        case 0:
            func_0200467c(0x11);
            break;
        default:
            func_0200467c(1);
            break;
        case 3:
            func_020045ac(1);
            break;
    }

    p = &self->unk_91;
    switch (*p) {
        case 0x2d:
        case 0x2e:
            func_02036470(data_021c526c + 0x1c4, 1);
            break;
        case 0x3f:
            func_02036470(data_021c526c + 0x1c4, 2);
            break;
        default:
            func_02036470(data_021c526c + 0x1c4, 0);
            break;
    }
}

void func_ov092_02298f58(char *self) {}

struct UnkStruct_02298f38 *func_ov092_02298f38(struct UnkStruct_02298f38 *self)
{
    self->unk_00 = (void *) data_ov092_02299508;
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov092_02298f20(void *this_ptr)
{
    *(void **) this_ptr = (void *) ((char *) data_ov092_02299508);
    func_ov002_0220826c(this_ptr);
    return this_ptr;
}
