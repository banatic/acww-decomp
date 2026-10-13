/* func_ov066_0226a8c4 @ 0x0226a8c4, 0x9c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226a8c4_2 {
    void *a;
    void *b;
    unsigned char pad_08[8];
} UnkStruct_0226a8c4_2;

typedef struct UnkStruct_0226a8c4 {
    unsigned char pad_00[0x1c];
    u16 mask; // 0x1c
    unsigned char pad_1E[0x30 - 0x1e];
    UnkStruct_0226a8c4_2 *tbl; // 0x30
} UnkStruct_0226a8c4;

typedef struct Lim {
    unsigned char pad_00[0xb];
    u8 count; // 0x0b
} Lim;

extern UnkStruct_0226a8c4 *data_ov066_0226be08;
extern void *data_ov066_0226bdf4;
extern Lim *data_ov066_0226bdec;

int OS_DisableInterrupts(void);
void OS_RestoreInterrupts(int state);

int func_ov066_0226a8c4(int idx, void *a, void *b)
{
    int ok = 0;
    int e = OS_DisableInterrupts();
    UnkStruct_0226a8c4 *q = data_ov066_0226be08;
    if (q != 0) {
        UnkStruct_0226a8c4_2 *tbl = q->tbl;
        if (tbl != 0 && data_ov066_0226bdf4 != 0 && idx < data_ov066_0226bdec->count && (q->mask & (1 << idx)) == 0) {
            tbl[idx].a = a;
            tbl[idx].b = b;
            ok = 1;
        }
    }
    OS_RestoreInterrupts(e);
    return ok;
}
