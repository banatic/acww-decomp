/* func_020be400 @ 0x020be400, 0x150 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020bef78(void *p);
extern void *func_020bedf4(void *p);
extern void *func_020bebc8(void *p);
extern void *func_020be64c(void *p);
extern void func_020bf1b8(void *p);
extern void *func_020be554(void *);
extern void func_020be550(void *);
extern void *func_020bf9ac(void *);
extern void *func_020bec04(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_020be400(void *self)
{
    u8 *base = (u8 *) self;
    u8 *p, *end;

    __cxa_vec_ctor((void *) (self), 0x3c, 0x74, (((void (*)(void *)) func_020bf9ac)), (((void (*)(void *)) func_020be554)));

    p = base + 0x1b30;
    end = base + 0x1b6c;
    do {
        func_020bef78(p);
        p += 12;
    } while (p != end);

    func_020bedf4(base + 0x2eb8);

    __cxa_vec_ctor((void *) (base + 0x2f58), 4, 0x14, (((void (*)(void *)) func_020bec04)), (void (*)(void *)) func_020be550);

    func_020bebc8(base + 0x2fa8);
    func_020be64c(base + 0x2fcc);

    *(u32 *) (base + 0x2f00) = 0;
    *(u32 *) (base + 0x2f04) = 0;
    *(u32 *) (base + 0x2f08) = 0;
    *(u32 *) (base + 0x2f0c) = 0;
    *(u32 *) (base + 0x2f10) = 0;
    *(u32 *) (base + 0x2f14) = 0;

    *(u8 *) (base + 0x2f24) = 0;
    *(u8 *) (base + 0x2f25) = 0;
    *(u8 *) (base + 0x2f26) = 0;
    *(u8 *) (base + 0x2f27) = 0;
    *(u8 *) (base + 0x2f28) = 0;
    *(u8 *) (base + 0x2f29) = 0;

    *(u32 *) (base + 0x2f2c) = 0;
    *(u32 *) (base + 0x2f30) = 0;
    *(u32 *) (base + 0x2f34) = 0;
    *(u32 *) (base + 0x2f38) = 0;
    *(u32 *) (base + 0x2f3c) = 0;
    *(u32 *) (base + 0x2f40) = 0;
    *(u32 *) (base + 0x2f44) = 0;
    *(u32 *) (base + 0x2f48) = 0;
    *(u32 *) (base + 0x2f4c) = 0;

    *(u8 *) (base + 0x2f50) = 0;
    *(u8 *) (base + 0x2f51) = 0;

    *(u32 *) (base + 0x2f54) = 0;

    func_020bf1b8(base + 0x1b6c);

    return self;
}
