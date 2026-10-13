/* func_ov119_0229c4d4 @ 0x0229c4d4, 0x5e bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229c4d4 {
    u8 pad_00[0x94];
    int unk_94;
};

extern int func_ov119_0229a420(struct UnkStruct_0229c4d4 *, int);
extern void func_ov119_0229a400(struct UnkStruct_0229c4d4 *, int);
extern void func_ov119_0229a968(struct UnkStruct_0229c4d4 *);
extern int func_ov002_02207f48(struct UnkStruct_0229c4d4 *, int);
extern void func_ov002_022080a0(struct UnkStruct_0229c4d4 *, int);
extern void func_ov119_0229bbe4(struct UnkStruct_0229c4d4 *);
extern void func_ov002_02207e80(struct UnkStruct_0229c4d4 *, int, int, int);
extern int func_ov002_02207f60(struct UnkStruct_0229c4d4 *);

void func_ov119_0229c4d4(struct UnkStruct_0229c4d4 *self)
{
    if (func_ov119_0229a420(self, 8) != 0) {
        func_ov119_0229a400(self, 8);
        func_ov119_0229a968(self);
    }
    if (func_ov002_02207f48(self, 0) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov119_0229bbe4(self);
    }
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, 0);
    self->unk_94 = func_ov002_02207f60(self);
}
