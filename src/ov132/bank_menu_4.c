/* bank_menu_4: 8 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229b514 @ 0x0229b514, 0x8 bytes, Thumb
 * func_ov132_0229b4fc @ 0x0229b4fc, 0x16 bytes, Thumb
 * func_ov132_0229b4f8 @ 0x0229b4f8, 0x2 bytes, Thumb
 * func_ov132_0229b4c0 @ 0x0229b4c0, 0x38 bytes, Thumb
 * func_ov132_0229b3d8 @ 0x0229b3d8, 0xe8 bytes, Thumb
 * func_ov132_0229b3cc @ 0x0229b3cc, 0xc bytes, Thumb
 * func_ov132_0229b340 @ 0x0229b340, 0x8c bytes, Thumb
 * func_ov132_0229b2a4 @ 0x0229b2a4, 0x9c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229b2a4 {
    unsigned char pad_00[0x1502];
    unsigned char unk_1502;
};

extern void func_ov002_0220af74(void *);
extern void func_ov132_0229adb8(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int func_ov130_0229a678(int);
extern int func_02064af4(const void *src, void *dst, unsigned int size);
extern void func_0206fdd4(void *addr, int a1, int a2, int a3, int a4, int a5);
extern int func_02002b40(void *addr, int a1, unsigned int size, int a3);
extern void *func_ov132_0229ad88(void *ctx);
extern int func_0207094c(void *obj, int id);
extern void func_02070adc(void *obj, int a1, unsigned int a2, int a3, int a4, int a5, int a6);
extern void func_02070a04(void *obj, int a1, int a2);
extern const unsigned char data_ov132_0229b9f0[];
extern const unsigned char data_ov132_0229ba04[];
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern int func_ov132_0229b124(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov132_0229b0d0(void *self);
extern void func_ov132_0229aff8(void *self);
extern void func_ov132_0229af88(void *self);
extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void *receiver);
extern char *func_ov002_02208008(void *p);
extern int func_ov002_02207ffc(void *p);
extern int func_ov002_02207ff0(void *p);
extern int func_ov132_0229b140(void *p);
extern void func_ov132_0229ae4c(void *p);
extern void func_ov132_0229ae90(void *p);
extern void func_ov132_0229ade4(void *p);

void func_ov132_0229b4f8(void);

void func_ov132_0229b514(void)
{
    func_ov132_0229b4f8();
}

void func_ov132_0229b4fc(void *p)
{
    func_ov002_0220af74((char *) p + 0xf8);
    func_ov132_0229adb8(p);
}

void func_ov132_0229b4f8(void) {}

void func_ov132_0229b4c0(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov132_0229b3d8(void *ctx)
{
    void *obj1;
    void *obj2;

    func_ov130_0229a678(6);
    func_02064af4(data_ov132_0229b9f0, (char *) ctx + 0x500, 0x800);
    func_0206fdd4((char *) ctx + 0x500, 6, 7, 0x19, 0xf, 6);
    func_02002b40((char *) ctx + 0x500, 6, 0x800, 0);

    func_02064af4(data_ov132_0229ba04, (char *) ctx + 0xd00, 0x800);
    func_0206fdd4((char *) ctx + 0xd00, 6, 7, 0x19, 0xf, 6);
    func_02002b40((char *) ctx + 0xd00, 4, 0x800, 0);

    obj1 = func_ov132_0229ad88(ctx);
    func_0207094c(obj1, 0x5f);
    func_02070adc(obj1, 4, 0x114, 0xe, 0xf, 0, 0);
    func_02070a04(obj1, 1, 0);

    obj2 = func_ov132_0229ad88(ctx);
    func_0207094c(obj2, 0x60);
    func_02070adc(obj2, 4, 0x130, 0xe, 0xf, 0, 0);
    func_02070a04(obj2, 1, 0);
}

void func_ov132_0229b3cc(void *receiver)
{
    func_ov002_0220af94((void *) ((char *) receiver + 0xf8));
}

void func_ov132_0229b340(char *self)
{
    unsigned int ok;
    int a;
    int b;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov132_0229b124(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0xf8, 6) != 0) {
        func_ov132_0229b0d0(self);
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    if (a < 0x40) {
        return;
    }
    if (a >= 0xc0) {
        return;
    }
    if (b >= 0x38 && b < 0x58) {
        func_ov132_0229aff8(self);
        return;
    }
    if (b >= 0x60 && b < 0x80) {
        func_ov132_0229af88(self);
    }
}

void func_ov132_0229b2a4(struct UnkStruct_0229b2a4 *p)
{
    unsigned char orig;

    if (func_ov002_02208014(p) != 0) {
        func_ov132_0229b140(p);
        return;
    }

    func_ov002_02208008(p);
    orig = p->unk_1502;

    if (func_ov002_02207ffc(p) != 0) {
        if (p->unk_1502 != 0) {
            p->unk_1502 = p->unk_1502 - 1;
        }
    } else {
        if (func_ov002_02207ff0(p) != 0) {
            if (p->unk_1502 < 2) {
                p->unk_1502 = p->unk_1502 + 1;
            }
        }
    }

    if (orig != p->unk_1502) {
        func_ov132_0229ae4c(p);
    } else {
        unsigned short flags = data_021fbe40[1];
        if ((flags & 2) != 0) {
            func_ov132_0229ae90(p);
            func_ov132_0229b0d0(p);
        } else if ((flags & 1) != 0) {
            func_ov132_0229ade4(p);
        }
    }
}
