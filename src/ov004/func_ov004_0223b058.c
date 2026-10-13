/* func_ov004_0223b058 @ 0x0223b058, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223adf8(void *, int, int, int);
extern int func_ov004_0223b0a8(void *, int, int, int, int);

int func_ov004_0223b058(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    return func_ov004_0223b0a8(self, func_ov004_0223adf8(self, a1, a2, a3), a1, a2, a3);
}
