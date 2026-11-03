/* player_actors: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209539c @ 0x0209539c, 0x2 bytes, Thumb
 * func_02095380 @ 0x02095380, 0x1a bytes, Thumb
 * func_02095304 @ 0x02095304, 0x7c bytes, Thumb
 * func_020952ec @ 0x020952ec, 0x18 bytes, Thumb
 * func_020952e4 @ 0x020952e4, 0x8 bytes, Thumb
 * func_020952e0 @ 0x020952e0, 0x4 bytes, Thumb
 * func_020952ac @ 0x020952ac, 0x34 bytes, Thumb
 */

extern int func_02096718(int);
extern int func_0200f328(int, int);
extern int func_020b65c4(void);
extern int func_020961a8(int a);
extern int func_020960f8(int a, int b);
extern void func_0204f818(int *a, int *b, int *c);
extern void func_0204a2a4(int a, int b, int c, int d, int e);
extern int func_02003348(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3, int context);

void func_0209539c(void) {}

int func_02095380(int a)
{
    int r;
    r = func_02096718(4);
    if (r != 0) {
        return func_0200f328(r, a);
    }
    return r;
}

void func_02095304(int *p0, unsigned char *p1, int *p2, int *p3, int *p4, int *p5)
{
    int f = func_020b65c4();
    if (*p1 == f) {
        if (*p2 != 0x75) {
            return;
        }
        if (*p3 == 0x75) {
            return;
        }
        if (func_020961a8(*p0) != 0 && func_020960f8(0x75, *p0) != 0) {
            return;
        }
    } else {
        if (*p3 != 0x75) {
            return;
        }
        if (*p2 == 0x75) {
            return;
        }
    }
    {
        int buf[5];
        int temp = *p5;
        buf[2] = *p4;
        buf[3] = 0;
        buf[4] = temp;
        func_0204f818(&buf[0], &buf[1], &buf[2]);
        func_0204a2a4(0, buf[0], buf[1], 0xfff1, 0);
    }
}

int func_020952ec(void)
{
    int *ptr;
    int result;

    ptr = (int *) func_02096718(4);
    result = ptr[0x200];
    return result;
}

int func_020952e4(void)
{
    return 3232;
}

int func_020952e0(void)
{
    return 4;
}

void func_020952ac(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    unsigned int combined;

    combined = ((arg0 << 30) & 0xC0000000) | (arg3 & 0x3fffffff);
    func_02003348(9, combined, arg1, arg2, 0);
}
