/* func_ov004_02229e74 @ 0x02229e74, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern void func_ov004_02229ea8(void *w, int k);
void func_ov004_02229e74(unsigned char *self, unsigned char *p, int previous)
{
    unsigned char *w;
    w = self + 0x7d4;
    if (*(unsigned char *) (p + 0xc) != 0) {
        func_020109a0(self, 0x1b, 3, 0);
    } else {
        func_020109a0(self, 0x1c, 3, 0);
    }
    func_ov004_02229ea8(w, 0);
}
