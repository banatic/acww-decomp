/* star_view_input_2: 5 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229bc10 @ 0x0229bc10, 0x20 bytes, Thumb
 * func_ov128_0229bbe4 @ 0x0229bbe4, 0x2c bytes, Thumb
 * func_ov128_0229bb60 @ 0x0229bb60, 0x84 bytes, Thumb
 * func_ov128_0229bb20 @ 0x0229bb20, 0x40 bytes, Thumb
 * func_ov128_0229bae0 @ 0x0229bae0, 0x40 bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *ptr);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);
extern int func_ov127_022998a8(void *);
extern unsigned char data_ov128_0229cca0[];
extern unsigned char data_ov128_0229cc20[];
extern int func_ov127_0229989c(char *addr);
extern int func_ov127_02299890(char *addr);
extern void func_ov128_0229ba54(void *p);
extern unsigned short data_021fbe40;

void func_ov128_0229bc10(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x110);
    func_ov002_02208098((void *) (self), 8);
}

void func_ov128_0229bbe4(char *self)
{
    unsigned char *p;
    unsigned char val;

    func_ov002_0220a164((void *) (self + 0x110));
    p = (unsigned char *) self;
    p += 0x8d;
    val = *p;
    self[0x2d6a] = val;
    func_ov002_02208098((void *) (self), 9);
}

void func_ov128_0229bb60(unsigned char *a, unsigned char *b)
{
    unsigned char *p;
    int t;

    p = b + 0x60;
    func_02088df8(1, data_ov128_0229cca0, 0x80, (int) (p - *(unsigned int *) (a + 0x2d58)), -1, 2, 0x1000, 0x1000, 0, -1, 0,
                  0);
    t = (int) (p + func_ov127_022998a8(a + 0x4a4));
    func_02088df8(1, data_ov128_0229cc20, 0x80 - *(unsigned int *) (a + 0x2d54), t, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov128_0229bb20(void *p)
{
    int a;
    int b;

    a = func_ov127_0229989c((char *) p + 0x4A4);
    b = func_ov127_02299890((char *) p + 0x4A4);
    *(int *) ((char *) p + 0x2D54) = a & 0xF;
    *(int *) ((char *) p + 0x2D58) = b & 0xF;
    func_ov128_0229ba54(p);
}

// Keypad decode: maps keys 0x20/0x10/0x40/0x80 to 0/1/3/2, default 4.
int func_ov128_0229bae0(void *receiver)
{
    int r = 4;
    unsigned short flags = data_021fbe40;
    if (flags & 0x20) {
        r = 0;
    } else if (flags & 0x10) {
        r = 1;
    } else if (flags & 0x40) {
        r = 3;
    } else if (flags & 0x80) {
        r = 2;
    }
    return r;
}
