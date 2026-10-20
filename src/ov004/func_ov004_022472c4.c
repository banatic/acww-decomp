/* func_ov004_022472c4 @ 0x022472c4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0224732c(void);
extern void func_0203caa4(void *self, int a, int b);
extern void func_0203c99c(void *self, int a);
extern void func_0203ad58(void);

int func_ov004_022472c4(char *self)
{
    func_0203caa4(self, func_ov004_0224732c() + 0x12, 0);
    func_0203c99c(self, 0);
    func_0203ad58();
    return 1;
}
