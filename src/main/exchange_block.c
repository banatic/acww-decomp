/* exchange_block: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020901d8 @ 0x020901d8, 0x34 bytes, Thumb
 * func_020901a0 @ 0x020901a0, 0x38 bytes, Thumb
 * func_0209019c @ 0x0209019c, 0x2 bytes, Thumb
 * func_02090174 @ 0x02090174, 0x28 bytes, Thumb
 * func_02090168 @ 0x02090168, 0xc bytes, Thumb
 * func_0209015c @ 0x0209015c, 0xc bytes, Thumb
 * func_02090158 @ 0x02090158, 0x4 bytes, Thumb
 * func_02090140 @ 0x02090140, 0x18 bytes, Thumb
 * func_02090130 @ 0x02090130, 0x10 bytes, Thumb
 * func_02090124 @ 0x02090124, 0xc bytes, Thumb
 * func_0209010c @ 0x0209010c, 0x18 bytes, Thumb
 * func_02090100 @ 0x02090100, 0xc bytes, Thumb
 * func_020900f4 @ 0x020900f4, 0xc bytes, Thumb
 * func_020900f0 @ 0x020900f0, 0x2 bytes, Thumb
 * func_020900e4 @ 0x020900e4, 0xc bytes, Thumb
 * func_020900d8 @ 0x020900d8, 0xc bytes, Thumb
 * func_020900ac @ 0x020900ac, 0x2c bytes, Thumb
 * func_0209008c @ 0x0209008c, 0x20 bytes, Thumb
 * func_02090078 @ 0x02090078, 0x14 bytes, Thumb
 * func_02090040 @ 0x02090040, 0x38 bytes, Thumb
 */

struct Func02090168Struct {
    char pad_00[0x94a];
    unsigned short unk_94A;
};

typedef struct {
    unsigned char pad_00[0x94a];
    unsigned short value;
} UnkStruct_0209015c;

struct UnkStruct_0209010c {
    unsigned char pad_00[0x938];
    unsigned char counter;
};

extern void func_02066694(void *);
extern int func_020b1a64(void *);
extern int func_02079914(void *);
extern int func_02088460(void *);
extern void *func_02088450(char *);
extern int func_02079904(char *);
extern void *func_020b1a54(char *);
extern void func_02066688(char *);
extern void MI_CpuFill8(void *a, int b, int c);
extern void func_02066650(void *a);
extern void func_020b1a24(void *a);
extern int __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char data_021d36d4[];
extern unsigned char data_021ee418[];

void *func_020901d8(void *arg)
{
    func_02066694(arg);
    func_020b1a64((char *) arg + 0x100);
    func_02079914((char *) arg + 0x14c);
    func_02088460((char *) arg + 0x93a);
    return arg;
}

char *func_020901a0(char *p)
{
    func_02088450(p + 0x93A);
    func_02079904(p + 0x14C);
    func_020b1a54(p + 0x100);
    func_02066688(p);
    return p;
}

void func_0209019c(void *object) {}

void func_02090174(char *arg)
{
    MI_CpuFill8(arg, 0, 0x950);
    func_02066650(arg);
    func_020b1a24(arg + 0x100);
}

void func_02090168(struct Func02090168Struct *s, unsigned short value)
{
    s->unk_94A = value;
}

unsigned short func_0209015c(UnkStruct_0209015c *arg0)
{
    return arg0->value;
}

int func_02090158(void *object)
{
    return 1;
}

void func_02090140(unsigned char *addr, unsigned int value)
{
    addr[0x939] = (addr[0x939] & ~1) | (value & 1);
}

int func_02090130(int p0)
{
    return (int) ((unsigned int) ((*(unsigned char *) ((char *) (p0) + (2361)) << 31)) >> 31);
}

int func_02090124(int a)
{
    return a + 0x93A;
}

void func_0209010c(struct UnkStruct_0209010c *s)
{
    int new;
    new = s->counter + 1;
    if (new > 5) {
        new = 5;
    }
    s->counter = new;
}

void func_02090100(unsigned char *r0)
{
    unsigned char *ptr;
    unsigned char value;

    value = 0;
    ptr = r0 + 0x938;
    *ptr = value;
}

unsigned char func_020900f4(unsigned char *arg0)
{
    return arg0[0x938];
}

void *func_020900f0(void *record)
{
    return record;
}

int func_020900e4(int r0)
{
    return r0 + 0x100;
}

int func_020900d8(int a)
{
    return a + 0x14c;
}

int func_020900ac(int arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 0x950, (((void (*)(void *)) func_020901d8)),
                   (((void (*)(void *))(void *(*) (void *) ) func_020901a0)));
    return arg;
}

int func_0209008c(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 3, 0x950, (((void (*)(void *))(void *(*) (void *) ) func_020901a0)));
    return arg;
}

int func_02090078(int index)
{
    return (int) (data_021d36d4 + 0x950 * index);
}

int func_02090040(int param)
{
    switch (param) {
        case 1:
            return func_02090078(0);
        case 2:
            return func_02090078(1);
        case 3:
            return func_02090078(2);
        default:
            return (unsigned int) data_021ee418;
    }
}
