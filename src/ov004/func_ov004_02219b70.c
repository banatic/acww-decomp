/* func_ov004_02219b70 @ 0x02219b70, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d058(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_0221078c(void *);

int func_ov004_02219b70(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0221078c(self);
    func_ov004_0220d058(self + 0x848, 0x1, 0x1, 0x0);
    return 0x1;
}
