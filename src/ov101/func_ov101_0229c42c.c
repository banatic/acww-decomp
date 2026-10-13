/* func_ov101_0229c42c @ 0x0229c42c, 0x54 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *, int);
extern void func_ov002_02207d24(void *, int);
extern int func_ov101_0229ce38(void *, int);
extern void func_ov101_0229c480(void *);
extern void func_ov101_0229c844(void *);
extern void func_ov101_0229c548(void *, int);

void func_ov101_0229c42c(char *self, int a, int c)
{
    self[0xb4] = (char) a;
    func_ov002_02208d30(self + 0x26e8, 1);

    if (func_ov101_0229ce38(self, a) != 0) {
        func_ov101_0229c480(self);
        func_ov101_0229c844(self);
        if (c == 0) {
            func_ov002_02207d24(self + 0x21b4, 1);
        }
        func_ov101_0229c548(self, c);
    }
}
