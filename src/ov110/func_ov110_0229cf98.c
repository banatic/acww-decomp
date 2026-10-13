/* func_ov110_0229cf98 @ 0x0229cf98, 0x3c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(int a, int b);
extern int func_ov110_0229d5d4(int a, int b);
extern int func_ov110_0229d590(int a, int b);
extern void func_ov094_0229aafc(void *addr, int val);

void func_ov110_0229cf98(int a, int b)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        func_ov094_0229aafc((char *) a + 0x138, func_ov110_0229d590(a, b));
    }
}
