/* func_0202d86c @ 0x0202d86c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02015d90(void *, int);

typedef void (*func_t)(void *, int, int);

void func_0202d86c(void *a, int b)
{
    void *ret;

    ret = func_02015d90(a, b);
    if (ret) {
        (*(func_t *) ((char *) *(void **) ret + 0xa4))(ret, 3, b);
    }
}
