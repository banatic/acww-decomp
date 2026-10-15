/* func_ov004_02215f8c @ 0x02215f8c, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8(int argument0, int argument1);
extern int func_02095ec4(void);
extern int func_ov004_0220d058(char *argument0, int argument1, int argument2, int argument3);
extern void func_ov004_0220d280(unsigned char *argument0, unsigned char argument1, int argument2);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_0220ffbc(char *argument0);
extern int func_ov004_022107d4(char *argument0);
extern void func_ov004_0223cf2c(char *argument0, int argument1);

int func_ov004_02215f8c(char *self)
{
    // DECLS
    int v5;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_022107d4(self);
    func_ov004_0220d058(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_0223cf2c((char *) (self + 0x798), (int) (self + 0x7b8));
    v5 = func_ov004_0220d2a8(self + 0x740);
    if (v5 != 0x0) {
        func_ov004_0220d280((unsigned char *) (self + 0x740), (unsigned char) (0x1), (int) (0x0));
        func_0203e0a8((int) (self), (int) (0x0));
        return func_02095ec4();
    }
    return v5;
}
