/* func_0203fa58 @ 0x0203fa58, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_020992f0(void);
extern int func_0203fa98(int, int);

int func_0203fa58(void)
{
    int i;
    int count;
    int a;

    func_020984e8();
    a = func_020992f0();
    count = 0;
    i = count;
    do {
        if (func_0203fa98(a, i) != 0xff) {
            count++;
        }
        i++;
    } while (i < 4);
    return count;
}
