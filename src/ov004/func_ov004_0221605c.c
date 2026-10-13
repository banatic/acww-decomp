/* func_ov004_0221605c @ 0x0221605c, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8(void *, int);
extern void func_02095ec4(int);
extern void func_ov004_0220d058(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0220d2a8(void *);
extern void func_ov004_0220ffbc(void *, int);

void func_ov004_0221605c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x780) == 0x29) {
        func_ov004_0220ffbc(self, *(int *) (self + 0x780));
    }
    func_ov004_0220d058(self + 0x848, 0x0, 0x1, 0x0);
    if (func_ov004_0220d2a8(self + 0x740) != 0x0) {
        func_ov004_0220d280(self + 0x740, 0x0, 0x0);
        func_02095ec4(func_0203e0a8(self, 0x0));
        return;
    }
}
