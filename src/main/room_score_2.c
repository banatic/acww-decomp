/* room_score_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205bbf4 @ 0x0205bbf4, 0x6c bytes, Thumb
 * func_0205bbe8 @ 0x0205bbe8, 0xc bytes, Thumb
 * func_0205bbdc @ 0x0205bbdc, 0xc bytes, Thumb
 * func_0205bbc4 @ 0x0205bbc4, 0x18 bytes, Thumb
 * func_0205bbac @ 0x0205bbac, 0x18 bytes, Thumb
 * func_0205bba0 @ 0x0205bba0, 0xc bytes, Thumb
 * func_0205bb80 @ 0x0205bb80, 0x20 bytes, Thumb
 * func_0205bb60 @ 0x0205bb60, 0x20 bytes, Thumb
 * func_0205bb48 @ 0x0205bb48, 0x18 bytes, Thumb
 * func_0205bb30 @ 0x0205bb30, 0x18 bytes, Thumb
 * func_0205bb24 @ 0x0205bb24, 0xc bytes, Thumb
 * func_0205bae8 @ 0x0205bae8, 0x3c bytes, Thumb
 * func_0205baac @ 0x0205baac, 0x3c bytes, Thumb
 */

typedef struct UnkStruct_0205bbac {
    void *unk_00;
} UnkStruct_0205bbac;

extern int func_0205a370(int *a, int *b, int *c, int *d, int e);
extern int func_0205bc60(unsigned char *out, int p2, int x, int y, int z, int w, int v);
extern int data_020dd404;
extern unsigned char data_020dd3b8;
extern int func_0204df30(int p1);
extern void *func_02060ee0(void *, int);
extern void *func_02061204(void *, int);
extern int data_021ebcd4;
extern unsigned short *func_020611e8(void *pointer, int flag);
extern int data_020dd3a4;
extern unsigned int data_021c95f0;
extern int func_0207cec0(void *, int);
extern unsigned char func_0207f30c(unsigned char *);
extern unsigned int func_0207f300(unsigned int x);
extern unsigned char data_021e5a2c[];

void func_0205bbf4(unsigned char *out, int p2)
{
    int a, b, c, d;
    func_0205a370(&a, &b, &c, &d, p2);
    out[0] = func_0205bc60(out, p2, a, a + 1, c, d, 1);
    out[1] = func_0205bc60(out, p2, a, b, d - 1, d, 4);
    out[2] = func_0205bc60(out, p2, b - 1, b, c, d, 2);
}

void func_0205bbe8(void **p)
{
    *p = &data_020dd404;
}

void func_0205bbdc(int *p)
{
    *p = (int) &data_020dd404;
}

void *func_0205bbc4(void *self)
{
    func_0205bbe8((void **) self);
    *(void **) self = (void *) &data_020dd3b8;
    return self;
}

UnkStruct_0205bbac *func_0205bbac(UnkStruct_0205bbac *self)
{
    self->unk_00 = ((char *) &data_020dd3b8);
    func_0205bbdc((int *) self);
    return self;
}

void func_0205bba0(int a, int b)
{
    func_0204df30(b);
}

void func_0205bb80(unsigned short *dst, int unused, int param)
{
    *dst = *(unsigned short *) func_02061204(func_02060ee0(&data_021ebcd4, param), 0);
}

void func_0205bb60(unsigned short *out, int unused, int idx)
{
    unsigned short *value = func_020611e8(func_02060ee0(((unsigned int *) &data_021ebcd4), idx), 0);
    *out = *value;
}

void *func_0205bb48(void *ptr)
{
    func_0205bbe8((void **) ptr);
    *(void **) ptr = (void *) &data_020dd3a4;
    return ptr;
}

void *func_0205bb30(void *this)
{
    *(void **) this = (void *) ((char *) &data_020dd3a4);
    func_0205bbdc((int *) this);
    return this;
}

unsigned int func_0205bb24(void)
{
    return data_021c95f0;
}

void func_0205bae8(unsigned short *out, int unused, int c)
{
    unsigned char *tested_value0;
    if ((tested_value0 = (unsigned char *) (func_0207cec0(((unsigned int *) data_021e5a2c), c))) != 0) {
        unsigned int v = func_0207f30c(tested_value0);
        unsigned short val;
        if (v < 0x44) {
            val = (unsigned short) (v + 0x1100);
        } else {
            val = 0x1100;
        }
        *out = val;
    } else {
        *out = 0x1100;
    }
}

void func_0205baac(unsigned short *out, int a, int b)
{
    unsigned int r;

    r = (unsigned int) func_0207cec0((void *) data_021e5a2c, b);
    if (r != 0) {
        r = func_0207f300(r);
        if (r < 0x44) {
            r = (unsigned short) (r + 0x1144);
        } else {
            r = 0x1144;
        }
        *out = r;
    } else {
        *out = 0x1144;
    }
}
