/* func_0209e100 @ 0x0209e100, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e140(unsigned char *p, int q);

void func_0209e100(unsigned char *p, int a)
{
    int diff = p[2] - a;
    if (diff < 0) {
        int q, rem, s;
        if (diff < 0) {
            diff = -diff;
        }
        q = diff / 24 + 1;
        rem = diff % 24;
        s = 24 - rem;
        if (s == 24) {
            s = 0;
            q--;
        }
        func_0209e140(p, q);
        diff = s;
    }
    p[2] = diff;
}
