/* func_ov112_022a1c94 @ 0x022a1c94, 0x198 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct VTblClass {
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" int func_ov112_0229fb70(void);
extern "C" void func_ov112_0229fae8(void *);
extern "C" void func_0200284c(int, int, int);
extern "C" int func_ov112_0229fe70(void *, int);
extern "C" void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);
extern "C" void func_ov095_0229b1c8(void *, int, void *, int);
extern "C" void func_ov095_0229ae84(void *, int, void *);
extern "C" int func_0206fe54(void);
extern "C" void func_020896b8(int, void *, int, void *, int, int, int);
extern "C" void func_0208ea70(void *, int, int);
extern "C" int func_ov002_0220a4f8(void *);
extern "C" int func_ov002_0220a4d4(void *);
extern "C" void func_ov095_02299b30(void *, int, int);
extern "C" void func_ov002_0220a0b4(void *, int, int);
extern "C" void func_ov002_02209eb8(void *);
extern "C" void func_ov095_0229af58(void *, int, int, int);
extern "C" void func_ov002_0220ad18(void *, int);

extern unsigned char data_ov112_022a2098;
extern unsigned char data_ov112_022a2080;

extern "C" int func_ov112_022a1c94(void *self)
{
    unsigned char *base = (unsigned char *) self;

    if (func_ov112_0229fb70()) {
        func_ov112_0229fae8(self);
        func_0200284c(4, 0, base[0xb6] + 8);
    }

    if (func_ov112_0229fe70(self, 1)) {
        unsigned int a0 = *(unsigned int *) (base + 0xa0);
        unsigned char *ptr = (unsigned char *) a0 + 0x60;
        func_02088df8(1, &data_ov112_022a2098, 0x80, ptr - 8, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_ov095_0229b1c8(base + 0x384, 0x80, ptr, 1);
        func_ov095_0229ae84(base + 0x384, 0x80, ptr);
        if (func_0206fe54()) {
            func_020896b8(1, &data_ov112_022a2080, 0x80, ptr, -1, 1, 0);
        }
        unsigned char b8 = base[0xb8];
        unsigned int a0_2 = *(unsigned int *) (base + 0xa0);
        func_0208ea70(base + 0x4234, 0x5d, b8 + (a0_2 - 0x50));
        unsigned int r5 = func_ov002_0220a4f8(base + 0x4234);
        unsigned int r2 = func_ov002_0220a4d4(base + 0x4234);
        func_ov095_02299b30(base + 0x384, r5, r2);
        ((VTblClass *) (base + 0x4234))->f2();
    }

    if (func_0206fe54()) {
        if (func_ov112_0229fe70(self, 0x1000)) {
            unsigned int r5b = func_ov002_0220a4f8(base + 0x4234);
            unsigned int r2b = func_ov002_0220a4d4(base + 0x4234);
            func_ov002_0220a0b4(base + 0x4448, r5b, r2b);
        }
        func_ov002_02209eb8(base + 0x4448);
    }

    if (func_ov112_0229fe70(self, 1)) {
        if (func_ov112_0229fe70(self, 0x40)) {
            unsigned int f98 = *(unsigned int *) (base + 0x98);
            unsigned int f9c = *(unsigned int *) (base + 0x9c);
            unsigned char b6 = base[0xb6];
            unsigned int delta = f9c - (b6 + 8);
            unsigned char *bc = base + 0xbc;
            *bc = *bc + 1;
            if (*bc & 0x10) {
                func_ov095_0229af58(base + 0x384, f98, delta, 2);
            }
        }
    }

    func_ov002_0220ad18(base + 0x427c, *(unsigned int *) (base + 0xa8));
    return 1;
}
