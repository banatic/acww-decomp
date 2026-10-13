/* func_020a9ce0 @ 0x020a9ce0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Handler)(void *);

void func_020a9ce0(void **pp)
{
    void *p = *pp;
    if (p != 0) {
        Handler *handlers = *(Handler **) p;
        handlers[3](p);
    }
}
