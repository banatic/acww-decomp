/* func_ov004_0221cec8 @ 0x0221cec8, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d20();
extern int func_ov004_0221d08c();

int func_ov004_0221cec8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0221d08c();
    if (v1 != 0x0) {
        return func_02081d20(v1);
    }
    return 0x0;
}
