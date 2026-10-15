/* func_ov004_02215ba8 @ 0x02215ba8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);

int func_ov004_02215ba8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8(self + 0x740);
    if (v1 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v1;
}
