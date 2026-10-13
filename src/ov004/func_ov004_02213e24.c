/* func_ov004_02213e24 @ 0x02213e24, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cfc8();
extern void func_020b9d3c();
extern void func_ov004_0220d280();
extern void *data_ov004_022531c8;

int func_ov004_02213e24(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    v2 = *(int *) (self + 0x594);
    func_020b9d3c(self + 0x848, v2, &data_ov004_022531c8, func_0203cfc8(*(int *) (self + 0x844)), 0x0, 0x0);
    return 0x1;
}
