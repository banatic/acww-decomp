/* date_screen_3: 19 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229caf8 @ 0x0229caf8, 0x84 bytes, Thumb
 * func_ov138_0229cad4 @ 0x0229cad4, 0x24 bytes, Thumb
 * func_ov138_0229ca70 @ 0x0229ca70, 0x62 bytes, Thumb
 * func_ov138_0229ca50 @ 0x0229ca50, 0x20 bytes, Thumb
 * func_ov138_0229ca14 @ 0x0229ca14, 0x3c bytes, Thumb
 * func_ov138_0229c9fc @ 0x0229c9fc, 0x16 bytes, Thumb
 * func_ov138_0229c9e0 @ 0x0229c9e0, 0x1c bytes, Thumb
 * func_ov138_0229c9c0 @ 0x0229c9c0, 0x20 bytes, Thumb
 * func_ov138_0229c978 @ 0x0229c978, 0x48 bytes, Thumb
 * func_ov138_0229c950 @ 0x0229c950, 0x28 bytes, Thumb
 * func_ov138_0229c924 @ 0x0229c924, 0x2c bytes, Thumb
 * func_ov138_0229c8f8 @ 0x0229c8f8, 0x2c bytes, Thumb
 * func_ov138_0229c8cc @ 0x0229c8cc, 0x2c bytes, Thumb
 * func_ov138_0229c8b4 @ 0x0229c8b4, 0x16 bytes, Thumb
 * func_ov138_0229c878 @ 0x0229c878, 0x3c bytes, Thumb
 * func_ov138_0229c858 @ 0x0229c858, 0x20 bytes, Thumb
 * func_ov138_0229c7fc @ 0x0229c7fc, 0x5c bytes, Thumb
 * func_ov138_0229c7a8 @ 0x0229c7a8, 0x54 bytes, Thumb
 * func_ov138_0229c754 @ 0x0229c754, 0x54 bytes, Thumb
 */

struct UnkStruct_0229cad4 {
    unsigned char pad_00[0x94];
    unsigned char unk_94;
    unsigned char pad_95[3];
    void *unk_98;
};

struct UnkStruct_0229c878 {
    char pad_00[0x2c8];
    char unk_2C8;
};

extern int func_0208e484(void *);
extern int func_ov138_0229c574(void *, int);
extern int func_ov134_02299b70(void *);
extern int func_ov134_022997b0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov138_0229c630(void *);
extern void func_ov138_0229c66c(struct UnkStruct_0229cad4 *);
extern int func_ov002_0220a700(const void *);
extern int func_0208e4bc(const void *);
extern int func_ov002_0220a6e0(const void *);
extern int func_ov002_0220a768(const void *, int);
extern int func_ov002_0220a72c(const void *, int);
extern void func_ov002_0220a0b4(const void *, int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov134_0229a4e4(void *);
extern int func_ov134_0229a24c(char *);
extern int func_ov134_0229a8a0(char *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void *func_ov002_0220a720(void *ptr, int n);
extern void func_ov002_02208090(void *self, int n);
extern void func_ov134_0229bbdc(void *dst, void *src);
extern void func_0206f820(void *p);
extern void func_0206fc4c(int n);
extern int func_ov138_0229c738(void *unused0);
extern void func_ov134_0229a5c8(void *p, void *q);
extern void func_ov138_0229c554(void *, int);
extern void func_ov134_0229a3e4(void *);
extern void func_ov134_0229a398(void *p);
extern int func_ov134_022999ac(void *p);
extern void func_ov134_02299980(void *p, int x);
extern void func_ov138_0229c564(void *p, int x);
extern void func_ov002_0220a374(void *p, int);
extern int func_ov134_022999e0(void *ptr);
extern int data_ov138_0229d404[];
extern int data_ov138_0229d418[];

int func_ov138_0229c9c0(int param);
void func_ov138_0229c978(void *arg);
void func_ov138_0229c950(void *p);
void func_ov138_0229c924(void *r0, void *r1);
void func_ov138_0229c8f8(void *self);
void func_ov138_0229c858(int param);
void func_ov138_0229c7fc(unsigned char *self);
int func_ov138_0229c7a8(void *self);
int func_ov138_0229c754(void *self);

void func_ov138_0229caf8(void *a0)
{
    if (func_0208e484((char *) a0 + 0x98)) {
        if (func_ov138_0229c574(a0, 2)) {
            if (func_ov134_02299b70((char *) a0 + 0x2c8)) {
                func_ov002_02208098((void *) (a0), 6);
            } else if (func_ov134_022997b0((char *) a0 + 0x2c8)) {
                func_ov138_0229c8f8(a0);
            } else {
                func_ov002_02208098((void *) (a0), 5);
                func_ov138_0229c630(a0);
            }
        } else {
            unsigned char v = *((unsigned char *) a0 + 0x95);
            if (v == 3) {
                func_ov138_0229c978(a0);
            } else if (v == 4) {
                func_ov138_0229c950(a0);
            } else {
                func_ov138_0229c924(a0, (void *) v);
            }
        }
    }
}

void func_ov138_0229cad4(struct UnkStruct_0229cad4 *arg)
{
    if (func_0208e484(&arg->unk_98) != 0) {
        func_ov138_0229c66c(arg);
        func_ov002_02208098((void *) (arg), arg->unk_94);
    }
}

void func_ov138_0229ca70(void *p)
{
    if (func_ov002_0220a700((char *) p + 0xfc)) {
        if (func_0208e4bc((char *) p + 0x98)) {
            int a = func_ov002_0220a6e0((char *) p + 0xfc);
            int b = func_ov002_0220a768((char *) p + 0xfc, -1);
            int c = func_ov002_0220a72c((char *) p + 0xfc, -1);
            func_ov002_0220a0b4((char *) p + 0x98, a + b, a + c);
        }
    } else {
        func_ov138_0229c738((void *) p);
        func_ov002_022080a0((void *) (p), 1);
    }
}

void func_ov138_0229ca50(void *arg0)
{
    if (func_ov134_0229a4e4((char *) arg0 + 0x2c8) != 0) {
        func_ov138_0229c858((int) arg0);
    }
}

void func_ov138_0229ca14(char *self)
{
    int v;
    if (func_ov134_0229a24c(self + 0x2c8) == 0) {
        return;
    }
    v = func_ov134_0229a8a0(self + 0x2c8);
    if (v == 6) {
        self[0x95] = 3;
    } else {
        self[0x95] = (char) v;
    }
    func_ov138_0229c9c0((int) self);
}

int func_ov138_0229c9fc(int arg)
{
    func_ov138_0229c738((void *) arg);
    return (int) func_ov002_02208098((void *) (arg), 0);
}

unsigned char *func_ov138_0229c9e0(void *p)
{
    func_ov138_0229c7fc((unsigned char *) p);
    func_ov002_02207fc0(p);
    return func_ov002_02208098((void *) (p), 4);
}

int func_ov138_0229c9c0(int param)
{
    int result;
    if (func_0206fe60() != 0) {
        result = func_ov138_0229c9fc(param);
    } else {
        result = (int) func_ov138_0229c9e0((void *) param);
    }
    return result;
}

void func_ov138_0229c978(void *arg)
{
    func_ov002_0220a720((char *) arg + 0xfc, 6);
    func_ov002_02208090(arg, 2);
    func_ov002_02208098((void *) (arg), 0xb);
    {
        int v[2];
        v[0] = 0;
        v[1] = 0;
        func_ov134_0229bbdc((char *) arg + 0x2c8, v);
        func_0206f820(v);
        func_0206fc4c(1);
    }
}

void func_ov138_0229c950(void *p)
{
    func_ov002_0220a720((char *) p + 0xfc, 7);
    func_ov002_02208090(p, 2);
    func_ov002_02208098((void *) (p), 0xb);
    func_0206fc4c(0);
}

void func_ov138_0229c924(void *r0, void *r1)
{
    void *r5 = r0;
    void *r4 = r1;
    func_ov138_0229c738(r0);
    func_ov134_0229a5c8((char *) r5 + 0x2c8, r4);
    func_ov002_02208098((void *) (r5), 0xc);
}

void func_ov138_0229c8f8(void *self)
{
    func_ov138_0229c738(self);
    func_ov138_0229c554(self, 2);
    func_ov134_0229a3e4((char *) self + 0x2c8);
    func_ov002_02208098((void *) (self), 0xd);
}

void func_ov138_0229c8cc(void *ptr)
{
    func_ov138_0229c738(ptr);
    func_ov138_0229c554(ptr, 2);
    func_ov134_0229a398((char *) ptr + 0x2c8);
    func_ov002_02208098((void *) (ptr), 0xd);
}

void func_ov138_0229c8b4(int param)
{
    func_ov138_0229c738((void *) param);
    func_ov002_02208098((void *) (param), 1);
}

void func_ov138_0229c878(struct UnkStruct_0229c878 *self)
{
    int ret;
    ret = func_ov134_022999ac(&self->unk_2C8);
    func_ov134_02299980(&self->unk_2C8, ret);
    func_ov138_0229c564(self, 2);
    func_ov138_0229c7fc((unsigned char *) self);
    func_ov002_02207fc0(self);
    func_ov002_02208098((void *) (self), 5);
}

void func_ov138_0229c858(int param)
{
    if (func_0206fe60()) {
        func_ov138_0229c8b4(param);
    } else {
        func_ov138_0229c878((struct UnkStruct_0229c878 *) param);
    }
}

void func_ov138_0229c7fc(unsigned char *self)
{
    int a, b;

    a = func_ov138_0229c7a8(self);
    b = func_ov138_0229c754(self);
    func_ov002_0220a0b4((const void *) (self + 0x98), a, b);

    if (func_ov138_0229c574(self, 2) != 0 || (self[0x95] != 3 && self[0x95] != 4)) {
        func_ov002_0220a374(self + 0x98, 1);
    } else {
        func_ov002_0220a374(self + 0x98, 7);
    }

    func_ov138_0229c66c((struct UnkStruct_0229cad4 *) self);
}

int func_ov138_0229c7a8(void *self)
{
    if (func_ov138_0229c574(self, 2)) {
        return func_ov134_022999e0((char *) self + 0x2c8);
    } else {
        unsigned char b = *((unsigned char *) self + 0x95);
        switch (b) {
            case 3:
                return func_ov002_0220a768((const void *) ((char *) self + 0xfc), 6);
            case 4:
                return func_ov002_0220a768((const void *) ((char *) self + 0xfc), 7);
            default:
                return data_ov138_0229d404[b];
        }
    }
}

int func_ov138_0229c754(void *self)
{
    if (func_ov138_0229c574(self, 2)) {
        return func_ov134_022999ac((char *) self + 0x2c8);
    } else {
        unsigned char b = *((unsigned char *) self + 0x95);
        switch (b) {
            case 3:
                return func_ov002_0220a72c((const void *) ((char *) self + 0xfc), 6);
            case 4:
                return func_ov002_0220a72c((const void *) ((char *) self + 0xfc), 7);
            default:
                return data_ov138_0229d418[b];
        }
    }
}
