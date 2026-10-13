/* func_ov004_0223cc10 @ 0x0223cc10, 0x4a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned func_ov004_0223c130(void);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, unsigned);
void *func_ov004_0223cc10(char *base, int x, int y, int layer)
{
    unsigned char *p = (unsigned char *) base + ((layer & 1) << 8) + ((y & 0xf) << 4) + (x & 0xf);
    unsigned char id = *p;
    if (id != 0xff && id < func_ov004_0223c130() && func_ov004_0223cd58(func_ov004_0223ce84(), id) != 0) {
        return func_ov004_0223cd58(func_ov004_0223ce84(), *p);
    }
    return 0;
}
