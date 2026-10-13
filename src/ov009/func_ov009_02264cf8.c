/* func_ov009_02264cf8 @ 0x02264cf8, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_02264884(void *p);

unsigned int func_ov009_02264cf8(void *p, unsigned int n)
{
    void *q;
    if (n >= 4) {
        goto fail;
    }
    q = func_ov009_02264884(p);
    if (q == 0) {
        goto fail;
    }
    return *(unsigned int *) ((char *) q + n * 4 + 0x20);
fail:
    return 0;
}
