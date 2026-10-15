/* func_020a8a34 @ 0x020a8a34, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int g_021f450c;
extern void func_020a8d20(int *g, int a, int b, int c, int d);
extern int func_020a922c(int *g, int x);
extern int func_020a8d08(int *g);
extern void func_020a8d10(int *g);

int func_020a8a34(int param0, int param1)
{
    int result;

    func_020a8d20(&g_021f450c, param0, param1, 0, 1);
    func_020a922c(&g_021f450c, 0);
    result = func_020a8d08(&g_021f450c);
    func_020a8d10(&g_021f450c);
    return result;
}
