/* func_ov004_0222fae4 @ 0x0222fae4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6590(int);
extern void func_020b7e04(int, void *);
extern int func_ov004_0222f640(void *);
extern void func_ov004_0222f908(void *);

int func_ov004_0222fae4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222f908(self);
    func_020b7e04(func_020b6590(func_ov004_0222f640(self)), self + 0x374);
    return 0x1;
}
