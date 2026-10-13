/* func_ov101_0229c9d8 @ 0x0229c9d8, 0x28 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *);
extern int func_ov002_02209d7c(void *);

void func_ov101_0229c9d8(char *self)
{
    *(int *) (self + 0xa4) = func_ov002_02209d84(self + 0x2284);
    *(int *) (self + 0xa8) = func_ov002_02209d7c(self + 0x2284);
}
