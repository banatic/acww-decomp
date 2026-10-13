/* func_ov105_0229d17c @ 0x0229d17c, 0x48 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(char *);
extern int func_ov002_02209f14(char *);
extern int func_0208e4bc(char *);

void func_ov105_0229d17c(char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209f3c(p + 0x24a4) - 2;
    *(int *) (p + 0xb0) = func_ov002_02209f14(p + 0x24a4) - 4;
    if (func_0208e4bc(p + 0x24a4) == 1) {
        *(int *) (p + 0xb0) -= 0x16;
    }
}
