/* func_ov003_0220e128 @ 0x0220e128, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200fbe0(void *self);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern void func_0205eae0(void *self, int, int, int);
extern int func_02034270(void *out, const u32 *data, int, int);
extern int func_02091254(int msg, const u32 *data, int, int);
extern unsigned int *func_0200f27c(void *self, int);
extern int func_ov003_02220b44(u32 val, const u32 *data);
extern int func_0200f328(void *self, u32 val);
extern void func_0203423c(void *out);

void func_ov003_0220e128(void *self, void *message, int previous)
{
    u32 data[3];
    struct UnkStruct_0220e128 {
        u8 pad[0x34];
        u32 type;
        u8 pad2[0x8];
    } out;
    u32 data2[3];
    u32 *src1;
    u32 *src2;
    int v;
    u32 tmp;

    v = func_0200fbe0(self);
    if (v == 10 || (unsigned) (v - 3) <= 1) {
        func_020109a0(self, 0x94, 3, 0);
        if (func_0200fbe0(self) == 4) {
            func_0205eae0((char *) self + 0x5a0, 0x12, 3, 1);
        }
    } else {
        func_020109a0(self, 0x93, 3, 0);
    }

    src1 = (u32 *) ((char *) self + 0x5c);
    data[0] = src1[0];
    data[1] = src1[1];
    data[2] = src1[2];

    func_02034270(&out, data, 0, 0);
    if (out.type == 0x13) {
        func_02091254(0x91, data, 0, 0);
    } else {
        func_02091254(0x90, data, 0, 0);
    }

    func_0200f27c(self, 9);

    src2 = (u32 *) ((char *) self + 0x5c);
    data2[0] = src2[0];
    data2[1] = src2[1];
    data2[2] = src2[2];

    tmp = *(u32 *) ((char *) self + 0x800);
    func_ov003_02220b44(tmp, data2);

    func_0200f328(self, 0x7e9);
    func_0203423c(&out);
}
