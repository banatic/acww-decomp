/* func_ov003_0220f7cc @ 0x0220f7cc, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0220f7cc {
    u32 unk_00;
    u32 w1;
    u8 pad_08[2];
    u8 count;
} UnkStruct_0220f7cc;

typedef struct SVec {
    u32 x;
    u32 y;
    u32 z;
} SVec;

extern void func_0204f818(u32 *a, u32 *b, SVec *c);
extern void func_ov003_022235d8(void *p, u32 *v);
extern void func_ov003_02224384(void *p, u32 *v, int n);
extern void func_02010f5c(void *self);
extern int func_02073908(u32 g, void *p);
extern void func_ov003_0220f968(void *self);
extern void func_02010d64(void *self);
extern void func_ov003_0220f8e0(void *self);
extern int func_0200f554(void *self);
extern void func_ov003_0220f884(void *self);
extern u32 data_020ccf94;

void func_ov003_0220f7cc(char *self)
{
    u32 out[2];
    u32 v[2];
    u32 v2[2];
    SVec st;
    UnkStruct_0220f7cc *sb;
    u32 a, b;

    sb = (UnkStruct_0220f7cc *) (self + 0x7d4);
    a = sb->w1;
    b = sb->unk_00;
    st.x = b;
    st.y = 0;
    st.z = a;
    out[0] = 0;
    out[1] = 0;
    func_0204f818(out, &out[1], &st);

    if (sb->count > 5u) {
        v[0] = out[0];
        v[1] = out[1];
        func_ov003_022235d8(*(void **) (self + 0x800), v);
    } else {
        sb->count = (u8) (sb->count + 1);
        if (sb->count == 5u) {
            v2[0] = out[0];
            v2[1] = out[1];
            func_ov003_02224384(*(void **) (self + 0x800), v2, 2);
        }
    }

    func_02010f5c(self);

    if (func_02073908(data_020ccf94, *(void **) (self + 0x800)) != 0) {
        func_ov003_0220f968(self);
        func_02010d64(self);
        func_ov003_0220f8e0(self);
    } else {
        if (func_0200f554(self) != 0) {
            func_ov003_0220f968(self);
        }
        func_02010d64(self);
        func_ov003_0220f884(self);
    }
}
