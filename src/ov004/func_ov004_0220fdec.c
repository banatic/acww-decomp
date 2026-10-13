/* func_ov004_0220fdec @ 0x0220fdec, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d4c0();
extern int func_ov004_0220d4c8();
extern int func_ov004_0223cd58();
extern int func_ov004_0223ce84();

int func_ov004_0220fdec(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0220d4c8(self + 0x17c);
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84(v1);
        return func_ov004_0223cd58(v2, func_ov004_0220d4c0(self + 0x17c));
    }
    return 0x0;
}
