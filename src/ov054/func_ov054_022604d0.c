/* func_ov054_022604d0 @ 0x022604d0, 0x19c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022604d0_2 UnkStruct_022604d0_2;
typedef struct SubVT {
    void (*unk_00)(UnkStruct_022604d0_2 *);
    void (*unk_04)(UnkStruct_022604d0_2 *);
    void (*unk_08)(UnkStruct_022604d0_2 *);
} SubVT;
struct UnkStruct_022604d0_2 {
    const SubVT *vt;
};

typedef struct UnkStruct_022604d0_3 UnkStruct_022604d0_3;
struct UnkStruct_022604d0_3 {
    u8 pad_00[0x560];
    u8 mode;
    u8 pad_561[0x658 - 0x561];
    UnkStruct_022604d0_2 sub;
};

typedef struct UnkStruct_022604d0 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_022604d0;
extern UnkStruct_022604d0 *data_020ccf94;

extern void func_0201c054(UnkStruct_022604d0_3 *, int, int, int);
extern int func_0201c0e0(UnkStruct_022604d0_3 *);
extern int func_0201c2a4(UnkStruct_022604d0_3 *, int);
extern void func_02016108(UnkStruct_022604d0_2 *, int);
extern void func_ov054_02262528(UnkStruct_022604d0_3 *, int);
extern int func_020a7278(UnkStruct_022604d0_3 *);
extern int func_0201c014(UnkStruct_022604d0_3 *);
extern int func_0201c040(UnkStruct_022604d0_3 *, int *, int *);

void func_ov054_022604d0(UnkStruct_022604d0_3 *self, int ev, int v)
{
    int a, b;
    int t;

    switch (ev) {
        case 3:
            self->mode = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov054_02262528(self, 0xb);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                func_ov054_02262528(self, 0xb);
            }
            break;
        case 1:
            self->sub.vt->unk_08(&self->sub);
            func_02016108(&self->sub, func_0201c2a4(self, 4));
            func_ov054_02262528(self, 1);
            break;
        case 0:
            self->mode = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov054_02262528(self, 0xa);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                self->sub.vt->unk_08(&self->sub);
                func_02016108(&self->sub, func_0201c2a4(self, 4));
                func_ov054_02262528(self, 4);
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278(self)) {
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov054_02262528(self, 2);
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov054_02262528(self, 9);
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
                    func_ov054_02262528(self, 2);
                }
            }
            break;
    }
}
