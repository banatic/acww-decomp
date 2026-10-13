/* func_ov115_0229e748 @ 0x0229e748, 0x5c bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xf8];
    u8 sub[0x132c];
    u32 unk_1424;
} UnkStruct_0229e748;

extern int func_ov115_0229ddb8(void *, int);
extern int func_ov114_0229d52c(void *, u32);
extern int func_0206fe54(int);
extern void func_ov002_02209eb8(void *);
extern void func_ov114_0229d5b8(void *, u32);
extern void func_ov114_0229cbe4(void *, u32);
extern void func_ov114_0229d54c(void *);

int func_ov115_0229e748(UnkStruct_0229e748 *self)
{
    if (func_ov115_0229ddb8(self, 1) == 0) {
        return 1;
    }

    if (func_0206fe54(func_ov114_0229d52c(self->sub, self->unk_1424)) != 0) {
        func_ov002_02209eb8((char *) self + 0x94);
    }

    func_ov114_0229d5b8(self->sub, self->unk_1424);
    func_ov114_0229cbe4(self->sub, self->unk_1424);
    func_ov114_0229d54c(self->sub);
    return 1;
}
