/* func_ov004_02245b8c @ 0x02245b8c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e508(void *p, int k);
extern int func_0208e278(void *p);

void func_ov004_02245b8c(char *self)
{
    unsigned char i;
    func_0208e508(self + 0x50, 7);
    for (i = 0; i < 5; i++) {
        func_0208e278(self + 0x9c + (i << 7));
    }
}
