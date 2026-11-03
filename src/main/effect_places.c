/* effect_places: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02094bcc @ 0x02094bcc, 0x6c bytes, Thumb
 * func_02094bc0 @ 0x02094bc0, 0xc bytes, Thumb
 * func_02094bb4 @ 0x02094bb4, 0xc bytes, Thumb
 * func_02094b58 @ 0x02094b58, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 b[4];
} Key;

typedef struct {
    u8 pad_00[0xe];
    short unk_0E;
    u8 pad_10[4];
    int unk_14;
    u8 pad_18[4];
} UnkStruct_02094bcc;

struct UnkStruct_02094b58 {
    unsigned char pad_00[0x1c];
    unsigned short unk_1C;
};

extern UnkStruct_02094bcc data_021d52d8[];
extern void func_02094d6c(int a, UnkStruct_02094bcc *e, int b, int c);
extern void func_020914dc(UnkStruct_02094bcc *e);
extern void func_02094c38(int a, int b, int c);
extern void func_02091494(int, unsigned short, int, int, int, int, int);
extern int func_02090ac4(int, int, int, int);
extern struct UnkStruct_02094b58 data_021d5658;
extern char data_020e2ac4;

int func_02094bcc(void *self, int a, int b)
{
    Key k;
    int ok;
    UnkStruct_02094bcc *e;

    k = *(Key *) ((char *) self + 4);
    e = &data_021d52d8[k.b[0]];
    ok = 0;
    if (e->unk_14 != -1 && e->unk_0E != 0) {
        func_02094d6c(*(int *) ((char *) self + 0xc), e, a, b);
        if (e->unk_0E > 0) {
            e->unk_0E = e->unk_0E - 1;
        }
        ok = 1;
    }
    if (ok == 0) {
        func_020914dc(e);
    }
    return ok;
}

void func_02094bc0(int a)
{
    int x = 0;
    func_02094c38(a, x, x);
}

void func_02094bb4(int a)
{
    int zero = 0;
    func_02094bcc((void *) a, zero, zero);
}

int func_02094b58(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int ptr = a5;
    int result;

    if (ptr == 0) {
        ptr = (int) &data_020e2ac4;
    }

    result = 3;
    func_02091494((int) &data_021d5658, data_021d5658.unk_1C, a1, a2, a3, a4, -1);

    if (func_02090ac4(a0, a2, a3, ptr) != 0) {
        result = 0;
    }

    func_020914dc((UnkStruct_02094bcc *) ((int) &data_021d5658));
    return result;
}
