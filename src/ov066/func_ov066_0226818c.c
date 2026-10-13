/* func_ov066_0226818c @ 0x0226818c, 0xdc bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226818c {
    u16 unk_00;
    unsigned char pad_02[6];
    volatile u16 kind;
} UnkStruct_0226818c;
typedef struct Ctl {
    unsigned char pad_00[0xc];
    u8 count;
} Ctl;
typedef struct Cfg {
    unsigned char pad_00[0x95];
    u8 unk_95;
} Cfg;
extern Ctl *data_ov066_0226bdec;
extern Cfg *data_ov066_0226bdf4;
UnkStruct_0226818c *func_ov066_02267784(int a, int idx);
int func_ov066_022683b4(const void *a, const void *b);
void func_ov066_022696b4(UnkStruct_0226818c *e, int flag);

int func_ov066_0226818c(void)
{
    u8 i;
    UnkStruct_0226818c *best;
    best = 0;
    for (i = 0; i < data_ov066_0226bdec->count; i = (u8) (i + 1)) {
        UnkStruct_0226818c *e = func_ov066_02267784(data_ov066_0226bdf4->unk_95, i);
        if (e->unk_00 != 0) {
            if (e->kind == 0xbd8a) {
                best = e;
                break;
            }
            if (e->kind == 0x2348) {
                if (best != 0) {
                    if (func_ov066_022683b4((u8 *) e + 2, (u8 *) best + 2) != 0) {
                        best = e;
                    }
                } else {
                    best = e;
                }
            }
        }
    }
    if (best == 0) {
        return 0;
    }
    func_ov066_022696b4(best, 1);
    return 1;
}
