/* func_ov048_0226056c @ 0x0226056c, 0x1a8 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct VT2;
struct UnkStruct_0226056c_2 {
    struct VT2 *vt;
};
struct VT2 {
    void (*fn[8])(struct UnkStruct_0226056c_2 *);
};

struct UnkStruct_0226056c_3 {
    u8 pad_00[0x560];
    u8 unk_560;
    u8 pad_561[0x658 - 0x561];
    struct UnkStruct_0226056c_2 unk_658;
};

struct UnkStruct_0226056c {
    u8 pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_0226056c *data_020ccf94;

extern void func_0201c054(struct UnkStruct_0226056c_3 *self, int a, int b, int c);
extern int func_0201c0e0(struct UnkStruct_0226056c_3 *self);
extern int func_0201c014(struct UnkStruct_0226056c_3 *self);
extern int func_0201c040(struct UnkStruct_0226056c_3 *self, int *a, int *b);
extern int func_0201c2a4(struct UnkStruct_0226056c_3 *self, int a);
extern void func_ov048_022635f4(struct UnkStruct_0226056c_3 *self, int a);
extern void func_02016108(struct UnkStruct_0226056c_2 *s, int a);
extern void func_ov048_02262678(struct UnkStruct_0226056c_2 *s, int a);
extern int func_020a7278(void);

void func_ov048_0226056c(struct UnkStruct_0226056c_3 *self, int sel, int v)
{
    switch (sel) {
        case 3:
            self->unk_560 = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov048_022635f4(self, 0x10);
            } else if (func_0201c0e0(self) != 0) {
                int k = data_020ccf94->unk_64;
                func_0201c054(self, 1, k, k);
                func_ov048_022635f4(self, 0x10);
            }
            break;
        case 1:
            self->unk_658.vt->fn[2](&self->unk_658);
            func_02016108(&self->unk_658, func_0201c2a4(self, 4));
            func_ov048_022635f4(self, 2);
            break;
        case 0:
            self->unk_560 = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov048_022635f4(self, 0x11);
            } else {
                if (func_0201c0e0(self) != 0) {
                    int k = data_020ccf94->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    func_ov048_022635f4(self, 2);
                }
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov048_022635f4(self, 4);
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov048_022635f4(self, 0xf);
                }
            }
            func_ov048_02262678(&self->unk_658, 0xb);
            break;
        case 4: {
            int a;
            int b;
            if (func_0201c014(self) == 0) {
                break;
            }
            if (func_0201c0e0(self) == 0) {
                break;
            }
            a = 4;
            b = 4;
            if (func_0201c040(self, &a, &b) == 0) {
                break;
            }
            if (v != 4) {
                if (v == b) {
                    goto ok;
                }
            }
            if (v != 4) {
                break;
            }
        ok:
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov048_022635f4(self, 1);
            break;
        }
    }
}
