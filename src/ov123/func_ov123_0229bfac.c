/* func_ov123_0229bfac @ 0x0229bfac, 0x34 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af74(void *);
extern void func_ov123_0229a1e8(void *);
extern void func_ov123_02299e84(void *);
extern void func_02095904(void);
extern int func_0206fca4(void);
extern void func_020045ac(int);

void func_ov123_0229bfac(void *self)
{
    func_ov002_0220af74((char *) self + 0x5030);
    func_ov123_0229a1e8(self);
    func_ov123_02299e84(self);
    func_02095904();
    if (func_0206fca4() == 3) {
        func_020045ac(0);
    }
}
