/* func_ov124_0229f2e4 @ 0x0229f2e4, 0x3c bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov124_0229f27c(void);
extern void func_02070978(int a, int b);

void func_ov124_0229f2e4(int a)
{
    int val;
    switch (func_ov124_0229f27c()) {
        case 0:
        case 1:
            val = 2;
            break;
        case 2:
        case 3:
        case 4:
            val = 0;
            break;
    }
    func_02070978(a, val);
}
