/* func_ov096_0229ea34 @ 0x0229ea34, 0x28 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(char *p);
extern int func_ov002_02209d7c(char *p);

void func_ov096_0229ea34(char *self)
{
    *(int *) (self + 0xa4) = func_ov002_02209d84(self + 0x24e8);
    *(int *) (self + 0xa8) = func_ov002_02209d7c(self + 0x24e8);
}
