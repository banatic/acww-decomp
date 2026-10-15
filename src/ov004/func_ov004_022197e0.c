/* func_ov004_022197e0 @ 0x022197e0, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d058(char *argument0, int argument1, int argument2, int argument3);
extern void func_ov004_0220d280(unsigned char *argument0, unsigned char argument1, int argument2);
extern int func_ov004_0221078c(char *argument0);

int func_ov004_022197e0(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x848) = 0x1000;
    func_ov004_0220d280((unsigned char *) (self + 0x740), (unsigned char) (0x1), (int) (0x0));
    func_ov004_0221078c(self);
    func_ov004_0220d058(self + 0x84c, 0x1, 0x1, 0x0);
    return 0x1;
}
