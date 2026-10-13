/* func_ov122_0229ff2c @ 0x0229ff2c, 0x68 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207fc0(char *);
extern void func_ov122_0229f2f4(char *);
extern int func_ov002_02208ad4(char *);
extern int func_ov002_02208ae4(char *);
extern int func_ov002_02208ad8(char *, unsigned char);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);
extern void func_ov002_02208098(char *, int);

void func_ov122_0229ff2c(char *self)
{
    int a, b;

    func_ov002_02207fc0(self);
    func_ov122_0229f2f4(self);

    *((unsigned char *) self + 0xb6) = func_ov002_02208ad4(self + 0x42b0) - 1;

    a = func_ov002_02208ae4(self + 0x42b0);
    b = func_ov002_02208ad8(self + 0x42b0, *((unsigned char *) self + 0xb6));

    func_ov002_0220a0b4(self + 0x4058, a, b);
    func_ov002_0220a374(self + 0x4058, 7);
    func_ov002_02208098(self, 0x14);
}
