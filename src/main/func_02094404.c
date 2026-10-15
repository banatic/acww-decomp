/* func_02094404 @ 0x02094404, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *p, int a, int b, int c);
extern void func_0203423c(void *p);
extern int func_02094cf8(int a, int b, int c, int d, int e, void *f);
extern char data_020e28cc;

int func_02094404(int a, int b, int c, int d)
{
    char buf[0x44];
    int value;

    func_02034270(buf, b, 0, 0);
    if (*(int *) (buf + 0x34) == 0x13) {
        value = 0x2e;
    } else {
        value = 0x2c;
    }
    value = func_02094cf8(value, a, b, c, d, &data_020e28cc);
    func_0203423c(buf);
    return value;
}
