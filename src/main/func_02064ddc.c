/* func_02064ddc @ 0x02064ddc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02064ddc {
    unsigned char pad_00[4];
    void *unk_04;
    unsigned char pad_08[0x34 - 0x8];
    unsigned short unk_34;
    unsigned char pad_36[0x38 - 0x36];
    int unk_38;
    int unk_3C;
    int unk_40;
};

extern void G3_MultMtx33(void *p);
extern void NNS_G3dGlbLightVector(void *p, short a, short b, short c);
extern void NNS_G3dGlbLightColor(void *p, unsigned short d);

void func_02064ddc(struct UnkStruct_02064ddc *s, void *arg)
{
    void *obj = s->unk_04;
    *(volatile unsigned int *) 0x04000440 = 2;
    *(volatile unsigned int *) 0x04000454 = 0;
    G3_MultMtx33(arg);
    NNS_G3dGlbLightVector(obj, (short) s->unk_38, (short) s->unk_3C, (short) s->unk_40);
    NNS_G3dGlbLightColor(obj, s->unk_34);
}
