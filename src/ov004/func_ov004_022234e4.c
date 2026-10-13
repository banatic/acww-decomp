/* func_ov004_022234e4 @ 0x022234e4, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_02222ec0(void *p, void *self);
extern void func_0202edfc(void *self, int a, int b);
extern void func_0201c3f4(void *self, int a);
extern void func_0203edf4(void *self, int a);

int func_ov004_022234e4(char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov004_02222ec0(self + 0x658, self);
    func_0202edfc(self, 0x119a, 0x2000);
    func_0201c3f4(self, 0);
    func_0203edf4(self, 0x3000);
    return 1;
}
