/* func_020c1608 @ 0x020c1608, 0x164 bytes, Thumb, module main
 * mwccarm 1.2/base -O3,s
 */

#include "types.h"

typedef union UnkStruct_020c1608 {
    u32 w[2];
    u8 b[8];
} UnkStruct_020c1608;

typedef struct UnkStruct_020c1608_2 {
    u8 unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} UnkStruct_020c1608_2;

typedef struct UnkStruct_020c1608_3 {
    u16 id;
    u8 rest[0xa];
} UnkStruct_020c1608_3;

extern int func_02073d90(void *p);
extern void MI_CpuCopy8(const void *src, void *dst, int n);
extern void func_0209e100(UnkStruct_020c1608 *d, int k);
extern u32 func_0209e350(UnkStruct_020c1608 *a, UnkStruct_020c1608 *b);
extern void func_0209e29c(UnkStruct_020c1608 *d, int k);
extern u8 func_020c15c8(UnkStruct_020c1608_2 *a, UnkStruct_020c1608 *d);
extern int func_020b65c4(void);
extern int func_020a12e8(void);
extern int func_020984e8(void);
extern int func_02099020(int h, int k);
extern UnkStruct_020c1608_3 *func_0203fc70(void);
extern void *data_020ccf94;
extern u8 data_021fbbd8;

int func_020c1608(UnkStruct_020c1608_2 *a, void *src)
{
    // DECLS
    UnkStruct_020c1608 t1;
    UnkStruct_020c1608 t2;
    int ret;
    int q;
    int k;
    UnkStruct_020c1608_3 *e;
    int h;
    // ENDDECLS

    ret = 0;
    if (func_02073d90(data_020ccf94) != 0) {
        return ret;
    }
    t1.w[0] = 0;
    t1.w[1] = 0;
    MI_CpuCopy8(src, &t1, 8);
    func_0209e100(&t1, 6);
    t1.b[2] = 0;
    t1.b[1] = 0;
    if (a->unk_02 != t1.b[5] || a->unk_01 != t1.b[4] || a->unk_00 != t1.b[3]) {
        t2.w[0] = 0;
        t2.w[1] = 0;
        ret = 1;
        t2.w[0] = 0;
        t2.w[1] = 0;
        t2.b[5] = a->unk_02;
        t2.b[4] = a->unk_01;
        t2.b[3] = a->unk_00;
        a->unk_02 = t1.b[5];
        a->unk_01 = t1.b[4];
        a->unk_00 = t1.b[3];
        q = (int) func_0209e350(&t2, &t1) / 0x5a0;
        if (q > 0) {
            if (q >= 2) {
                a->unk_04 = func_020c15c8(a, &t1);
                func_0209e29c(&t1, 1);
                a->unk_05 = func_020c15c8(a, &t1);
            } else {
                a->unk_04 = a->unk_05;
                func_0209e29c(&t1, 1);
                a->unk_05 = func_020c15c8(a, &t1);
            }
        } else if (q < 0) {
            if (q <= -2) {
                a->unk_04 = func_020c15c8(a, &t1);
                func_0209e29c(&t1, 1);
                a->unk_05 = func_020c15c8(a, &t1);
            } else {
                a->unk_05 = a->unk_04;
                a->unk_04 = func_020c15c8(a, &t1);
            }
        }
        data_021fbbd8 = a->unk_07;
        a->unk_07 = 0;
    }
    if (func_020b65c4() == 0x3f) {
        goto done;
    }
    if (func_020a12e8() != 0) {
        a->unk_04 = 4;
        goto done;
    }
    h = func_020984e8();
    if (h != 0 && func_02099020(h, 1) != 0) {
        a->unk_04 = 4;
        goto done;
    }
    e = func_0203fc70();
    for (k = 0; k < 7; k++) {
        if (e->id == 9 || e->id == 0xa) {
            a->unk_04 = 4;
        }
        e++;
    }
done:
    return ret;
}
