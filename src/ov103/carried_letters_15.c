/* carried_letters_15: 11 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229cd1c @ 0x0229cd1c, 0x30 bytes, Thumb
 * func_ov103_0229cce8 @ 0x0229cce8, 0x34 bytes, Thumb
 * func_ov103_0229ccb4 @ 0x0229ccb4, 0x34 bytes, Thumb
 * func_ov103_0229cc80 @ 0x0229cc80, 0x34 bytes, Thumb
 * func_ov103_0229cc70 @ 0x0229cc70, 0x10 bytes, Thumb
 * func_ov103_0229cc3c @ 0x0229cc3c, 0x34 bytes, Thumb
 * func_ov103_0229cc08 @ 0x0229cc08, 0x34 bytes, Thumb
 * func_ov103_0229cbec @ 0x0229cbec, 0x1c bytes, Thumb
 * func_ov103_0229cbac @ 0x0229cbac, 0x40 bytes, Thumb
 * func_ov103_0229cb90 @ 0x0229cb90, 0x1c bytes, Thumb
 * func_ov103_0229cb60 @ 0x0229cb60, 0x30 bytes, Thumb
 */

extern int func_ov103_0229cdfc(int arg0, unsigned int arg1);
extern int func_ov103_0229cde8(int, int);
extern void func_ov094_0229b8b4(int, int, int);
extern int func_ov094_0229b8d8(char *p, int n);
extern int func_ov094_0229b384(int a, int b);
extern int func_ov094_0229b328(char *p, int x);
extern void func_ov094_0229a898(void *dst, int val, int size);
extern int func_ov094_0229b788(void *p, int n);
extern int func_ov094_0229b30c(void *a, int b);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229b950(int, int);
extern void func_ov094_0229ab0c(void *p);
extern void func_ov094_0229b944(void *p);
extern void func_ov094_0229b938(int, int);

void func_ov103_0229cd1c(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;

    if (func_ov103_0229cdfc(a, b) != 0) {
        int r0 = func_ov103_0229cde8(r5, r4);
        func_ov094_0229b8b4(r5 + 0xb2c, r0, r6);
    }
}

int func_ov103_0229cce8(void *p, int n)
{
    if (func_ov103_0229cdfc((int) p, n) != 0) {
        return func_ov094_0229b8d8((char *) p + 0xb2c, func_ov103_0229cde8((int) p, n));
    }
    return 0;
}

int func_ov103_0229ccb4(int a, int b)
{
    if (func_ov103_0229cdfc(a, b) != 0) {
        int r = func_ov103_0229cde8(a, b);
        return func_ov094_0229b384(a + 0xb2c, r);
    } else {
        return 0;
    }
}

int func_ov103_0229cc80(void *a, int b)
{
    if (func_ov103_0229cdfc((int) a, b)) {
        return func_ov094_0229b328((char *) a + 0xb2c, func_ov103_0229cde8((int) a, b));
    }
    return 0;
}

void func_ov103_0229cc70(void *p)
{
    func_ov094_0229a898((char *) p + 0xcc, 0, 0xe);
}

int func_ov103_0229cc3c(void *a, int b)
{
    if (func_ov103_0229cdfc((int) a, b)) {
        return func_ov094_0229b788((char *) a + 0xb2c, func_ov103_0229cde8((int) a, b));
    }
    return 0;
}

int func_ov103_0229cc08(void *a, void *b)
{
    if (func_ov103_0229cdfc((int) a, (unsigned int) b) != 0) {
        int tmp;
        tmp = func_ov103_0229cde8((int) a, (int) b);
        return func_ov094_0229b30c((char *) a + 0xB2C, tmp);
    } else {
        return 1;
    }
}

void func_ov103_0229cbec(void *self)
{
    func_ov094_0229ab5c((char *) self + 0xcc);
    func_ov094_0229b98c((char *) self + 0xb2c);
}

void func_ov103_0229cbac(int param1, int param2)
{
    int r4 = param1;
    int r5 = param2;
    int result;

    if (func_ov103_0229cdfc(param1, param2) != 0) {
        result = func_ov103_0229cde8(r4, r5);
        func_ov094_0229b950(r4 + 0xb2c, result);
        func_ov094_0229ab5c((void *) (r4 + 0xcc));
    } else {
        func_ov103_0229cbec((void *) r4);
    }
}

void func_ov103_0229cb90(void *self)
{
    func_ov094_0229ab0c((char *) self + 0xcc);
    func_ov094_0229b944((char *) self + 0xb2c);
}

void func_ov103_0229cb60(int r4, int r5)
{
    if (func_ov103_0229cdfc(r4, r5) != 0) {
        func_ov094_0229b938(r4 + 0xb2c, func_ov103_0229cde8(r4, r5));
    }
}
