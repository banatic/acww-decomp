/* func_0201d9b8 @ 0x0201d9b8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d8f8(void *, void *, void *, void *);

int func_0201d9b8(void *p)
{
    volatile int unused = 0;
    return func_0202d8f8(p, (char *) p + 0x12c, (char *) p + 0x128,
                         *(void **) ((char *) *(void **) ((char *) p + 0x100) + 0x830));
}
