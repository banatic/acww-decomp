/* birthday_screen_3: 33 functions, module ov137
 * mwccarm 1.2/base -O4,s
 * func_ov137_0229cf28 @ 0x0229cf28, 0x8 bytes, Thumb
 * func_ov137_0229cf0c @ 0x0229cf0c, 0x1c bytes, Thumb
 * func_ov137_0229cefc @ 0x0229cefc, 0x10 bytes, Thumb
 * func_ov137_0229ceb0 @ 0x0229ceb0, 0x4c bytes, Thumb
 * func_ov137_0229ce90 @ 0x0229ce90, 0x20 bytes, Thumb
 * func_ov137_0229ce70 @ 0x0229ce70, 0x20 bytes, Thumb
 * func_ov137_0229cdf4 @ 0x0229cdf4, 0x7c bytes, Thumb
 * func_ov137_0229cd5c @ 0x0229cd5c, 0x98 bytes, Thumb
 * func_ov137_0229cd20 @ 0x0229cd20, 0x3c bytes, Thumb
 * func_ov137_0229cce4 @ 0x0229cce4, 0x3c bytes, Thumb
 * func_ov137_0229cc80 @ 0x0229cc80, 0x64 bytes, Thumb
 * func_ov137_0229cbe8 @ 0x0229cbe8, 0x98 bytes, Thumb
 * func_ov137_0229cb90 @ 0x0229cb90, 0x58 bytes, Thumb
 * func_ov137_0229cb48 @ 0x0229cb48, 0x48 bytes, Thumb
 * func_ov137_0229cb20 @ 0x0229cb20, 0x28 bytes, Thumb
 * func_ov137_0229cab8 @ 0x0229cab8, 0x68 bytes, Thumb
 * func_ov137_0229ca90 @ 0x0229ca90, 0x28 bytes, Thumb
 * func_ov137_0229ca2c @ 0x0229ca2c, 0x62 bytes, Thumb
 * func_ov137_0229ca0c @ 0x0229ca0c, 0x20 bytes, Thumb
 * func_ov137_0229c9cc @ 0x0229c9cc, 0x40 bytes, Thumb
 * func_ov137_0229c9b4 @ 0x0229c9b4, 0x16 bytes, Thumb
 * func_ov137_0229c998 @ 0x0229c998, 0x1c bytes, Thumb
 * func_ov137_0229c978 @ 0x0229c978, 0x20 bytes, Thumb
 * func_ov137_0229c92c @ 0x0229c92c, 0x4c bytes, Thumb
 * func_ov137_0229c900 @ 0x0229c900, 0x2c bytes, Thumb
 * func_ov137_0229c8d4 @ 0x0229c8d4, 0x2c bytes, Thumb
 * func_ov137_0229c8a8 @ 0x0229c8a8, 0x2c bytes, Thumb
 * func_ov137_0229c890 @ 0x0229c890, 0x16 bytes, Thumb
 * func_ov137_0229c854 @ 0x0229c854, 0x3c bytes, Thumb
 * func_ov137_0229c834 @ 0x0229c834, 0x20 bytes, Thumb
 * func_ov137_0229c7d8 @ 0x0229c7d8, 0x5c bytes, Thumb
 * func_ov137_0229c794 @ 0x0229c794, 0x44 bytes, Thumb
 * func_ov137_0229c750 @ 0x0229c750, 0x44 bytes, Thumb
 */

typedef struct UnkStruct_0229cdf4 UnkStruct_0229cdf4;

struct UnkStruct_0229cdf4 {
    unsigned char pad_00[0xf8];
    unsigned char unk_F8;
    unsigned char pad_F9[0x2c4 - 0xf8 - 1];
    unsigned char unk_2C4;
};

typedef struct {
    char pad_00[2];
    unsigned short flags;
} SomeGlobal;

struct UnkStruct_0229cb20 {
    char pad_00[0x94];
    char unk_94[1];
    char pad_95[0x2b76 - 0x94 - 1];
    unsigned char unk_2B76;
};

struct UnkStruct_0229c854;

struct UnkStruct_0229c854 {
    char pad_00[0x2c4];
    int unk_2C4;
};

extern void func_ov002_0220af74(void *);
extern void func_ov134_0229bcac(void *);
extern void func_ov134_0229bbe8(int);
extern void func_02001c08(unsigned char mode);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned int layer, int a, int b, int c);
extern int func_ov134_0229baec(void *);
extern void func_ov134_0229ba10(void *, int);
extern int func_ov134_0229b954(void *);
extern void func_ov002_0220af94(void *receiver);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(UnkStruct_0229cdf4 *p, int a);
extern int func_ov002_0220a784(void *p, int a);
extern int func_ov134_0229ab2c(void *p, unsigned char a, unsigned char b);
extern int func_ov134_0229a1f0(int ptr, int b1, int b2);
extern void func_ov134_02299b18(void *, unsigned char);
extern int func_ov134_02299a84(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov134_02299af0(void *ptr, unsigned char val);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *arg);
extern int func_ov137_0229c58c(void *arg, int value);
extern void func_ov137_0229c6e4(void *arg);
extern void func_ov137_0229c650(void *arg);
extern void func_ov137_0229c734(void *arg);
extern int func_ov134_022997dc(void *, int);
extern void func_ov137_0229c564(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned short data_021fbe40[];
extern void func_ov134_02299a90(void *);
extern int func_ov134_02299a60(void *);
extern void func_ov137_0229c628(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov137_0229d0e0(void *);
extern int func_0208e484(void *object);
extern int func_ov134_02299b70(void *object);
extern int func_ov134_022997b0(void *object);
extern void func_ov137_0229c668(void *);
extern int func_ov002_0220a700(void *ptr);
extern int func_0208e4bc(void *ptr);
extern int func_ov002_0220a6e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int);
extern int func_ov002_0220a72c(void *ptr, int);
extern unsigned char *func_ov002_022080a0(void *ptr, unsigned char value);
extern int func_ov134_0229a4e4(void *);
extern int func_ov134_0229a24c(char *p);
extern int func_ov134_0229a8a0(char *p);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void *func_ov002_0220a720(void *ptr, int n);
extern void func_ov002_02208090(void *ptr, int n);
extern void *func_020984e8(void);
extern void func_ov134_0229bbdc(void *dst, void *src);
extern void func_020992d0(void *ptr, int a, int b);
extern void func_ov134_0229a5c8(char *a, int b);
extern void func_ov137_0229c554(void *, int);
extern void func_ov134_0229a3e4(void *);
extern void func_ov134_0229a398(void *);
extern int func_ov134_022999ac(int *p);
extern void func_ov134_02299980(int *p, int val);
extern int func_ov137_0229c574(void *self, int x);
extern void func_ov002_0220a374(void *p, int v);
extern void *func_ov134_022999e0(void *p);
extern void *data_ov137_0229d368[];
extern int data_ov137_0229d374[];

void func_ov137_0229cefc(int p0);
void func_ov137_0229c9b4(void *p);
void func_ov137_0229c998(void *p);
void func_ov137_0229c978(int param);
void func_ov137_0229c92c(char *self);
void func_ov137_0229c900(char *a, int b);
void func_ov137_0229c8d4(void *r0);
void func_ov137_0229c8a8(void *self);
void func_ov137_0229c890(void *param);
void func_ov137_0229c854(struct UnkStruct_0229c854 *self);
void func_ov137_0229c834(unsigned int arg);
void func_ov137_0229c7d8(void *self);
void *func_ov137_0229c794(void *p);
int func_ov137_0229c750(void *param);

void func_ov137_0229cf28(int arg0)
{
    func_ov137_0229cefc(arg0);
}

void func_ov137_0229cf0c(void *self)
{
    func_ov002_0220af74((char *) self + 0xf8);
    func_ov134_0229bcac((char *) self + 0x2c4);
}

void func_ov137_0229cefc(int p0)
{
    func_ov134_0229bbe8((p0 + 708));
}

void func_ov137_0229ceb0(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
}

void func_ov137_0229ce90(void *arg0)
{
    func_ov134_0229baec((char *) arg0 + 0x2c4);
    func_ov134_0229ba10((char *) arg0 + 0x2c4, 0x6d);
}

void func_ov137_0229ce70(void *arg0)
{
    func_ov134_0229b954((char *) arg0 + 0x2c4);
    func_ov002_0220af94((void *) ((char *) arg0 + 0xf8));
}

void func_ov137_0229cdf4(UnkStruct_0229cdf4 *self)
{
    if (func_ov002_02208054(self, 1)) {
        func_ov137_0229c998((void *) self);
        return;
    }
    {
        unsigned int flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (flag > 0) {
            if (func_ov002_0220a784(&self->unk_F8, 6)) {
                func_ov137_0229c92c((char *) self);
                return;
            }
            {
                int ret = func_ov134_0229ab2c(&self->unk_2C4, data_021f6c58, data_021f6c54);
                if (ret == 6) {
                    return;
                }
                func_ov137_0229c900((char *) self, ret);
            }
        }
    }
}

void func_ov137_0229cd5c(int self)
{
    unsigned int ok;
    int r;
    if (func_ov002_02208054((UnkStruct_0229cdf4 *) self, 1)) {
        func_ov137_0229c854((struct UnkStruct_0229c854 *) self);
        return;
    }
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    r = func_ov134_0229a1f0(self + 0x2c4, data_021f6c58, data_021f6c54);
    switch (r) {
        case 0:
            func_ov137_0229c8d4((void *) self);
            break;
        case 1:
            func_ov137_0229c8a8((void *) self);
            break;
        case 3:
            func_ov002_02208098((void *) self, 2);
            break;
        case 2:
            func_ov002_02208098((void *) self, 3);
            break;
    }
}

void func_ov137_0229cd20(void *p)
{
    if (data_021fbdd8) {
        func_ov134_02299b18((char *) p + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p + 0x2c4);
        func_ov002_02208098(p, 1);
    }
}

void func_ov137_0229cce4(void *arg)
{
    if (data_021fbdd8) {
        func_ov134_02299af0((char *) arg + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) arg + 0x2c4);
        func_ov002_02208098(arg, 1);
    }
}

void func_ov137_0229cc80(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov137_0229c9b4(arg);
        return;
    }
    if (func_ov137_0229c58c(arg, func_ov002_02208008(arg)) != 0) {
        func_ov137_0229c6e4(arg);
        return;
    }
    if (((*(SomeGlobal *) data_021fbe40).flags & 1) != 0) {
        func_ov137_0229c650(arg);
        return;
    }
    if (((*(SomeGlobal *) data_021fbe40).flags & 8) != 0) {
        func_ov137_0229c734(arg);
        func_ov137_0229c92c((char *) arg);
    }
}

void func_ov137_0229cbe8(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov137_0229c890(arg);
        return;
    }
    switch (func_ov134_022997dc((char *) arg + 0x2c4, func_ov002_02208008(arg))) {
        case 2:
            func_ov137_0229c564(arg, 4);
            goto default_case;
        case 3: {
            int v1 = (int) func_ov137_0229c794(arg);
            int v2 = func_ov137_0229c750(arg);
            func_ov002_0220a0b4((char *) arg + 0x94, v1, v2);
            return;
        }
        default:
        default_case:
            func_ov137_0229c6e4(arg);
            return;
        case 0: {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov137_0229c650(arg);
                return;
            }
            if (flags & 2) {
                func_ov137_0229c8a8(arg);
            }
            return;
        }
    }
}

void func_ov137_0229cb90(char *self)
{
    if (((*(unsigned short *) data_021fbe40) & 1) != 0) {
        int a;
        int b;
        func_ov134_02299a90(self + 0x2c4);
        a = (int) func_ov137_0229c794(self);
        b = func_ov137_0229c750(self);
        self += 0x94;
        func_ov002_0220a0b4(self, a, b);
    } else {
        func_ov134_02299a84(self + 0x2c4);
        func_ov002_02208098(self, 7);
    }
}

void func_ov137_0229cb48(void *arg0)
{
    if (func_ov134_02299a60((char *) arg0 + 0x2c4)) {
        func_ov002_02208098(arg0, 5);
        func_ov137_0229c628(arg0);
    }
    {
        int r5 = (int) func_ov137_0229c794(arg0);
        int r2 = func_ov137_0229c750(arg0);
        func_ov002_0220a0b4((char *) arg0 + 0x94, r5, r2);
    }
}

void func_ov137_0229cb20(struct UnkStruct_0229cb20 *p)
{
    if (func_ov002_02209f64(&p->unk_94) == 0) {
        func_ov002_02208098(p, p->unk_2B76);
        func_ov137_0229d0e0(p);
    }
}

void func_ov137_0229cab8(void *this)
{
    if (func_0208e484((unsigned char *) this + 0x94) != 0) {
        if (func_ov137_0229c574((void *) this, (unsigned short) 2) != 0) {
            if (func_ov134_02299b70((unsigned char *) this + 0x2c4) != 0) {
                func_ov002_02208098(this, 6);
            } else {
                func_ov134_022997b0((unsigned char *) this + 0x2c4);
                func_ov137_0229c8d4(this);
            }
        } else {
            unsigned char b = *((unsigned char *) this + 0x2b77);
            if (b == 2) {
                func_ov137_0229c92c(this);
            } else {
                func_ov137_0229c900(this, b + 1);
            }
        }
    }
}

void func_ov137_0229ca90(void *p)
{
    if (func_0208e484((char *) p + 0x94)) {
        func_ov137_0229c668(p);
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0x2b76));
    }
}

void func_ov137_0229ca2c(char *p)
{
    int a, b, c;

    if (func_ov002_0220a700(p + 0xf8)) {
        if (func_0208e4bc(p + 0x94) == 0) {
            return;
        }
        a = func_ov002_0220a6e0(p + 0xf8);
        b = func_ov002_0220a768(p + 0xf8, -1);
        c = func_ov002_0220a72c(p + 0xf8, -1);
        p += 0x94;
        func_ov002_0220a0b4(p, a + b, a + c);
    } else {
        func_ov137_0229c734(p);
        func_ov002_022080a0(p, 1);
    }
}

void func_ov137_0229ca0c(void *self)
{
    if (func_ov134_0229a4e4((char *) self + 0x2c4)) {
        func_ov137_0229c834((unsigned int) self);
    }
}

void func_ov137_0229c9cc(char *param)
{
    if (func_ov134_0229a24c(param + 0x2c4) != 0) {
        int ret = func_ov134_0229a8a0(param + 0x2c4);
        if (ret == 6) {
            *(char *) (param + 0x2b77) = 2;
        } else {
            *(char *) (param + 0x2b77) = ret - 1;
        }
        func_ov137_0229c978((int) param);
    }
}

void func_ov137_0229c9b4(void *p)
{
    func_ov137_0229c734((void *) p);
    func_ov002_02208098(p, 0);
}

void func_ov137_0229c998(void *p)
{
    func_ov137_0229c7d8(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098(p, 4);
}

void func_ov137_0229c978(int param)
{
    if (func_0206fe60() != 0) {
        func_ov137_0229c9b4((void *) param);
    } else {
        func_ov137_0229c998((void *) param);
    }
}

void func_ov137_0229c92c(char *self)
{
    unsigned int local[3];
    void *r;
    func_ov002_0220a720(self + 0xf8, 6);
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 0xb);
    r = func_020984e8();
    local[0] = 0;
    local[1] = 0;
    func_ov134_0229bbdc(self + 0x2c4, local);
    func_020992d0(r, ((unsigned char *) local)[4], ((unsigned char *) local)[3]);
}

void func_ov137_0229c900(char *a, int b)
{
    func_ov137_0229c734((void *) a);
    func_ov134_0229a5c8(a + 0x2c4, b);
    func_ov002_02208098((void *) a, 0xc);
}

void func_ov137_0229c8d4(void *r0)
{
    void *r4 = r0;
    func_ov137_0229c734(r4);
    func_ov137_0229c554(r4, 2);
    func_ov134_0229a3e4((char *) r4 + 0x2c4);
    func_ov002_02208098(r4, 0xd);
}

void func_ov137_0229c8a8(void *self)
{
    func_ov137_0229c734(self);
    func_ov137_0229c554(self, 2);
    func_ov134_0229a398((char *) self + 0x2c4);
    func_ov002_02208098(self, 0xd);
}

void func_ov137_0229c890(void *param)
{
    func_ov137_0229c734(param);
    func_ov002_02208098(param, 1);
}

void func_ov137_0229c854(struct UnkStruct_0229c854 *self)
{
    int tmp;
    tmp = func_ov134_022999ac(&self->unk_2C4);
    func_ov134_02299980(&self->unk_2C4, tmp);
    func_ov137_0229c564((void *) self, 2);
    func_ov137_0229c7d8((void *) self);
    func_ov002_02207fc0((void *) self);
    func_ov002_02208098((void *) self, 5);
}

void func_ov137_0229c834(unsigned int arg)
{
    if (func_0206fe60()) {
        func_ov137_0229c890((void *) arg);
    } else {
        func_ov137_0229c854((struct UnkStruct_0229c854 *) arg);
    }
}

void func_ov137_0229c7d8(void *self)
{
    int a;
    int b;

    a = (int) func_ov137_0229c794(self);
    b = func_ov137_0229c750(self);
    func_ov002_0220a0b4((char *) self + 0x94, a, b);

    if (func_ov137_0229c574(self, 2) != 0 || *(unsigned char *) ((char *) self + 0x2b77) != 2) {
        func_ov002_0220a374((char *) self + 0x94, 1);
    } else {
        func_ov002_0220a374((char *) self + 0x94, 7);
    }

    func_ov137_0229c668(self);
}

void *func_ov137_0229c794(void *p)
{
    unsigned char v;

    if (func_ov137_0229c574(p, 2)) {
        return func_ov134_022999e0((char *) p + 0x2c4);
    }

    v = *(unsigned char *) ((char *) p + 0x2b77);
    if (v == 2) {
        p = (char *) p + 0xf8;
        return (void *) func_ov002_0220a768(p, 6);
    }

    return data_ov137_0229d368[v];
}

int func_ov137_0229c750(void *param)
{
    unsigned char b;

    if (func_ov137_0229c574(param, 2) != 0) {
        return func_ov134_022999ac((int *) ((char *) param + 0x2c4));
    }
    b = ((unsigned char *) param)[0x2b77];
    if (b == 2) {
        param = (char *) param + 0xf8;
        return func_ov002_0220a72c(param, 6);
    }
    return data_ov137_0229d374[b];
}
