/* func_02050140 @ 0x02050140, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    unsigned char unk_4C[0x98 - 0x4c];
    unsigned char unk_98[0x164 - 0x98];
    int unk_164;
} UnkStruct_02050140;

extern void *func_0209d238(void *b, int *p);
extern int func_0209d0ac(void *p, void *h, void *g);
extern void *func_0209d088(void *p);
extern void func_02055f2c(void *a, void *b, int c);
extern void *func_0209d324(void *h);
extern void *func_02064b2c(void *g, void *v, int n, int k);
extern void *NNS_G3dGetJntAnmSet(void *x);
extern void *func_02107b44(void *x, int k);
extern int func_02055140(void *a, void *v);
extern void func_02055060(void *a, void *x, int c, int d, int e, int f);
extern void func_02055050(void *a);
extern void func_02050394(void *a, UnkStruct_02050140 *s);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern void *data_020dcd74;
extern void *data_020dcd70;

int func_02050140(void *a, void *b, UnkStruct_02050140 *s)
{
    int ret = 0;
    void *p;
    void *h;
    void *v;
    void *x;
    void *r4;
    int kind;

    if (b == 0 || s == 0) {
        return 0;
    }
    kind = s->unk_40;
    h = func_0209d238(b, &s->unk_48);
    p = s;
    p = &s->unk_4C;
    if (func_0209d0ac(p, h, data_020dcd74) != 0) {
        r4 = &s->unk_98;
        func_02055f2c(r4, func_0209d088(p), 0);
        v = func_0209d324(h);
        x = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_020dcd70, v, 4, 0)), 0);
        if (func_02055140(r4, v) != 0) {
            func_02055060(r4, x, 0, 0x1000, 1, 0);
            func_02055050(r4);
            s->unk_44 = 3;
            func_02050394(a, s);
            if (kind == 0x3b) {
                NNS_G3dMdlSetMdlAlpha(func_0209d088(p), 0, s->unk_164);
            }
            ret = 1;
        }
    }
    return ret;
}
