/* shop_points: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020adf74 @ 0x020adf74, 0x16 bytes, Thumb
 * func_020adf64 @ 0x020adf64, 0x10 bytes, Thumb
 * func_020adf5c @ 0x020adf5c, 0x8 bytes, Thumb
 * func_020adf54 @ 0x020adf54, 0x8 bytes, Thumb
 * func_020adf50 @ 0x020adf50, 0x2 bytes, Thumb
 * func_020adf40 @ 0x020adf40, 0x10 bytes, Thumb
 * func_020adf3c @ 0x020adf3c, 0x2 bytes, Thumb
 * func_020adf34 @ 0x020adf34, 0x6 bytes, Thumb
 * func_020ade78 @ 0x020ade78, 0xbc bytes, Thumb
 * func_020ade44 @ 0x020ade44, 0x34 bytes, Thumb
 * func_020ade0c @ 0x020ade0c, 0x38 bytes, Thumb
 * func_020adde4 @ 0x020adde4, 0x28 bytes, Thumb
 * func_020addd0 @ 0x020addd0, 0x14 bytes, Thumb
 * func_020adda8 @ 0x020adda8, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
} UnkStruct_020adf34;

typedef struct {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
} Hdr;

extern int func_02073d90(void *);
extern void *func_020984e8(void);
extern void *func_020996a0(void *);
extern int func_02099020(void *, int);
extern void func_02066694(void *);
extern void *func_02099870(void *);
extern void func_02066024(void *, Hdr *, void *, void *, void *, void *);
extern unsigned short func_02065ed0(void *, unsigned short, int);
extern int func_020979f0(void *, int);
extern void func_02098ff8(void *, int);
extern void func_02066688(void *);
extern void *data_020ccf94;
extern const unsigned short data_020d1e34[];
extern unsigned char data_020e4150[];
extern unsigned char data_020e4154[];
extern unsigned char data_020e4190[];
extern int func_020afb24(void *p);
extern unsigned char data_021f395c[];
extern unsigned short data_020d1e3c[];

void func_020adf54(void *argument0);
unsigned int func_020adf40(unsigned int arg);
void func_020adf3c(void);
void func_020adf34(UnkStruct_020adf34 *p);
int func_020adde4(unsigned int arg);
unsigned short func_020addd0(unsigned param);

int func_020adf74(int arg)
{
    func_020adf40(arg);
    func_020adf54((void *) arg);
    return arg;
}

unsigned int func_020adf64(unsigned int arg)
{
    func_020adf3c();
    return arg;
}

void func_020adf5c(void *argument0)
{
    func_020adf34((UnkStruct_020adf34 *) ((void *) argument0));
}

void func_020adf54(void *argument0)
{
    func_020adf5c((void *) argument0);
}

unsigned short *func_020adf50(void *record)
{
    return record;
}

unsigned int func_020adf40(unsigned int arg)
{
    func_020adf34((UnkStruct_020adf34 *) arg);
    return arg;
}

void func_020adf3c(void) {}

void func_020adf34(UnkStruct_020adf34 *p)
{
    p->unk_00 = 0;
}

void func_020ade78(void)
{
    int zero;
    Hdr hdr;
    char buf[0x104];
    void *h;
    unsigned int i, n;
    int id;

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    h = func_020984e8();
    if (h == 0) {
        return;
    }
    n = (unsigned int) func_020adde4((unsigned short) (*func_020adf50(func_020996a0(h))));
    if (n == 0) {
        return;
    }
    zero = 0;
    for (i = 0; i < n; i++) {
        id = i + 0x1c;
        if (i < 4 && func_02099020(h, id) == 0) {
            func_02066694(buf);
            hdr.b = (unsigned char) i;
            func_02066024(buf, &hdr, (void *) data_020e4190, (void *) data_020e4150, (void *) data_020e4154, func_02099870(h));
            func_02065ed0(buf, data_020d1e34[i & 3], 1);
            if (func_020979f0(buf, zero) != 0) {
                func_02098ff8(h, id);
            }
            func_02066688(buf);
        }
    }
}

void func_020ade44(unsigned short *p, int delta)
{
    int res1;
    int tmp;
    int res2;

    res1 = func_020adde4(*p);
    tmp = delta + *p;
    if (tmp >= 50000) {
        tmp = 50000;
    }
    *p = (unsigned short) tmp;
    res2 = func_020adde4(*p);
    if (res1 != res2) {
        func_020ade78();
    }
}

void func_020ade0c(int arg0, int arg1)
{
    unsigned short r4;
    r4 = (unsigned short) (arg1 / 100);
    if (func_020afb24((void *) data_021f395c)) {
        r4 = (unsigned short) (r4 * 5);
    }
    func_020ade44((unsigned short *) arg0, (unsigned short) r4);
}

int func_020adde4(unsigned int arg)
{
    int i;
    for (i = 4; i >= 0; i--) {
        if (arg >= (unsigned int) func_020addd0(i)) {
            return i;
        }
    }
    return 0;
}

unsigned short func_020addd0(unsigned param)
{
    if (param < 5) {
        return data_020d1e3c[param];
    }
    return 0;
}

unsigned short func_020adda8(unsigned short *param)
{
    int b;

    b = func_020adde4(*param);
    if (b != 4) {
        return (unsigned short) ((int) func_020addd0(b + 1) - *param);
    } else {
        return 0;
    }
}
