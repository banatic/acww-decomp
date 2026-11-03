/* activity_card: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a1774 @ 0x020a1774, 0x32 bytes, Thumb
 * func_020a1768 @ 0x020a1768, 0xc bytes, Thumb
 * func_020a1738 @ 0x020a1738, 0x30 bytes, Thumb
 */

extern void func_0209fb70(void *);
extern void func_0209fb6c(void *);
extern int func_02050a10(int a, int b, int c, int d);
extern char data_021dc7a8[];
extern char data_021f3ba0[];
extern int data_020d1c20[];
extern unsigned char data_021c8188[];

int func_020a1738(int idx, int param1);

int func_020a1774(void *param)
{
    void *sp;
    int result;

    func_0209fb70(&sp);
    result = func_020a1738((int) param, (int) (&sp));
    if (result != 0) {
        func_0209fb6c(&sp);
        return 1;
    } else {
        func_0209fb6c(&sp);
        return 0;
    }
}

int func_020a1768(void)
{
    return func_020a1774(0);
}

int func_020a1738(int idx, int param1)
{
    return func_02050a10((unsigned int) data_021c8188, param1, 4, (data_021f3ba0 - data_021dc7a8) + data_020d1c20[idx]);
}
