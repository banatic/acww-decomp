/* func_ov126_022a0854 @ 0x022a0854, 0x70 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bb34(void *a, void *b, unsigned char c, unsigned char d, unsigned int e, unsigned char *f);
extern void func_ov126_022a0924(void *self, unsigned char val);
extern void func_ov126_022a0978(void *self);

typedef struct UnkStruct_022a0854 {
    unsigned char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0xa6 - 0x9c];
    unsigned char unk_A6;
    unsigned char pad_A7[0xab - 0xa7];
    unsigned char unk_AB;
    unsigned char pad_AC[0xaf - 0xac];
    unsigned char unk_AF;
} UnkStruct_022a0854;

void func_ov126_022a0854(UnkStruct_022a0854 *self, int arg)
{
    int diff;
    unsigned int clamp;
    unsigned char *p;
    unsigned char result;

    diff = arg - self->unk_AB;
    if (diff < 0) {
        diff = 0;
    }
    clamp = (unsigned char) diff;
    p = &result;
    self->unk_98 = func_ov095_0229bb34((char *) self + 0x19c, (char *) self + 0x4248, self->unk_A6, self->unk_AF, clamp, p);
    self->unk_98 += self->unk_AB;
    func_ov126_022a0924(self, result);
    func_ov126_022a0978(self);
}
