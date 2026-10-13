/* func_0205f570 @ 0x0205f570, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055ce8(void);
extern void func_02055cf4(void);
extern void func_02054e18(void);
extern void func_02054e54(void);
extern void func_020051b0(void);
extern void func_02034ce0(void);
extern void func_020ba01c(void *p);
extern void func_02138d6c(void *addr, int a, int b, void (*f1)(void), void (*f2)(void));

void *func_0205f570(void *self)
{
    char *p, *q;

    func_02138d6c((char *) self + 0xdc, 9, 0x14, func_02055cf4, func_02055ce8);

    p = (char *) self + 0x190;
    q = (char *) self + 0x28c;

    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != q);

    func_02138d6c(q, 9, 0xf4, func_02054e54, func_02054e18);
    func_02138d6c((char *) self + 0xb44, 9, 2, func_02034ce0, func_020051b0);

    return self;
}
