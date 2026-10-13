/* func_ov004_0220d2bc @ 0x0220d2bc, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220e5c8(void *b);
extern int func_ov004_0220e758(void *b, int *x, int *y, int c, int d);
extern int func_020b65c4(void);
extern void func_02052ee8(int x, int y, int c, int d, int t);

void func_ov004_0220d2bc(unsigned char *self, unsigned char *b)
{
    int x, y;
    if (func_ov004_0220e5c8(b) == 0) {
        if (func_ov004_0220e758(b, &x, &y, 0, 0) != 0) {
            func_02052ee8(x, y, b[0x288], self[1], func_020b65c4());
        }
    }
}
