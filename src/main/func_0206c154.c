/* func_0206c154 @ 0x0206c154, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9034(int, int, int);
extern void func_0205166c(void *, int);

void func_0206c154(void *base)
{
    unsigned int i;
    unsigned int offset;
    unsigned int zero;
    void *p;

    i = 0;
    offset = 0x11;
    zero = i;

    do {
        p = func_020a9034(offset, 0x14, 2);
        if (p) {
            *(void **) ((char *) base + i * 4 + 0x420) = p;
            *(int *) ((char *) p + 0x50) = 2;
            *(char *) ((char *) p + 0x39) = 0x0e;
            func_0205166c(p, zero);
        }
        i++;
        offset += 0x28;
    } while (i < 3);
}
