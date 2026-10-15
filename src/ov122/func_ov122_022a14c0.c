/* func_ov122_022a14c0 @ 0x022a14c0, 0xf8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022a14c0 {
    u8 pad_00[0xaa];
    u8 unk_AA;
    u8 pad_AB;
    u8 unk_AC;
    u8 pad_AD[0x0f];
    u32 unk_BC;
    u8 sub[1];
};

extern int func_ov095_0229bc00(void *a, void *b, int c, void *d, int e, int f, int g, int h, int i, int j);
extern void func_ov095_0229ce84(void *a, int b);
extern void func_ov095_0229cef4(void *a, int b);
extern void func_ov095_0229bee4(void *a);
extern void func_ov095_0229bed8(void *receiver, int value);
extern int func_ov122_0229f958(struct UnkStruct_022a14c0 *p);
extern int func_ov122_0229efe8(struct UnkStruct_022a14c0 *p, int n);
extern int func_ov122_0229f980(struct UnkStruct_022a14c0 *p);

void func_ov122_022a14c0(struct UnkStruct_022a14c0 *p)
{
    u8 local;
    int r;

    if (p->unk_AA == 2) {
        local = p->unk_AC;
        r = func_ov095_0229bc00(p->sub, (void *) (p->unk_BC + 0x58), 0xa, &local, 0x40, 0x28, 0x4, 0xa0, 0x1, 0x1);
        if (r) {
            func_ov095_0229ce84(p->sub, 0);
        } else {
            func_ov095_0229cef4(p->sub, 0);
        }
    } else {
        func_ov095_0229cef4(p->sub, 0);
    }

    if (func_ov122_0229f958(p)) {
        func_ov095_0229ce84(p->sub, 0xb);
    } else {
        func_ov095_0229cef4(p->sub, 0xb);
    }

    if (func_ov122_0229efe8(p, 0x400)) {
        func_ov095_0229ce84(p->sub, 0xc);
    } else {
        func_ov095_0229cef4(p->sub, 0xc);
    }

    if (func_ov122_0229f958(p)) {
        func_ov095_0229bee4(p->sub);
        func_ov095_0229ce84(p->sub, 6);
    } else {
        if (p->unk_AC == 0) {
            func_ov095_0229bee4(p->sub);
        } else {
            r = func_ov122_0229f980(p);
            func_ov095_0229bed8(p->sub, r);
        }
    }
}
