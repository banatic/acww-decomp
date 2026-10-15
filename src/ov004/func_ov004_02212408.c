/* func_ov004_02212408 @ 0x02212408, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(unsigned char *object, unsigned char value, int pending);
extern void func_ov004_0220cfec(void *object, unsigned char value);
void func_ov004_02212408(char *self)
{
    func_ov004_0220d280((unsigned char *) self + 0x740, 0, 0);
    func_ov004_0220cfec(self + 0x764, 0);
}
