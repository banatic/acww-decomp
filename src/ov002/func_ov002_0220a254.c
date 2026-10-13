/* func_ov002_0220a254 @ 0x0220a254, 0x60 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *self);
extern int func_ov002_02209f3c(void *self);
extern int func_ov002_02209f14(void *self);
extern void func_ov002_0220a0b4(void *self, int a, int b);
extern void func_ov002_0220a374(void *self, int v);

void func_ov002_0220a254(void *self)
{
    if (func_0208e4bc(self) == 1) {
        func_ov002_0220a0b4(self, func_ov002_02209f3c(self) + 0xc, func_ov002_02209f14(self) - 0x18);
    } else if (func_0208e4bc(self) == 7) {
        func_ov002_0220a0b4(self, func_ov002_02209f3c(self) - 4, func_ov002_02209f14(self) - 0x18);
    }
    func_ov002_0220a374(self, 0xd);
}
