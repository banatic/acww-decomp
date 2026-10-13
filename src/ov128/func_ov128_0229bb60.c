/* func_ov128_0229bb60 @ 0x0229bb60, 0x84 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);
extern int func_ov127_022998a8(void *);
extern unsigned char data_ov128_0229cca0[];
extern unsigned char data_ov128_0229cc20[];

void func_ov128_0229bb60(unsigned char *a, unsigned char *b)
{
    unsigned char *p;
    int t;

    p = b + 0x60;
    func_02088df8(1, data_ov128_0229cca0, 0x80, (int) (p - *(unsigned int *) (a + 0x2d58)), -1, 2, 0x1000, 0x1000, 0, -1, 0,
                  0);
    t = (int) (p + func_ov127_022998a8(a + 0x4a4));
    func_02088df8(1, data_ov128_0229cc20, 0x80 - *(unsigned int *) (a + 0x2d54), t, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
