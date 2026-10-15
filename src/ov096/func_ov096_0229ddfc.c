/* func_ov096_0229ddfc @ 0x0229ddfc, 0x10 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f200(void *p, unsigned char c);

int func_ov096_0229ddfc(unsigned char *p)
{
    unsigned char *q = p;
    q += 0xb5;
    return func_ov096_0229f200(p, *q);
}
