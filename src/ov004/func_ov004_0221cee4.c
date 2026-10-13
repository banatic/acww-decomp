/* func_ov004_0221cee4 @ 0x0221cee4, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081cec();
extern int func_ov004_0221d08c();

int func_ov004_0221cee4(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0221d08c(self, a1);
    if (v1 != 0x0) {
        return func_02081cec(v1, (char) a1);
    }
    return v1;
}
