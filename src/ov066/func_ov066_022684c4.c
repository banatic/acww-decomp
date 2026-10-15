/* func_ov066_022684c4 @ 0x022684c4, 0x78 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_022684c4 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_022684c4;

typedef struct UnkStruct_022684c4_2 {
    unsigned char pad_00[0x1e];
    u16 unk_1E;
    unsigned char pad_20[0xa0];
    unsigned long b0 : 3;
    signed long b3 : 1;
    unsigned long b4 : 28;
} UnkStruct_022684c4_2;

extern UnkStruct_022684c4_2 *data_ov066_0226bdf4;

extern int func_ov066_02266e08(void);
extern void func_ov066_0226686c(int code);
extern void func_ov066_02268ad0(void);
extern int func_ov066_022688cc(int a);

void func_ov066_022684c4(UnkStruct_022684c4 *p)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (p->unk_02 == 0) {
        UnkStruct_022684c4_2 *q = data_ov066_0226bdf4;
        if (!q->b3) {
            return;
        }
        if (q->unk_1E == 0) {
            func_ov066_02268ad0();
            return;
        }
        func_ov066_022688cc(0);
        return;
    }
    func_ov066_0226686c(p->unk_02);
}
