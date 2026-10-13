/* func_02094bcc @ 0x02094bcc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern UnkStruct_02094bcc data_021d52d8[];
extern void func_02094d6c(int a, UnkStruct_02094bcc *e, int b, int c);
extern void func_020914dc(UnkStruct_02094bcc *e);

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
