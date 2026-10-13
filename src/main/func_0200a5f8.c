/* func_0200a5f8 @ 0x0200a5f8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
} Src;

extern void func_0200a694(void *out, const Src *src, u8 val);
extern void func_0200f328(void *self, int a);
extern void func_020109a0(void *self, int a, int b, int c);
extern int func_0200fbe0(void *self);
extern void func_0205eae0(void *ptr, int a, int b, int c);

void func_0200a5f8(void *selfv, u8 *param2)
{
    u8 *self = (u8 *) selfv;
    u8 *p;
    u8 b0d, b0e, b0c;
    u8 *field7d4;
    Src local;

    p = &param2[0xc];
    b0d = p[1];
    b0e = p[2];
    b0c = param2[0xc];

    field7d4 = self + 0x7d4;
    field7d4[1] = 0;
    field7d4[2] = b0d;
    field7d4[3] = b0e;
    field7d4[0] = b0c;

    local.a = b0d;
    local.b = b0e;
    func_0200a694(self + 0x8f0, &local, b0c);

    *(u32 *) (self + 0x830) = 0x1000;
    *(u32 *) (self + 0x834) = 0x1000;
    *(u32 *) (self + 0x838) = 0x1000;

    func_0200f328(self, 0x4f);
    func_020109a0(self, 0x18, 3, 0);

    if (func_0200fbe0(self) == 4) {
        func_0205eae0(self + 0x5a0, 6, 3, 1);
    }
}
