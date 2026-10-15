/* func_020bd124 @ 0x020bd124, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x64];
    u32 unk_64;
} UnkStruct_020bd124_2;

extern UnkStruct_020bd124_2 *data_020ccf94;

typedef struct {
    u8 pad_00[0x1464];
    u32 unk_1464;
    u8 pad_1468[0x2f19 - 0x1468];
    u8 unk_2F19;
    u8 pad_2F1A;
    u8 unk_2F1B;
    u8 pad_2F1C[0x2f27 - 0x2f1c];
    u8 unk_2F27;
} UnkStruct_020bd124;

extern u32 func_02082644(u32);
extern u32 func_0201bea4(u32);
extern u32 func_02073dd4(void *, u32);
extern u32 func_020ba4e4(void);
extern int func_0208602c(void);
extern int func_020860c0(int);
extern u32 func_02087e0c(void *);
extern void *func_020bdc50(UnkStruct_020bd124 *, u32, u32, u32, u32);

void func_020bd124(UnkStruct_020bd124 *p)
{
    u32 r;
    u32 v;
    u8 b1, b2;

    if (p->unk_2F27) {
        r = func_02082644(8);
        if (r) {
            if (func_0201bea4(r)) {
                p->unk_2F27 = 0;
            }
        }
    }

    if (p->unk_2F27 == 0) {
        return;
    }

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    v = func_020ba4e4();
    if (v == 1) {
        return;
    }
    if (v == 2) {
        return;
    }

    b1 = p->unk_2F19;
    b2 = p->unk_2F1B;
    if (b1 == b2) {
        return;
    }
    if (b1 != 9 && b1 != 0x11) {
        return;
    }

    if (func_02087e0c((void *) func_020860c0((int) func_0208602c())) != 0) {
        return;
    }

    if (p->unk_1464 == 7) {
        return;
    }

    func_020bdc50(p, 7, 0x2d, 0, 0);
}
