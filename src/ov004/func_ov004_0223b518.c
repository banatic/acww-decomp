/* func_ov004_0223b518 @ 0x0223b518, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8();
extern int func_0209871c();
extern int func_02099870();
extern void *data_021dc7bc;

int func_ov004_0223b518(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020984e8();
    if (v1 != 0x0) {
        return func_0209871c(&data_021dc7bc, func_02099870(v1));
    }
    return -0x1;
}
