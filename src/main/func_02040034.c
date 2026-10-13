/* func_02040034 @ 0x02040034, 0x130 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union UnkStruct_02040034 {
    u32 v;
    u8 a;
} UnkStruct_02040034;

typedef struct Rec {
    u16 id;
    u16 kind;
    u32 lo;
    u32 hi;
} Rec;

extern int func_02040a48(int id);
extern int func_020408e8(int id, int k);
extern int func_020883cc(void);
extern int func_02088394(void);
extern int func_020881c4(void *p);
extern int func_02040b20(UnkStruct_02040034 x);
extern int func_02040a90(UnkStruct_02040034 x);
extern int data_021f3278;

int func_02040034(Rec *hdr, UnkStruct_02040034 x, Rec *a, Rec *b, int n, int f1, int f2)
{
    // DECLS
    u32 aLo;
    u32 aHi;
    u32 bLo;
    Rec *q;
    int i;
    u32 bHi;
    int kind;
    // ENDDECLS

    kind = hdr->kind;
    if (kind == 5) {
        return 0;
    }
    if (f1 == 0) {
        if (func_02040a48(a->id) != 0) {
            return 1;
        }
    }
    if (kind == 4) {
        if (f2 != 0) {
            if (func_020408e8(a->id, x.a) != 0) {
                return 1;
            }
        } else {
            if (func_020408e8(a->id, x.a) != 0) {
                if (func_020408e8(a->id, (u8) (x.a - 1)) != 0) {
                    return 1;
                }
            }
        }
        if (func_020883cc() != 0 || func_02088394() != 0) {
            return 1;
        }
        return 0;
    }

    aLo = a->lo & ~0xff;
    aHi = a->hi & ~0xff;
    q = b;
    for (i = 0; i < n; q = q + 1, i++) {
        if (q->kind == 5) {
            continue;
        }
        if (kind < q->kind) {
            continue;
        }
        bLo = q->lo & ~0xff;
        bHi = q->hi;
        bHi &= ~0xff;
        if ((aLo < bHi && aHi > bLo) || (bLo < aHi && bHi > aLo)) {
            return 1;
        }
    }
    if (kind >= 2) {
        if (func_020883cc() != 0 || func_02088394() != 0) {
            return 1;
        }
    }
    if (kind >= 3) {
        if (func_020881c4(&data_021f3278) != 0) {
            return 1;
        }
    }
    switch (a->id) {
        case 0x3c:
            return func_02040b20(x);
        case 0x3d:
            return func_02040a90(x);
    }
    return 0;
}
