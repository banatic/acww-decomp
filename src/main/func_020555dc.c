/* func_020555dc @ 0x020555dc, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbe94;

struct UnkStruct_020555dc {
    unsigned char pad_00[0x5c];
    void *unk_5C;
    unsigned char pad_60[0x94 - 0x60];
    void *unk_94;
};

extern unsigned int func_02064b2c(unsigned int, unsigned int, int, int);
extern unsigned char *func_02107828(unsigned int);
extern void *func_02056268(void *, void *);
extern void *func_020561fc(void *, unsigned int);
extern void NNS_G3dBindMdlTex(void *, void *);
extern void *func_021077e8(unsigned int);
extern void func_02056064(void *, void *);
extern void NNS_G3dForceBindMdlPltt(void *, void *, int, unsigned int);
extern void func_020e993c(unsigned int, unsigned int);
extern void func_02055f6c(struct UnkStruct_020555dc *);

int func_020555dc(struct UnkStruct_020555dc *self, unsigned int a, void *b, void *c, void *d, unsigned int *e, int f,
                  unsigned int g)
{
    unsigned int local0;
    unsigned int local1;
    unsigned char *p, *obj;
    unsigned short off;
    unsigned int w;
    void *r;
    int i;

    local1 = data_021fbe94;
    local0 = func_02064b2c(a, local1, -4, 0);
    if (local0 == 0) {
        return 0;
    }

    p = func_02107828(local0);
    off = *(unsigned short *) (p + 0xe);
    w = *(unsigned int *) (p + off + 0xc);
    obj = p + w;

    if (b != 0) {
        self->unk_5C = func_02056268(obj, b);
    } else {
        self->unk_5C = func_020561fc(obj, g);
    }

    if (c != 0) {
        NNS_G3dBindMdlTex(self->unk_5C, c);
    } else {
        r = func_021077e8(local0);
        if (r != 0) {
            func_02056064(r, self->unk_94);
            NNS_G3dBindMdlTex(self->unk_5C, r);
        }
    }

    if (d != 0) {
        for (i = 0; i < f; i++) {
            NNS_G3dForceBindMdlPltt(self->unk_5C, d, i, e[i]);
        }
    }

    func_020e993c(local1, local0);
    func_02055f6c(self);

    return 1;
}
