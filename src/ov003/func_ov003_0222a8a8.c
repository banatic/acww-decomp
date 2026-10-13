/* func_ov003_0222a8a8 @ 0x0222a8a8, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xa0 - 0x44];
    u8 unk_A0;
    char pad_A1[3];
} UnkStruct_0222a8a8;

extern UnkStruct_0222a8a8 data_ov003_0225f4dc[];
extern void *data_020ccf94;
extern void func_02073820(void *h);
extern void func_020737f0(void *h, char *b, int n);
extern void func_02073770(void *h, int a, int b);

int func_ov003_0222a8a8(int idx)
{
    int r = 0;
    UnkStruct_0222a8a8 *e;
    if (idx < 0 || idx >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[idx];
    if (e->unk_40 != 3 && e->unk_40 != 2) {
        return r;
    }
    if (e->unk_A0 == 0) {
        char b = 1;
        void *h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &b, 1);
        func_02073770(h, 0x2a, 4);
        e->unk_A0 = 1;
        r = 1;
    }
    return r;
}
