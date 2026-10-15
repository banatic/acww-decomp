/* func_ov101_0229ce50 @ 0x0229ce50, 0x64 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209d68(void *, void *, void *);
extern int func_ov002_02209d38(void *, int, int, int);
extern int func_ov002_02209d8c(void *);
extern int func_ov101_0229cd08(void *, int);
extern int func_ov101_0229ccd0(void *, int);
extern void func_ov101_0229c9d8(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov101_0229ce50(char *self, int a, int b)
{
    int res1, res2;

    self[0xb2] = (char) a;
    func_ov002_02209d68(self + 0x2284, *(void **) (self + 0xa4), *(void **) (self + 0xa8));
    res1 = func_ov101_0229cd08(self, a);
    res2 = func_ov101_0229ccd0(self, a);
    func_ov002_02209d38(self + 0x2284, res1, res2, b);
    func_ov002_02209d8c(self + 0x2284);
    func_ov101_0229c9d8(self);
    func_ov002_02208098(self, 0x12);
}
