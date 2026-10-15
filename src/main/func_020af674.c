/* func_020af674 @ 0x020af674, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020af674 {
    u32 unk_00;
    u8 pad_04[0x58];
    u8 unk_5C[8];
};

extern u32 func_020af028(unsigned short *);
extern u32 func_020af8e0(struct UnkStruct_020af674 *, u32);
extern int func_020af870(struct UnkStruct_020af674 *, u32);
extern u16 *func_020af854(struct UnkStruct_020af674 *, u32, int);
extern void func_020af658(struct UnkStruct_020af674 *, void *);
extern void func_020af788(struct UnkStruct_020af674 *);

int func_020af674(struct UnkStruct_020af674 *o, u32 idx, u32 delta, void *a3)
{
    u32 cap;
    unsigned int ok;
    unsigned int ok2;
    u16 v;
    u32 byteIdx;
    u32 bit;
    u16 *p;

    if (idx < 0x25) {
        cap = func_020af8e0(o, func_020af028((unsigned short *) o));
        o->unk_00 = o->unk_00 + delta;
        if (o->unk_00 > cap) {
            o->unk_00 = cap;
        }
        if (func_020af870(o, idx) == 0) {
            byteIdx = idx >> 3;
            bit = idx & 7;
            p = func_020af854(o, idx, 0);
            ok = 0;
            v = *p;
            if (v >= 0x1000 && v <= 0x10ff) {
                ok = 1;
            }
            if (ok == 0) {
                p = func_020af854(o, idx, 0);
                ok2 = 0;
                v = *p;
                if (v >= 0x151f && v <= 0x151f) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    o->unk_5C[byteIdx] |= 1 << bit;
                }
            }
        }
        func_020af658(o, a3);
        func_020af788(o);
        return 1;
    }
    cap = func_020af8e0(o, func_020af028((unsigned short *) o));
    o->unk_00 = o->unk_00 + delta;
    if (o->unk_00 > cap) {
        o->unk_00 = cap;
    }
    func_020af658(o, a3);
    func_020af788(o);
    return 0;
}
