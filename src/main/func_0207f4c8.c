/* func_0207f4c8 @ 0x0207f4c8, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0207f4c8 {
    u16 a;
    u16 b;
    u16 c;
} UnkStruct_0207f4c8;

extern int func_0207f150(void *a0);
extern int func_0207ff58(void *a0, u16 *p);
extern void func_0207ff0c(u16 *dst, void *a0, int t);
extern int func_0204bcdc(u16 *p);
extern int func_0207d608(void *a0, int t);
extern void func_0207f590(u16 *dst, void *a0, u16 *src);
extern void func_0204bc28(u16 *p, int k);

void func_0207f4c8(void *a0, u16 *p)
{
    UnkStruct_0207f4c8 h;
    int i;
    int mode;
    int t;
    unsigned int in;

    h.a = 0xfff1;
    mode = (func_0207f150(a0) == 3) ? 0 : 1;
    for (i = 0; i < 0x100; i++) {
        in = 0;
        if (*p >= 0xf000 && *p <= 0xf02f) {
            in = 1;
        }
        if (in != 0) {
            t = func_0207ff58(a0, p);
            func_0207ff0c(&h.b, a0, t);
            h.a = h.b;
            if (mode != 0 && func_0204bcdc(&h.a) != 0) {
                if (func_0207d608(a0, t) != 0) {
                    func_0207f590(&h.c, a0, &h.a);
                    h.a = h.c;
                } else {
                    h.a = 0xfff1;
                }
            }
            if (func_0204bcdc(&h.a) != 0) {
                func_0204bc28(&h.a, *p & 3);
                *p = h.a;
            } else {
                *p = 0xfff1;
            }
        }
        p++;
    }
}
