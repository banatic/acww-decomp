/* func_ov122_0229fa34 @ 0x0229fa34, 0x5c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206de38(void *ptr, unsigned char b);
extern unsigned int *func_0206de7c(void *ptr);
extern int func_02051d08(unsigned short *ptr, int diff);

void func_ov122_0229fa34(char *self)
{
    int idx;
    unsigned char b;
    unsigned int *arr;
    unsigned int val;
    char *base;
    unsigned short *p;
    int diff;
    int res;

    idx = func_0206de38(self + 0x3ce8, *(unsigned char *) (self + 0xac));
    *(unsigned int *) (self + 0xa0) = (idx << 4) + 0x40;
    arr = func_0206de7c(self + 0x3ce8);
    val = arr[idx];
    base = *(char **) (self + 0xbc);
    p = (unsigned short *) (base + 0x58 + val * 2);
    b = *(unsigned char *) (self + 0xac);
    diff = (int) (b - val);
    res = func_02051d08(p, diff);
    *(unsigned int *) (self + 0x9c) = (unsigned char) (res + 0x30);
}
