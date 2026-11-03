/* letter_storage_5: 14 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229d7d4 @ 0x0229d7d4, 0x20 bytes, Thumb
 * func_ov105_0229d78c @ 0x0229d78c, 0x48 bytes, Thumb
 * func_ov105_0229d77c @ 0x0229d77c, 0x10 bytes, Thumb
 * func_ov105_0229d76c @ 0x0229d76c, 0x10 bytes, Thumb
 * func_ov105_0229d75c @ 0x0229d75c, 0x10 bytes, Thumb
 * func_ov105_0229d750 @ 0x0229d750, 0xc bytes, Thumb
 * func_ov105_0229d73c @ 0x0229d73c, 0x12 bytes, Thumb
 * func_ov105_0229d718 @ 0x0229d718, 0x24 bytes, Thumb
 * func_ov105_0229d6f8 @ 0x0229d6f8, 0x20 bytes, Thumb
 * func_ov105_0229d69c @ 0x0229d69c, 0x5c bytes, Thumb
 * func_ov105_0229d650 @ 0x0229d650, 0x4c bytes, Thumb
 * func_ov105_0229d5dc @ 0x0229d5dc, 0x74 bytes, Thumb
 * func_ov105_0229d59c @ 0x0229d59c, 0x40 bytes, Thumb
 * func_ov105_0229d530 @ 0x0229d530, 0x6c bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} UnkData8;

extern int func_0209a1e8(void);
extern int func_02065ec0(void *ptr);
extern void func_020b9ccc(int x);
extern int func_ov094_0229bba4(void *p, int arg1, int arg2);
extern int func_ov094_0229bb70(void *p, int a, int b);
extern int func_ov094_0229b30c(void *p, int x);
extern int func_ov105_0229d428(int, int);
extern int func_02066830(int, int);
extern void func_ov105_0229d0d4(int, int);
extern void func_ov094_0229b8b4(unsigned char *, int, int);
extern int func_ov094_0229b8d8(void *, int);
extern int func_ov094_0229b384(unsigned char *, int);
extern int func_02088d9c(UnkData8 *);
extern UnkData8 data_ov105_0229fa80[];

void func_ov105_0229d5dc(unsigned char *a, int b, int c);
int func_ov105_0229d59c(void *a, void *b);

int func_ov105_0229d7d4(void *receiver)
{
    int result;
    int ret;

    result = func_0209a1e8();
    if (result == -1) {
        ret = 0x40;
    } else {
        ret = (unsigned char) (result + 0x1a);
    }
    return ret;
}

unsigned char func_ov105_0229d78c(void *self)
{
    unsigned char idx;
    unsigned char *p;
    int i;

    idx = ((unsigned char *) self)[0x2c0];
    p = (unsigned char *) self + 0x2db8 + ((idx * 25) << 8);
    for (i = 0; i < 25; i++) {
        if (func_02065ec0(p) == 0) {
            return (unsigned char) (i + 36);
        }
        p += 256;
    }
    return 64;
}

void func_ov105_0229d77c(int x)
{
    func_020b9ccc(x + 0x2c4);
}

int func_ov105_0229d76c(int a, unsigned int b)
{
    if (b >= 0x1a && b <= 0x23) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov105_0229d75c(unsigned int a, unsigned int b)
{
    if (b >= 0x24 && b <= 0x3c) {
        return 1;
    }
    return 0;
}

int func_ov105_0229d750(int r0, int r1)
{
    if (r1 == 0x3d) {
        return 1;
    }
    return 0;
}

int func_ov105_0229d73c(int a, int key)
{
    if ((unsigned int) (unsigned char) (key + 0xC2) > 1) {
        return 0;
    } else {
        return 1;
    }
}

unsigned char func_ov105_0229d718(unsigned int a, unsigned int n)
{
    if (n >= 26 && n <= 35) {
        return n - 26;
    } else if (n >= 36 && n <= 60) {
        return n - 26;
    } else {
        return 0;
    }
}

unsigned char func_ov105_0229d6f8(unsigned int a, unsigned int b)
{
    if (b <= 9) {
        return b + 0x1a;
    } else if (b >= 10 && b <= 0x22) {
        return b + 0x1a;
    } else {
        return 0x40;
    }
}

int func_ov105_0229d69c(void *self, int a, int b, int c)
{
    int r;
    r = func_ov094_0229bba4((unsigned char *) self + 0xd5c, a, b);
    if (r == 0x37) {
        r = func_ov094_0229bb70((unsigned char *) self + 0xd5c, a, b);
    }
    if (r == 0x37) {
        goto ret_early;
    }
    if (c && func_ov094_0229b30c((unsigned char *) self + 0xd5c, r) != 0) {
        return 0x40;
    }
    return (int) func_ov105_0229d6f8((unsigned int) self, r);
ret_early:
    return 0x40;
}

int func_ov105_0229d650(int a, int b)
{
    if (func_ov105_0229d428(a, b) == 0) {
        int res = func_ov105_0229d59c((void *) a, (void *) b);
        func_02066830(a + 0x1b4, res);
        func_ov105_0229d5dc((unsigned char *) a, (unsigned char) (*(unsigned char *) (a + 0x2b7)), a + 0x1b4);
    }
    func_ov105_0229d0d4(a, b);
    return 1;
}

void func_ov105_0229d5dc(unsigned char *a, int b, int c)
{
    if (func_ov105_0229d76c((int) (a), (unsigned int) (b)) != 0 || func_ov105_0229d75c((unsigned int) a, b) != 0) {
        func_ov094_0229b8b4(a + 0xd5c, (int) func_ov105_0229d718((unsigned int) a, b), c);
    } else {
        if (func_ov105_0229d73c((int) a, b) != 0) {
            func_02066830((int) (a + 0x2db8 + (((a[0x2b9] - 0x24) + 0x19 * a[0x2b8]) << 8)), c);
        }
    }
}

int func_ov105_0229d59c(void *a, void *b)
{
    if (func_ov105_0229d76c((int) a, (unsigned int) b) != 0 || func_ov105_0229d75c((unsigned int) a, (unsigned int) b) != 0) {
        int tmp = (int) func_ov105_0229d718((unsigned int) a, (unsigned int) b);
        return func_ov094_0229b8d8((char *) a + 0xd5c, tmp);
    }
    return 0;
}

int func_ov105_0229d530(unsigned char *a, int b)
{
    if (func_ov105_0229d76c((int) a, b) || func_ov105_0229d75c((unsigned int) a, b)) {
        return func_ov094_0229b384(a + 0xd5c, (int) func_ov105_0229d718((unsigned int) a, b));
    }

    if (b == 0x3d) {
        return 0xbc;
    }

    if (func_ov105_0229d73c((int) a, b)) {
        return func_02088d9c(&data_ov105_0229fa80[(b - 0x3e) * 3]) + 0x80;
    }

    return 0;
}
