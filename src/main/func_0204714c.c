/* func_0204714c @ 0x0204714c, 0x3b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

// func_0204714c  main  0x0204714c  0x3b4  Thumb  1.2/base -O4,s

typedef struct Rec {
    u8 pad_00[3];
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
} Rec;

typedef struct World {
    int unk_00;
    int unk_04;
    int unk_08;
} World;

typedef struct Bag {
    int a;
    int b;
} Bag;
typedef struct Obj54 {
    int w[6];
} Obj54;

extern int data_021c79c4;
extern int data_021f39fc;
extern int data_021f3aa4;
extern int data_021f38f8;
extern int data_021ebcd4;
extern u8 data_021ebcd3;
extern int data_021f3a68;
extern u8 data_021f3a86;
extern int data_021e9aac;
extern int data_021f395c;
extern int data_021f3278;
extern int data_021e5a2c;
extern int data_021c7c48;

extern World *func_0204e414(void);
extern void func_0204d0ac(World *w);
extern void func_02047500(void *self, World *w, int mx, int my);
extern void func_0204a5d4(void *p, World *w, int mx, int my);
extern void func_0204cac0(void *p, int v, int c);
extern void func_02048fdc(void *self, World *w, int mx, int my);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void func_0209e140(Bag *b, int n);
extern int func_0209dc48(Bag *b);
extern void func_020489c4(void *self, World *w);
extern int func_020644cc(int n);
extern void func_0204864c(void *self, World *w, int mx, int my);
extern void func_0209e29c(Bag *b, int n);
extern void func_02048698(void *self, World *w, int mx, int my);
extern void func_02049ad0(void *self, World *w);
extern void func_020486d8(void *self, World *w, int mx, int my);
extern void func_020487d8(void *self, World *w, int mx, int my);
extern void func_020499cc(void *self, World *w, int k);
extern void func_02048824(void *self, World *w, Rec *r, int c);
extern void func_020b1e54(void);
extern void func_02047688(void *self, World *w, int mx, int my, Rec *r, int e);
extern void func_02048a80(void *self, World *w, int mx, int my);
extern void func_0204855c(void *self, World *w, int mx, int my);
extern void func_02048498(void *self, World *w, int mx, int my);
extern void func_02048418(void *self, World *w, int mx, int my);
extern void func_020483c4(void *self, World *w, int mx, int my);
extern void func_02048238(void *self, World *w, int mx, int my);
extern void func_02048000(void *self, World *w, int c);
extern void func_02047fac(void *self, World *w, int mx);
extern void func_02047ee8(void *self, World *w, int mx, int my, int f);
extern void func_02047e54(void *self, World *w, int mx, int my);
extern void func_020868e8(void *p);
extern void func_0207122c(void *p);
extern void func_02060f5c(void *p);
extern void func_020aea84(void);
extern void func_02060d48(void *p, int c);
extern void func_020617f0(void);
extern void func_0203a508(void *p, int c);
extern void func_0203a46c(void *p, Rec *r, int c);
extern void func_0205ba64(Obj54 *o);
extern void func_0205b8e0(Obj54 *o);
extern void func_0204e938(void *p);
extern void func_020ba36c(int c);
extern void func_02096d10(int c);
extern void func_0209751c(int *rgb, int c);
extern void func_02086ee8(void *p);
extern void func_020af3a0(void *p, int n);
extern void func_02053050(void);
extern void func_02088404(int c);
extern int func_02088208(void *p);
extern void func_02088214(void *p, int n);
extern void func_020790a8(void *p, Rec *r);
extern int func_0209de88(int a, int b, int c);
extern void func_02046c2c(void *self);
extern void func_0205ba60(Obj54 *o);
extern void func_02042c40(void *p);
extern void func_020481a0(void *self);

void func_0204714c(void *self, Rec *a1, Rec *a2, int a3, u8 a5, int a6)
{
    int s14, s18, s1c, s20, s24, s28, s2c, s30;
    Bag bag1;
    Bag bag2;
    int rgb[4];
    Obj54 obj;
    World *w;
    int mx, my;
    int *p;
    int va, vb, dif;

    w = func_0204e414();
    if (w != 0) {
        mx = w->unk_04 - 2;
        my = w->unk_08 - 2;
        func_0204d0ac(w);
        if (a5 != 0) {
            func_02047500(self, w, mx, my);
        }
        func_0204a5d4(&data_021c79c4, w, mx, my);
        func_0204cac0(&data_021f39fc, data_021c79c4, a3);

        s14 = a3;
        if (s14 > 5) {
            s14 = 5;
        }
        for (s18 = 0; s18 < s14; s18++) {
            func_02048fdc(self, w, mx, my);
        }

        bag1.a = 0;
        bag1.b = 0;
        MI_CpuCopy8(a2, &bag1, 8);
        s24 = a3;
        if (s24 > 0x16d) {
            s24 = 0x16d;
        }
        func_0209e140(&bag1, s24);
        for (s30 = 0; s30 < s24; s30++) {
            switch (func_0209dc48(&bag1)) {
                case 0:
                case 1:
                case 2:
                case 0x16:
                    func_020489c4(self, w);
                    break;
                default:
                    func_020489c4(self, w);
                    if (func_020644cc(100) < 0x32) {
                        func_0204864c(self, w, mx, my);
                    }
                    break;
            }
            func_0209e29c(&bag1, 1);
        }

        bag2.a = 0;
        bag2.b = 0;
        MI_CpuCopy8(a2, &bag2, 8);
        s20 = a3;
        if (s20 > 0x1e) {
            s20 = 0x1e;
        }
        func_0209e140(&bag2, s20);
        for (s2c = 0; s2c < s20; s2c++) {
            switch (func_0209dc48(&bag2)) {
                case 0:
                case 1:
                case 2:
                case 0x16:
                    break;
                default:
                    if (func_020644cc(100) < 0x14) {
                        func_02048698(self, w, mx, my);
                    }
                    break;
            }
            func_0209e29c(&bag2, 1);
        }

        s1c = a3;
        if (s1c > 0x3c) {
            s1c = 0x3c;
        }
        func_02049ad0(self, w);
        func_020486d8(self, w, mx, my);
        func_020487d8(self, w, mx, my);
        if (s1c > 1) {
            for (s28 = 1; s28 < s1c; s28++) {
                func_020499cc(self, w, s28);
                func_020486d8(self, w, mx, my);
                func_020487d8(self, w, mx, my);
            }
        }

        func_02048824(self, w, a2, a3);
        rgb[0] = a2->unk_05;
        rgb[1] = a2->unk_04;
        rgb[2] = a2->unk_03;
        func_020b1e54();
        func_02047688(self, w, mx, my, a2, a6);
        func_02048a80(self, w, mx, my);
        func_0204855c(self, w, mx, my);
        func_02048498(self, w, mx, my);
        func_02048418(self, w, mx, my);
        func_020483c4(self, w, mx, my);
        func_02048238(self, w, mx, my);
        func_02048000(self, w, a3);
        func_02047fac(self, w, mx);
        func_02047ee8(self, w, mx, my, a5);
        func_02047e54(self, w, mx, my);
        func_020868e8(&data_021f3aa4);
        func_0207122c(&data_021f38f8);
        p = &data_021ebcd4;
        func_02060f5c(p);
        func_020aea84();
        func_02060d48(p, a3);
        func_020617f0();
        func_0203a508(&data_021f3a68, a3);
        func_0203a46c(&data_021f3a86, a2, a3);
        func_0205ba64(&obj);
        func_0205b8e0(&obj);
        func_0204e938(&data_021e9aac);
        func_020ba36c(a3);
        func_02096d10(a3);
        func_0209751c(rgb, a3);
        func_02086ee8(&data_021ebcd3);
        func_020af3a0(&data_021f395c, 0);
        func_02053050();
        func_02088404(a3);
        if (a3 > 0) {
            int *q = &data_021f3278;
            if (func_02088208(q) == 1) {
                func_02088214(q, 2);
            }
        }
        func_020790a8(&data_021e5a2c, a2);
        va = func_0209de88(a1->unk_05, a1->unk_04, a1->unk_03);
        vb = func_0209de88(a2->unk_05, a2->unk_04, a2->unk_03);
        dif = vb - va;
        if (vb == 0 || a3 >= 7 || dif < 0) {
            func_02046c2c(self);
        }
        func_0205ba60(&obj);
    }
    func_02042c40(&data_021c7c48);
    func_020481a0(self);
}
