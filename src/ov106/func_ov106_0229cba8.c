/* func_ov106_0229cba8 @ 0x0229cba8, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *, int, int, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov106_0229cba8(void *p, int a, int b)
{
    func_ov002_0220a05c((char *) p + 0x22a0, a, b, 3, 1);
    ((unsigned char *) p)[0xbb] = ((unsigned char *) p)[0x8d];
    func_ov002_02208098(p, 0xd);
}
