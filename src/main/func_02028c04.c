/* func_02028c04 @ 0x02028c04, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_02028c04;
typedef struct {
    int pad_00[8];
    u8 a;
    u8 b;
    u8 pad_22[2];
} ST;
typedef struct {
    int x;
    int y;
} UnkStruct_02028c04_2;
typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} GS;
typedef struct {
    u8 pad_00[0x10];
    int unk_10;
} SUB;
typedef struct {
    u8 pad_00[0xa4];
    SUB sub;
} UnkStruct_02028c04_3;
typedef struct {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x100 - 0x44];
    void *unk_100;
} CTX;

extern GS *data_020ccf94;
extern int data_020c8928;
extern int data_021c2fec;
extern int data_020c8924;
extern int data_021c1d6c;
extern UnkStruct_02028c04_2 data_020d8eb8;

extern void func_0207f270(void *);
extern int func_020794d0(void);
extern void func_0209e474(UnkStruct_02028c04 *);
extern int func_02073dd4(GS *, int);
extern int func_0209bd44(int *);
extern int func_0207ef54(void *, UnkStruct_02028c04_3 *);
extern int func_0207f150(void *);
extern int func_0201cddc(void *);
extern int func_02080998(void *, int, UnkStruct_02028c04 *);
extern int func_0207aeac(int, UnkStruct_02028c04 *);
extern void func_0201cfb4(CTX *, ST *);
extern void func_0201cf74(CTX *, ST *, int, void *, void *);
extern void func_0202d9d0(CTX *, int);
extern void func_0201cec8(CTX *, ST *);
extern void func_0202da74(CTX *, UnkStruct_02028c04_2);
extern void func_02068388(int, int);

int func_02028c04(CTX *a1, void *a2, UnkStruct_02028c04_3 *a3)
{
    int x;
    UnkStruct_02028c04 s;
    ST st;
    SUB *p;

    func_0207f270(a2);
    x = func_020794d0();
    p = &a3->sub;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 && func_0209bd44(&p->unk_10) == 0 &&
        func_0207ef54(a2, a3) == 0 && func_0207f150(a2) == 3 && func_0201cddc(a1->unk_100) == 0xb &&
        func_02080998(a2, 1, &s) == -1 && func_0207aeac(1, &s) == 0xb) {
        func_0201cfb4(a1, &st);
        func_0201cf74(a1, &st, 0, &data_020c8928, &data_021c2fec);
        func_0201cf74(a1, &st, 1, &data_020c8924, &data_021c1d6c);
        func_0202d9d0(a1, x);
        st.a = 2;
        st.b = st.a - 1;
        func_0201cec8(a1, &st);
        func_0202da74(a1, data_020d8eb8);
        func_02068388(a1->unk_40, 1);
        return 1;
    }
    return 0;
}
