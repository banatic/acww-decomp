/* func_ov106_0229cde4 @ 0x0229cde4, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(unsigned char *p);
extern int func_ov002_02209d7c(unsigned char *p);

void func_ov106_0229cde4(unsigned char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209d84(p + 0x2288);
    *(int *) (p + 0xb0) = func_ov002_02209d7c(p + 0x2288);
}
