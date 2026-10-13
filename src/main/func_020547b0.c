/* func_020547b0 @ 0x020547b0, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056e60(void *a, int b);
extern unsigned short func_020550b8(void *a, void *b);
extern void func_02056fcc(void *a, unsigned short b, void *c, int d, unsigned short e);
extern void NNS_G3dAnmObjInit(void *a, void *b, void *c, int d);

typedef struct UnkStruct_020547b0 {
    unsigned char pad_00[4];
    unsigned short flags;
    unsigned char pad_06[0x56];
    void *unk_5C;
    unsigned char pad_60[0x94];
    void *unk_F4;
    unsigned char unk_F8[0x18];
    unsigned char unk_110[0x10];
} UnkStruct_020547b0;

void func_020547b0(UnkStruct_020547b0 *s, void *p, int x, void *q, int z, unsigned short w, unsigned short v, int flag)
{
    func_02056e60(s->unk_110, x);
    if (v == 0) {
        v = func_020550b8(q, p);
    }
    func_02056fcc(s->unk_F8, v, q, z, w);
    NNS_G3dAnmObjInit(s->unk_F4, p, s->unk_5C, 0);
    if (flag) {
        s->flags |= 0x4000;
    } else {
        s->flags &= ~0x4000;
    }
}
