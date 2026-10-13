/* func_ov004_0220ffbc @ 0x0220ffbc, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02054ec4(char *);
extern void func_02054cdc(char *);
extern int func_02056f94(char *);
extern int func_ov004_0220e4b0(char *);
extern void func_02056ffc(char *);

int func_ov004_0220ffbc(char *self)
{
    // DECLS
    int a;
    int ok;
    unsigned int i;
    char *p;
    // ENDDECLS

    ok = 1;
    a = 1;
    if (func_02054ec4(self + 0x538) != 0) {
        func_02054cdc(self + 0x538);
        if (func_02056f94(self + 0x5d4) == 0) {
            a = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (func_ov004_0220e4b0(self + 0x7c4 + i * 0x20) != 0) {
            p = self + 0x7c4;
            p = p + i * 0x20;
            func_02056ffc(p);
            **(unsigned int **) (self + i * 0x20 + 0x7dc) = *(unsigned int *) (self + i * 0x20 + 0x7cc);
            if (func_02056f94(p) == 0) {
                ok = 0;
            }
        }
    }
    if (ok != 0 && a != 0) {
        return 1;
    }
    return 0;
}
