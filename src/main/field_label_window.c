/* field_label_window: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b91c4 @ 0x020b91c4, 0x48 bytes, Thumb
 * func_020b91a0 @ 0x020b91a0, 0x24 bytes, Thumb
 * func_020b9178 @ 0x020b9178, 0x28 bytes, Thumb
 * func_020b90cc @ 0x020b90cc, 0xac bytes, Thumb
 * func_020b90ac @ 0x020b90ac, 0x20 bytes, Thumb
 * func_020b90a4 @ 0x020b90a4, 0x8 bytes, Thumb
 * func_020b9070 @ 0x020b9070, 0x32 bytes, Thumb
 * func_020b9068 @ 0x020b9068, 0x6 bytes, Thumb
 * func_020b904c @ 0x020b904c, 0x1a bytes, Thumb
 * func_020b9030 @ 0x020b9030, 0x1a bytes, Thumb
 * func_020b8fe0 @ 0x020b8fe0, 0x50 bytes, Thumb
 * func_020b8f20 @ 0x020b8f20, 0xbe bytes, Thumb
 * func_020b8edc @ 0x020b8edc, 0x44 bytes, Thumb
 */

typedef struct {
    void *ptr;
    char pad_04[0xc8];
    char sub[20];
    int unk_E0;
    char unk_E4;
    char unk_E5;
    char unk_E6;
    char unk_E7;
    char unk_E8;
} UnkStruct_020b91c4;

typedef struct {
    void *unk_00;
    char pad_04[0xCC - 4];
    void *unk_CC;
} UnkStruct_020b9178;

typedef struct {
    char pad_00[0xcc];
    char unk_CC[0x14];
    int unk_E0;
    char pad_E4[1];
    unsigned char unk_E5;
    unsigned char unk_E6;
} UnkStruct_020b90cc;

typedef struct {
    unsigned char pad_00[0xE6];
    unsigned char unk_E6;
    unsigned char unk_E7;
} UnkStruct_020b90ac;

typedef struct {
    unsigned char pad_00[232];
    unsigned char unk_E8;
} UnkStruct_020b9068;

struct UnkStruct_020b904c {
    unsigned char pad_00[0xe0];
    unsigned int unk_E0;
    unsigned char pad_E4[0x4];
    unsigned char unk_E8;
};

typedef struct {
    char pad_00[0xE0];
    int unk_E0;
    char pad_E4[4];
    unsigned char unk_E8;
} UnkStruct_020b9030;

typedef struct {
    char pad_00[0xcc];
    int unk_CC;
} UnkStruct_020b8fe0;

typedef struct {
    unsigned char pad_00[0xe0];
    int unk_E0;
    unsigned char unk_E4;
    unsigned char unk_E5;
    unsigned char unk_E6;
    unsigned char unk_E7;
    unsigned char unk_E8;
} UnkStruct_020b8f20;

extern void *func_0208ade8(void *self, int flag);
extern void func_0208a1f8(void *sub);
extern char data_020e5858;
extern void func_0208a1f4(void *p);
extern void *func_0208ad24(void *p);
extern void func_020edb3c(void *);
extern void *func_0208a1d0(char *p);
extern void *func_0208a840(UnkStruct_020b90cc *self);
extern int func_0208a824(UnkStruct_020b90cc *self);
extern int func_0208a80c(UnkStruct_020b90cc *self);
extern int func_0208a1b0(void *p, int k);
extern int func_0208a198(void *p, int k);
extern void func_02088df8(int z, void *p, int a, int b, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8);
extern void func_0208ab3c(UnkStruct_020b90cc *self);
extern void func_0208aaa0(UnkStruct_020b90ac *param);
extern void func_0208a784(void *);
extern int func_0208a1cc(int *);
extern void func_0208a1f0(void *dst, const void *src);
extern void func_0208a1ec(void *dst, int a);
extern void *func_0208a1e8(void *dst, int a);
extern void *func_0208a1e0(void *dst, int a, int b);
extern void func_0208a0c8(void *dst);
extern char data_020d71d4[];
extern int func_0208a844(void *self);
extern void func_0200467c(int cmd);
extern int func_0206fce0(void);
extern int func_0206fd04(void);
extern int func_0206fd34(void);

void func_020b8f20(UnkStruct_020b8f20 *self);
int func_020b8edc(void);

void *func_020b91c4(UnkStruct_020b91c4 *self)
{
    func_0208ade8(self, 1);
    self->ptr = &data_020e5858;
    func_0208a1f8(self->sub);
    self->unk_E0 = 0;
    self->unk_E4 = 0;
    self->unk_E5 = 0;
    self->unk_E6 = 0;
    self->unk_E7 = 0;
    self->unk_E8 = 0;
    return self;
}

void *func_020b91a0(void *self)
{
    struct {
        void *field_0;
        char pad[0xC8];
        char field_CC;
    } *obj = self;

    obj->field_0 = &data_020e5858;
    func_0208a1f4(&obj->field_CC);
    func_0208ad24(self);
    return self;
}

UnkStruct_020b9178 *func_020b9178(UnkStruct_020b9178 *self)
{
    self->unk_00 = ((int *) &data_020e5858);
    func_0208a1f4(&self->unk_CC);
    func_0208ad24(self);
    func_020edb3c(self);
    return self;
}

void func_020b90cc(UnkStruct_020b90cc *self)
{
    int ok;
    int a;
    int s;
    void *p;
    void *q;
    int r;

    ok = 0;
    if (self->unk_E0 < 0x19) {
        if (self->unk_E5 != 0) {
            p = func_0208a1d0(self->unk_CC);
            q = func_0208a840(self);
            a = func_0208a824(self);
            s = func_0208a80c(self);
            r = func_0208a1b0(q, -1);
            a = a + r + func_0208a1b0(self->unk_CC, -1);
            r = func_0208a198(q, -1);
            s = s + r + func_0208a198(self->unk_CC, -1);
            func_02088df8(0, p, a, s, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            ok = 1;
        }
        func_0208ab3c(self);
    }
    self->unk_E6 = (unsigned char) ok;
}

void func_020b90ac(UnkStruct_020b90ac *param)
{
    param->unk_E7 = param->unk_E6;
    func_0208aaa0(param);
    func_020b8f20((UnkStruct_020b8f20 *) param);
}

void func_020b90a4(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (228))) + (0)) = 1;
}

void func_020b9070(void *arg0)
{
    func_0208a784(arg0);
    ((unsigned char *) arg0)[0xe4] = 0;
    ((unsigned char *) arg0)[0xe5] = 0;
    *(unsigned int *) ((unsigned char *) arg0 + 0xe0) = 0;
    ((unsigned char *) arg0)[0xe6] = 0;
    ((unsigned char *) arg0)[0xe7] = 0;
    ((unsigned char *) arg0)[0xe8] = 0;
}

void func_020b9068(UnkStruct_020b9068 *p, unsigned char v)
{
    p->unk_E8 = v;
}

int func_020b904c(struct UnkStruct_020b904c *p)
{
    if (p->unk_E8 && p->unk_E0 == 0x1D) {
        return 1;
    }
    return 0;
}

int func_020b9030(UnkStruct_020b9030 *arg)
{
    if (arg->unk_E8 != 0 && arg->unk_E0 < 25) {
        return 1;
    }
    return 0;
}

void func_020b8fe0(UnkStruct_020b8fe0 *self)
{
    int v;

    v = func_0208a1cc((int *) (int) func_0208a840((UnkStruct_020b90cc *) ((int) self)));
    func_0208a1f0(&self->unk_CC, data_020d71d4);
    func_0208a1ec(&self->unk_CC, 1);
    func_0208a1e8(&self->unk_CC, 0);
    func_0208a1e0(&self->unk_CC, v, 0);
    func_0208a0c8(&self->unk_CC);
}

void func_020b8f20(UnkStruct_020b8f20 *self)
{
    int res;

    if (self->unk_E5 != 0) {
        res = func_0208a844(self);
        if (res == 0) {
            self->unk_E4 = 0;
            self->unk_E5 = 0;
            self->unk_E0 = 0;
            return;
        } else if (res == 2) {
            if (self->unk_E0 == 0) {
                func_0200467c(0x3d);
            }
            if (func_020b8edc() != 0) {
                self->unk_E0 = 0x19;
                return;
            }
            if (self->unk_E8 != 0) {
                self->unk_E0 = self->unk_E0 + 1;
                if (self->unk_E0 < 0x1e) {
                    return;
                }
                self->unk_E0 = 0;
                return;
            } else {
                self->unk_E0 = 1;
                return;
            }
        } else {
            return;
        }
    } else {
        if (self->unk_E4 != 0) {
            self->unk_E4 = 0;
            self->unk_E5 = 1;
            if (func_020b8edc() != 0) {
                self->unk_E0 = 0x19;
            } else {
                self->unk_E0 = 0;
            }
            func_020b8fe0((UnkStruct_020b8fe0 *) self);
        }
        return;
    }
}

int func_020b8edc(void)
{
    int a = func_0206fce0() != 0;
    int b = func_0206fd04() != 0;
    int c = func_0206fd34();
    if (a || (b && c < 0x1000)) {
        return 1;
    } else {
        return 0;
    }
}
