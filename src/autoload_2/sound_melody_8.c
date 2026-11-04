/* sound_melody_8: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f6f80 @ 0x020f6f80, 0x8 bytes, ARM
 * func_020f6f70 @ 0x020f6f70, 0x10 bytes, ARM
 * func_020f6f3c @ 0x020f6f3c, 0x34 bytes, ARM
 * func_020f6eb4 @ 0x020f6eb4, 0x88 bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
} UnkStruct_020f6f80;

typedef struct UnkStruct_020f6f3c {
    char pad_00[10];
    s8 unk_0A;
    s8 unk_0B;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    s8 unk_10;
    s8 unk_11;
} UnkStruct_020f6f3c;

typedef struct {
    char pad_00[14];
    char e, unk_0F, g, h;
} UnkStruct_020f6eb4;

extern int func_020eed18(int a, int b);
extern int NNS_SndPlayerReadVariable(void *s, int index, short *out);

void func_020f6f80(UnkStruct_020f6f80 *p, unsigned short v)
{
    p->unk_08 = v;
}

void func_020f6f70(int a)
{
    func_020eed18(a, 5);
}

void func_020f6f3c(UnkStruct_020f6f3c *self)
{
    self->unk_0A = 0;
    self->unk_0B = -1;
    self->unk_0C = 0;
    self->unk_11 = -1;
    self->unk_10 = self->unk_11;
    self->unk_0F = self->unk_10;
    self->unk_0E = self->unk_0F;
}

void func_020f6eb4(UnkStruct_020f6eb4 *s)
{
    short a, b, c, d;
    a = b = c = d = -1;
    NNS_SndPlayerReadVariable(s, 0, &a);
    NNS_SndPlayerReadVariable(s, 1, &b);
    NNS_SndPlayerReadVariable(s, 2, &c);
    NNS_SndPlayerReadVariable(s, 3, &d);
    s->e = a;
    s->unk_0F = b;
    s->g = c;
    s->h = d;
}
