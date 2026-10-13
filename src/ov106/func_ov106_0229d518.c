/* func_ov106_0229d518 @ 0x0229d518, 0x64 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209d68(void *, int, int);
extern void func_ov002_02209d38(void *, int, int, int);
extern void func_ov002_02209d8c(void *);
extern void func_ov002_02208098(void *, int);
extern int func_ov106_0229d170(void *, int);
extern int func_ov106_0229d128(void *, int);
extern void func_ov106_0229cde4(void *);

void func_ov106_0229d518(char *self, int p2, int p3)
{
    int a, b;
    self[0xB7] = (char) p2;
    func_ov002_02209d68(self + 0x2288, *(int *) (self + 0xac), *(int *) (self + 0xb0));
    a = func_ov106_0229d170(self, p2);
    b = func_ov106_0229d128(self, p2);
    func_ov002_02209d38(self + 0x2288, a, b, p3);
    func_ov002_02209d8c(self + 0x2288);
    func_ov106_0229cde4(self);
    func_ov002_02208098(self, 0x15);
}
