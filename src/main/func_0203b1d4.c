/* func_0203b1d4 @ 0x0203b1d4, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0203b1d4 {
    void *ptr;
    s16 unk_04;
    s16 unk_06;
};

typedef struct {
    s16 x;
    s16 y;
} TabEntry;

extern TabEntry FX_SinCosTable_[];

extern void func_020e89dc(void *, u32, u32);
extern int FX_MulFunc(int, void *);
extern void func_0203bc50(void *, void *);
extern void func_020e8bb0(void *, u32, u32, u32, u32);
extern void func_0203be6c(void *);
extern void func_01ffcbb0(void *, void *);
extern void *func_0203c57c(void *);
extern void *func_0203c568(void *);
extern void *func_0203c548(void *);
extern void func_0203bd84(void *, void *, void *, void *, void *);
extern void MTX_MultVec33(void *, void *, void *);
extern void func_020eabc8(void *, int);
extern void VEC_Add(void *, void *, void *);

void func_0203b1d4(unsigned char *p)
{
    struct UnkStruct_0203b1d4 *w;
    int v;
    void *a;
    void *b;
    void *c;
    u32 local_b[3];
    u32 local_a[3];

    w = (struct UnkStruct_0203b1d4 *) (p + 0x21c);
    w->unk_04 = w->unk_04 + w->unk_06;
    func_020e89dc(&w->unk_06, 0x6000, 0x180);
    v = FX_MulFunc(FX_SinCosTable_[(u16) w->unk_04 >> 4].x, *(void **) (p + 0x21c));

    func_0203bc50(p, p + 0x130);
    func_020e8bb0(w, 0, 0x400, 0x80, 0x10);
    func_0203be6c(p);
    func_01ffcbb0(local_a, p);
    a = func_0203c57c(p);
    b = func_0203c568(p);
    c = func_0203c548(p);
    func_0203bd84(p, local_a, a, b, c);

    local_b[0] = 0;
    local_b[1] = 0x1000;
    local_b[2] = 0;
    MTX_MultVec33(local_b, p + 0xcc, local_b);
    func_020eabc8(local_b, v);
    VEC_Add(p + 0x194, local_b, p + 0x194);
    VEC_Add(p + 0x188, local_b, p + 0x188);
}
