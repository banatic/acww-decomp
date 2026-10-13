/* func_0204dc9c @ 0x0204dc9c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *a, void *b);

void func_0204dc9c(void *a, void *b)
{
    void *p;
    void *q;

    p = *(void **) a;
    if (p != 0) {
        func_020e993c(b, p);
        *(void **) a = 0;
    }
}
