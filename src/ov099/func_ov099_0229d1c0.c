/* func_ov099_0229d1c0 @ 0x0229d1c0, 0x44 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0208e4bc(void *);
extern void func_ov099_0229c608(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov099_0229d1c0(char *self)
{
    if (func_ov002_0220909c(self + 0x22d8) == 0) {
        return;
    }
    func_ov002_022096d8(self + 0x22d8, 0);
    if (func_0208e4bc(self + 0x2274)) {
        func_ov099_0229c608(self);
    }
    func_ov002_02208098(self, 0x13);
}
