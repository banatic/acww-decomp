/* func_ov143_0229ae84 @ 0x0229ae84, 0x74 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 *func_ov002_02207f80(u32 size);
extern void func_ov002_0220830c(void);
extern void func_ov002_02209ccc(void *obj);
extern void func_ov002_0220b008(void *obj);
extern void func_020b9cfc(void *obj);
extern void __cxa_vec_ctor(void *obj, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov143_0229b1c0;

void *func_ov143_0229ae84(void)
{
    u8 *mem;
    u8 *p;
    u8 *end;

    mem = func_ov002_02207f80(0x11c0);
    if (mem != 0) {
        func_ov002_0220830c();
        *(void **) mem = (void *) &data_ov143_0229b1c0;
        func_ov002_02209ccc(mem + 0xac);
        func_ov002_0220b008(mem + 0x110);
        __cxa_vec_ctor(mem + 0x2dc, 0x10, 0x6c, func_02070c08, func_02070be8);
        p = mem + 0x119c;
        end = mem + 0x11c0;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return mem;
}
