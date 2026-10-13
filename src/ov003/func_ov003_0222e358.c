/* func_ov003_0222e358 @ 0x0222e358, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int num, int den);

void func_ov003_0222e358(char *self, int pct)
{
    if (pct == 0x64) {
        *(int *) (self + 0x210) = 0x1000;
        *(int *) (self + 0x214) = 0x1000;
        *(int *) (self + 0x218) = 0x1000;
    } else {
        *(int *) (self + 0x210) = FX_Div(pct << 12, 0x64000);
        *(int *) (self + 0x214) = *(int *) (self + 0x210);
        *(int *) (self + 0x218) = *(int *) (self + 0x210);
    }
}
