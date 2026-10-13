/* func_02092914 @ 0x02092914, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int v;
} UnkStruct_02092914;
typedef struct {
    UnkStruct_02092914 a;
    UnkStruct_02092914 b;
    UnkStruct_02092914 c;
} UnkStruct_02092914_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0xe - 0xc];
    short unk_0E;
    char pad1[0x14 - 0x10];
    int unk_14;
    char pad_18[0x1c - 0x18];
} Entry;

typedef struct {
    char pad0[0x18];
    int **unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    char pad1[0x68 - 0x2c];
    u8 unk_68;
} HObj;

typedef struct {
    char pad0[4];
    u8 id[4];
    char pad1[0xc - 8];
    HObj *h;
} UnkStruct_02092914_3;

extern Entry data_021d52d8[];
extern void func_020914dc(Entry *e);

int func_02092914(UnkStruct_02092914_3 *self)
{
    u8 id[4];
    int done;
    Entry *e;
    UnkStruct_02092914_2 q;
    short v;
    HObj *h;
    u16 t;

    {
        u8 *src = (u8 *) self + 4;
        u8 *dst = id;
        int n = 4;
        do {
            *dst++ = *src++;
            n--;
        } while (n != 0);
    }

    e = &data_021d52d8[id[0]];
    done = 0;

    if (e->unk_14 != -1 && e->unk_0E != 0) {
        q.a = *(UnkStruct_02092914 *) &e->unk_00;
        q.b = *(UnkStruct_02092914 *) &e->unk_04;
        q.c = *(UnkStruct_02092914 *) &e->unk_08;
        v = e->unk_0E;
        h = self->h;
        h->unk_20 = q.a.v + (*h->unk_18)[1];
        h->unk_24 = q.b.v + (*h->unk_18)[2];
        h->unk_28 = q.c.v + (*h->unk_18)[3];
        if (v > 0) {
            e->unk_0E = (short) (e->unk_0E - 1);
            self->h->unk_68 = 5;
        } else if (v < -1) {
            e->unk_0E = (short) (e->unk_0E + 1);
            if (e->unk_0E <= -41) {
                t = 1;
            } else {
                t = (u16) (((e->unk_0E + 40) * 410 >> 12) + 1);
            }
            self->h->unk_68 = (u8) t;
        } else {
            self->h->unk_68 = 5;
        }
        done = 1;
    }

    if (!done) {
        func_020914dc(e);
    }

    return done;
}
