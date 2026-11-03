/* text_base_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8a34 @ 0x020a8a34, 0x3c bytes, Thumb
 * func_020a89f8 @ 0x020a89f8, 0x3c bytes, Thumb
 */

extern void func_020a8d20(int *g, int a, int b, int c, int d);
extern int func_020a922c(int *g, int x);
extern int func_020a8d08(int *g);
extern void func_020a8d10(int *g);
extern char data_021f450c[];

int func_020a8a34(int param0, int param1)
{
    int result;

    func_020a8d20(((int *) data_021f450c), param0, param1, 0, 1);
    func_020a922c(((int *) data_021f450c), 0);
    result = func_020a8d08(((int *) data_021f450c));
    func_020a8d10(((int *) data_021f450c));
    return result;
}

int func_020a89f8(int a, int b)
{
    int result;
    func_020a8d20((int *) data_021f450c, a, b, 1, 0);
    func_020a922c((int *) data_021f450c, 0);
    result = func_020a8d08((int *) data_021f450c);
    func_020a8d10((int *) data_021f450c);
    return result;
}
