/* town_beach_2: 2 functions, module main
 * mwccarm 1.2/base -O1,s
 * func_02047050 @ 0x02047050, 0x70 bytes, Thumb
 * func_02046fa4 @ 0x02046fa4, 0xac bytes, Thumb
 */

#include "types.h"

union Date {
    u16 h;
    u8 b;
    int pad_00;
};

typedef struct {
    int x;
    int y;
    int z;
} Vec;

struct UnkStruct_02047050 {
    char pad_00[0x5c];
    Vec v;
};

typedef union {
    u16 h;
    u8 b;
} Date;

typedef struct {
    Date unk_00;
    Date d1;
} Buf;

extern void func_0209def4(union Date *d);
extern struct UnkStruct_02047050 *func_020961a8(int n);
extern int func_0204e414(void);
extern void func_020470c0(void *a, int b, int c);
extern int func_020644cc(int);
extern u16 data_021c779c;
extern int func_02073918(void *a, int b);
extern int func_02096614(Buf *a, u32 *b, int *c, int d, int e);
extern int func_020b6674(int a);
extern int func_020b6654(int a);
extern void *data_020ccf94;

void func_02047050(void *a)
{
    union Date d;
    struct UnkStruct_02047050 *obj;
    Vec *q;
    u16 *gp;
    int v0;
    int v1;
    int x;
    int r;

    func_0209def4(&d);
    if (d.h == data_021c779c) {
        return;
    }
    if (d.b % 10 != 3) {
        return;
    }
    obj = func_020961a8(4);
    if (obj != 0) {
        x = func_0204e414();
        q = &obj->v;
        r = func_020644cc(4);
        v0 = obj->v.x >> 17;
        v1 = q->z >> 17;
        if (v1 != 4 || v0 != r + 1) {
            func_020470c0(a, x, r);
        }
    }
    gp = &data_021c779c;
    *gp = d.h;
}

void func_02046fa4(void *a)
{
    Buf buf;
    u32 v[2];
    int y;
    int found;
    int i;
    int x;
    int r;
    u16 *gp;

    if (func_02073918(data_020ccf94, 0) == 0) {
        return;
    }
    func_0209def4((union Date *) (&buf.d1));
    if (buf.d1.h == data_021c779c) {
        return;
    }
    if (buf.d1.b % 10 != 3) {
        return;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (func_02096614(&buf, v, &y, -1, i) != 0) {
            if (func_020b6674(buf.unk_00.b) != 0 || func_020b6654(buf.unk_00.b) != 0) {
                if ((y >> 17) == 4) {
                    found = 1;
                    break;
                }
            }
        }
    }
    if (found == 0) {
        x = func_0204e414();
        r = func_020644cc(4);
        func_020470c0(a, x, r);
    }
    gp = &data_021c779c;
    *gp = buf.d1.h;
}
