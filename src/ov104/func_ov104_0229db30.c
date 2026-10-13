/* func_ov104_0229db30 @ 0x0229db30, 0x44 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da70(int, int, int);
extern int func_ov104_0229dad8(int);
extern int func_ov104_0229da80(int, int, int);
extern int func_ov104_0229daa0(int);
extern int func_ov104_0229db74(int, int, int);

int func_ov104_0229db30(int a0, int a1, int a2)
{
    int a = 0x21;
    if (a2 >= 0xC0) {
        if (func_ov104_0229da70(a0, a1, a2) != 0) {
            a = func_ov104_0229dad8(a0);
        }
    } else {
        if (func_ov104_0229da80(a0, a1, a2) != 0) {
            a = func_ov104_0229daa0(a0);
        }
    }
    if (a != 0x21) {
        a1 = a;
    }
    return func_ov104_0229db74(a0, a1, 4);
}
