/* func_020554ec @ 0x020554ec, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
    void *mdl;
} UnkStruct_020554ec;

typedef struct {
    char pad_00[0xe];
    unsigned short dictOff;
} Hdr;

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_020554ec_2;

extern void *data_021fbe94;
extern Hdr *func_02064b2c(void *file, void *heap, int a, int b);
extern Hdr *func_02107828(Hdr *res);
extern void *func_020561fc(void *ptr, int name);
extern void *func_02072614(void);
extern void *func_02072630(void *a, int b, int c);
extern int NNS_G3dForceBindMdlTex(void *m, void *t, int a, int b);
extern int NNS_G3dForceBindMdlPltt(void *m, void *t, int a, int b);
extern void func_020e993c(void *heap, void *p);
extern void func_02055f6c(UnkStruct_020554ec *self);

int func_020554ec(UnkStruct_020554ec *self, void *file, int a2, int a3)
{
    void *heap = data_021fbe94;
    Hdr *res;
    Hdr *h;
    void *tex;

    res = func_02064b2c(file, heap, -4, 0);
    if (res == 0) {
        return 0;
    }
    h = func_02107828(res);
    self->mdl = func_020561fc((char *) h + ((UnkStruct_020554ec_2 *) ((char *) h + h->dictOff))->unk_0C, 0x4e554c4c);
    tex = func_02072630(func_02072614(), a2, a3);
    NNS_G3dForceBindMdlTex(self->mdl, tex, 0, 0);
    NNS_G3dForceBindMdlPltt(self->mdl, tex, 0, 0);
    func_020e993c(heap, res);
    func_02055f6c(self);
    return 1;
}
