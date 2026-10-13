/* func_ov004_0223de14 @ 0x0223de14, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *buf, void *vec, int a, int b);
extern int func_020341c8(void *buf, int flag);
extern void func_0203423c(void *buf);

int func_ov004_0223de14(char *self)
{
    char buf[0x40];
    if (*(int *) (self + 0x60) >= 0xc00) {
        *(int *) (self + 0x60) = *(int *) (self + 0x6c);
        if ((*(int *) (self + 0xe0) & 1) != 0) {
            *(int *) (self + 0x10c) = 2;
            func_02034270(buf, self + 0x5c, 0, 0);
            *(int *) (self + 0x60) = func_020341c8(buf, 1);
            func_0203423c(buf);
            return 1;
        }
    }
    return 0;
}
