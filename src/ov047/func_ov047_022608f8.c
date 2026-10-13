/* func_ov047_022608f8 @ 0x022608f8, 0x190 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_020160b4(void *);
extern int func_020ab504(int);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov047_02262fc0;

typedef struct {
    int a;
    int b;
} MP;
typedef struct {
    int key;
    MP fn;
} Entry;

extern int data_ov047_02263000;
extern Entry data_ov047_02262d50[];
extern MP data_ov047_022629d0, data_ov047_022629c8, data_ov047_022629b0;
extern MP data_ov047_022629b8, data_ov047_02262a28, data_ov047_02262ac8;
extern MP data_ov047_02262a20, data_ov047_02262998, data_ov047_02262a00;
extern MP data_ov047_02262968, data_ov047_02262a88, data_ov047_02262980;
extern MP data_ov047_022629c0, data_ov047_02262a38, data_ov047_022629a0;
extern MP data_ov047_02262990, data_ov047_02262a98;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x8c];
    int unk_D0;
} UnkStruct_022608f8;

typedef void (*FN)(void *, int);

void func_ov047_022608f8(UnkStruct_022608f8 *p)
{
    u8 m;
    int r;
    unsigned int i;
    int f;
    u8 *st;

    r = func_020ab504(func_020160b4(p));
    p->unk_D0 = 0xff;
    f = data_ov047_02263000;
    if ((f & 1) == 0) {
        data_ov047_02262d50[0].fn = data_ov047_022629d0;
        data_ov047_02262d50[1].fn = data_ov047_022629c8;
        data_ov047_02262d50[2].fn = data_ov047_022629b0;
        data_ov047_02262d50[3].fn = data_ov047_022629b8;
        data_ov047_02262d50[4].fn = data_ov047_02262a28;
        data_ov047_02262d50[5].fn = data_ov047_02262ac8;
        data_ov047_02262d50[6].fn = data_ov047_02262a20;
        data_ov047_02262d50[7].fn = data_ov047_02262998;
        data_ov047_02262d50[8].fn = data_ov047_02262a00;
        data_ov047_02262d50[9].fn = data_ov047_02262968;
        data_ov047_02262d50[10].fn = data_ov047_02262a88;
        data_ov047_02262d50[11].fn = data_ov047_02262980;
        data_ov047_02262d50[12].fn = data_ov047_022629c0;
        data_ov047_02262d50[13].fn = data_ov047_02262a38;
        data_ov047_02262d50[14].fn = data_ov047_022629a0;
        data_ov047_02262d50[15].fn = data_ov047_02262990;
        data_ov047_02262d50[16].fn = data_ov047_02262a98;
        data_ov047_02263000 = f | 1;
    }

    i = 0;
    st = &p->unk_1E;
    for (; i < 0x11; i++) {
        int k = data_ov047_02262d50[i].key;
        if (k == *st) {
            MP *mp = &data_ov047_02262d50[i].fn;
            int d = mp->b;
            char *self = (char *) p + (d >> 1);
            FN g;
            if (d & 1) {
                g = *(FN *) (*(int *) self + mp->a);
            } else {
                g = (FN) mp->a;
            }
            g(self, r);
        }
    }

    if (p->unk_D0 != 0xff) {
        m = (u8) p->unk_D0;
        func_0206844c(p->unk_40, &m, &data_ov047_02262fc0);
    }
}
