/* func_020be6e4 @ 0x020be6e4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern fx32 FX_Div(fx32 a, fx32 b);
extern void *func_02095794(int);
extern void func_020c14bc(int *a, void *b);
extern void func_02095518(int a, int b, int c);

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14;
    unsigned char unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned char unk_1E, unk_1F, unk_20, unk_21;
} UnkStruct_020be6e4;

void func_020be6e4(UnkStruct_020be6e4 *self)
{
    void *ptr = func_02095794(4);
    int local = 0x00080000;
    int v;
    short sv;

    if (ptr != 0) {
        func_020c14bc(&local, ptr);
    }
    v = self->unk_0C - local;
    v = FX_Div(v, 0x00100000);
    v = (v * -10000) >> 12;
    if (v < -5000) {
        v = -5000;
    } else if (v > 5000) {
        v = 5000;
    }
    sv = (short) v;
    func_02095518(4000, sv, 4);
    self->unk_1A = 4000;
    self->unk_1C = sv;
}
