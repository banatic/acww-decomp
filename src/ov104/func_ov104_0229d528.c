/* func_ov104_0229d528 @ 0x0229d528, 0x2c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(char *ptr);
extern int func_ov002_02209f14(char *ptr);

void func_ov104_0229d528(char *obj)
{
    *(int *) (obj + 0xa8) = func_ov002_02209f3c(obj + 0x24a0) - 2;
    *(int *) (obj + 0xac) = func_ov002_02209f14(obj + 0x24a0) - 4;
}
