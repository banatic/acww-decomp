/* func_02037e44 @ 0x02037e44, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void *func_02037e0c(void *a, void *b, void *c, unsigned char d);

int func_02037e44(void *a, unsigned short *b, void *c, void *d, unsigned char e)
{
    void *p = func_02037e0c(a, c, d, e);
    int ret = 0;
    if (p) {
        *(unsigned short *) p = *b;
        ret = 1;
    }
    return ret;
}
