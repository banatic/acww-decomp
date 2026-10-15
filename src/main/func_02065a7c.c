/* func_02065a7c @ 0x02065a7c, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    u16 unk_08;
    u16 unk_0A;
    int unk_0C;
    s16 unk_10;
    s16 unk_12;
} UnkStruct_02065a7c;

typedef struct {
    int unk_00;
    int unk_04;
    u16 unk_08;
    u16 unk_0A;
    int unk_0C;
    s16 unk_10;
    s16 unk_12;
    u8 unk_14;
    u8 pad_15[7];
    u8 sub[0x44 - 0x1c];
} UnkStruct_02065a7c_2;

typedef struct {
    u8 pad_00[0x50];
    int idx;
    int count;
    UnkStruct_02065a7c_2 e[4];
    u8 pad2[0x174 - 0x168];
    void *unk_174;
} UnkStruct_02065a7c_5;

typedef struct {
    int n;
    UnkStruct_02065a7c **list;
} UnkStruct_02065a7c_3;

typedef struct {
    u8 pad_00[4];
    s16 unk_04;
    s16 unk_06;
    u8 pad2[2];
} UnkStruct_02065a7c_4;

extern u8 data_020e54a8;
extern UnkStruct_02065a7c_3 *data_020de6f4[];
extern UnkStruct_02065a7c_4 data_020ccc7c[];

extern int func_020b65c4(void);
extern int func_020b67d4(void);
extern void func_02064db8(int a, int b, int c);
extern void func_02064da0(int a, int b);
extern void func_020b3720(void *p, int z);

void func_02065a7c(UnkStruct_02065a7c_5 *self)
{
    UnkStruct_02065a7c **list;
    int count;
    UnkStruct_02065a7c **q;
    int z;
    UnkStruct_02065a7c s;
    int i;
    int h;
    unsigned int cond;
    int ok;
    UnkStruct_02065a7c_3 *p;
    UnkStruct_02065a7c_4 *t2;

    UnkStruct_02065a7c_2 *e;
    ok = 0;
    h = func_020b65c4();
    cond = (data_020e54a8 == 1) ? 1 : 0;
    if (cond != 0 && func_020b67d4() == 0) {
        ok = 1;
    }
    if (ok != 0) {
        func_02064db8(0, 2, 0);
    } else {
        func_02064da0(0, 1);
    }
    func_02064da0(1, 1);

    p = data_020de6f4[self->idx];
    list = p->list;
    count = p->n;
    self->count = count;
    i = 0;
    t2 = &data_020ccc7c[h];
    z = 0;
    while (i < count) {
        q = &list[i];
        s = *list[i];
        self->e[i].unk_00 = s.unk_00;
        self->e[i].unk_04 = s.unk_04;
        self->e[i].unk_08 = s.unk_08;
        self->e[i].unk_0C = s.unk_0C;
        self->e[i].unk_10 = s.unk_10;
        self->e[i].unk_12 = s.unk_12;
        switch ((*q)->unk_00) {
            case 3:
            case 4:
            case 5:
                self->e[i].unk_10 = t2->unk_04;
                self->e[i].unk_12 = t2->unk_06;
                e = &self->e[i];
                e->unk_14 = (u8) z;
                func_020b3720(e->sub, z);
                self->unk_174 = e->sub;
                break;
        }
        i++;
    }
}
