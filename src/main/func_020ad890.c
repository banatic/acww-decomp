/* func_020ad890 @ 0x020ad890, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02245ff8(int a, int b);
extern int func_020adf8c(const int *p, int b);
extern void func_020b0200(const int *p);
extern void func_020ad8d0(int a, int b, int c, int d);

extern int data_021f3b30;
extern int data_021f49ec;

void func_020ad890(int a, int b, int c)
{
    int x = func_ov004_02245ff8(a, b);
    int y = func_020adf8c(&data_021f3b30, x);
    if (y != -1) {
        func_020b0200(&data_021f49ec);
        func_020ad8d0(y, c, 1, 0);
    }
}
