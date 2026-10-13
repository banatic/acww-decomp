/* func_ov004_0222be34 @ 0x0222be34, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0();
extern int func_02096718();

int func_ov004_0222be34(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        func_020109a0(v1, 0x98, 0x0, 0x0);
        return 0x1;
    }
    return 0x0;
}
