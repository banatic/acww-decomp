/* func_02055f40 @ 0x02055f40, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dBindMdlTex(unsigned int, unsigned int);
extern void NNS_G3dBindMdlPltt(unsigned int, unsigned int);
extern void func_02055f6c(void *);

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
} UnkStruct_02055f40;

int func_02055f40(UnkStruct_02055f40 *self, unsigned int a, unsigned int b)
{
    self->unk_5C = a;
    self->unk_60 = b;
    if (self->unk_60 != 0) {
        NNS_G3dBindMdlTex(self->unk_5C, self->unk_60);
        NNS_G3dBindMdlPltt(self->unk_5C, self->unk_60);
    }
    func_02055f6c(self);
    return 1;
}