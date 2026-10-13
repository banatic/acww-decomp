/* func_ov004_02239bb4 @ 0x02239bb4, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02239bd4(void *, int, int);
extern void func_ov004_02239c00(void *, int, int);

int func_ov004_02239bb4(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239c00(self, a1, a2);
    return func_ov004_02239bd4(self + 0x8, a1, a2);
}
