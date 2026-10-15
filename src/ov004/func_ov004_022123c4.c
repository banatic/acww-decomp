/* func_ov004_022123c4 @ 0x022123c4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(unsigned char *object, unsigned char value, int pending);
extern void func_ov004_0220cfec(void *object, unsigned char value);
void func_ov004_022123c4(char *self)
{
    func_ov004_0220d280((unsigned char *) self + 0x740, 1, 0);
    func_ov004_0220cfec(self + 0x764, 1);
}
