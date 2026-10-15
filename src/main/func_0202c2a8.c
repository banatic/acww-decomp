/* func_0202c2a8 @ 0x0202c2a8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0202c2a8(void *self)
{
    void *p;
    void *base;
    int (*fp)(void *);

    p = *(void **) ((char *) self + 0x100);
    base = *(void **) p;
    fp = *(int (**)(void *))((char *) base + 0xb0);
    return fp(p);
}
