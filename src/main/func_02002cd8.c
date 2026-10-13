/* func_02002cd8 @ 0x02002cd8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02064b2c(int, int, int, void *);
extern int func_02002bd0(char *, int, unsigned char, unsigned char, unsigned char);
extern void func_020e993c(int, char *);

int func_02002cd8(int p0, int a, int b, int c, unsigned char d5)
{
    int tmp[2];
    char *base;
    char *slot;
    int result;

    base = func_02064b2c(p0, a, -4, tmp);
    slot = base;
    slot += c << 5;
    result = func_02002bd0(slot, b, d5, d5, d5);
    func_020e993c(a, base);
    return result;
}
