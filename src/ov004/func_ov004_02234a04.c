/* func_ov004_02234a04 @ 0x02234a04, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02234a04;
struct UnkStruct_02234a04_2 {
    struct UnkStruct_02234a04 *p;
};

struct UnkStruct_02234a04_3 {
    u8 pad_00[4];
};

extern u8 data_ov004_022593a0;
extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern u8 data_ov004_02255c34;
extern struct UnkStruct_02234a04_2 data_ov004_022594d4[];

extern int func_020b6590(void);
extern int func_020b7e04(int h, void *p);
extern void func_ov004_02234b9c(struct UnkStruct_02234a04_3 *self, struct UnkStruct_02234a04_2 *x, int i);
extern void func_ov004_0223494c(struct UnkStruct_02234a04_3 *self, int k);

int func_ov004_02234a04(struct UnkStruct_02234a04_3 *self)
{
    u8 m;
    int i;
    struct UnkStruct_02234a04_2 *p;

    m = data_ov004_022593a0;
    if (m == 0) {
        func_020b7e04(func_020b6590(), (u8 *) self + 0x2a8);
        func_020b7e04(func_020b6590(), (u8 *) self + 0x550);
    } else if (m == 1) {
        func_020b7e04(func_020b6590(), (u8 *) self + 0x2a8);
    }
    i = data_ov004_02255c30 - 1;
    p = &data_ov004_022594d4[i];
    while (i >= data_ov004_022593a4) {
        if (p->p != 0) {
            func_ov004_02234b9c(self, p, i);
        }
        p--;
        i--;
    }
    func_ov004_0223494c(self, data_ov004_02255c34);
    return 1;
}
