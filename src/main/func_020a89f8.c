/* func_020a89f8 @ 0x020a89f8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f450c[];
extern void func_020a8d20(void *g, int a, int b, int c, int d);
extern int func_020a922c(void *g, int a);
extern int func_020a8d08(void *g);
extern void func_020a8d10(void *g);

int func_020a89f8(int a, int b)
{
    int result;
    func_020a8d20(data_021f450c, a, b, 1, 0);
    func_020a922c(data_021f450c, 0);
    result = func_020a8d08(data_021f450c);
    func_020a8d10(data_021f450c);
    return result;
}
