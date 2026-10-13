/* func_ov004_0222bf74 @ 0x0222bf74, 0x3e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern void *func_ov004_02228100(void *, int, int, unsigned char, int, int, int, int);

void *func_ov004_0222bf74(int a, int *b, unsigned char *c, int *d, int e)
{
    void *ptr;

    ptr = func_02096718(4);
    if (ptr != 0) {
        return func_ov004_02228100(ptr, a, *b, *c, *d, e, 6, -1);
    }
    return 0;
}
