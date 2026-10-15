/* func_ov004_02219f28 @ 0x02219f28, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210054(void *self, int a, int b, int c);
extern int func_ov004_0220fde0(void *self);
extern int func_ov004_02210744(void *self);

int func_ov004_02219f28(void *self)
{
    func_ov004_02210054(self, 0, 1, 0x1000);
    if (func_ov004_0220fde0(self) != 0x207) {
        func_ov004_02210744(self);
    }
    return 1;
}
