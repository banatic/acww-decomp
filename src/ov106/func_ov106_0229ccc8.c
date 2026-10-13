/* func_ov106_0229ccc8 @ 0x0229ccc8, 0x58 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229cc84(unsigned char *p);
extern int func_ov106_0229cc74(unsigned char *p);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int v);
extern int func_ov106_0229d384(unsigned char *p, unsigned char c);
extern void func_ov106_0229ca3c(unsigned char *p);

void func_ov106_0229ccc8(unsigned char *p)
{
    func_ov002_0220a0b4(p + 0x22a0, func_ov106_0229cc84(p), func_ov106_0229cc74(p));
    if (func_ov106_0229d384(p, p[0xb8]) != 0) {
        func_ov002_0220a374(p + 0x22a0, 7);
    } else {
        func_ov002_0220a374(p + 0x22a0, 1);
    }
    func_ov106_0229ca3c(p);
}
