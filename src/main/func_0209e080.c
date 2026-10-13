/* func_0209e080 @ 0x0209e080, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e0c0(unsigned char *, int);

void func_0209e080(unsigned char *p, int v)
{
    int delta;
    int quotient;
    int remainder;
    int rounded;

    delta = *p - v;
    if (delta < 0) {
        delta = delta < 0 ? -delta : delta;
        quotient = delta / 60;
        rounded = quotient + 1;
        remainder = delta % 60;
        delta = 60 - remainder;
        if (delta == 60) {
            delta = 0;
            rounded--;
        }
        func_0209e0c0(p, rounded);
    }
    *p = delta;
}
