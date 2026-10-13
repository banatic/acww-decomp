/* func_ov047_02260474 @ 0x02260474, 0x19c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260474_2 UnkStruct_02260474_2;
typedef struct SubVT {
    void (*unk_00)(UnkStruct_02260474_2 *);
    void (*unk_04)(UnkStruct_02260474_2 *);
    void (*unk_08)(UnkStruct_02260474_2 *);
} SubVT;
struct UnkStruct_02260474_2 {
    const SubVT *vt;
};

typedef struct UnkStruct_02260474_3 UnkStruct_02260474_3;
struct UnkStruct_02260474_3 {
    u8 pad_00[0x560];
    u8 mode;
    u8 pad_561[0x658 - 0x561];
    UnkStruct_02260474_2 sub;
};

typedef struct UnkStruct_02260474 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_02260474;
extern UnkStruct_02260474 *data_020ccf94;

extern void func_0201c054(UnkStruct_02260474_3 *, int, int, int);
extern int func_0201c0e0(UnkStruct_02260474_3 *);
extern int func_0201c2a4(UnkStruct_02260474_3 *, int);
extern void func_02016108(UnkStruct_02260474_2 *, int);
extern void func_ov047_022624f4(UnkStruct_02260474_3 *, int);
extern int func_020a7278(UnkStruct_02260474_3 *);
extern int func_02073d90(UnkStruct_02260474 *);
extern short *func_0209d358(int, int);
extern int func_0201c014(UnkStruct_02260474_3 *);
extern int func_0201c040(UnkStruct_02260474_3 *, int *, int *);

void func_ov047_02260474(UnkStruct_02260474_3 *self, int ev, int v)
{
    int a, b;
    int t;
    UnkStruct_02260474 *g;

    switch (ev) {
        case 3:
            self->mode = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov047_022624f4(self, 8);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                func_ov047_022624f4(self, 8);
            }
            break;
        case 0:
            self->mode = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov047_022624f4(self, 7);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                self->sub.vt->unk_08(&self->sub);
                func_02016108(&self->sub, func_0201c2a4(self, 4));
                func_ov047_022624f4(self, 3);
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278(self)) {
                    g = data_020ccf94;
                    func_0201c054(self, 1, g->unk_64, 4);
                    if (func_02073d90(g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                        func_ov047_022624f4(self, 0);
                    } else {
                        func_ov047_022624f4(self, 1);
                    }
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov047_022624f4(self, 6);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                a = 4;
                b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if (v != 4) {
                        if (v == b) {
                            goto ok4;
                        }
                    }
                    if (v != 4) {
                        return;
                    }
                ok4:
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov047_022624f4(self, 0);
                }
            }
            break;
    }
}
