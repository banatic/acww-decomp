/* func_ov106_0229cb58 @ 0x0229cb58, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(unsigned char *);
extern int func_ov002_02208ad8(unsigned char *, unsigned char);
extern void func_ov002_0220a08c(unsigned char *, int, int, int);
extern void func_ov002_02208098(unsigned char *, int);

void func_ov106_0229cb58(unsigned char *p)
{
    int a = func_ov002_02208ae4(p + 0x2304);
    int b = func_ov002_02208ad8(p + 0x2304, *(unsigned char *) (p + 0xbd));
    func_ov002_0220a08c(p + 0x22a0, a, b, 2);
    *(unsigned char *) (p + 0xbb) = *(unsigned char *) (p + 0x8d);
    func_ov002_02208098(p, 0xd);
}
