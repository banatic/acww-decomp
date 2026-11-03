/* music_list_scene_2: 10 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229ad70 @ 0x0229ad70, 0x20 bytes, Thumb
 * func_ov144_0229ad24 @ 0x0229ad24, 0x4c bytes, Thumb
 * func_ov144_0229ac90 @ 0x0229ac90, 0x94 bytes, Thumb
 * func_ov144_0229ac40 @ 0x0229ac40, 0x50 bytes, Thumb
 * func_ov144_0229ab88 @ 0x0229ab88, 0xb8 bytes, Thumb
 * func_ov144_0229ab54 @ 0x0229ab54, 0x34 bytes, Thumb
 * func_ov144_0229ab20 @ 0x0229ab20, 0x34 bytes, Thumb
 * func_ov144_0229aabc @ 0x0229aabc, 0x64 bytes, Thumb
 * func_ov144_0229aa70 @ 0x0229aa70, 0x4c bytes, Thumb
 * func_ov144_0229aa30 @ 0x0229aa30, 0x3e bytes, Thumb
 */

#include "types.h"

typedef struct Obj_ov144_0229b3f8 Obj_ov144_0229b3f8;

struct FlagsStruct {
    char pad_00[2];
    unsigned short flags;
};

extern void func_ov144_02299cc4(void *);
extern void func_ov144_02299ed4(void *);
extern void func_ov002_0220a544(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int data_021fbe94;
extern int func_02002c6c(void *data, int obj, int type, int a4, int a5, int a6);
extern int func_02002d14(void *data, int obj, int type, int a4, int a5, int a6);
extern int func_02064af4(void *src, void *dst, int size);
extern void func_ov144_02299b7c(void *param);
extern unsigned char data_ov144_0229b480[];
extern unsigned char data_ov144_0229b494[];
extern unsigned char data_ov144_0229b4a8[];
extern unsigned char data_ov144_0229b4bc[];
extern unsigned char data_ov144_0229b4d0[];
extern void func_ov002_0220af94(void *receiver);
extern unsigned char data_ov144_0229b458[];
extern unsigned char data_ov144_0229b46c[];
extern int func_ov002_02208054(void *self, int a);
extern unsigned char *func_ov144_0229a7e8(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern int func_ov144_02299a30(void *self, int a, int b);
extern int func_ov144_02299ac4(void *self, int n);
extern int func_ov144_0229a540(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_0220a574(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov144_0229a4c8(int a, unsigned char b, int c);
extern int func_ov144_0229a4b8(int arg0);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(Obj_ov144_0229b3f8 *);
extern int func_ov144_022996d4(Obj_ov144_0229b3f8 *, int);
extern unsigned char *func_ov144_0229a824(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a12c(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a0c8(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a17c(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a798(Obj_ov144_0229b3f8 *);
extern struct FlagsStruct data_021fbe40;
extern void func_ov144_0229a42c(char *p);
extern int func_ov144_0229a208(char *p);
extern int func_ov144_0229a198(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern int func_ov144_0229a404(void *p);
extern void func_ov144_0229a0a4(void *p);

void func_ov144_0229ad70(void *obj)
{
    func_ov144_02299cc4(obj);
    func_ov144_02299ed4(obj);
    func_ov002_0220a544((char *) obj + 0x128);
}

void func_ov144_0229ad24(void)
{
    func_02001c08(0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 2);
    func_020028bc(3, 0, 0, 0);
}

void func_ov144_0229ac90(void *param)
{
    int local = data_021fbe94;

    func_02002c6c((void *) data_ov144_0229b480, local, 6, 17, 17, 152);
    func_02002c6c((void *) data_ov144_0229b494, local, 6, 0x26e, 0x26e, 0x27e);
    func_02002d14((void *) data_ov144_0229b4a8, local, 6, 1, 1, 0xa);
    func_02064af4((void *) data_ov144_0229b4bc, (char *) param + 0x90a, 0x800);
    func_02064af4((void *) data_ov144_0229b4d0, (char *) param + 0x190a, 0x800);
    func_ov144_02299b7c(param);
}

void func_ov144_0229ac40(void *self)
{
    int val;
    func_ov002_0220af94((char *) self + 0x170);
    val = data_021fbe94;
    func_02002c6c(data_ov144_0229b458, val, 8, 0xc0, 0xc0, 0x120);
    func_02002d14(data_ov144_0229b46c, val, 8, 4, 4, 5);
}

void func_ov144_0229ab88(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov144_0229a7e8(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = (*(u8 *) &data_021f6c54);
    n = func_ov144_02299a30(self, a, b);
    if (n != 0xe) {
        func_ov144_02299ac4(self, n);
        return;
    }

    if (*(int *) (self + 0xa4) <= 0) {
        return;
    }
    if (func_ov144_0229a540(self, a, b) != 0) {
        func_ov002_02208098(self, 1);
        return;
    }
    if (a < 0xcf) {
        return;
    }
    if (a > 0xdf) {
        return;
    }
    if (b < 0x1d) {
        return;
    }
    if (b > 0x93) {
        return;
    }
    func_ov002_0220a574(self + 0x128);
    *(int *) (self + 0xb0) = *(int *) (self + 0xa8);
    func_ov002_02208098(self, 2);
}

void func_ov144_0229ab54(int param)
{
    if (data_021fbdd8) {
        func_ov144_0229a4c8(param, data_021f6c54, 0);
    } else {
        func_ov144_0229a4b8(param);
        func_ov002_02208098((void *) param, 0);
    }
}

void func_ov144_0229ab20(int p)
{
    if (data_021fbdd8) {
        func_ov144_0229a4c8(p, data_021f6c54, 1);
    } else {
        func_ov144_0229a4b8(p);
        func_ov002_02208098((void *) p, 0);
    }
}

void func_ov144_0229aabc(Obj_ov144_0229b3f8 *obj)
{
    if (func_ov002_02208014(obj)) {
        func_ov144_0229a824(obj);
        return;
    }
    if (func_ov144_022996d4(obj, func_ov002_02208008(obj))) {
        func_ov144_0229a12c(obj);
        return;
    }
    if (data_021fbe40.flags & 1) {
        func_ov144_0229a0c8(obj);
        return;
    }
    if (data_021fbe40.flags & 2) {
        func_ov144_0229a17c(obj);
        func_ov144_0229a798(obj);
    }
}

void func_ov144_0229aa70(char *p)
{
    int t;
    int x;
    int y;
    t = (*(unsigned short *) &data_021fbe40) & 1;
    if (t != 0) {
        func_ov144_0229a42c(p);
        x = func_ov144_0229a208(p);
        y = func_ov144_0229a198(p);
        p += 0xc4;
        func_ov002_0220a0b4(p, x, y);
    } else {
        func_ov144_0229a4b8((int) p);
        func_ov002_02208098((void *) p, 5);
    }
}

void func_ov144_0229aa30(void *p)
{
    int a, b;

    if (func_ov144_0229a404(p)) {
        func_ov002_02208098(p, 3);
        func_ov144_0229a0a4(p);
    }

    a = func_ov144_0229a208((char *) p);
    b = func_ov144_0229a198((char *) p);
    func_ov002_0220a0b4((char *) ((char *) p + 0xc4), a, b);
}
