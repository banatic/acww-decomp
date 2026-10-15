/* func_ov122_0229f2f4 @ 0x0229f2f4, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229efc8(unsigned char *, unsigned int);
extern void func_ov095_02299aec(unsigned char *);
extern int func_ov095_02299b7c(unsigned char *);
extern int func_ov095_02299b38(unsigned char *);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern void func_ov122_0229f150(unsigned char *);

void func_ov122_0229f2f4(unsigned char *self)
{
    int x, y;

    func_ov122_0229efc8(self, 0x100);
    func_ov095_02299aec(self + 0xc0);
    x = func_ov095_02299b7c(self + 0xc0);
    y = func_ov095_02299b38(self + 0xc0);
    func_ov002_0220a0b4(self + 0x4058, x, y);
    func_ov002_0220a374(self + 0x4058, 1);
    func_ov122_0229f150(self);
}
