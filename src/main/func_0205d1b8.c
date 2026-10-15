/* func_0205d1b8 @ 0x0205d1b8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02055cf4(void *);
extern void func_02055ce8(void *);
extern void *func_020ba01c(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_0205d1b8(void *p)
{
    char *ptr;
    char *end;
    __cxa_vec_ctor((void *) ((char *) p + 0x10), 4, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);
    ptr = (char *) p + 0x60;
    end = (char *) p + 0xd0;
    do {
        func_020ba01c(ptr);
        ptr += 0x1c;
    } while (ptr != end);
    return p;
}
