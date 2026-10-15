/* func_020a261c @ 0x020a261c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020682e0(int);
extern void func_02068358(int);
extern void func_02068434(int);
extern void func_0206844c(int, char *, char *);
extern char data_020e3c40[];

void func_020a261c(void *object)
{
    int a;
    char c;
    a = func_020682e0(0);
    func_02068358(a);
    func_02068434(a);
    c = 10;
    func_0206844c(a, &c, data_020e3c40);
}
