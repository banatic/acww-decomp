/* func_ov002_02209e50 @ 0x02209e50, 0x66 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(char *p);
extern int func_ov002_02209d84(char *p);
extern int func_ov002_02209d7c(char *p);
extern void func_ov002_0220a0e0(char *self, int a, int b);
extern int func_0208e484(char *self);
extern int func_0208e4bc(char *self);
extern void func_0208e508(char *self, int v);
extern void func_0208e5d4(char *self);

void func_ov002_02209e50(char *self)
{
    int a;
    int b;

    func_ov002_02209d8c(self + 0x4c);
    a = func_ov002_02209d84(self + 0x4c);
    b = func_ov002_02209d7c(self + 0x4c);
    func_ov002_0220a0e0(self, a, b);
    if (func_0208e484(self)) {
        if (func_0208e4bc(self) == 5) {
            func_0208e508(self, 1);
        } else if (func_0208e4bc(self) == 0xb) {
            func_0208e508(self, 7);
        }
    }
    func_0208e5d4(self);
}
