/* func_020f6eb4 @ 0x020f6eb4, 0x88 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerReadVariable(void *s, int index, short *out);

typedef struct {
    char pad_00[14];
    char e, unk_0F, g, h;
} UnkStruct_020f6eb4;

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
