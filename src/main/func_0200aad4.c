/* func_0200aad4 @ 0x0200aad4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200ac8c(void *a, u32 *w, u16 *h, u8 *b);
extern void func_0200acd4(void *a, u32 *buf, u16 h, u8 b, u32 c, u32 d);

typedef struct {
    u8 pad_00[0x7f0];
    u32 unk_7F0;
    u8 pad_7F4[0x8ec - 0x7f0 - 4];
    u8 unk_8EC;
    u8 pad_8ED[0x8f0 - 0x8ec - 1];
    u8 sub[0xc84 - 0x8f0];
    u16 unk_C84;
} UnkStruct_0200aad4;

void func_0200aad4(UnkStruct_0200aad4 *s, u32 arg1)
{
    if (s->unk_8EC != 0) {
        s->unk_8EC++;
        return;
    }
    if (s->unk_7F0 == 0x1A) {
        s->unk_C84 = arg1;
        return;
    }
    {
        struct {
            u8 b;
            u8 pad;
            u16 h;
            u32 w;
            u32 v;
            u32 buf[2];
        } loc;

        loc.w = 0;
        loc.v = 0;
        func_0200ac8c(&s->sub[0], &loc.w, &loc.h, &loc.b);
        loc.buf[0] = loc.w;
        loc.buf[1] = loc.v;
        func_0200acd4(s, loc.buf, loc.h, loc.b, 6, arg1);
    }
}
