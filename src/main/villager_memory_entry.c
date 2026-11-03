/* villager_memory_entry: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02081cd8 @ 0x02081cd8, 0x14 bytes, Thumb
 * func_02081cc4 @ 0x02081cc4, 0x12 bytes, Thumb
 * func_02081c94 @ 0x02081c94, 0x30 bytes, Thumb
 * func_02081c70 @ 0x02081c70, 0x22 bytes, Thumb
 * func_02081c40 @ 0x02081c40, 0x30 bytes, Thumb
 * func_02081c14 @ 0x02081c14, 0x2a bytes, Thumb
 * func_02081c00 @ 0x02081c00, 0x14 bytes, Thumb
 * func_02081bc4 @ 0x02081bc4, 0x3c bytes, Thumb
 * func_02081ba0 @ 0x02081ba0, 0x22 bytes, Thumb
 * func_02081b68 @ 0x02081b68, 0x38 bytes, Thumb
 * func_02081b54 @ 0x02081b54, 0x14 bytes, Thumb
 * func_02081b24 @ 0x02081b24, 0x30 bytes, Thumb
 * func_02081b00 @ 0x02081b00, 0x22 bytes, Thumb
 * func_02081ac8 @ 0x02081ac8, 0x38 bytes, Thumb
 * func_02081ac0 @ 0x02081ac0, 0x8 bytes, Thumb
 * func_02081abc @ 0x02081abc, 0x4 bytes, Thumb
 * func_02081aa8 @ 0x02081aa8, 0x14 bytes, Thumb
 * func_02081a90 @ 0x02081a90, 0x18 bytes, Thumb
 * func_02081a88 @ 0x02081a88, 0x6 bytes, Thumb
 * func_02081a80 @ 0x02081a80, 0x6 bytes, Thumb
 * func_02081a14 @ 0x02081a14, 0x6a bytes, Thumb
 * func_02081a04 @ 0x02081a04, 0x10 bytes, Thumb
 * func_020819f0 @ 0x020819f0, 0x14 bytes, Thumb
 * func_020819e0 @ 0x020819e0, 0x10 bytes, Thumb
 * func_020819d0 @ 0x020819d0, 0x10 bytes, Thumb
 * func_020819bc @ 0x020819bc, 0x14 bytes, Thumb
 * func_020819ac @ 0x020819ac, 0x10 bytes, Thumb
 * func_0208199c @ 0x0208199c, 0x10 bytes, Thumb
 * func_02081988 @ 0x02081988, 0x14 bytes, Thumb
 */

struct UnkStruct_02081cd8 {
    unsigned char pad_00[0x7c];
    unsigned short flag : 1;
};

typedef struct {
    char pad_00[0x7c];
    unsigned short unk_7C;
} UnkStruct_02081cc4;

struct UnkStruct_02081c00 {
    unsigned char pad_00[0x7c];
    unsigned short : 1;
    unsigned short flag : 1;
};

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short : 2;
    unsigned short bit2 : 1;
} UnkStruct_02081aa8;

typedef struct {
    unsigned char pad_00[109];
    unsigned char unk_6D;
} UnkStruct_02081a88;

typedef struct {
    unsigned char pad_00[109];
    unsigned char unk_6D;
} UnkStruct_02081a80;

struct UnkStruct_02081a14 {
    char pad_00[0x70];
    unsigned int unk_70;
};

struct UnkStruct_020819bc {
    unsigned char pad_00[0x7c];
    unsigned short : 6;
    unsigned short flag : 1;
};

typedef struct {
    char pad_00[0x7c];
    unsigned short flag;
} UnkStruct_020819ac;

typedef struct {
    char pad_00[0x7c];
    unsigned short unk_7C;
} UnkStruct_0208199c;

typedef struct {
    unsigned char pad_00[0x7C];
    unsigned short : 7;
    unsigned short flag : 1;
} UnkStruct_02081988;

extern void *func_02094f7c(void *);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_02094f64(void *);
extern void func_0205195c(void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a87e0(void *, void *);
extern void func_02094f34(void *, void *, int);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern void *func_020820a0(void *);
extern void *func_02082088(void *);
extern void *func_02081ff0(void *);
extern void *func_02081fd8(void *);
extern int func_020644cc(int count);

void func_02081c70(void *param0, void *param1);
void func_02081ba0(void *r0, void *r1);
void func_02081b00(void *arg0, void *arg1);

int func_02081cd8(struct UnkStruct_02081cd8 *s)
{
    return (s->flag == 1);
}

void func_02081cc4(UnkStruct_02081cc4 *p)
{
    p->unk_7C = (p->unk_7C & ~1) | 1;
}

void func_02081c94(void *param0, void *param1)
{
    unsigned char local[0x1c];

    func_02094f7c(local);
    func_02081c70(param0, local);
    func_020a8a70(param1, local, 0, 0);
    func_02094f64(local);
}

void func_02081c70(void *param0, void *param1)
{
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_0205195c(r4);
    func_020a8874(r4, (char *) r5 + 0x1e, 6);
}

void *func_02081c40(void *param0, void *param1)
{
    char sp[0x1c];
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_02094f7c(sp);
    func_020a87e0(sp, r4);
    func_02094f34(sp, (char *) r5 + 0x1e, 6);
    return func_02094f64(sp);
}

void func_02081c14(void *param0, void *param1, int param2)
{
    int r4;
    void *r5;
    void *r6;

    r5 = param0;
    r6 = param1;
    r4 = param2;

    MI_CpuFill8((char *) r5 + 0x1e, 0, 0xc);

    if (r4 > 6) {
        r4 = 6;
    }

    MI_CpuCopy8(r6, (char *) r5 + 0x1e, r4 << 1);

    return;
}

int func_02081c00(struct UnkStruct_02081c00 *s)
{
    if (s->flag == 1) {
        return 1;
    } else {
        return 0;
    }
}

void *func_02081bc4(void *p0, void *p1)
{
    char local[0x24];
    func_020820a0(local);
    func_02081ba0(p0, local);
    func_020a8874(local, (char *) p0 + 0x2a, 0xa);
    func_020a8a70(p1, local, 0, 0);
    return func_02082088(local);
}

void func_02081ba0(void *r0, void *r1)
{
    void *r5 = r0;
    void *r4 = r1;

    func_0205195c(r4);
    func_020a8874(r4, (char *) r5 + 0x2a, 0xa);
}

void func_02081b68(void *a, void *b, int c)
{
    void *p;
    int i;
    unsigned short *s;

    p = (void *) ((char *) a + 0x2a);
    MI_CpuFill8(p, 0, 0x14);
    if (c > 10) {
        c = 10;
    }
    MI_CpuCopy8(b, (const void *) ((char *) a + 0x2a), c << 1);
    s = (unsigned short *) ((char *) a + 0x7c);
    *s |= 2;
}

int func_02081b54(void *arg)
{
    unsigned short h = *(unsigned short *) ((char *) arg + 0x7c);
    if ((((unsigned int) h << 28) >> 31) == 1) {
        return 1;
    } else {
        return 0;
    }
}

void func_02081b24(void *param0, void *param1)
{
    unsigned char stack[0x24];
    func_02081ff0(stack);
    func_02081b00(param0, stack);
    func_020a8a70(param1, stack, 0, 0);
    func_02081fd8(stack);
}

void func_02081b00(void *arg0, void *arg1)
{
    void *r5;
    void *r4;
    void *sp_4;

    r5 = arg0;
    r4 = arg1;
    func_0205195c(r4);
    r5 = (char *) r5 + 0x3e;
    func_020a8874(r4, r5, 0xa);
    return;
}

void func_02081ac8(void *param0, void *param1, int param2)
{
    int capped;
    unsigned short *flags;

    capped = param2;
    MI_CpuFill8((char *) param0 + 0x3e, 0, 0x14);
    if (capped > 0xa) {
        capped = 0xa;
    }
    MI_CpuCopy8((void *) param1, (const void *) ((char *) param0 + 0x3e), capped << 1);
    flags = (unsigned short *) ((char *) param0 + 0x7c);
    *flags = (unsigned short) (*flags | 8);
}

void func_02081ac0(int p0, unsigned short *p1)
{
    *(unsigned short *) ((char *) (((int) (p0) + (106))) + (0)) = p1[0];
}

int func_02081abc(int p0)
{
    return ((int) (p0) + (106));
}

int func_02081aa8(UnkStruct_02081aa8 *s)
{
    return (s->bit2 == 1) ? 1 : 0;
}

void func_02081a90(void *obj, void *src)
{
    *((unsigned short *) ((char *) obj + 0x7c)) |= 4;
    *((unsigned long long *) ((char *) obj + 0x74)) = *((unsigned long long *) src);
}

unsigned char func_02081a88(UnkStruct_02081a88 *p)
{
    return p->unk_6D;
}

void func_02081a80(UnkStruct_02081a80 *p, unsigned char v)
{
    p->unk_6D = v;
}

int func_02081a14(struct UnkStruct_02081a14 *this)
{
    int count = 0;
    int i;
    int rnd;
    int result = 0;
    if (this->unk_70 == -1) {
        this->unk_70 = 0;
    }
    for (i = 0; i < 32; i++) {
        if (((this->unk_70 >> i) & 1) == 0) {
            count++;
        }
    }
    rnd = func_020644cc(count);
    for (i = 0; i < 32; i++) {
        if (((this->unk_70 >> i) & 1) == 0) {
            if (rnd == 0) {
                result = i;
                break;
            }
            rnd--;
        }
    }
    if (count == 1) {
        this->unk_70 = 0;
    }
    this->unk_70 |= (1 << result);
    return result;
}

void func_02081a04(unsigned short *data)
{
    data[0x3e] |= 0x10;
}

int func_020819f0(void *ptr)
{
    unsigned short v = *(unsigned short *) ((char *) ptr + 0x7c);
    if (((unsigned int) v << 27) >> 31) {
        return 1;
    } else {
        return 0;
    }
}

void func_020819e0(unsigned short *p)
{
    p[0x3e] |= 0x40;
}

void func_020819d0(unsigned short *arg)
{
    arg[0x3E] &= ~0x40;
}

int func_020819bc(struct UnkStruct_020819bc *s)
{
    if (s->flag) {
        return 1;
    } else {
        return 0;
    }
}

void func_020819ac(UnkStruct_020819ac *s)
{
    s->flag |= 0x80;
}

void func_0208199c(UnkStruct_0208199c *s)
{
    s->unk_7C &= ~0x80;
}

int func_02081988(UnkStruct_02081988 *p)
{
    if (p->flag) {
        return 1;
    } else {
        return 0;
    }
}
