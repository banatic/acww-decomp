/* func_ov004_022134dc @ 0x022134dc, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8();
extern int func_ov004_0220d2a8();

int func_ov004_022134dc(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8(self + 0x740);
    if (v1 != 0x0) {
        return func_0203e0a8(self, 0x0);
    }
    return v1;
}
