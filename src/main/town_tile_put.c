/* town_tile_put: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204a330 @ 0x0204a330, 0x3e bytes, Thumb
 * func_0204a2a4 @ 0x0204a2a4, 0x8c bytes, Thumb
 * func_0204a25c @ 0x0204a25c, 0x48 bytes, Thumb
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_ov003_02224140(int, int, int, int);
extern void func_ov004_02233ad4(int, int, int, int);
extern int func_020b6674(int);
extern int func_020b6654(int);
extern int func_0204e414(void);
extern int func_0204df08(int);
extern int func_0204f538(int, volatile unsigned short *, int, int, int);
extern int func_0204f31c(int, int, int);
extern void func_0204f380(int, int, int);

void func_0204a330(int a, int b, int c, int d)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        func_ov003_02224140(a, b, c, d);
    } else {
        func_ov004_02233ad4(a, b, c, 0);
    }
}

void func_0204a2a4(int a, int b, int c, int d, int e)
{
    volatile unsigned short arr[2];
    int x;
    int y;

    x = func_020b6674(a);
    if (x == 0) {
        x = func_020b6654(a);
        if (x == 0) {
            goto L0;
        }
    }

    x = func_0204e414();
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

void func_0204a25c(unsigned int a, unsigned int b, unsigned int c, unsigned short d, unsigned int e)
{
    volatile unsigned short tmp;
    tmp = 0xFFF1;
    tmp = d;
    func_0204f538(a, (volatile unsigned short *) ((unsigned short *) &tmp), b, c, 0);
    if (e != 0) {
        func_0204f380(a, b, c);
    } else {
        func_0204f31c(a, b, c);
    }
}
