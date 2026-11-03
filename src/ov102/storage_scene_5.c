/* storage_scene_5: 16 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229d4ac @ 0x0229d4ac, 0x1e bytes, Thumb
 * func_ov102_0229d47c @ 0x0229d47c, 0x30 bytes, Thumb
 * func_ov102_0229d470 @ 0x0229d470, 0xc bytes, Thumb
 * func_ov102_0229d464 @ 0x0229d464, 0xc bytes, Thumb
 * func_ov102_0229d454 @ 0x0229d454, 0x10 bytes, Thumb
 * func_ov102_0229d444 @ 0x0229d444, 0x10 bytes, Thumb
 * func_ov102_0229d438 @ 0x0229d438, 0xc bytes, Thumb
 * func_ov102_0229d400 @ 0x0229d400, 0x36 bytes, Thumb
 * func_ov102_0229d3f0 @ 0x0229d3f0, 0xe bytes, Thumb
 * func_ov102_0229d37c @ 0x0229d37c, 0x74 bytes, Thumb
 * func_ov102_0229d320 @ 0x0229d320, 0x5c bytes, Thumb
 * func_ov102_0229d2a4 @ 0x0229d2a4, 0x7c bytes, Thumb
 * func_ov102_0229d288 @ 0x0229d288, 0x1a bytes, Thumb
 * func_ov102_0229d274 @ 0x0229d274, 0x12 bytes, Thumb
 * func_ov102_0229d258 @ 0x0229d258, 0x1c bytes, Thumb
 * func_ov102_0229d1e8 @ 0x0229d1e8, 0x70 bytes, Thumb
 */

struct Node {
    char pad_00[0x25aa];
    unsigned char index;
};

extern int func_02099fe8(void);
extern void func_020b9ccc(void *arg);
extern int func_ov094_0229aee8(void *ptr, int arg1, int arg2);
extern int func_ov094_0229a69c(void *ptr, int value);
extern int func_ov094_0229aeb8(void *ptr, int a, int b);
extern int func_ov102_0229d034(void *a, int b);
extern int func_ov102_0229cff8(void *a, int b);
extern void func_ov102_0229cc60(void *a, int b);
extern void func_ov094_0229aa14(void *p, int r, int s, int t);
extern void func_ov094_0229a9b4(void *p, int r);
extern int func_ov094_0229aba4(int, int);
extern int func_02088d9c(void *);
extern char data_ov102_0229eac0[][8];

void func_ov102_0229d2a4(unsigned char *p1, void *p2, int p3, int p4);
int func_ov102_0229d288(int a, int b);
unsigned int func_ov102_0229d274(unsigned int a, unsigned int x);
void *func_ov102_0229d258(struct Node *n);

int func_ov102_0229d4ac(void *receiver)
{
    int result;
    int ret;

    result = func_02099fe8();
    if (result == -1) {
        ret = 0x25;
    } else {
        ret = (unsigned char) result;
    }
    return ret;
}

unsigned char func_ov102_0229d47c(void *arg0)
{
    unsigned short *ptr = (unsigned short *) func_ov102_0229d258((struct Node *) ((void *) arg0));
    int i = 0;
    while (i < 15) {
        if (ptr[i] == 0xfff1) {
            return (unsigned char) (i + 15);
        }
        i++;
    }
    return 0x25;
}

void func_ov102_0229d470(void *ptr)
{
    func_020b9ccc((char *) ptr + 0x94);
}

int func_ov102_0229d464(int a, unsigned int b)
{
    if (b > 14) {
        return 0;
    }
    return 1;
}

int func_ov102_0229d454(int a, unsigned int b)
{
    if (b >= 0xf && b <= 0x1d) {
        return 1;
    }
    return 0;
}

int func_ov102_0229d444(int a, unsigned int b)
{
    if (b >= 0x1e && b <= 0x23) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov102_0229d438(int r0, int r1)
{
    if (r1 == 0x24) {
        return 1;
    }
    return 0;
}

int func_ov102_0229d400(int a, int b)
{
    if (func_ov102_0229d464(a, b) != 0) {
        return (unsigned char) b;
    }
    if (func_ov102_0229d454(a, b) != 0) {
        return func_ov102_0229d288(a, b);
    }
    return 0;
}

unsigned char func_ov102_0229d3f0(unsigned int unused, unsigned int x)
{
    if (x <= 14) {
        return (unsigned char) x;
    } else {
        return 0x25;
    }
}

int func_ov102_0229d37c(void *self, int arg1, int arg2, int flag)
{
    int result;
    result = func_ov094_0229aee8((char *) self + 0xcc, arg1, arg2);
    if (result != 0x23) {
        if (flag != 0) {
            if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                return 0x25;
            }
        }
        return (int) func_ov102_0229d3f0((unsigned int) self, result);
    } else {
        result = func_ov094_0229aeb8((char *) self + 0xcc, arg1, arg2);
        if (result != 0x23) {
            if (flag != 0) {
                if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                    return 0x25;
                }
            }
            return (int) func_ov102_0229d274((unsigned int) self, result);
        } else {
            return 0x25;
        }
    }
}

int func_ov102_0229d320(void *a, int b)
{
    if (func_ov102_0229d464((int) a, b) != 0 || func_ov102_0229d454((int) a, b) != 0) {
        int r6 = func_ov102_0229d034(a, b);
        if (r6 != 0xfff1) {
            int r3 = func_ov102_0229cff8(a, b);
            unsigned char byte = ((unsigned char *) a)[0x25a2];
            func_ov102_0229d2a4((unsigned char *) a, (void *) byte, r6, r3);
        }
        func_ov102_0229cc60(a, b);
        return 1;
    } else {
        return 0;
    }
}

void func_ov102_0229d2a4(unsigned char *p1, void *p2, int p3, int p4)
{
    if (func_ov102_0229d464((int) p1, (unsigned int) p2) || func_ov102_0229d454((int) p1, (unsigned int) p2)) {
        int r = func_ov102_0229d400((int) p1, (int) p2);
        func_ov094_0229aa14(p1 + 0xcc, r, p3, p4);
        func_ov094_0229a9b4(p1 + 0xcc, r);
    } else if (func_ov102_0229d444((int) p1, (unsigned int) p2)) {
        unsigned char a = p1[0x25a3];
        int t = (a - 1) * 15;
        unsigned char b = p1[0x25a4];
        unsigned char *base = p1 + ((t + b) * 2);
        *(unsigned short *) (base + 0x24e8) = (unsigned short) p3;
    }
}

int func_ov102_0229d288(int a, int b)
{
    if (func_ov102_0229d454(a, b)) {
        return (unsigned char) b;
    }
    return 15;
}

unsigned int func_ov102_0229d274(unsigned int a, unsigned int x)
{
    if (x >= 0xf && x <= 0x1d) {
        return (unsigned char) x;
    } else {
        return 0x25;
    }
}

void *func_ov102_0229d258(struct Node *n)
{
    return (char *) n + 0x24e8 + ((15 * n->index) << 1);
}

int func_ov102_0229d1e8(int p1, int p2)
{
    if (func_ov102_0229d464(p1, p2) != 0 || func_ov102_0229d454(p1, p2) != 0) {
        return func_ov094_0229aba4(p1 + 0xcc, func_ov102_0229d400(p1, p2));
    } else {
        if (func_ov102_0229d438(p1, p2) != 0) {
            return 0xc4;
        } else {
            if (func_ov102_0229d444(p1, p2) != 0) {
                return func_02088d9c(&data_ov102_0229eac0[(p2 - 0x1e) * 3]) + 0x80;
            } else {
                return 0;
            }
        }
    }
}
