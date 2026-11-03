/* letter: 48 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02066688 @ 0x02066688, 0xc bytes, Thumb
 * func_02066670 @ 0x02066670, 0x18 bytes, Thumb
 * func_02066650 @ 0x02066650, 0x20 bytes, Thumb
 * func_02066648 @ 0x02066648, 0x6 bytes, Thumb
 * func_020665f0 @ 0x020665f0, 0x58 bytes, Thumb
 * func_020665b8 @ 0x020665b8, 0x38 bytes, Thumb
 * func_0206658c @ 0x0206658c, 0x2c bytes, Thumb
 * func_02066560 @ 0x02066560, 0x2c bytes, Thumb
 * func_02066514 @ 0x02066514, 0x4a bytes, Thumb
 * func_020664e0 @ 0x020664e0, 0x32 bytes, Thumb
 * func_020664a8 @ 0x020664a8, 0x38 bytes, Thumb
 * func_02066478 @ 0x02066478, 0x30 bytes, Thumb
 * func_020663d4 @ 0x020663d4, 0xa4 bytes, Thumb
 * func_02066344 @ 0x02066344, 0x8e bytes, Thumb
 * func_020662bc @ 0x020662bc, 0x88 bytes, Thumb
 * func_02066228 @ 0x02066228, 0x94 bytes, Thumb
 * func_02066198 @ 0x02066198, 0x8e bytes, Thumb
 * func_02066104 @ 0x02066104, 0x94 bytes, Thumb
 * func_02066088 @ 0x02066088, 0x7c bytes, Thumb
 * func_02066024 @ 0x02066024, 0x64 bytes, Thumb
 * func_02065fc4 @ 0x02065fc4, 0x60 bytes, Thumb
 * func_02065f88 @ 0x02065f88, 0x3c bytes, Thumb
 * func_02065f7c @ 0x02065f7c, 0xc bytes, Thumb
 * func_02065f70 @ 0x02065f70, 0xc bytes, Thumb
 * func_02065f64 @ 0x02065f64, 0xc bytes, Thumb
 * func_02065f58 @ 0x02065f58, 0xc bytes, Thumb
 * func_02065f4c @ 0x02065f4c, 0xc bytes, Thumb
 * func_02065f44 @ 0x02065f44, 0x6 bytes, Thumb
 * func_02065f38 @ 0x02065f38, 0xc bytes, Thumb
 * func_02065f2c @ 0x02065f2c, 0xc bytes, Thumb
 * func_02065f20 @ 0x02065f20, 0xc bytes, Thumb
 * func_02065f18 @ 0x02065f18, 0x6 bytes, Thumb
 * func_02065f08 @ 0x02065f08, 0xe bytes, Thumb
 * func_02065ef4 @ 0x02065ef4, 0x14 bytes, Thumb
 * func_02065ed0 @ 0x02065ed0, 0x22 bytes, Thumb
 * func_02065ec0 @ 0x02065ec0, 0xe bytes, Thumb
 * func_02065eac @ 0x02065eac, 0x12 bytes, Thumb
 * func_02065e9c @ 0x02065e9c, 0x10 bytes, Thumb
 * func_02065e60 @ 0x02065e60, 0x3c bytes, Thumb
 * func_02065e10 @ 0x02065e10, 0x4e bytes, Thumb
 * func_02065db8 @ 0x02065db8, 0x58 bytes, Thumb
 * func_02065d0c @ 0x02065d0c, 0xaa bytes, Thumb
 * func_02065cc8 @ 0x02065cc8, 0x42 bytes, Thumb
 * func_02065cb0 @ 0x02065cb0, 0x18 bytes, Thumb
 * func_02065c98 @ 0x02065c98, 0x18 bytes, Thumb
 * func_02065c78 @ 0x02065c78, 0x20 bytes, Thumb
 * func_02065c74 @ 0x02065c74, 0x4 bytes, Thumb
 * func_02065c70 @ 0x02065c70, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[249];
    unsigned char unk_F9;
} UnkStruct_02066648;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0206658c;

typedef struct {
    char data[32];
} UnkStruct_020662bc;

struct UnkStruct_02066104 {
    char data[0x20];
};

struct UnkStruct_02066104_2 {
    char data[0x24];
};

typedef struct UnkStruct_02066088 {
    char data[32];
} UnkStruct_02066088;

typedef struct {
    char pad_00[4];
    unsigned char unk_04[0x20];
    unsigned char unk_24[0xD5];
    unsigned char unk_F9;
    unsigned char pad_FA;
    unsigned char unk_FB;
} UnkStruct_02065fc4;

typedef struct {
    unsigned char pad_00[251];
    unsigned char unk_FB;
} UnkStruct_02065f44;

typedef struct {
    unsigned char pad_00[252];
    unsigned short unk_FC;
} UnkStruct_02065f18;

struct UnkStruct_02065ed0 {
    unsigned char pad_00[0xFC];
    unsigned short unk_FC;
};

struct UnkStruct_02065e60 {
    unsigned char pad_00[0x22];
    unsigned char unk_22;
    unsigned char pad_23[0x44 - 0x23];
    unsigned char unk_44[0xA];
    unsigned char pad_4E[0xF8 - 0x4E];
    unsigned char unk_F8;
};

struct UnkStruct_02065c78 {
    void *unk_00;
};

extern void func_020edb3c(void *);
extern unsigned char data_020de760[];
extern void MI_CpuFill8(void *param1, int param2, int param3);
extern void *func_020984e8(void);
extern void *func_02099870(void *x);
extern void func_020951dc(void *x, char *p);
extern void *func_02099734(void *x);
extern void *func_02098ddc(void *x);
extern void func_020666b4(void *ptr);
extern int func_0207cec0(void *addr, int);
extern int func_0208150c(unsigned int);
extern void func_020666e4(int *ptr, int value);
extern unsigned char data_021e5a2c[];
extern int func_02098844(int *ptr, int);
extern void func_020666d0(int arg1, int arg2);
extern int data_021dc7bc;
extern void func_020666bc(void *, void *);
extern void *func_020707d0(void *ptr);
extern void *func_020707b8(void *ptr);
extern int func_020a87e0(void *p1, void *p2);
extern void func_0205195c(void *ptr);
extern void __register_global_object(void *, void *, void *);
extern unsigned int data_021cd890;
extern unsigned int data_021cd920;
extern unsigned int data_021cd8ac;
extern unsigned int data_021cd92e;
extern int func_02003780(void *);
extern void func_02003728(void *, int);
extern int func_02003750(void *);
extern void *func_0209529c(void *);
extern void func_0209525c(void *, int);
extern int func_0209526c(void *);
extern void func_020666b0(void *, int);
extern int func_0203d930(void *, void *, void *, int *, int, int);
extern void *func_02094fd4(void *);
extern int func_02003618(int, void *);
extern int func_0203d7c4(int, void *);
extern void *func_02094fbc(void *);
extern void *func_02095074(int, void *);
extern void func_0203d73c(void *);
extern int func_0203d834(int, int, int, void *, int, int, int, int, int);
extern unsigned char data_021cd8c4[];
extern unsigned char data_021cd8ec[];
extern unsigned char data_021cd9b0[];
extern int func_02066708(void *a);
extern void *func_020666f8(void *ptr);
extern int func_02066788(int x, void *);
extern int func_0206671c(void *ptr, void *);
extern int func_020666a0(int a, int b);
extern void func_02051c08(void *dest, const void *src, int size);
extern void func_02051bf8(void *dst, int size);
extern int func_02070c08(void *);
extern int func_020b4980(void *, const char *, int);
extern int func_02051ce0(void *, int, int);
extern int func_02051c8c_unk(void *, int);
extern int **func_02070be8(void *);
extern void *func_020a88ec(void *);
extern char data_020de770[];
extern void *func_020a887c(void *);

void func_02065ef4(unsigned char *base, unsigned int value);
unsigned char func_02065ec0(unsigned char *param);
void func_02065eac(unsigned char *p, unsigned char x);
void func_02065e60(struct UnkStruct_02065e60 *p);
void func_02065e10(void *obj, const unsigned short *p);
void func_02065d0c(const char *arg0, const unsigned short *arg1, unsigned char *out, void *dest);
void *func_02065cb0(void *self);
void *func_02065c98(void *obj);

void func_02066688(int *r0)
{
    *r0 = (int) ((int *) data_020de760);
}

void *func_02066670(void *obj)
{
    void *ptr = (void *) data_020de760;
    *(void **) obj = ptr;
    func_020edb3c(obj);
    return obj;
}

void func_02066650(void *param1)
{
    MI_CpuFill8(param1, 0, 0x100);
    *(unsigned short *) ((char *) param1 + 0xfc) = 0xfff1;
}

unsigned char func_02066648(UnkStruct_02066648 *p)
{
    return p->unk_F9;
}

void func_020665f0(char *a, int b)
{
    void *v0;

    v0 = func_020984e8();
    func_02066650((void *) a);
    *(a + 0xf9) = (char) b;
    *(a + 0xfb) = 0;
    *(a + 0x42) = 2;
    func_020951dc(func_02099870(v0), a + 0x24);
    func_02065eac((unsigned char *) a, 1);
    func_02065e10((void *) a, (const unsigned short *) ((char *) func_02098ddc(func_02099734(v0)) + 0x28));
}

void func_020665b8(void *arg)
{
    char c;
    char *p;
    func_020665f0((char *) arg, 12);
    func_02065eac((unsigned char *) arg, 4);
    func_020666b4((char *) arg + 4);
    c = 0x23;
    p = &c;
    func_02065d0c((const char *) p, (const unsigned short *) ((char *) arg + 0x44), (unsigned char *) ((char *) arg + 0xf8), 0);
}

void func_0206658c(UnkStruct_0206658c *ptr, int index)
{
    int result;
    result = func_0208150c((unsigned int) func_0207cec0((void *) data_021e5a2c, index));
    func_02065e60((struct UnkStruct_02065e60 *) ptr);
    func_020666e4(&ptr->unk_04, result);
}

void func_02066560(int a0, int index)
{
    int r4;
    r4 = (int) func_02099870((void *) (func_02098844(&data_021dc7bc, index)));
    func_02065e60((struct UnkStruct_02065e60 *) a0);
    func_020666d0(a0 + 4, r4);
}

void func_02066514(void *param0)
{
    void *r5;
    void *r6;
    r5 = func_020984e8();
    r6 = func_02099870((void *) ((int) r5));
    if (*(unsigned char *) ((char *) param0 + 0x22) != 1) {
        r5 = func_02098ddc(func_02099734(r5));
        func_02051c08((void *) ((char *) r5 + 0x14), (const void *) ((void *) ((char *) param0 + 0x44)), 10);
        *(unsigned char *) ((char *) param0 + 0xf8) = *(unsigned char *) ((char *) r5 + 0x49);
    }
    func_020666bc((void *) ((char *) param0 + 4), r6);
}

void func_020664e0(int arg)
{
    int result;
    result = (int) func_02065ec0((unsigned char *) arg);
    switch (result) {
        case 1:
            func_02065eac((unsigned char *) arg, 2);
            break;
        case 4:
            func_02065eac((unsigned char *) arg, 5);
            break;
        default:
            return;
    }
    func_02065ef4((unsigned char *) arg, 1);
}

void func_020664a8(void *arg)
{
    int result;

    result = (int) func_02065ec0((unsigned char *) arg);
    switch (result) {
        case 2:
            func_02065eac((unsigned char *) arg, 3);
            break;
        case 5:
            func_02065eac((unsigned char *) arg, 6);
            break;
        case 7:
            func_02065eac((unsigned char *) arg, 8);
            break;
        default:
            break;
    }
}

void func_02066478(void *param0)
{
    unsigned char *ptr;
    unsigned short val;
    void *base;

    base = param0;
    func_02065eac((unsigned char *) base, 2);

    ptr = (unsigned char *) base + 0xfb;
    *ptr = 0x11;

    val = *(unsigned short *) ((unsigned char *) base + 0xfc);
    if (val != 0xfff1) {
        func_02065ef4((unsigned char *) base, 1);
    }
}

void func_020663d4(unsigned char *self, void *src1, void *arg2, void *arg3, void *stackArg5)
{
    unsigned char local_buf[0x60];

    self[0xf8] = (unsigned char) (*(unsigned int *) src1);
    func_020707d0(local_buf);
    func_020a87e0(local_buf, arg2);
    func_02051c08(local_buf + 0xe, self + 0x44, 0xa);

    if ((data_021cd890 & 1) == 0) {
        func_02065cb0(&data_021cd920);
        __register_global_object((void *) (&data_021cd920), (((void *) func_02065c98)), (void *) (&data_021cd8ac));
        data_021cd890 |= 1;
    }

    func_0205195c(&data_021cd920);
    func_020a87e0(&data_021cd920, arg3);
    func_02051c08(&data_021cd92e, self + 0x58, 0x40);
    func_020a87e0(local_buf, stackArg5);
    func_02051c08(local_buf + 0xe, self + 0xd8, 0x10);
    func_020707b8(local_buf);
}

void func_02066344(char *obj, int arg1, int arg2, int arg3, int arg5, unsigned char *arg6, int arg7, int arg8)
{
    unsigned char local0[0x10];
    unsigned char local1[0x20];

    func_02003780(local0);
    func_0209529c(local1);
    func_02003728(local0, arg7);
    func_0209525c(local1, arg8);
    func_02066650(obj);

    obj[0xf9] = *arg6;
    obj[0xfb] = 0;

    func_020666e4((int *) (obj + 0x24), (int) local0);
    func_020666d0((int) (obj + 4), (int) local1);

    if (arg5 < 0) {
        func_020666b0(obj + 4, 5);
        arg5 = 0;
    }

    func_02065eac((unsigned char *) obj, 2);
    func_020663d4((unsigned char *) obj, (void *) (&arg5), (void *) arg1, (void *) arg2, (void *) arg3);

    func_0209526c(local1);
    func_02003750(local0);
}

void func_020662bc(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    int local3;
    UnkStruct_020662bc local1;
    UnkStruct_020662bc local2;

    if (p7 != 11) {
        func_02094fd4((void *) (&local1));
        func_02003618(p5, (void *) (&local1));
        func_0203d7c4(p7, (void *) (&local1));
        func_02094fbc((void *) (&local1));
    }

    func_02094fd4((void *) (&local2));
    func_02095074(p6, (void *) (&local2));
    func_0203d73c((void *) (&local2));
    func_02094fbc((void *) (&local2));

    func_0203d930(((char *) data_021cd8c4), ((char *) data_021cd9b0), ((char *) data_021cd8ec), &local3, p2, p3);
    func_02066344((char *) p1, (int) (((char *) data_021cd8c4)), (int) (((char *) data_021cd9b0)), (int) (((char *) data_021cd8ec)), local3, (unsigned char *) p4, p5, p6);
}

void func_02066228(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int tmp;
    char buf1[0x20];
    char buf2[0x20];

    if (a9 != 0xb) {
        func_02094fd4(buf1);
        func_02003618(a7, buf1);
        func_0203d7c4(a9, buf1);
        func_02094fbc(buf1);
    }

    func_02094fd4(buf2);
    func_02095074(a8, buf2);
    func_0203d73c(buf2);
    func_02094fbc(buf2);

    func_0203d834((unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, &tmp, a1, a2, a3,
                  a4, a5);
    func_02066344((char *) a0, (unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, tmp, (unsigned char *) a6, a7, a8);
}

void func_02066198(void *self, int a2, int a3, int a4, int a5, const unsigned char *a6, int a7, int a8)
{
    int tmp1[4];
    int tmp2[4];

    func_02003780(tmp1);
    func_02003780(tmp2);

    func_02003728(tmp1, a7);
    func_02003728(tmp2, a8);

    func_02066650(self);

    ((unsigned char *) self)[0xf9] = *a6;
    ((unsigned char *) self)[0xfb] = 0;

    func_020666e4((int *) ((unsigned char *) self + 0x24), (int) tmp1);
    func_020666e4((int *) ((unsigned char *) self + 4), (int) tmp2);

    if (a5 < 0) {
        func_020666b0((unsigned char *) self + 4, 5);
        a5 = 0;
    }

    func_02065eac((unsigned char *) self, 7);

    func_020663d4((unsigned char *) self, (void *) (&a5), (void *) a2, (void *) a3, (void *) a4);

    func_02003750(tmp2);
    func_02003750(tmp1);
}

void func_02066104(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
    int local14;
    struct UnkStruct_02066104 local18;
    struct UnkStruct_02066104_2 local38;

    if (a10 != 0xb) {
        func_02094fd4(&local18);
        func_02003618(a8, &local18);
        func_0203d7c4(a10, &local18);
        func_02094fbc(&local18);
    }

    func_02094fd4(&local38);
    func_02003618(a9, &local38);
    func_0203d73c(&local38);
    func_02094fbc(&local38);

    func_0203d834((int) (((char *) data_021cd8c4)), (int) (((char *) data_021cd9b0)), (int) (((char *) data_021cd8ec)), (void *) (&local14), a2, a3, a4, a5, a6);

    func_02066198((void *) a1, (int) (((char *) data_021cd8c4)), (int) (((char *) data_021cd9b0)), (int) (((char *) data_021cd8ec)), local14, (const unsigned char *) a7, a8, a9);

    return;
}

void func_02066088(char *a, int b, int c, int d, int e, unsigned char *fptr, unsigned char *gptr, int h)
{
    UnkStruct_02066088 local;
    func_0209529c((void *) (&local));
    func_0209525c((void *) (&local), h);
    func_02066650((void *) a);
    a[0xf9] = *gptr;
    a[0xfb] = *fptr;
    func_020666b0((void *) (a + 0x24), 4);
    func_020666d0((int) (a + 4), (int) (&local));
    if (e < 0) {
        func_020666b0((void *) (a + 4), 6);
        e = 0;
    }
    func_02065eac((unsigned char *) a, 2);
    func_020663d4((unsigned char *) a, (void *) (&e), (void *) b, (void *) c, (void *) d);
    func_0209526c((void *) (&local));
}

void func_02066024(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int tmp;
    struct {
        char data[0x20];
    } local;

    func_02094fd4(&local);
    func_02095074(p6, &local);
    func_0203d73c(&local);
    func_02094fbc(&local);
    func_0203d930((void *) ((unsigned int) data_021cd8c4), (void *) ((unsigned int) data_021cd9b0), (void *) ((unsigned int) data_021cd8ec), &tmp, p2, p3);
    func_02066088((char *) p1, (unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, tmp, (unsigned char *) p4, (unsigned char *) p5, p6);
}

void func_02065fc4(UnkStruct_02065fc4 *self, int a, int b, int c, int d)
{
    func_02066650(self);
    self->unk_F9 = 0xc;
    func_02065eac((unsigned char *) self, 5);
    func_020666b0(&self->unk_24, 4);
    func_020666b4(&self->unk_04);
    if (d < 0) {
        func_020666b0(&self->unk_04, 6);
        d = 0;
    }
    self->unk_FB = 0xc;
    func_020663d4((unsigned char *) self, (void *) (&d), (void *) a, (void *) b, (void *) c);
}

void func_02065f88(int a, int b, int c)
{
    int result;
    func_0203d930(((char *) data_021cd8c4), ((char *) data_021cd9b0), ((char *) data_021cd8ec), &result, (int) ((const unsigned char *) b), c);
    func_02065fc4((UnkStruct_02065fc4 *) a, (int) (((char *) data_021cd8c4)), (int) (((char *) data_021cd9b0)), (int) (((char *) data_021cd8ec)), result);
}

int func_02065f7c(void *a)
{
    return func_02066708((char *) a + 0x24);
}

void *func_02065f70(void *ptr)
{
    return (void *) func_02066708((char *) ptr + 4);
}

void *func_02065f64(void *ptr)
{
    return func_020666f8((char *) ptr + 4);
}

int func_02065f58(int arg, void *argument1)
{
    return func_02066788(arg + 0x24, (void *) argument1);
}

int func_02065f4c(int a, int b)
{
    return func_02066788(a + 4, (void *) b);
}

unsigned char func_02065f44(UnkStruct_02065f44 *p)
{
    return p->unk_FB;
}

void func_02065f38(void *ptr, void *argument1)
{
    func_0206671c((char *) ptr + 0x24, (void *) argument1);
}

int func_02065f2c(int arg, void *argument1)
{
    return func_0206671c((void *) (arg + 4), (void *) argument1);
}

int func_02065f20(int a)
{
    return func_020666a0(a + 4, 7);
}

unsigned short func_02065f18(UnkStruct_02065f18 *p)
{
    return p->unk_FC;
}

unsigned int func_02065f08(unsigned char *p)
{
    return ((unsigned int) (p[0xFA] & 0xC0) << 18) >> 24;
}

void func_02065ef4(unsigned char *base, unsigned int value)
{
    unsigned char *p = base + 0xFA;
    *p = (*p & 0x3F) | (value << 6);
}

unsigned short func_02065ed0(struct UnkStruct_02065ed0 *obj, unsigned short value, int param)
{
    unsigned short old = obj->unk_FC;
    if (param == 0xFF) {
        param = 0;
    }
    obj->unk_FC = value;
    func_02065ef4((unsigned char *) obj, param);
    return old;
}

unsigned char func_02065ec0(unsigned char *param)
{
    unsigned char val;
    unsigned char result;

    val = *(param + 0xfa);
    result = val & 0x3f;
    return result;
}

void func_02065eac(unsigned char *p, unsigned char x)
{
    *(p + 0xfa) = (*(p + 0xfa) & 0xc0) | x;
}

int func_02065e9c(unsigned char *p)
{
    if (p[0x22] != 1) {
        return 0;
    }
    return 1;
}

void func_02065e60(struct UnkStruct_02065e60 *p)
{
    unsigned char *result;

    if ((unsigned char) (p->unk_22 + 0xfe) <= 1) {
        return;
    }

    result = (unsigned char *) func_02098ddc((void *) ((unsigned int) (int) func_02099734((void *) ((int) (int) func_020984e8()))));
    func_02051c08(result, p->unk_44, 0xa);
    p->unk_F8 = result[0x48];
}

void func_02065e10(void *obj, const unsigned short *p)
{
    unsigned char local[16];

    if (*p != 0) {
        func_02051c08((void *) p, (const void *) ((unsigned char *) obj + 0xd8), 0x10);
    } else {
        func_02051bf8(&local[2], 6);
        func_02065f58((int) obj, &local[2]);
        local[0] = 0x24;
        func_02065d0c((const char *) local, (const unsigned short *) ((unsigned char *) obj + 0xd8), (unsigned char *) (&local[1]), &local[2]);
    }
}

void func_02065db8(unsigned char *base1, unsigned char *base2)
{
    unsigned char *src;
    func_02051c08((void *) (base2 + 0xd8), (const void *) (base1 + 0x28), 0x10);
    if (func_02065f20((int) base2)) {
        return;
    }
    if (func_02065e9c(base2)) {
        src = base1 + 0x14;
        base1[0x49] = base2[0xf8];
    } else {
        src = base1;
        base1[0x48] = base2[0xf8];
    }
    func_02051c08((void *) (base2 + 0x44), (const void *) src, 0xa);
}

void func_02065d0c(const char *arg0, const unsigned short *arg1, unsigned char *out, void *dest)
{
    struct {
        char objA[0x6c];
        char objB[0x0c];
        char buf[0x54];
    } s;
    int val;
    unsigned int len;
    int offset;
    int len2;
    unsigned short *q;
    func_02070c08(s.objA);
    func_020707d0(s.objB);
    func_020b4980(s.objA, arg0, 0);
    func_020a87e0(s.objB, s.objA);
    len = func_02051ce0((unsigned short *) (&s.buf[2]), 0x29, 0);
    *out = (unsigned char) len;
    if (len != 0) {
        func_02051c08((unsigned short *) (&s.buf[2]), arg1, len);
    }
    offset = len;
    if (dest != 0) {
        offset = func_02051c8c_unk(dest, 6);
        func_02051c08(dest, arg1 + len, offset);
        offset = len + offset;
    }
    if (((unsigned short *) (&s.buf[2]))[len] == 0xa) {
        val = len + 1;
        q = ((unsigned short *) (&s.buf[2])) + val;
        len2 = func_02051ce0(q, 0x29 - val, 0);
        if (len2 != 0) {
            func_02051c08(q, arg1 + offset, len2);
        }
    }
    func_020707b8(s.objB);
    func_02070be8(s.objA);
}

void func_02065cc8(void *p)
{
    char buf[2];
    MI_CpuFill8(p, 0, 0x4a);
    buf[0] = 0x23;
    func_02065d0c((const char *) buf, (const unsigned short *) p, (unsigned char *) ((char *) p + 0x48), 0);
    buf[1] = 0x26;
    func_02065d0c((const char *) (buf + 1), (const unsigned short *) ((char *) p + 0x14), (unsigned char *) ((char *) p + 0x49), 0);
}

void *func_02065cb0(void *self)
{
    func_020a88ec(self);
    *(void **) self = ((char *) data_020de770);
    return self;
}

void *func_02065c98(void *obj)
{
    *(void **) obj = data_020de770;
    func_020a887c(obj);
    return obj;
}

struct UnkStruct_02065c78 *func_02065c78(struct UnkStruct_02065c78 *obj)
{
    obj->unk_00 = ((char *) data_020de770);
    func_020a887c((void *) obj);
    func_020edb3c((void *) obj);
    return obj;
}

int func_02065c74(void)
{
    return 64;
}

int func_02065c70(int p0)
{
    return ((int) (p0) + (14));
}
