/* func_ov050_02260dd4 @ 0x02260dd4, 0x7c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
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

extern unsigned char data_021dc7bc[1];

extern void func_0201b420(Work *a, Other *b);
extern void func_0209a000(void *a, int b);
extern void func_020984e8(void);
extern int func_02099870(void);
extern void func_0209871c(void *a, int b);
extern int func_020b65c4(void);
extern void func_020ada48(u32 a, u32 b, Other *c, int d);
extern void func_02079708(void);

void func_ov050_02260dd4(UnkStruct_02260dd4 *self)
{
    self->w->unk_73C = 1;
    func_0201b420(self->w, self->e);
    func_0209a000(&self->w->unk_732, 0);
    func_020984e8();
    func_0209871c(data_021dc7bc, func_02099870());
    func_020ada48(self->w->unk_734, self->w->unk_738, self->e, func_020b65c4());
    func_02079708();
}
