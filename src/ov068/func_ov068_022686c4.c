/* func_ov068_022686c4 @ 0x022686c4, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *p, int n);
extern int func_02019de8(void *p);
extern void func_02012508(void *a, void *b, void *c, int d, int e);
extern int func_ov068_0226ccb0(void *a, void *b);
extern void func_ov068_0226cce8(void *a, void *b, int c);
extern int func_020121f8(void *p);
extern void func_020121e0(void *p, int n);

void func_ov068_022686c4(unsigned char *self, void *work)
{
    unsigned short h;

    if (func_020164a0((char *) work + 0x334, 0) != 0xd6) {
        return;
    }

    if (func_02019de8((char *) work + 0x564) != 0) {
        h = 0xfff1;
        func_02012508((char *) work + 0x9b4, work, &h, 0, 3);
        self[0x1c] = 2;
        if (func_ov068_0226ccb0(self, work) == 0) {
            func_ov068_0226cce8(self, work, 0);
        }
    } else {
        int n;

        n = func_020121f8((char *) work + 0x9b4);
        if (n != 0) {
            n -= 0x249;
            if (n < 0) {
                n = 0;
            }
        }
        func_020121e0((char *) work + 0x9b4, n);
    }
}
