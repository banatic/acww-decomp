/* func_ov003_0221a0d4 @ 0x0221a0d4, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203edd0(char *a);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020ea990(char *a, char *b);

int func_ov003_0221a0d4(char *a, char *b)
{
    int v;
    func_0203edd0(a);
    v = FX_MulFunc(0x2000, FX_Div(0x7d000, 0x64000));
    if (b != 0 && func_020ea990(b + 0x5c, a + 0x5c) < v && *(int *) (a + 0x39c) == 0xb) {
        return 1;
    } else {
        return 0;
    }
}
