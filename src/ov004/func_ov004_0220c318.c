/* func_ov004_0220c318 @ 0x0220c318, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020321bc(void *a, int b, int c, int d, void *e, int f, int g);
extern int func_020b6590(void);
extern int func_020b7dc8(int a, void *b, void *c, int d, int e, int f, int g, int h, int i);

void func_ov004_0220c318(char *self)
{
    func_020321bc(self + 0x138, 0x2000, 0x2000, 0x2000, self + 0x5c, 0, 0);
    func_020b7dc8(func_020b6590(), self + 0x1d4, self + 0x5c, 0x2000, 0x2000, 0x2000, 0, 0xb, 0xff);
}
