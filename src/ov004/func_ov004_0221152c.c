/* func_ov004_0221152c @ 0x0221152c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void memset();
extern int func_ov004_0223ce98();
extern int func_ov004_0223cf10();

int func_ov004_0221152c(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_ov004_0223ce98(func_ov004_0223cf10(self), self);
    if (v2 == 0x0) {
        return 0x0;
    }
    memset(v2, 0x0, self);
    return v2;
}
