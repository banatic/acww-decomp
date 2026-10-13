/* func_ov003_0223108c @ 0x0223108c, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);
extern int FX_Div(int num, int den);

void func_ov003_0223108c(char *self)
{
    int *v = (int *) (self + 0x204);
    if (func_020644cc(2) == 0) {
        v[0] += FX_Div(0x7000, 0x10000);
        v[1] = FX_Div(0xc000, 0x10000);
        v[2] += FX_Div(0x3000, 0x10000);
    } else {
        v[0] -= FX_Div(0x7000, 0x10000);
        v[1] = FX_Div(0xc000, 0x10000);
        v[2] += FX_Div(0x3000, 0x10000);
    }
}
