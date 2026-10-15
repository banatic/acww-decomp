/* func_020a5750 @ 0x020a5750, 0x448 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a5750_2;

struct UnkStruct_020a5750 {
    char pad_00[0x64];
    int unk_64;
};

struct Thr {
    unsigned long unk_00;
    unsigned long unk_04;
    unsigned long unk_08;
};

struct Nm {
    unsigned short h;
    unsigned char rest[0xc];
};

extern struct UnkStruct_020a5750 *data_020ccf94;
extern unsigned char data_021f42f0;
extern unsigned long data_021f42f8;
extern int data_021f4308;
extern struct Thr data_021f4314;
extern struct UnkStruct_020a5750_2 data_021f4320;
extern struct Nm data_021dc7aa;

extern int func_020a5bb8(struct UnkStruct_020a5750_2 *o, int i);
extern void func_020a5bc4(struct UnkStruct_020a5750_2 *o, int i, int v);
extern unsigned long func_020a5bd8(struct UnkStruct_020a5750_2 *o);
extern unsigned long OSi_GetSystemErrno(struct UnkStruct_020a5750_2 *o);
extern void func_020a5c30(struct UnkStruct_020a5750_2 *o, unsigned long v);
extern unsigned char func_020a5730(struct UnkStruct_020a5750_2 *o);
extern void func_020a5738(struct UnkStruct_020a5750_2 *o, unsigned char v);
extern unsigned long func_020a5740(struct UnkStruct_020a5750_2 *o);
extern void func_020a5748(struct UnkStruct_020a5750_2 *o, unsigned long v);
extern void func_020a5728(struct UnkStruct_020a5750_2 *o, unsigned long v);

extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *p);
extern int func_0203df10(void);
extern int func_0203dee8(void);
extern void func_0206f5b0(void);
extern void func_020b8df0(unsigned long i);
extern void func_020b8e10(unsigned long i);
extern void func_020b8dd8(void);
extern void func_020a76cc(unsigned char *p);
extern void func_020a76c8(unsigned char *p);
extern void func_020a76ac(unsigned char *out, int a, int b, int c);
extern void func_02073820(struct UnkStruct_020a5750 *g);
extern void func_020737f0(struct UnkStruct_020a5750 *g, unsigned char *p, int n);
extern void func_02073770(struct UnkStruct_020a5750 *g, int a, int b);
extern int func_02073918(struct UnkStruct_020a5750 *g, int i);
extern void func_02073150(struct UnkStruct_020a5750 *g, int v);
extern int func_020740b4(void);
extern int func_02098420(unsigned long a);
extern void *func_0209847c(unsigned long a);
extern void *func_02099688(void *p);
extern int func_0208829c(void *p);
extern struct Nm *func_020882ec(void *record);
extern int memcmp(const void *a, const void *b, int n);
extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void *);
extern int func_020ec1f8(void);
extern int func_020732c0(struct UnkStruct_020a5750 *g);
extern void func_020732cc(struct UnkStruct_020a5750 *g, int v);
extern int func_020b6434(int a, int b, int c, int d);
extern int func_020b63f4(int dst, unsigned char val, struct Thr *src, unsigned int extra, short p1, unsigned char p2,
                         unsigned char p3);
extern void func_020a13c4(unsigned long a);
extern int func_020b5ee4(int a, int b);
extern void func_020a18e8(void);
extern void func_020a18c4(void);
extern void func_020a18dc(void);
extern void func_020a18b8(void);
extern void func_020a18a0(void);
extern void func_020a01e0(int a);

void func_020a5750(struct UnkStruct_020a5750_2 *self)
{
    struct UnkStruct_020a5750 *g;
    struct UnkStruct_020a5750 *h;
    struct Nm *r;
    struct Nm *nm;
    void *q;
    int n;
    int flag;
    int x;
    int f;
    unsigned long t;
    int m;
    unsigned long k;
    unsigned long e;
    unsigned long v;
    unsigned short mask;
    unsigned char c;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;

    g = data_020ccf94;

    n = g->unk_64;
    if (func_020a5bb8(self, n) == 0) {
        func_020a5748(self, 0);
        func_020a5bc4(self, n, 1);
    }

    n = g->unk_64;
    if (func_020a5bb8(self, n) == 1) {
        flag = 0;
        x = func_020b65c4();
        if (x != 0x2e && x != 0xc && x != 0xd && x != 0xe && x != 0x2f &&
            func_020b5e84((unsigned char *) func_020b5e10()) == 0x3f && data_021f42f0 == 0 && func_0203df10()) {
            flag = 1;
        }
        t = func_020a5bd8(self);
        if (flag) {
            func_020a5738(self, 0x28);
            func_020a5748(self, 0);
            if (n != 0) {
                func_020a76cc(&b0);
                func_020a76ac(&b0, 2, 4, OSi_GetSystemErrno(self));
                h = data_020ccf94;
                func_02073820(h);
                func_020737f0(h, &b0, 1);
                func_02073770(h, 0xc, 0);
                func_020a76c8(&b0);
            }
            func_020b8df0(t);
            func_020a5bc4(self, n, 2);
            func_02073150(g, func_020740b4());
        } else {
            v = func_020a5740(self) + 1;
            if (v >= 0xa0) {
                if (n == 0) {
                    func_020a5bc4(self, 0, 3);
                } else {
                    func_020a76cc(&b1);
                    func_020a76ac(&b1, 3, 4, OSi_GetSystemErrno(self));
                    h = data_020ccf94;
                    func_02073820(h);
                    func_020737f0(h, &b1, 1);
                    func_02073770(h, 0xc, 0);
                    func_020a5bc4(self, n, 6);
                    func_020a76c8(&b1);
                }
                func_0206f5b0();
                func_020a5748(self, 0);
            } else {
                func_020a5748(self, v);
            }
            func_020b8e10(t);
        }
    }

    m = g->unk_64;
    x = func_020a5bb8(self, m);
    if (x == 2) {
        func_020b8df0(func_020a5bd8(self));
    } else if (x == 4) {
        func_0203dee8();
        func_0206f5b0();
        func_020b8dd8();
        func_020a5738(self, 0);
        if (m != 0) {
            func_020a76cc(&b2);
            func_020a76ac(&b2, 6, 4, OSi_GetSystemErrno(self));
            h = data_020ccf94;
            func_02073820(h);
            func_020737f0(h, &b2, 1);
            func_02073770(h, 0xc, 0);
            func_020a76c8(&b2);
        }
        func_020a5bc4(self, m, 6);
    } else if (x == 5) {
        k = func_020a5bd8(self);
        func_020b8df0(k);
        c = func_020a5730(&data_021f4320);
        if (c != 0) {
            func_020a5738(&data_021f4320, c - 1);
        }
        flag = 0;
        if (func_020a5730(self) != 0) {
            flag = 1;
        }
        if (!flag) {
            if (k == 0) {
                e = OSi_GetSystemErrno(self);
                if (func_02098420(e + 3) == 0) {
                    flag = 1;
                    if (m == 0) {
                        x = func_020ec1f8();
                        mask = (unsigned short) (1 << e);
                        if (mask != (mask & x)) {
                            f = func_020732c0(g);
                            if ((f & 4) == 0) {
                                func_020732cc(g, f | 4);
                            }
                        }
                    }
                }
            } else if (k == 1) {
                func_020a5c30(self, OSi_GetSystemErrno(self));
            }
        }
        if (!flag) {
            func_020a5728(self, func_020a5bd8(self));
            func_020a13c4(OSi_GetSystemErrno(self));
            func_020b5ee4(func_020b5e10(), 0);
            if (func_020a5bd8(self) == 0) {
                nm = &data_021dc7aa;
                q = func_0209847c(OSi_GetSystemErrno(self) + 3);
                if (q != 0 && func_0208829c(func_02099688(q)) != 0 &&
                    ((r = func_020882ec((void *) func_02099688(q))), r->h == nm->h) && memcmp(r->rest, nm->rest, 0xc) == 0) {
                    func_020b6434(func_020b5e10(), 0x2f, 2, 2);
                } else {
                    if ((data_021f42f8 & 1) == 0) {
                        data_021f4314.unk_00 = 0x10000;
                        data_021f4314.unk_04 = 0;
                        data_021f4314.unk_08 = 0x5000;
                        __register_global_object((void *) (&data_021f4314), (((void *) func_020012dc)),
                                                 (void *) (&data_021f4308));
                        data_021f42f8 |= 1;
                    }
                    func_020b63f4(func_020b5e10(), 0xd, &data_021f4314, 0x800000, 0, 2, 2);
                }
            } else {
                func_020b6434(func_020b5e10(), 0x2e, 2, 3);
            }

            if (func_02073918(g, 0)) {
                if (k == 0) {
                    func_020a18e8();
                } else if (k == 1) {
                    func_020a18c4();
                }
            } else {
                if (k == 0) {
                    func_020a18dc();
                } else if (k == 1) {
                    func_020a18b8();
                } else if (k == 2) {
                    func_020a18a0();
                    func_020a01e0(0);
                } else {
                    func_020a18a0();
                    func_020a01e0(1);
                }
            }

            if (m != 0) {
                func_020a76cc(&b3);
                func_020a76ac(&b3, 6, 4, OSi_GetSystemErrno(self));
                h = data_020ccf94;
                func_02073820(h);
                func_020737f0(h, &b3, 1);
                func_02073770(h, 0xc, 0);
                func_020a76c8(&b3);
            }
            func_020a5bc4(self, m, 6);
        }
    }
}
