/* func_0203feec @ 0x0203feec, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    u32 w;
    struct {
        u8 a, b, c, d;
    } s;
} UnkStruct_0203feec;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u32 unk_08;
} Dst;
typedef struct {
    u8 pad_00[2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
} Src;
typedef struct {
    u8 pad_00[0x1c];
} UnkStruct_0203feec_2;
typedef struct {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u32 unk_08;
} UnkStruct_0203feec_3;

extern UnkStruct_0203feec_2 data_020dac08[];

extern u8 func_0209de88(int a, int b);
extern void func_02040164(void *a, int n);
extern int func_0203ff98(Dst *d, UnkStruct_0203feec_2 *e, int t, UnkStruct_0203feec p);
extern int func_02040034(UnkStruct_0203feec_2 *e, UnkStruct_0203feec p, Dst *d, void *a, int n, void *c, void *dd);
extern void func_02040010(Dst *d, UnkStruct_0203feec p);

int func_0203feec(UnkStruct_0203feec_3 *arr, Src *src, void *c, void *dd)
{
    UnkStruct_0203feec pp;
    Dst d;
    UnkStruct_0203feec_2 *e;
    UnkStruct_0203feec_3 *o;
    int n;
    int i;
    int t;
    int d4;

    n = 0;
    t = src->unk_05;
    d4 = src->unk_04;
    pp.s.d = (u8) d4;
    pp.s.c = src->unk_03;
    pp.s.b = src->unk_02;
    pp.s.a = func_0209de88(t, d4);
    func_02040164(arr, 7);
    e = data_020dac08;
    for (i = 0; i < 0x63; e++, i++) {
        if (func_0203ff98(&d, e, t, pp) == 0) {
            continue;
        }
        if (func_02040034(e, pp, &d, arr, n, c, dd) != 0) {
            continue;
        }
        func_02040010(&d, pp);
        o = &arr[n];
        arr[n].unk_00 = d.unk_00;
        o->unk_02 = d.unk_02;
        o->unk_04 = d.unk_04;
        o->unk_08 = d.unk_08;
        n++;
        if (n == 7) {
            break;
        }
    }
    return n;
}
