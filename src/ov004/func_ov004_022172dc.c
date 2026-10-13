/* func_ov004_022172dc @ 0x022172dc, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern void func_ov004_02210744(void *);

int func_ov004_022172dc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_02210744(self);
    if (*(int *) (self + 0x780) == 0xf) {
        func_ov004_022101e4(self, 0x1, 0x1, 0x1000, 0x0);
    } else {
        func_ov004_02210054(self, 0x0, 0x3, 0x1000);
    }
    return 0x1;
}
