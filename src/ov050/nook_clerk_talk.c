/* nook_clerk_talk: 2 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02260e50 @ 0x02260e50, 0x2e bytes, Thumb
 * func_ov050_02260dd4 @ 0x02260dd4, 0x7c bytes, Thumb
 */

#include "types.h"

typedef struct Work Work;

typedef struct Other Other;

struct Work {
    u8 pad_00[0x732];
    u16 unk_732;
    u32 unk_734;
    u32 unk_738;
    u8 unk_73C;
};

struct Other;

typedef struct UnkStruct_02260dd4 {
    u8 pad_00[0xb4];
    Work *w;
    u8 pad_B8[0xc];
    Other *e;
} UnkStruct_02260dd4;

extern int func_020984e8(void);
extern int func_02099fe8(void);
extern unsigned char data_021dc7bc[1];
extern void func_0201b420(Work *a, Other *b);
extern int func_0209a000(void *a, int b);
extern int func_02099870(int argument0);
extern int func_0209871c(void *a, int b);
extern int func_020b65c4(void);
extern void func_020ada48(u32 a, u32 b, Other *c, int d);
extern void func_02079708(void);

void func_ov050_02260e50(int *r0, int r1)
{
    int *r4 = r0;
    int r5 = r1;
    func_020984e8();
    if (r5 == 0) {
        if (func_02099fe8() >= 0) {
            r4[0x34] = 0x25;
        } else {
            r4[0x34] = 0x17;
        }
    }
}

void func_ov050_02260dd4(UnkStruct_02260dd4 *self)
{
    self->w->unk_73C = 1;
    func_0201b420(self->w, self->e);
    func_0209a000(&self->w->unk_732, 0);

    func_0209871c(data_021dc7bc, func_02099870((int) func_020984e8()));
    func_020ada48(self->w->unk_734, self->w->unk_738, self->e, func_020b65c4());
    func_02079708();
}
