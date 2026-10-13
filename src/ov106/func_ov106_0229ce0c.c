/* func_ov106_0229ce0c @ 0x0229ce0c, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *ptr);
extern int func_ov002_02209f14(void *ptr);

void func_ov106_0229ce0c(char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209f3c(p + 0x22a0) - 2;
    *(int *) (p + 0xb0) = func_ov002_02209f14(p + 0x22a0) - 4;
}
