/* func_02091310 @ 0x02091310, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02091444(void *a, int b, void *c, int d);

unsigned short func_02091310(void *a, int b)
{
    void *result;
    unsigned short ret;
    result = func_02091444(a, b, a, 0x20);
    ret = 0x66;
    if (result != 0) {
        ret = *(unsigned short *) ((char *) result + 0x18);
    }
    return ret;
}
