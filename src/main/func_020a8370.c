/* func_020a8370 @ 0x020a8370, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a8370;
typedef struct {
    char pad_00[8];
    int unk_08;
    int unk_0C;
} UnkStruct_020a8370_2;
typedef struct {
    int hdr;
    u8 b[8];
} Buf;

extern void func_020a8630(UnkStruct_020a8370_2 *self, u8 *dst, int n);
extern void func_020a8a34(UnkStruct_020a8370 *o, int pos);

int func_020a8370(UnkStruct_020a8370_2 *self, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f, u8 *g, u8 *h, UnkStruct_020a8370 *o0,
                  UnkStruct_020a8370 *o1)
{
    struct {
        Buf t;
        UnkStruct_020a8370 *arr[2];
    } L;
    int pos;
    int total;
    unsigned int i;
    int n;

    func_020a8630(self, L.t.b, 8);
    *a = L.t.b[0];
    *c = L.t.b[2];
    *e = L.t.b[4];
    *g = L.t.b[6];
    *b = L.t.b[1];
    *d = L.t.b[3];
    *f = L.t.b[5];
    *h = L.t.b[7];
    L.arr[0] = o0;
    L.arr[1] = o1;
    pos = self->unk_0C + self->unk_08 + 2;
    total = 2;
    for (i = 0; i < 2; i++) {
        UnkStruct_020a8370 *o = *(UnkStruct_020a8370 **) ((char *) L.arr + i * 4);
        func_020a8a34(o, pos);
        n = o->unk_04 + 2;
        total = total + n;
        pos = pos + n;
    }
    return total;
}
