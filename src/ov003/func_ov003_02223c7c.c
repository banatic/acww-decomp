/* func_ov003_02223c7c @ 0x02223c7c, 0x98 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02223c7c_4 {
    u8 pad_00[0x40];
    u32 unk_40;
};

struct UnkStruct_02223c7c {
    u32 unk_00;
    u32 w1;
};

struct UnkStruct_02223c7c_2 {
    u32 unk_00;
    u32 w1;
    u32 w2;
    u32 w3;
};

struct UnkStruct_02223c7c_3 {
    u32 x;
    u32 y;
    u32 z;
};

extern struct UnkStruct_02223c7c_2 data_ov003_0223a1b8;

extern void *func_ov003_02223e88(struct UnkStruct_02223c7c_4 *);
extern void func_ov003_02223dc8(struct UnkStruct_02223c7c_4 *, void *, u32 *, u32 *, struct UnkStruct_02223c7c_3 *, int,
                                struct UnkStruct_02223c7c *);
extern void func_ov003_022240fc(void *, u32, int, int, int, struct UnkStruct_02223c7c_3 *, int);
extern int func_ov003_022240cc(void *);
extern int func_02090ac4(u32, struct UnkStruct_02223c7c_3 *, int, struct UnkStruct_02223c7c_2 *);

void *func_ov003_02223c7c(struct UnkStruct_02223c7c_4 *self, int p1, int p2, int p3, struct UnkStruct_02223c7c *p4, int p5)
{
    u32 outA;
    u32 outB;
    struct UnkStruct_02223c7c s8;
    struct UnkStruct_02223c7c_2 local16 = data_ov003_0223a1b8;
    struct UnkStruct_02223c7c_3 a3;
    struct UnkStruct_02223c7c_3 b3;
    void *result;

    result = func_ov003_02223e88(self);

    if (result != 0) {
        s8.unk_00 = p4->unk_00;
        s8.w1 = p4->w1;

        func_ov003_02223dc8(self, result, &outA, &outB, &a3, p3, &s8);

        b3.x = a3.x;
        b3.y = a3.y;
        b3.z = a3.z;

        func_ov003_022240fc(result, outA, 1, p1, p2, &b3, p5);

        if (func_ov003_022240cc(result) != 0) {
            func_02090ac4(outB, &a3, 0, &local16);
        } else {
            *(u32 *) result = 3;
        }

        self->unk_40 = -1;
    }

    return result;
}
