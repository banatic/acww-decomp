/* func_02048b0c @ 0x02048b0c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c79e4[];
extern int func_020644cc(int);
extern int func_02048bc0(int, int, int, int, int);

void func_02048b0c(int a, int b, int c, int d)
{
    int i;
    int t1;
    int t2;

    i = 2 - data_021c79e4[0xc];
    while (i != 0) {
        t1 = func_020644cc(c);
        t2 = func_020644cc(d);
        func_02048bc0(a, b, t1 + 1, t2 + 1, 0);
        i--;
    }
}
