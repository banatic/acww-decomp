/* func_ov004_02218b5c @ 0x02218b5c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);
extern int func_ov004_02210744(void *);

int func_ov004_02218b5c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210744(self);
    func_ov004_02210054(self, 0x0, 0x3, 0x1000);
    return 0x1;
}
