/* func_ov004_02214568 @ 0x02214568, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_022107d4(char *argument0);
extern int func_ov004_0221081c(char *argument0);

int func_ov004_02214568(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0221081c(self);
    func_ov004_022107d4(self);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x3), (int) (0xff), (int) (0x1));
    }
    return v3;
}
