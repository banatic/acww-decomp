/* func_02084260 @ 0x02084260, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_0208602c(void);
extern int func_020860c4(int);
extern void func_02087f40(int a, int *b);
extern void func_0204f794(int *a, int b, int c);

int func_02084260(int unused, int *p)
{
    int flag;

    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        func_02087f40(func_020860c4((int) func_0208602c()), p);
        return 1;
    } else {
        func_0204f794(p, 6, 0x11);
        *p = *p + 0x1000;
        return 1;
    }
}
