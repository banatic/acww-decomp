/* func_0204ebb0 @ 0x0204ebb0, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0204ebb0 {
    u8 d[0x28];
} UnkStruct_0204ebb0;
typedef struct UnkStruct_0204ebb0_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0204ebb0_2;
typedef struct Dim {
    int w;
    int h;
} Dim;
typedef struct St {
    volatile int a;
    volatile int b;
    int c;
    int d;
    int e;
} St;
typedef struct St2 {
    int x;
    int y;
    int z;
} St2;

typedef struct UnkStruct_0204ebb0_3 {
    UnkStruct_0204ebb0 *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_0204ebb0_3;

extern int data_020ca0ec;
extern int data_020ca0e8;
extern u32 data_021c80d0;
extern u8 data_021c80c4[];
extern u8 data_021c80d4[12];
extern void *func_020b3ae4(void *);
extern void *func_020b3afc(void *o);
extern void __register_global_object(void *, void *, void *);

extern UnkStruct_0204ebb0 *func_02037e90(int n, void *heap, int al);
extern void func_0204f800(int *a, int *b, int w, int h, int z1, int z2);
extern int func_02030ddc(int w, int h, void *o, int k);
extern int func_0203750c(void);
extern int func_02037608(int x, int y);
extern void func_02037eec(UnkStruct_0204ebb0 *e, int a, St2 *s, int b, int c, int d, int r, int z1, St *st, int z2);

int func_0204ebb0(UnkStruct_0204ebb0_3 *p, UnkStruct_0204ebb0_2 *q, Dim *dm, void *heap)
{
    int ret;
    int n;
    UnkStruct_0204ebb0 *e;
    St st;
    St2 st2;

    n = dm->w * dm->h;
    ret = 0;
    p->unk_1C = 0;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(n, heap, 4);
    }
    if (p->unk_00 != 0) {
        st.a = 0;
        st.b = 0;
        st.c = 0;
        st.d = 0;
        st.e = 0;
        e = p->unk_00;
        p->unk_04 = dm->w;
        p->unk_08 = dm->h;
        p->unk_14 = p->unk_04 * data_020ca0ec;
        p->unk_18 = p->unk_08 * data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        if (!(data_021c80d0 & 1)) {
            func_020b3afc(data_021c80c4);
            __register_global_object((void *) (data_021c80c4), (((void *) func_020b3ae4)), (void *) (data_021c80d4));
            data_021c80d0 |= 1;
        }
        func_02030ddc(p->unk_04, p->unk_08, data_021c80c4, p->unk_1C);
        for (st.b = 0; st.b < p->unk_08; st.b++) {
            for (st.a = 0; st.a < p->unk_04; st.a++) {
                st.c = st.a << 17;
                st.e = st.b << 17;
                st2.x = st.c;
                st2.y = st.d;
                st2.z = st.e;
                func_02037eec(e, q->unk_00, &st2, q->unk_04, q->unk_08, q->unk_0C, func_02037608(func_0203750c(), q->unk_00),
                              0, &st, 0);
                e++;
                q++;
            }
        }
        ret = 1;
    }
    return ret;
}
