/* letter_storage_7: 22 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229e110 @ 0x0229e110, 0x70 bytes, Thumb
 * func_ov105_0229e0d0 @ 0x0229e0d0, 0x40 bytes, Thumb
 * func_ov105_0229e0a0 @ 0x0229e0a0, 0x30 bytes, Thumb
 * func_ov105_0229e070 @ 0x0229e070, 0x30 bytes, Thumb
 * func_ov105_0229e018 @ 0x0229e018, 0x58 bytes, Thumb
 * func_ov105_0229dfd0 @ 0x0229dfd0, 0x48 bytes, Thumb
 * func_ov105_0229df7c @ 0x0229df7c, 0x54 bytes, Thumb
 * func_ov105_0229df20 @ 0x0229df20, 0x5c bytes, Thumb
 * func_ov105_0229dee4 @ 0x0229dee4, 0x3c bytes, Thumb
 * func_ov105_0229de94 @ 0x0229de94, 0x50 bytes, Thumb
 * func_ov105_0229de74 @ 0x0229de74, 0x20 bytes, Thumb
 * func_ov105_0229de3c @ 0x0229de3c, 0x38 bytes, Thumb
 * func_ov105_0229ddd4 @ 0x0229ddd4, 0x68 bytes, Thumb
 * func_ov105_0229dd68 @ 0x0229dd68, 0x6c bytes, Thumb
 * func_ov105_0229dd30 @ 0x0229dd30, 0x38 bytes, Thumb
 * func_ov105_0229dcc4 @ 0x0229dcc4, 0x6c bytes, Thumb
 * func_ov105_0229dbc0 @ 0x0229dbc0, 0x104 bytes, Thumb
 * func_ov105_0229db8c @ 0x0229db8c, 0x34 bytes, Thumb
 * func_ov105_0229db70 @ 0x0229db70, 0x1c bytes, Thumb
 * func_ov105_0229db34 @ 0x0229db34, 0x3c bytes, Thumb
 * func_ov105_0229db14 @ 0x0229db14, 0x20 bytes, Thumb
 * func_ov105_0229dafc @ 0x0229dafc, 0x16 bytes, Thumb
 */

struct UnkStruct_0229e110 {
    char pad_00[0x2BA];
    unsigned char unk_2BA;
    char pad_2BB[0x2C0 - 0x2BA - 1];
    unsigned char unk_2C0;
    char pad_2C1[0x24A4 - 0x2C0 - 1];
    char unk_24A4;
};

struct UnkStruct_0229e070 {
    char pad_00[0x2bd];
    unsigned char unk_2BD;
    char pad_2BE[0x24a4 - 0x2be];
    char unk_24A4;
};

struct Global {
    unsigned short pad_00;
    unsigned short flags;
};

struct UnkStruct_0229dbc0 {
    char pad_00[0x2c2];                 // 0x0000
    unsigned char unk_2C2;              // 0x02c2
    char pad_2C3[0x24a4 - 0x2c2 - 1];   // 0x02c3
    char unk_24A4;                      // 0x24a4
    char pad_24A5[0x5fb8 - 0x24a4 - 1]; // 0x24a5
    char unk_5FB8;                      // 0x5fb8
};

extern int func_0208e484(void *);
extern int func_ov105_0229d750(struct UnkStruct_0229e110 *, int);
extern void func_ov105_0229c668(struct UnkStruct_0229e110 *);
extern int func_ov105_0229d73c(struct UnkStruct_0229e110 *, int);
extern void func_ov105_0229cd5c(struct UnkStruct_0229e110 *);
extern void func_ov105_0229c3ec(struct UnkStruct_0229e110 *);
extern void func_ov105_0229cd9c(void *ptr);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern void func_ov105_0229d908(void *param1, unsigned char param2);
extern int func_ov002_02209f9c(void *param1);
extern void func_ov105_0229d17c(void *obj);
extern void func_ov094_022999d8(void);
extern int func_ov105_0229d650(void *, int arg1);
extern void func_ov105_0229d230(void *);
extern void func_ov105_0229d870(void *, int, int);
extern int func_ov002_02209f70(void *p);
extern void func_ov105_0229d094(void *p, unsigned char b);
extern void func_ov105_0229c330(void *p, int x);
extern int func_ov105_0229c340(void *ptr, int arg);
extern void func_ov105_0229c320(void *ptr, int arg);
extern void func_ov094_022999c0(void);
extern int func_ov002_02209d8c(void *);
extern void func_ov105_0229d154(void *);
extern void func_ov105_0229d0d4(void *, unsigned char);
extern int func_0206fe54(void);
extern void func_ov105_0229cdf0(int);
extern int func_ov002_02208e28(int);
extern int func_ov002_0220909c(unsigned char *);
extern void func_ov002_022096d8(unsigned char *, int);
extern int func_ov002_02207d24(unsigned char *, int);
extern int func_0208e4bc(unsigned char *);
extern void func_ov105_0229cdbc(unsigned char *);
extern int func_ov002_02208e18(void *);
extern void func_ov105_0229cc5c(void *);
extern int func_ov002_0220b8ac(void *p, int x);
extern void func_0208e5cc(void *p);
extern int func_ov002_0220b57c(const char *p);
extern int func_ov002_0220b5ec(const char *p, int);
extern int func_ov002_0220b59c(const char *p, int);
extern void func_ov002_0220a0b4(const char *p, int, int);
extern void func_ov002_02208090(const char *p, int);
extern unsigned char *func_ov002_022080a0(const char *p, unsigned char value);
extern int func_ov002_0220a700(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int idx);
extern int func_ov002_0220a72c(char *p, int idx);
extern int func_ov094_0229b19c(void *);
extern int func_ov002_02208054(int self, int a);
extern void func_ov105_0229da9c(int self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_0220a784(int ptr, int a);
extern void func_ov105_0229c62c(int self);
extern void func_ov105_0229c5fc(int self);
extern int func_ov002_02208014(void *receiver);
extern void func_ov002_0220a1dc(void *this);
extern void func_ov105_0229cfc0(void *this);
extern void *func_ov002_02208008(void *this);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern void func_ov105_0229cf10(void *this, int a, int b);
extern struct Global data_021fbe40;
extern void func_ov105_0229d404(void *);
extern void func_ov105_0229d03c(void *);
extern void func_ov105_0229d3b4(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);

void func_ov105_0229db14(int param);
void func_ov105_0229dafc(int param);

void func_ov105_0229e110(struct UnkStruct_0229e110 *p)
{
    if (func_0208e484(&p->unk_24A4)) {
        if (func_ov105_0229d750(p, p->unk_2BA)) {
            func_ov105_0229c668(p);
        } else if (func_ov105_0229d73c(p, p->unk_2BA)) {
            int v = p->unk_2BA - 0x3e;
            if (v == p->unk_2C0) {
                func_ov105_0229cd5c(p);
            } else {
                p->unk_2C0 = v;
                func_ov105_0229c3ec(p);
            }
        } else {
            func_ov105_0229cd5c(p);
        }
    }
}

void func_ov105_0229e0d0(void *self)
{
    if (func_0208e484((char *) self + 0x24a4) != 0) {
        func_ov105_0229cd9c(self);
        if (*(unsigned char *) ((char *) self + 0x2b4) == 1) {
            func_ov002_02208098(self, 8);
        } else {
            func_ov002_02208098(self, 7);
        }
    }
}

void func_ov105_0229e0a0(void *param1)
{
    if (func_ov002_02209f9c((char *) param1 + 0x24a4)) {
        func_ov105_0229d908(param1, *(unsigned char *) ((char *) param1 + 0x2ba));
        func_ov002_02208098(param1, 0x11);
    }
}

void func_ov105_0229e070(struct UnkStruct_0229e070 *obj)
{
    if (func_0208e484(&obj->unk_24A4)) {
        func_ov002_02208098(obj, obj->unk_2BD);
    }
    func_ov105_0229d17c(obj);
}

void func_ov105_0229e018(unsigned char *p)
{
    if (func_ov002_02209f9c(p + 0x24a4) == 0) {
        unsigned char bc = p[0x2bc];
        unsigned char ba = p[0x2ba];
        if (ba == bc) {
            func_ov105_0229d650(p, bc);
            func_ov105_0229d230(p);
            func_ov002_02208098(p, 7);
            func_ov094_022999d8();
        } else {
            func_ov105_0229d870(p, bc, 4);
        }
    } else {
        func_ov105_0229d17c(p);
    }
}

void func_ov105_0229dfd0(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x24A4) == 0) {
        func_ov105_0229d094(p, *(unsigned char *) ((char *) p + 0x2BC));
        func_ov105_0229c330(p, 0x40);
        func_ov002_02208098(p, 0x14);
        func_ov105_0229d230(p);
    } else {
        func_ov002_02208098(p, 7);
    }
}

void func_ov105_0229df7c(char *p)
{
    if (func_0208e484(p + 0x24a4)) {
        func_ov002_02208098(p, *((unsigned char *) (p + 0x2bd)));
    }
    if (func_ov002_02209f9c(p + 0x24a4)) {
        if (func_ov105_0229c340(p, 0x40)) {
            func_ov105_0229c320(p, 0x40);
            func_ov094_022999c0();
        }
        func_ov105_0229d17c(p);
    }
}

void func_ov105_0229df20(unsigned char *self)
{
    if (func_ov002_02209d8c(self + 0x248c) != 0) {
        if (func_ov105_0229c340(self, 0x2000) != 0) {
            func_ov105_0229c320(self, 0x2000);
            func_ov105_0229d154(self);
        } else {
            func_ov105_0229d0d4(self, self[0x2b7]);
            func_ov105_0229db14((int) self);
            func_ov094_022999d8();
        }
    } else {
        func_ov105_0229d154(self);
    }
}

void func_ov105_0229dee4(int param)
{
    if (func_ov002_02208e28(param + 0x2508) != 0) {
        if (func_0206fe54() != 0) {
            func_ov105_0229cdf0(param);
            func_ov002_02208098((void *) param, 0xb);
        } else {
            func_ov002_02208098((void *) param, 6);
        }
    }
}

void func_ov105_0229de94(unsigned char *p)
{
    if (func_ov002_0220909c(p + 0x2508) != 0) {
        func_ov002_022096d8(p + 0x2508, 0);
        func_ov002_02207d24(p + 0x23bc, 1);
        if (func_0208e4bc(p + 0x24a4) != 0) {
            func_ov105_0229cdbc(p);
        }
        func_ov002_02208098((void *) p, 0x18);
    }
}

void func_ov105_0229de74(void *arg0)
{
    if (func_ov002_02208e18((char *) arg0 + 0x2508) != 0) {
        func_ov105_0229cc5c(arg0);
    }
}

void func_ov105_0229de3c(unsigned char *p)
{
    if (func_ov002_0220b8ac(p + 0x28fc, 0)) {
        func_ov002_02208098(p, p[0x2bd]);
        func_0208e5cc(p + 0x24a4);
    }
}

void func_ov105_0229ddd4(char *self)
{
    if (func_ov002_0220b57c(self + 0x2d40) != 0) {
        if (func_0208e4bc((unsigned char *) (self + 0x24a4)) != 0) {
            int a = func_ov002_0220b5ec(self + 0x2d40, 1);
            int b = func_ov002_0220b59c(self + 0x2d40, 1);
            func_ov002_0220a0b4(self + 0x24a4, a, b);
        }
    } else {
        func_ov105_0229cfc0((void *) self);
        func_ov002_02208090(self, 9);
        func_ov002_022080a0(self, 1);
    }
}

void func_ov105_0229dd68(char *arg)
{
    if (func_ov002_0220a700(arg + 0x5fb8) != 0) {
        if (func_0208e4bc((unsigned char *) (arg + 0x24a4)) != 0) {
            int a = func_ov002_0220a6e0(arg + 0x5fb8);
            int b = func_ov002_0220a768(arg + 0x5fb8, -1);
            int c = func_ov002_0220a72c(arg + 0x5fb8, -1);
            func_ov002_0220a0b4((const char *) (arg + 0x24a4), a + b, a + c);
        }
    } else {
        func_ov105_0229cfc0((void *) arg);
        func_ov002_022080a0((const char *) arg, 1);
    }
}

void func_ov105_0229dd30(char *p)
{
    if (func_ov094_0229b19c(p + 0xd5c)) {
        func_ov105_0229c330(p, 0x1000);
        p[0x2b4] = 0;
        func_ov105_0229db14((int) p);
    }
}

void func_ov105_0229dcc4(int self)
{
    unsigned int ok;
    if (func_ov002_02208054(self, 1)) {
        func_ov105_0229da9c(self);
        return;
    }
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    if (func_ov002_0220a784(self + 0x5fb8, 3)) {
        func_ov105_0229c62c(self);
    }
    if (func_ov002_0220a784(self + 0x5fb8, 4)) {
        func_ov105_0229c5fc(self);
    }
}

void func_ov105_0229dbc0(struct UnkStruct_0229dbc0 *self)
{
    unsigned short flags;
    unsigned char old;
    void *p;
    int a;
    int b;

    if (func_ov002_02208014(self) != 0) {
        func_ov105_0229dafc((int) self);
        return;
    }

    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov002_0220a1dc(&self->unk_24A4);
        func_ov002_02208098(self, 0x1f);
        return;
    }

    if (flags & 2) {
        func_ov105_0229cfc0(self);
        func_ov105_0229c5fc((int) self);
        return;
    }

    if (flags & 8) {
        func_ov105_0229cfc0(self);
        func_ov105_0229c62c((int) self);
        return;
    }

    old = self->unk_2C2;
    p = func_ov002_02208008(self);
    if (func_ov002_022088ac(p) != 0) {
        if (self->unk_2C2 != 0) {
            self->unk_2C2--;
        }
    } else {
        if (func_ov002_0220889c(p) != 0) {
            if (self->unk_2C2 < 1) {
                self->unk_2C2++;
            }
        }
    }

    if (old != self->unk_2C2) {
        if (self->unk_2C2 != 0) {
            a = func_ov002_0220a768((char *) (&self->unk_5FB8), 4);
            b = func_ov002_0220a72c((char *) (&self->unk_5FB8), 4);
            func_ov105_0229cf10(self, a, b);
        } else {
            a = func_ov002_0220a768((char *) (&self->unk_5FB8), 3);
            b = func_ov002_0220a72c((char *) (&self->unk_5FB8), 3);
            func_ov105_0229cf10(self, a, b);
        }
    }
}

void func_ov105_0229db8c(unsigned char *this)
{
    if (func_0208e484((void *) (this + 0x24a4)) != 0) {
        if (this[0x2c2] != 0) {
            func_ov105_0229c5fc((int) this);
        } else {
            func_ov105_0229c62c((int) this);
        }
    }
}

void func_ov105_0229db70(void *p)
{
    func_ov105_0229cfc0(p);
    func_ov105_0229d404(p);
    func_ov002_02208098(p, 0);
}

void func_ov105_0229db34(void *p)
{
    unsigned char *base = (unsigned char *) p;
    base[0x2b6] = 0x40;
    func_ov105_0229d03c(p);
    func_ov002_02207fc0(p);
    func_ov105_0229d230(p);
    func_ov002_02208098(p, 7);
    func_ov105_0229d3b4(p, base[0x2ba]);
}

void func_ov105_0229db14(int param)
{
    if (func_0206fe60()) {
        func_ov105_0229db70((void *) param);
    } else {
        func_ov105_0229db34((void *) param);
    }
}

void func_ov105_0229dafc(int param)
{
    func_ov105_0229cfc0((void *) param);
    func_ov002_02208098((void *) param, 0x1d);
}
