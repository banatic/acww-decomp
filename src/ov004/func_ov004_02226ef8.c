/* func_ov004_02226ef8 @ 0x02226ef8, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int a, int b);
extern void func_0200fbc4(void *self, int a, int b, int c);
extern void func_0200f554(void *self);
extern int data_020ccf94;
void func_ov004_02226ef8(unsigned char *self)
{
    int *w;
    w = (int *) (self + 0x7d4);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_0200fbc4(self, w[0], w[2], -0x8000);
    } else {
        func_0200f554(self);
    }
}
