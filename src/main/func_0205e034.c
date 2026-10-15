/* func_0205e034 @ 0x0205e034, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ba01c(void *p);
extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);

void *func_0205e034(void *self)
{
    char *p;
    char *end;
    int i;
    int zero;

    __cxa_vec_ctor((void *) ((char *) self + 0x10), 4, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);

    p = (char *) self + 0x60;
    end = (char *) self + 0xd0;
    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != end);

    i = 0;
    zero = i;
    for (; i < 4; i++) {
        ((int *) self)[i] = zero;
        ((char *) self + i)[0xd0] = 0x4b;
    }

    return self;
}
