/* func_02095304 @ 0x02095304, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020961a8(int a);
extern int func_020960f8(int a, int b);
extern void func_0204f818(int *a, int *b, int *c);
extern void func_0204a2a4(int a, int b, int c, int d);

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
        int buf[7];
        int temp = *p5;
        buf[3] = *p4;
        buf[4] = 0;
        buf[5] = temp;
        func_0204f818(&buf[1], &buf[2], &buf[3]);
        buf[0] = 0;
        func_0204a2a4(buf[0], buf[1], buf[2], 0xfff1);
    }
}
