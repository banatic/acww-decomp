/* func_ov066_0226b738 @ 0x0226b738, 0x74 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226b738_2 {
    u8 kind : 2;  // 0x00 bits 0..1
    u8 armed : 1; // bit 2
    u8 rest : 5;
} UnkStruct_0226b738_2;

typedef struct UnkStruct_0226b738 {
    unsigned char pad_00[0x14];
    UnkStruct_0226b738_2 *item; // 0x14
} UnkStruct_0226b738;

typedef struct Ctl {
    unsigned char pad_00[2];
    signed char count; // 0x02
} Ctl;

extern Ctl *data_ov066_0226be08;
void func_ov066_0226b7ac(void);

void func_ov066_0226b738(UnkStruct_0226b738 *q)
{
    UnkStruct_0226b738_2 *it = q->item;
    data_ov066_0226be08->count--;
    switch (it->kind) {
        case 0:
        case 1:
            if (it->armed) {
                it->armed = 0;
                func_ov066_0226b7ac();
            }
            break;
    }
}
