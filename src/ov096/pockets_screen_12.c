/* pockets_screen_12: 13 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229f5ac @ 0x0229f5ac, 0x34 bytes, Thumb
 * func_ov096_0229f57c @ 0x0229f57c, 0x30 bytes, Thumb
 * func_ov096_0229f55c @ 0x0229f55c, 0x1e bytes, Thumb
 * func_ov096_0229f548 @ 0x0229f548, 0x14 bytes, Thumb
 * func_ov096_0229f538 @ 0x0229f538, 0x10 bytes, Thumb
 * func_ov096_0229f4f8 @ 0x0229f4f8, 0x40 bytes, Thumb
 * func_ov096_0229f4ac @ 0x0229f4ac, 0x4c bytes, Thumb
 * func_ov096_0229f47c @ 0x0229f47c, 0x30 bytes, Thumb
 * func_ov096_0229f460 @ 0x0229f460, 0x1c bytes, Thumb
 * func_ov096_0229f3d4 @ 0x0229f3d4, 0x8c bytes, Thumb
 * func_ov096_0229f3bc @ 0x0229f3bc, 0x18 bytes, Thumb
 * func_ov096_0229f39c @ 0x0229f39c, 0x20 bytes, Thumb
 * func_ov096_0229f320 @ 0x0229f320, 0x7c bytes, Thumb
 */

extern int func_ov096_0229f830(void *a, void *b);
extern void func_ov096_0229f5e0(void *a, void *b, int c, int d);
extern int func_ov096_0229f820(int unused0, unsigned int unused1);
extern void func_ov094_0229b890(int, int);
extern int func_02099fe8(void);
extern int func_ov094_0229bba4(void *, int unused1, int unused2);
extern int func_ov094_0229b30c(void *, int);
extern int func_ov096_0229f150(void *object, void *value);
extern int func_ov096_0229f054(int, int);
extern int func_02066830(int, int);
extern void func_ov096_0229e898(int, int, int);
extern void func_ov094_0229b8b4(int, int, int);
extern int func_ov096_0229c2fc(int, int);
extern void func_ov096_0229c2dc(int, int);
extern int func_ov094_0229aea8(int, int, int);
extern int func_ov096_0229e158(void *receiver);
extern int func_0204c120(int a, int b, int c);

int func_ov096_0229f548(int a, unsigned int b);
void func_ov096_0229f47c(int a, int b, int c);
int func_ov096_0229f3bc(int r0, int r1, int r2);
int func_ov096_0229f39c(int p, int b, int c);

void func_ov096_0229f5ac(void *r5, void *r4)
{
    if (func_ov096_0229f830(r5, r4) == 0) {
        if (func_ov096_0229f820((int) r5, (unsigned int) r4) == 0) {
            return;
        }
    }
    func_ov096_0229f5e0(r5, r4, 0x0000fff1, 0);
}

void func_ov096_0229f57c(int r4, int r5)
{
    if (func_ov096_0229f820(r4, r5)) {
        func_ov094_0229b890(r4 + 0xdb8, func_ov096_0229f548(r4, r5));
    }
}

int func_ov096_0229f55c(void *receiver)
{
    int r0;
    r0 = func_02099fe8();
    if (r0 == -1) {
        return 0x26;
    }
    r0 = (unsigned char) r0;
    return r0;
}

int func_ov096_0229f548(int a, unsigned int b)
{
    if (b >= 15 && b <= 24) {
        return (unsigned char) (b - 15);
    }
    return 0;
}

unsigned char func_ov096_0229f538(int arg0, unsigned int b)
{
    if (b <= 9) {
        return (unsigned char) (b + 15);
    }
    return 38;
}

int func_ov096_0229f4f8(void *p1, int p2, int p3, int p4)
{
    int result = func_ov094_0229bba4((char *) p1 + 0xDB8, p2, p3);
    if (result != 0x37) {
        if (p4 != 0 && func_ov094_0229b30c((char *) p1 + 0xDB8, result) != 0) {
            return 38;
        }
        return (int) func_ov096_0229f538((int) p1, result);
    } else {
        return 38;
    }
}

int func_ov096_0229f4ac(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_ov096_0229f150((void *) a, (void *) b) == 0) {
        int r0 = func_ov096_0229f054(r5, r4);
        func_02066830(r5 + 0x2f28, r0);
        func_ov096_0229f47c(r5, *(unsigned char *) (r5 + 0xb4), r5 + 0x2f28);
    }
    func_ov096_0229e898(r5, r4, 1);
    return 1;
}

void func_ov096_0229f47c(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;
    if (func_ov096_0229f820(a, b)) {
        int r0 = func_ov096_0229f548(r5, r4);
        func_ov094_0229b8b4(r5 + 0xdb8, r0, r6);
    }
}

int func_ov096_0229f460(int r0, int r1, int r2)
{
    if (r1 < 4 || r1 >= 0x1c) {
        return 0;
    }
    if (r2 < 0xac || r2 >= 0xc4) {
        return 0;
    }
    return 1;
}

int func_ov096_0229f3d4(int a, int b, int c)
{
    int r0;
    int r5 = b;
    int r4 = c;
    int r6 = a;

    if (func_ov096_0229f3bc(a, b, c) != 0) {
        return 0x24;
    }

    if (r5 > 0x6c && r5 < 0xc4 && r4 > 0x50 && r4 < 0x68) {
        if (r5 < 0x98) {
            return 0x22;
        } else {
            return 0x23;
        }
    }

    r0 = func_ov096_0229f39c(r6, r5, r4);
    if (r0 != 0) {
        if (func_ov096_0229c2fc(r6, 0x4000) != 0) {
            return 0x26;
        } else {
            return 0x25;
        }
    }

    if (r5 > 0x30 && r5 < 0x60 && r4 > 0x50 && r4 < 0x60) {
        if (func_ov096_0229c2fc(r6, 0x4000) != 0) {
            return 0x26;
        } else {
            return 0x25;
        }
    }

    func_ov096_0229c2dc(r6, 0x4000);
    return 0x26;
}

int func_ov096_0229f3bc(int r0, int r1, int r2)
{
    if (r1 > 0x88 && r1 < 0xa8 && r2 > 0x20 && r2 < 0x50) {
        return 1;
    }
    return 0;
}

int func_ov096_0229f39c(int p, int b, int c)
{
    if (func_ov094_0229aea8(p + 0x358, b, c)) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov096_0229f320(char *p, int a, int b)
{
    int threshold;

    if (b < 0x50 || b > 0x60) {
        return 0;
    }
    p[0xbf] = 0;
    if (a < 0x30) {
        return 0;
    }
    if (a < 0x40) {
        threshold = 10000;
        p[0xbf] = 3;
    } else if (a < 0x48) {
        threshold = 1000;
        p[0xbf] = 2;
    } else if (a < 0x60) {
        threshold = 100;
        p[0xbf] = 1;
    } else {
        return 0;
    }
    if (threshold > func_ov096_0229e158(p)) {
        return 1;
    }
    *(short *) (p + 0xae) = func_0204c120(threshold, 0, 0);
    return 2;
}
