/* func_0201a48c @ 0x0201a48c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201a5d8(void);
extern void func_02091278(int, int, short *, int);
extern void func_0201a518(int *, int, short, int, unsigned short, int);

void func_0201a48c(int *a, int b, short c, int d, unsigned short e)
{
    int i;
    int zero;

    func_0201a5d8();
    zero = 0;

    for (i = 0; i < 4; i++) {
        if (a[i] != ~zero) {
            func_02091278(a[i], b, &c, zero);
        }
    }

    for (i = 0; i < 2; i++) {
        func_0201a518(a, b, c, d, e, i);
    }
}
