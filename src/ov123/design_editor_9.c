/* design_editor_9: 19 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229c52c @ 0x0229c52c, 0x4 bytes, Thumb
 * func_ov123_0229c528 @ 0x0229c528, 0x4 bytes, Thumb
 * func_ov123_0229c518 @ 0x0229c518, 0x10 bytes, Thumb
 * func_ov123_0229c470 @ 0x0229c470, 0xa8 bytes, Thumb
 * func_ov123_0229c448 @ 0x0229c448, 0x28 bytes, Thumb
 * func_ov123_0229c3b8 @ 0x0229c3b8, 0x90 bytes, Thumb
 * func_ov123_0229c39c @ 0x0229c39c, 0x1a bytes, Thumb
 * func_ov123_0229c35c @ 0x0229c35c, 0x3e bytes, Thumb
 * func_ov123_0229c30c @ 0x0229c30c, 0x50 bytes, Thumb
 * func_ov123_0229c2dc @ 0x0229c2dc, 0x30 bytes, Thumb
 * func_ov123_0229c248 @ 0x0229c248, 0x94 bytes, Thumb
 * func_ov123_0229c1b8 @ 0x0229c1b8, 0x90 bytes, Thumb
 * func_ov123_0229c174 @ 0x0229c174, 0x44 bytes, Thumb
 * func_ov123_0229c118 @ 0x0229c118, 0x5c bytes, Thumb
 * func_ov123_0229c0c0 @ 0x0229c0c0, 0x56 bytes, Thumb
 * func_ov123_0229c07c @ 0x0229c07c, 0x42 bytes, Thumb
 * func_ov123_0229c044 @ 0x0229c044, 0x38 bytes, Thumb
 * func_ov123_0229bfe0 @ 0x0229bfe0, 0x64 bytes, Thumb
 * func_ov123_0229bfac @ 0x0229bfac, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char pad_A5[0x4f8b];
    unsigned char unk_5030[1];
} UnkStruct_0229c470;

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c2dc;

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c1b8;

struct GameObj {
    unsigned char pad_00[0x98];
    int counter;
};

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c0c0;

struct UnkStruct_0229bfe0 {
    unsigned char pad_00[0x98];
    int unk_98;
    int unk_9C;
    unsigned char pad_A0[6];
    unsigned char unk_A6;
    unsigned char pad_A7[3];
    unsigned char unk_AA;
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char pad_AD[2];
    unsigned char unk_AF;
    unsigned char unk_B0;
    unsigned char pad_B1[2];
    unsigned char unk_B3;
};

extern void func_020ee470(void *parameter0);
extern void func_ov123_0229bf04(void);
extern void func_ov123_0229be60(void *);
extern void func_ov123_0229a278(void *, int);
extern void func_ov123_0229bdfc(void *receiver);
extern int func_0206fca4(void);
extern void func_ov123_0229b508(void *);
extern void func_ov123_0229b3c4(void *);
extern void func_ov123_0229b364(void *);
extern void func_ov123_0229b228(void *);
extern int func_ov123_0229b33c(void *);
extern void func_ov123_0229b204(void *);
extern int func_ov002_0220acc4(unsigned char *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov123_02299954(void *);
extern void func_ov123_02299640(void *, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(void *param, int value);
extern unsigned char *func_ov002_022080a0(void *param, unsigned char value);
extern void func_ov123_0229b65c(void *param);
extern int func_ov123_02299650(int, int);
extern void func_ov123_02299630(int, int);
extern int func_020984e8(void);
extern int func_02099710(int);
extern int func_02095b58(int);
extern int func_020996f8(int);
extern int func_02095b40(int);
extern int func_02095f58(void);
extern void func_ov123_02299664(int arg);
extern int func_020ee45c(int arg);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(int a, int b, int c, int d, int e);
extern void func_020027f0(int);
extern void func_020019f4(void);
extern void *func_ov002_0220ad0c(int);
extern void func_ov002_02207e9c(void *, int, int);
extern int func_ov002_02207f3c(void *p, int a);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov002_0220aacc(void *p, int a);
extern void func_ov123_02299684(void *p);
extern void func_ov123_0229b600(UnkStruct_0229c1b8 *self);
extern void func_ov002_02207e80(void *this, int a, int b, void *c);
extern void *func_ov002_02207f60(void *this);
extern void func_0200284c(int, int, int);
extern void func_ov123_0229b160(struct UnkStruct_0229bfe0 *p, int x);
extern void func_ov123_0229a224(struct UnkStruct_0229bfe0 *p);
extern void func_ov123_02299ec4(struct UnkStruct_0229bfe0 *p);
extern void func_0206fc4c(char value);
extern int func_02095ce0(void);
extern void func_ov002_0220af74(void *);
extern void func_ov123_0229a1e8(void *);
extern void func_ov123_02299e84(void *);
extern int func_02095904(void);
extern void func_020045ac(int);

void func_ov123_0229c35c(int arg);
void func_ov123_0229c07c(void *this);
void func_ov123_0229c044(void *arg);

int func_ov123_0229c52c(void)
{
    return 1;
}

int func_ov123_0229c528(void)
{
    return 1;
}

int func_ov123_0229c518(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov123_0229c470(UnkStruct_0229c470 *self)
{
    int r;

    func_ov123_0229bf04();
    func_ov123_0229be60(self);
    self->unk_A4 = 0x22;
    func_ov123_0229a278(self, 0);
    func_ov123_0229bdfc(self);

    r = func_0206fca4();
    switch (r) {
        case 2:
            func_ov123_0229b508(self);
            break;
        case 3:
            func_ov123_0229b3c4(self);
            break;
    }

    func_ov123_0229b364(self);
    func_ov123_0229b228(self);
    func_ov123_0229b33c(self);
    func_ov123_0229b204(self);

    func_ov002_0220acc4(self->unk_5030);
    func_ov002_02207f20(self, 0xb, 4, 0, 0x30);

    func_02002708(6);
    func_02002708(4);

    func_ov123_02299954(self);
    func_ov123_0229c07c(self);
    func_ov123_02299640(self, 1);
    func_ov002_02208090(self, 1);
}

void func_ov123_0229c448(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0(param, 2);
        func_ov123_0229b65c(param);
    }
    func_ov123_0229c07c(param);
}

void func_ov123_0229c3b8(int param)
{
    if (func_ov123_02299650(param, 0x8000) == 0 && func_ov123_02299650(param, 0x10000) == 0) {
        func_ov002_02208090((void *) param, 4);
        func_ov123_0229c35c(param);
        return;
    }

    {
        int r4 = func_020984e8();
        if (func_ov123_02299650(param, 0x8000) != 0) {
            if (func_02095b58(func_02099710(r4)) != 0) {
                func_ov123_02299630(param, 0x8000);
            } else {
                return;
            }
        }
        if (func_ov123_02299650(param, 0x10000) != 0) {
            if (func_02095b40(func_020996f8(r4)) != 0) {
                func_ov123_02299630(param, 0x8000);
            } else {
                return;
            }
        }
        func_ov002_02208090((void *) param, 3);
    }
}

void func_ov123_0229c39c(int param)
{
    int r4 = param;
    if (func_02095f58() == 0) {
        func_ov002_02208090((void *) r4, 4);
    }
}

void func_ov123_0229c35c(int arg)
{
    func_ov123_02299664(arg);
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 0xb, 0, 0, 0x30);
    func_ov123_0229c07c((void *) arg);
    func_ov002_02208090((void *) arg, (unsigned char) 5);
}

void func_ov123_0229c30c(int r0)
{
    int r4 = r0;
    if (func_ov002_02207f3c((void *) r4, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_020027f0(3);
        func_ov002_022080a0((void *) r4, 5);
        func_020019f4();
        func_ov123_02299630(r4, 1);
        func_ov002_0220ad0c(r4 + 0x5030);
    } else {
        func_ov123_0229c07c((void *) r4);
    }
}

void func_ov123_0229c2dc(UnkStruct_0229c2dc *self)
{
    int zero = 0;
    func_ov002_02207e9c(self, zero, zero);
    func_ov002_02208090(self, 7);
    self->unk_98 = 0;
    func_ov123_02299640(self, 0x400);
}

void func_ov123_0229c248(void *param)
{
    if (func_ov002_02207f3c(param, -1) != 0) {
        func_ov002_02207eb4(param, 0, 0);
        if (func_ov123_02299650((int) param, 8) != 0) {
            func_ov002_0220aacc((char *) param + 0x5030, 0x87);
        } else {
            func_ov002_0220aacc((char *) param + 0x5030, 0x22);
        }
        func_ov002_02208090(param, 8);
    }

    if (func_ov123_02299650((int) param, 0x400) != 0) {
        if (*(int *) ((char *) param + 0x98) < 0x10) {
            *(int *) ((char *) param + 0x98) = *(int *) ((char *) param + 0x98) + 2;
        } else {
            func_ov123_02299684(param);
            *(int *) ((char *) param + 0x98) = 0x10;
            func_ov123_02299630((int) param, 0x400);
        }
    }
    func_ov123_0229c044(param);
}

void func_ov123_0229c1b8(UnkStruct_0229c1b8 *self)
{
    if (func_ov002_02207f48((void *) self, -1) != 0) {
        func_ov002_022080a0((void *) self, 2);
        func_ov123_0229b600(self);
        if (func_ov123_02299650((int) self, 0x400) != 0) {
            func_ov123_02299684((void *) self);
            self->unk_98 = 0x10;
            func_ov123_02299630((int) self, 0x400);
        }
    } else {
        if (func_ov123_02299650((int) self, 0x400) != 0) {
            if (self->unk_98 < 0x10) {
                self->unk_98 = self->unk_98 + 2;
            } else {
                func_ov123_02299684((void *) self);
                self->unk_98 = 0x10;
                func_ov123_02299630((int) self, 0x400);
            }
        }
    }
    func_ov123_0229c044((void *) self);
}

void func_ov123_0229c174(int param)
{
    int *p;
    func_ov123_02299664((int) ((void *) param));
    if (func_ov123_02299650(param, 0x00020000)) {
        func_ov123_02299630(param, 0x00020000);
        func_ov123_02299954((void *) param);
    }
    func_ov002_02207e9c((void *) param, 0, 0);
    func_ov002_02208090((void *) param, 10);
    p = (int *) (param + 0x98);
    *p = 0x10;
}

void func_ov123_0229c118(struct GameObj *self)
{
    if (func_ov002_02207f3c(self, -1)) {
        func_ov002_02207eb4(self, 0, 0);
        func_ov002_0220acc4((unsigned char *) ((char *) self + 0x5030));
        func_ov002_02208090(self, 0xb);
    }
    if (self->counter >= 2) {
        self->counter = self->counter - 2;
    } else {
        self->counter = 0;
    }
    func_ov123_0229c044(self);
}

void func_ov123_0229c0c0(UnkStruct_0229c0c0 *self)
{
    if (func_ov002_02207f48(self, -1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov123_0229b65c(self);
        self->unk_98 = 0;
    } else {
        if (self->unk_98 >= 2) {
            self->unk_98 -= 2;
        } else {
            self->unk_98 = 0;
        }
    }
    func_ov123_0229c044(self);
}

void func_ov123_0229c07c(void *this)
{
    func_ov002_02207e80(this, 6, 0, *(void **) ((char *) this + 0x98));
    func_ov002_02207e80(this, 4, 0, *(void **) ((char *) this + 0x98));
    func_ov002_02207e80(this, 3, 0, *(void **) ((char *) this + 0x98));
    *(void **) ((char *) this + 0x94) = func_ov002_02207f60(this);
}

void func_ov123_0229c044(void *arg)
{
    int *p;
    p = (int *) ((char *) arg + 0x98);
    func_0200284c(6, 0, -*p);
    func_0200284c(4, 0, -*p);
    func_0200284c(3, 0, -*p);
}

void func_ov123_0229bfe0(struct UnkStruct_0229bfe0 *p)
{
    func_ov123_0229b160(p, 1);
    p->unk_9C = 0;
    p->unk_A6 = 0x22;
    func_ov123_0229a224(p);
    p->unk_AA = 0;
    p->unk_AB = 0;
    p->unk_AC = 0;
    func_ov123_02299ec4(p);
    p->unk_AF = 0x10;
    p->unk_B0 = 0x10;
    func_0206fc4c(0);
    func_02095ce0();
    p->unk_98 = 0;
    p->unk_B3 = 0;
}

void func_ov123_0229bfac(void *self)
{
    func_ov002_0220af74((char *) self + 0x5030);
    func_ov123_0229a1e8(self);
    func_ov123_02299e84(self);
    func_02095904();
    if (func_0206fca4() == 3) {
        func_020045ac(0);
    }
}
