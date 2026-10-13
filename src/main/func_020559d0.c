/* func_020559d0 @ 0x020559d0, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021fbe94;

extern void *func_02064b2c(int a, void *b, int c, int d);
extern void func_02055b50(int a, void *b);
extern void func_020b9eec(void *a, void *b, int c);
extern void *func_021077e8(void *a);
extern void *func_02107828(void *a);
extern void *func_02056268(void *a, void *b);
extern void NNS_G3dBindMdlTex(void *a, void *b);
extern void NNS_G3dBindMdlPltt(void *a, void *b);
extern void func_020e993c(void *a, void *b);

typedef struct {
    u8 pad_00[4];
    void *unk_04;
    void *unk_08;
    void *unk_0C;
    u8 pad_10[4];
    u8 unk_14[13];
    u8 unk_21;
    u8 pad_22[14];
    u8 unk_30;
} UnkStruct_020559d0;

u8 func_020559d0(UnkStruct_020559d0 *s, int a1, int a2, int a3, void *a4)
{
    void *p = a4;
    u8 state = s->unk_30;
    void *p2;
    u8 *q;
    unsigned int flag;

    if (state == 3) {
        return state;
    }

    if (p == 0) {
        p = data_021fbe94;
    }

    if (state == 0) {
        s->unk_04 = func_02064b2c(a1, p, ~3, 0);
        s->unk_08 = p;
        p2 = func_021077e8(s->unk_04);
        func_02055b50(a2, p2);
        func_020b9eec(&s->unk_14, p2, 1);
        s->unk_30 = 1;
        return s->unk_30;
    }

    if (state == 1) {
        flag = (s->unk_21 == 2) ? 1u : 0u;
        if (flag == 0) {
            return state;
        }
        s->unk_30 = 2;
    }

    if (s->unk_30 == 2) {
        q = (u8 *) func_02107828(s->unk_04);
        q = q + *(u32 *) (q + *(u16 *) (q + 0xe) + 0xc);
        s->unk_0C = func_02056268(q, (void *) a3);
        p2 = func_021077e8(s->unk_04);
        NNS_G3dBindMdlTex(s->unk_0C, p2);
        NNS_G3dBindMdlPltt(s->unk_0C, p2);
        func_020e993c(s->unk_08, s->unk_04);
        s->unk_08 = 0;
        s->unk_04 = 0;
        s->unk_30 = 3;
    }

    return s->unk_30;
}