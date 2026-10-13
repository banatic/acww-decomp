/* func_ov004_02212b70 @ 0x02212b70, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern void func_ov004_02210744(void *);

int func_ov004_02212b70(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210744(self);
    func_ov004_022101e4(self, 0x1, 0x1, 0x1000, 0xffff);
    return 0x1;
}
