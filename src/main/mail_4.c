/* mail_4: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020980c4 @ 0x020980c4, 0x2c bytes, Thumb
 * func_020980a4 @ 0x020980a4, 0x20 bytes, Thumb
 * func_02098090 @ 0x02098090, 0x12 bytes, Thumb
 * func_02098068 @ 0x02098068, 0x28 bytes, Thumb
 * func_0209805c @ 0x0209805c, 0xc bytes, Thumb
 * func_02098050 @ 0x02098050, 0xc bytes, Thumb
 * func_02098024 @ 0x02098024, 0x2c bytes, Thumb
 * func_02098004 @ 0x02098004, 0x20 bytes, Thumb
 * func_02097ff0 @ 0x02097ff0, 0x12 bytes, Thumb
 * func_02097fa4 @ 0x02097fa4, 0x4c bytes, Thumb
 * func_02097f98 @ 0x02097f98, 0xc bytes, Thumb
 * func_02097f88 @ 0x02097f88, 0x10 bytes, Thumb
 * func_02097f70 @ 0x02097f70, 0x18 bytes, Thumb
 */

typedef struct {
    char pad_00[0x0a04];
    unsigned short unk_A04;
} UnkStruct_02097f88;

extern void func_02066688(void *);
extern void func_02066694(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02066650(void *);

int func_020980c4(int param)
{
    __cxa_vec_ctor((void *) (param), 10, 256, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    return param;
}

void *func_020980a4(void *p)
{
    __cxa_vec_cleanup((void *) (p), 10, 0x100, (void (*)(void *)) func_02066688);
    return p;
}

char *func_02098090(char *base, int idx)
{
    if (idx >= 0 && idx < 10) {
        return base + (idx << 8);
    }
    return 0;
}

void func_02098068(void *param)
{
    int i;
    for (i = 0; i < 10; i++) {
        func_02066650((char *) param + (i << 8));
    }
    *(unsigned short *) ((char *) param + 0xa00) = 0;
}

unsigned short func_0209805c(const unsigned short *ptr)
{
    return ptr[0x500];
}

void func_02098050(unsigned short *ptr, unsigned int value)
{
    ptr[0x500] = value;
}

int func_02098024(int x)
{
    __cxa_vec_ctor((void *) (x), 10, 0x100, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    return x;
}

int func_02098004(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 0xa, 0x100, (void (*)(void *)) func_02066688);
    return arg;
}

int func_02097ff0(int a, int b)
{
    if (b >= 0 && b < 10) {
        return a + (b << 8);
    }
    return 0;
}

void func_02097fa4(void *p)
{
    int i;
    unsigned short *s;
    unsigned char *b;
    int j;

    for (i = 0; i < 10; i++) {
        func_02066650((char *) p + (i << 8));
    }

    s = (unsigned short *) ((char *) p + 0xa04);
    *s = 0;

    b = (unsigned char *) p + 0xa00;
    *b = 1;
    b = (unsigned char *) p + 0xa01;
    *b = 1;
    b = (unsigned char *) p + 0xa02;
    *b = 0;
    b = (unsigned char *) p + 0xa03;
    *b = 0;
}

unsigned int func_02097f98(unsigned int r0)
{
    return r0 + 0x00000a00;
}

void func_02097f88(UnkStruct_02097f88 *s, unsigned short val)
{
    s->unk_A04 |= val;
}

int func_02097f70(void *ptr, unsigned int mask)
{
    unsigned short val;
    val = *(unsigned short *) ((char *) ptr + 0x0a04);
    return (val & mask) ? 1 : 0;
}
