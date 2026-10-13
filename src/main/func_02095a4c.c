/* func_02095a4c @ 0x02095a4c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern void *func_0200a448(void *, int, int, unsigned char, int, int, int, int);

void *func_02095a4c(int a, int *b, unsigned char *c, int *d, int e)
{
    void *ptr;

    ptr = func_02096718(4);
    if (ptr != 0) {
        return func_0200a448(ptr, a, *b, *c, *d, e, 6, -1);
    }
    return 0;
}
