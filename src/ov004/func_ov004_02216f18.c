/* func_ov004_02216f18 @ 0x02216f18, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbc0(void);
extern int func_ov004_02217124(void *argument0, int argument1);

int func_ov004_02216f18(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_0206fbc0();
    if (v1 != 0x0) {
        return func_ov004_02217124(self, 0x5);
    }
    return v1;
}
