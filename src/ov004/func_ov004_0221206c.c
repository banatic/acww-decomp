/* func_ov004_0221206c @ 0x0221206c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d058(char *argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_0220ffbc(char *argument0);
extern int func_ov004_022107d4(char *argument0);

int func_ov004_0221206c(char *self)
{
    // DECLS
    int v4;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_0220d058(self + 0x844, 0x1, 0x1, 0x0);
    func_ov004_022107d4(self);
    v4 = func_ov004_0220d2a8(self + 0x740);
    if (v4 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v4;
}
