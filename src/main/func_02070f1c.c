/* func_02070f1c @ 0x02070f1c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071298(int a, short *b);

int func_02070f1c(int param)
{
    unsigned int i;
    short val;
    int base = 0x450c;
    for (i = 0; i < 52; i++) {
        val = (i < 52) ? base + i * 4 : base;
        if (func_02071298(param, &val) == 0) {
            return 0;
        }
    }
    return 1;
}
