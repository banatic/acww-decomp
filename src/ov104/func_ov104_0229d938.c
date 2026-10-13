/* func_ov104_0229d938 @ 0x0229d938, 0x3c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(void);
extern int func_ov104_0229da70(int, int);
extern int func_ov104_0229da38(int, int);
extern void func_ov094_0229b8b4(int, int, int);

void func_ov104_0229d938(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;

    if (func_ov104_0229da80() == 0) {
        if (func_ov104_0229da70(r5, r4) == 0) {
            return;
        }
    }

    func_ov094_0229b8b4(r5 + 0xd58, func_ov104_0229da38(r5, r4), r6);
}
