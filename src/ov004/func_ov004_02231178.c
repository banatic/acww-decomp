/* func_ov004_02231178 @ 0x02231178, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94();
extern int func_ov004_0223121c();

int func_ov004_02231178(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02056f94(self + 0x188);
    if (v1 != 0x0) {
        return func_ov004_0223121c(self, 0x2);
    }
    return v1;
}
