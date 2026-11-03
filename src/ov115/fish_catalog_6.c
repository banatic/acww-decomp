/* fish_catalog_6: 3 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229e7c0 @ 0x0229e7c0, 0x20 bytes, Thumb
 * func_ov115_0229e7a4 @ 0x0229e7a4, 0x1a bytes, Thumb
 * func_ov115_0229e748 @ 0x0229e748, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xf8];
    u8 sub[0x132c];
    u32 unk_1424;
} UnkStruct_0229e748;

extern void func_ov115_0229e384(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern __arm int func_020ee45c(void *p);
extern unsigned char func_ov090_0229936c(int x);
extern void func_ov115_0229e36c(void *p);
extern int func_ov115_0229ddb8(void *, int);
extern void func_ov114_0229d52c(void *, u32);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov114_0229d5b8(void *, u32);
extern void func_ov114_0229cbe4(void *, u32);
extern void func_ov114_0229d54c(void *);

int func_ov115_0229e7c0(void *p)
{
    func_ov115_0229e384(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 1);
    return 1;
}

int func_ov115_0229e7a4(void *p)
{
    func_ov090_0229936c(func_020ee45c(p));
    func_ov115_0229e36c(p);
    return 1;
}

int func_ov115_0229e748(UnkStruct_0229e748 *self)
{
    if (func_ov115_0229ddb8(self, 1) == 0) {
        return 1;
    }

    if (((void) (func_ov114_0229d52c(self->sub, self->unk_1424)), func_0206fe54()) != 0) {
        func_ov002_02209eb8((char *) self + 0x94);
    }

    func_ov114_0229d5b8(self->sub, self->unk_1424);
    func_ov114_0229cbe4(self->sub, self->unk_1424);
    func_ov114_0229d54c(self->sub);
    return 1;
}
