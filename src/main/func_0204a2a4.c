/* func_0204a2a4 @ 0x0204a2a4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6674(int, int, int, int);
extern int func_020b6654(int);
extern int func_0204e414(int);
extern int func_0204df08(int);
extern void func_0204f538(int, volatile unsigned short *, int, int, int);
extern void func_0204f31c(int, int, int);
extern void func_0204f380(int, int, int);

void func_0204a2a4(int a, int b, int c, int d, int e)
{
    volatile unsigned short arr[2];
    int x;
    int y;

    x = func_020b6674(a, b, c, d);
    if (x == 0) {
        x = func_020b6654(a);
        if (x == 0) {
            goto L0;
        }
    }

    x = func_0204e414(x);
    if (x != 0) {
        arr[0] = (unsigned short) 0xfff1u;
        arr[0] = (unsigned short) d;
        func_0204f538(x, &arr[0], b, c, 0);
        if (e != 0) {
            func_0204f380(x, b, c);
        } else {
            func_0204f31c(x, b, c);
        }
    }
    return;

L0:
    if ((y = func_0204df08(a)) != 0) {
        arr[1] = (unsigned short) 0xfff1u;
        arr[1] = (unsigned short) d;
        func_0204f538(y, &arr[1], b, c, 0);
    }
}
