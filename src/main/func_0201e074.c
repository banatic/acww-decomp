/* func_0201e074 @ 0x0201e074, 0x164 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};
typedef struct Rec {
    u16 id;
    u8 name[12];
    u8 pad;
    u8 unk_0F;
} Rec;

typedef struct UnkStruct_0201e074_2 {
    u8 pad[0x830];
    int unk_830;
} UnkStruct_0201e074_2;

typedef struct UnkStruct_0201e074_3 {
    u8 pad_00[0xf8];
    struct Pair pair;
    UnkStruct_0201e074_2 *unk_100;
    u8 unk_104;
    u8 pad_105[0x122 - 0x105];
    u8 unk_122;
    u8 pad_123[0x194 - 0x123];
    u8 unk_194;
    u8 pad_195[3];
    int unk_198;
} UnkStruct_0201e074_3;

typedef struct UnkStruct_0201e074_4 {
    u8 *p;
    u8 unk_04;
} UnkStruct_0201e074_4;

typedef struct UnkStruct_0201e074 {
    int unk_00;
    u8 unk_04;
} UnkStruct_0201e074;

extern UnkStruct_0201e074 data_020c8d18;
extern int data_021e5a2c;
extern struct Pair data_020d9228;

extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern int func_0202da38(UnkStruct_0201e074_3 *s, u8 *a, u8 *b, int c, int d, int e, int f, int g, int h);
extern int func_020984e8(void);
extern int func_02099870(int a);
extern int func_020951bc(int a);
extern int func_02003704(int a);
extern int func_0207cec0(void *p, int i);
extern int memcmp(const void *a, const void *b, int n);
extern int func_020807a8(int a, int b);
extern int func_02081d20(void *object);

void func_0201e074(UnkStruct_0201e074_3 *self, UnkStruct_0201e074_4 *out)
{
    int forwarded_value;

    int x;
    int g0;
    int one;
    int one2;
    int g4;
    int t;
    Rec *u;
    int h;
    Rec *r;
    int i;
    int w0;
    int w1;

    x = func_020036e8(func_0208150c(self->unk_100->unk_830));
    g0 = data_020c8d18.unk_00;
    one = 1;
    one2 = 1;
    g4 = data_020c8d18.unk_04;
    func_0202da38(self, &self->unk_104, &self->unk_122, 0x1e, x, g0, one, one2, g4);
    out->p = &self->unk_104;
    out->unk_04 = self->unk_122;
    if (func_020984e8() != 0) {
        h = func_02099870(func_020984e8());
    } else {
        h = 0;
    }
    if (self->unk_100->unk_830 != 0) {
        r = (Rec *) func_0208150c(self->unk_100->unk_830);
    } else {
        r = 0;
    }
    self->unk_194 = 0;
    self->unk_198 = 0;
    if ((int) &data_021e5a2c == 0) {
        goto done;
    }
    if (h == 0) {
        goto done;
    }
    if (func_020951bc(h) == 0) {
        goto done;
    }
    if (r == 0) {
        goto done;
    }
    if (func_02003704((int) r) == 0) {
        goto done;
    }
    i = 0;
loop:
    t = func_0207cec0(&data_021e5a2c, i);
    if (t == 0) {
        goto cont;
    }
    if (func_02003704(func_0208150c(t)) == 0) {
        goto cont;
    }
    u = (Rec *) func_0208150c(t);
    if (u->id == r->id) {
        if (memcmp(u->name, r->name, 0xc) == 0) {
            if (u->unk_0F == r->unk_0F) {
                goto cont;
            }
        }
    }
    if ((forwarded_value = (int) func_020807a8(t, h)) == 0) {
        goto cont;
    }
    if (func_02081d20((void *) forwarded_value) < 0x40) {
        goto cont;
    }
    self->unk_194 = (u8) (self->unk_194 | (1 << i));
    self->unk_198 = self->unk_198 + 1;
cont:
    i++;
    if (i < 8) {
        goto loop;
    }
done:
    if (self->unk_198 == 1) {
        self->unk_194 = 0;
        self->unk_198 = 0;
    }
    self->pair = data_020d9228;
}
