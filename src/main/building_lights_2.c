/* building_lights_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3650 @ 0x020b3650, 0x8 bytes, Thumb
 * func_020b364c @ 0x020b364c, 0x2 bytes, Thumb
 * func_020b3634 @ 0x020b3634, 0x18 bytes, Thumb
 * func_020b35e8 @ 0x020b35e8, 0x4a bytes, Thumb
 * func_020b35e0 @ 0x020b35e0, 0x8 bytes, Thumb
 * func_020b35d8 @ 0x020b35d8, 0x8 bytes, Thumb
 * func_020b35c0 @ 0x020b35c0, 0x18 bytes, Thumb
 * func_020b3598 @ 0x020b3598, 0x26 bytes, Thumb
 * func_020b356c @ 0x020b356c, 0x2c bytes, Thumb
 * func_020b3550 @ 0x020b3550, 0x1c bytes, Thumb
 */

typedef struct {
    void *vtable;
    int pad_04;
    char sub[1];
} UnkStruct_020b3550;

extern int func_02057a50(unsigned int, const unsigned char *);
extern unsigned char data_020e5108[];
extern unsigned int NNS_G3dMdlSetMdlDiff(int a, signed char b, unsigned short c);
extern char data_020e50fc[];
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern int data_020e50dc;
extern void func_020b3740(void *);
extern void func_020b373c(void *ptr);

void func_020b3650(signed char *p0)
{
    p0[0] = (~0);
}

void func_020b364c(void *object) {}

void func_020b3634(char *out, unsigned int in)
{
    *out = func_02057a50(in, data_020e5108);
}

void func_020b35e8(signed char *p, int a, int y)
{
    signed char c;
    c = *p;
    if (c == -1) {
        return;
    }
    NNS_G3dMdlSetMdlDiff(a, c,
                         (unsigned short) (((unsigned char) ((y * 13) >> 12) << 10) |
                                           ((unsigned char) ((y * 31) >> 12) | ((unsigned char) ((y * 27) >> 12) << 5))));
}

void func_020b35e0(signed char *p0)
{
    p0[0] = (~0);
}

void func_020b35d8(signed char *p0)
{
    p0[0] = (~0);
}

void func_020b35c0(unsigned char *out, int arg)
{
    *out = (unsigned char) func_02057a50(arg, (const unsigned char *) data_020e50fc);
}

void func_020b3598(signed char *str, void *arg1, int r2)
{
    signed char ch = *str;
    if (ch == -1) {
        return;
    }
    NNS_G3dMdlSetMdlAlpha(arg1, ch, (unsigned char) (((r2 * 29) >> 12) + 1));
}

void *func_020b356c(void *self)
{
    unsigned int i;
    *(int *) self = (int) &data_020e50dc;
    func_020b3740((char *) self + 8);
    for (i = 0; i < 3; i++) {
        ((signed char *) self + i)[4] = -1;
    }
    return self;
}

UnkStruct_020b3550 *func_020b3550(UnkStruct_020b3550 *this)
{
    this->vtable = ((char *) &data_020e50dc);
    func_020b373c(this->sub);
    return this;
}
