/* func_02034b80 @ 0x02034b80, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_022321b8(void *, int, int);
extern void func_02034bd4(void *, int, int, int);
extern int data_021c5174;

int func_02034b80(unsigned short *self, int a, int b, int c)
{
    unsigned short t = *self;
    unsigned int flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        int r = func_ov004_022321b8(&t, a, b);
        if (c) {
            func_02034bd4(&t, a, 1, b);
        }
        return r;
    } else {
        return (int) &data_021c5174;
    }
}
