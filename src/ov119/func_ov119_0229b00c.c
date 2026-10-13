/* func_ov119_0229b00c @ 0x0229b00c, 0xec bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov119_0229a434(void *self);
extern int func_ov119_0229a420(void *self, int mode);
extern void func_ov119_0229a400(void *self, int mode);
extern void func_ov119_0229a410(void *self, int mode);
extern void func_0206fdd4(void *dst, int a, int b, int c, int d, int e);
extern int func_020b9bbc(void *dst, u32 v, int a, int b, int c);
extern void func_020b9b6c(void *dst, void *src, int a, int c);

void func_ov119_0229b00c(unsigned char *self)
{
    func_ov119_0229a434(self);

    if (func_ov119_0229a420(self, 4)) {
        if (self[0x9c] <= 3) {
            s16 s;

            func_0206fdd4(self + 0xe0c, 5, 6, 0x17, 0x15, 3);
            s = *(s16 *) (self + 0x9a);
            if (s != -1) {
                int w;

                w = s * 2 + 6;
                func_0206fdd4(self + 0xe0c, 5, w, 0x17, w + 1, 4);
            }
        }
        func_ov119_0229a400(self, 4);
        func_ov119_0229a410(self, 2);
    }

    if (func_ov119_0229a420(self, 2)) {
        if (func_020b9bbc(self + 0x1e90, *(u32 *) (self + 0x1e0c), 4, 0x800, 0)) {
            func_ov119_0229a400(self, 2);
        }
    }

    if (func_ov119_0229a420(self, 0x20)) {
        func_020b9b6c(self + 0x1eb4, self + 0x1e70, 6, 3);
        func_020b9b6c(self + 0x1ed8, self + 0x1e50, 8, 0xa);
    }
}
