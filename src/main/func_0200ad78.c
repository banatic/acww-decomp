/* func_0200ad78 @ 0x0200ad78, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct In0200ad78 {
    unsigned long x;
    unsigned long y;
};

struct Out0200ad78 {
    unsigned short a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};

void func_0200ad78(struct Out0200ad78 *out, const struct In0200ad78 *in, unsigned short a, unsigned char b)
{
    out->b = in->x;
    out->c = in->y;
    out->a = a;
    out->d = b;
}
