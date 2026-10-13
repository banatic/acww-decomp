/* func_ov102_0229cd38 @ 0x0229cd38, 0x48 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(char *);
extern int func_ov002_02209f14(char *);
extern int func_0208e4bc(char *);

void func_ov102_0229cd38(char *obj)
{
    *(int *) (obj + 0x24e0) = func_ov002_02209f3c(obj + 0x2274) - 2;
    *(int *) (obj + 0x24e4) = func_ov002_02209f14(obj + 0x2274) - 4;
    if (func_0208e4bc(obj + 0x2274) == 1) {
        *(int *) (obj + 0x24e4) -= 22;
    }
}
