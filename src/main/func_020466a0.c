/* func_020466a0 @ 0x020466a0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_020466d8(void);

void func_020466a0(unsigned int a, unsigned int b)
{
    unsigned int *p;
    int i;
    int mask;
    int zero;

    p = func_020466d8();
    i = 0;
    mask = ~i;
    zero = i;
    while (i < 24) {
        if (p[0] == ~zero && p[1] == mask) {
            p[0] = a;
            p[1] = b;
            break;
        }
        p += 2;
        i++;
    }
}
