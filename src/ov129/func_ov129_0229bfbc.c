/* func_ov129_0229bfbc @ 0x0229bfbc, 0xd8 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x1e];
    u16 b[6];
    u16 a[16];
} Src;

typedef struct {
    char pad_00[0xb1];
    u8 unk_B1;
    char pad_B2[1];
    u8 unk_B3;
    char pad_B4[0x734 - 0xb4];
    char unk_734;
    char pad_735[0x2f6c - 0x735];
    u16 dst6[6];
    u16 dst16[16];
} UnkStruct_0229bfbc;

extern void func_0206fc8c(void);
extern Src *func_020b1530(void);
extern u8 *func_ov127_022996bc(int a);
extern int func_ov127_022996d8(int a);
extern int func_ov127_022996c8(int a);
extern void func_ov127_02299a94(void *p, int a, int b);
extern void func_ov129_0229bf88(UnkStruct_0229bfbc *self);

void func_ov129_0229bfbc(UnkStruct_0229bfbc *self)
{
    int i;
    u16 *p;
    Src *src;
    int first;
    int h;
    int w;

    func_0206fc8c();
    src = func_020b1530();
    p = self->dst16;
    first = 0xffff;
    if (src != 0) {
        for (i = 0; i < 0x10; i++) {
            *p = src->a[i];
            if (*p != 0xffff && first == 0xffff) {
                first = *p;
            }
            p++;
        }
        self->unk_B1 = 2;
        self->unk_B3 = *func_ov127_022996bc(first);
        w = func_ov127_022996d8(self->unk_B3) << 3;
        h = func_ov127_022996c8(self->unk_B3) << 3;
        w = (w + 4) & 0xfffc;
        h = (h + 4) & 0xfffc;
        func_ov127_02299a94(&self->unk_734, w, h);
        for (i = 0; i < 6; i++) {
            self->dst6[i] = src->b[i];
        }
    } else {
        for (i = 0; i < 0x10; i++) {
            *p = (u16) first;
            p++;
        }
        for (i = 0; i < 6; i++) {
            self->dst6[i] = 0;
        }
        self->unk_B1 = 0;
    }
    func_ov129_0229bf88(self);
}
