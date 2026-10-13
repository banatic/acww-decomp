/* func_0200a694 @ 0x0200a694, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Src;

void func_0200a694(unsigned char *out, const Src *src, unsigned char val)
{
    out[1] = (unsigned char) src->a;
    out[2] = (unsigned char) src->b;
    out[0] = val;
}
