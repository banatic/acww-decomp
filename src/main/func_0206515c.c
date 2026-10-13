/* func_0206515c @ 0x0206515c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea838(int *, int *);
extern int VEC_Mag(int *);
extern int FX_MulFunc(int, int);

void func_0206515c(int *arg1, int *arg2)
{
    if (func_020ea838(arg1, arg2) != 0) {
        if (VEC_Mag(arg1) >= 0xff0) {
            arg1[0] = FX_MulFunc(arg1[0], 0xff0);
            arg1[1] = FX_MulFunc(arg1[1], 0xff0);
            arg1[2] = FX_MulFunc(arg1[2], 0xff0);
        }
    }
    if (arg2 != 0) {
        arg2[0] = arg1[0];
        arg2[1] = arg1[1];
        arg2[2] = arg1[2];
    }
}
