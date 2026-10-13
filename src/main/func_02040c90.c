/* func_02040c90 @ 0x02040c90, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    u64 q;
    u8 b[8];
} UnkStruct_02040c90;
typedef struct {
    u8 d[0x14];
} UnkStruct_02040c90_2;
typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
} UnkStruct_02040c90_4;

typedef struct {
    u8 pad_00[0x34];
    u64 unk_34;
} UnkStruct_02040c90_3;

extern u32 data_021c7584;

extern void func_0209e474(UnkStruct_02040c90 *);
extern u32 MB_GetBeaconRecvStatus(void);
extern void func_0209e314(UnkStruct_02040c90 *, UnkStruct_02040c90 *);
extern UnkStruct_02040c90_4 *func_020409c8(UnkStruct_02040c90_3 *, u32);
extern void func_0204101c(UnkStruct_02040c90_3 *);
extern void MI_CpuCopy8(const void *, void *, u32);
extern int func_02041140(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, UnkStruct_02040c90 *);
extern void func_02040e44(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, UnkStruct_02040c90 *);
extern void func_02040f8c(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, u8 *, UnkStruct_02040c90 *);
extern void func_02040f04(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, UnkStruct_02040c90 *);
extern void func_02040da8(UnkStruct_02040c90_3 *);
extern u32 func_02040bcc(UnkStruct_02040c90_3 *, int);
extern void func_020ae190(void);

void func_02040c90(UnkStruct_02040c90_3 *a0, int a1)
{
    UnkStruct_02040c90 s1;
    UnkStruct_02040c90 s2;
    u8 buf[8];
    int v;
    UnkStruct_02040c90 c1;
    UnkStruct_02040c90 c2;
    UnkStruct_02040c90 c3;
    UnkStruct_02040c90 c4;
    UnkStruct_02040c90_2 big;
    u32 t0;
    u32 v1;
    UnkStruct_02040c90_4 *p;
    UnkStruct_02040c90_4 *e;
    int j;

    s1.q = 0;
    s2.q = 0;
    func_0209e474(&s1);
    t0 = MB_GetBeaconRecvStatus();
    data_021c7584 = s1.b[2];
    func_0209e314(&s1, &s2);
    if (a0->unk_34 == 0 || a0->unk_34 != s2.q || a1) {
        p = func_020409c8(a0, 1);
        for (j = 0; j < 5; j++) {
            buf[j] = p->unk_02;
            p++;
        }
        buf[5] = 0x63;
        func_0204101c(a0);
        MI_CpuCopy8(&s2, &c1, 8);
        v = func_02041140(a0, &big, &c1);
        MI_CpuCopy8(&s2, &c2, 8);
        func_02040e44(a0, &big, &v, &c2);
        MI_CpuCopy8(&s2, &c3, 8);
        func_02040f8c(a0, &big, &v, buf, &c3);
        MI_CpuCopy8(&s2, &c4, 8);
        func_02040f04(a0, &big, &v, &c4);
        MI_CpuCopy8(&s2, &a0->unk_34, 8);
    }
    func_02040da8(a0);
    v1 = func_02040bcc(a0, 0x3d);
    if (v1 - t0 <= 1) {
        e = func_020409c8(a0, v1);
        if (e != 0 && e->unk_04 == 0) {
            func_020ae190();
            e->unk_04 = 1;
        }
    }
}
