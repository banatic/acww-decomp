/* func_0205f570 @ 0x0205f570, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void *func_02054e18(void *);
extern void *func_02054e54(void *);
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void *func_020ba01c(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_0205f570(void *self)
{
    char *p, *q;

    __cxa_vec_ctor((void *) ((char *) self + 0xdc), 9, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);

    p = (char *) self + 0x190;
    q = (char *) self + 0x28c;

    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != q);

    __cxa_vec_ctor((void *) (q), 9, 0xf4, (((void (*)(void *)) func_02054e54)), (((void (*)(void *)) func_02054e18)));
    __cxa_vec_ctor((void *) ((char *) self + 0xb44), 9, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);

    return self;
}
