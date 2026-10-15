/* func_ov004_02232314 @ 0x02232314, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02032180(void *arg0);
extern int func_020b65c4(void);

int func_ov004_02232314(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020b65c4();
    if (v1 == 0xa) {
        return func_02032180(self);
    }
    return v1;
}
