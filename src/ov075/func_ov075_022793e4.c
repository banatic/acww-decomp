/* func_ov075_022793e4 @ 0x022793e4, 0x54 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec3 {
    u32 x, y, z;
};

struct UnkStruct_022793e4 {
    u8 pad_00[0x5c];
    struct Vec3 src; // offset 0x5c
    struct Vec3 dst; // offset 0x68
    u8 pad_74[0x4ed];
    u8 flag; // offset 0x561
};

extern int func_0208602c(struct UnkStruct_022793e4 *);
extern int func_020860c0(int);
extern int func_02087e38(int);
extern void func_02087e4c(int, struct Vec3 *);
extern void func_ov075_022794b8(struct UnkStruct_022793e4 *, int);

int func_ov075_022793e4(struct UnkStruct_022793e4 *obj)
{
    int a, b, c;
    u32 *src;
    u32 *dst;

    a = func_0208602c(obj);
    b = func_020860c0(a);
    c = func_02087e38(b);
    if (c != 0) {
        func_02087e4c(b, &obj->src);
        src = (u32 *) &obj->src;
        dst = (u32 *) &obj->dst;
        obj->dst.x = obj->src.x;
        dst[1] = src[1];
        dst[2] = src[2];
        obj->flag = 1;
        func_ov075_022794b8(obj, 0);
    }
    return 1;
}
