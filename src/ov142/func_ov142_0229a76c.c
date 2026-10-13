/* func_ov142_0229a76c @ 0x0229a76c, 0x74 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(short *, unsigned short *, unsigned short, int);
extern int func_0204c2b4(unsigned short *);
extern int func_020996ac(int);
extern int func_0203cdcc(int, unsigned short *);

int func_ov142_0229a76c(short *base, unsigned short *out, unsigned short step, int count, int index)
{
    int i = 0;
    int saved;
    unsigned short local;
    int j;
    short *p;

    saved = func_020984e8(base, out, step, count);
    local = 0xfff1;
    j = 0;
    p = base + index;

    while (j < count) {
        local = step;
        if (func_0204c2b4(&local)) {
            p[0x6b] = p[0x6b] + 1;
            if (func_0203cdcc(func_020996ac(saved), &local)) {
                out[i] = step;
                i++;
            }
        }
        step = (unsigned short) (step + 4);
        j++;
    }
    return i;
}
