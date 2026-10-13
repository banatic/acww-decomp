/* func_ov110_0229d0fc @ 0x0229d0fc, 0x40 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(int, int);
extern int func_ov110_0229d5d4(int, int);
extern int func_ov110_0229d590(int, int);
extern int func_ov094_0229a69c(int, int);

int func_ov110_0229d0fc(int param1, int param2)
{
    if (func_ov110_0229d5e4(param1, param2) || func_ov110_0229d5d4(param1, param2)) {
        return func_ov094_0229a69c(param1 + 0x138, func_ov110_0229d590(param1, param2));
    } else {
        return 1;
    }
}
