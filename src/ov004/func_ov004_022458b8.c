/* func_ov004_022458b8 @ 0x022458b8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8840();
extern int func_ov004_02245cf4();

int func_ov004_022458b8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020e8840(self + 0x324);
    if (v1 == 0x0) {
        return func_ov004_02245cf4(self, 0x4);
    }
    return v1;
}
