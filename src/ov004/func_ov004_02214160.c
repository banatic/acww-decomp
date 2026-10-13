/* func_ov004_02214160 @ 0x02214160, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern void func_ov004_0221078c(void *);

int func_ov004_02214160(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x1);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}
