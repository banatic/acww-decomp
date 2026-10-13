/* func_020a25e8 @ 0x020a25e8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020682e0(int);
extern void func_02068358(int);
extern void func_02068434(int);
extern void func_0206844c(int, char *, char *);
extern char data_020e3c40;

void func_020a25e8(void)
{
    int a;
    char b;
    a = func_020682e0(0);
    func_02068358(a);
    func_02068434(a);
    b = 0x0b;
    func_0206844c(a, &b, &data_020e3c40);
}
