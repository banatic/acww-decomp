/* func_020653fc @ 0x020653fc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G3_MultMtx33(int);
extern void NNS_G3dGlbLightVector(int, short, short, short);
extern void NNS_G3dGlbLightColor(int, unsigned short);

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020653fc;

void func_020653fc(UnkStruct_020653fc *p, int arg)
{
    if (p->unk_00 != 9) {
        *(volatile unsigned int *) 0x04000440 = 2;
        *(volatile unsigned int *) 0x04000454 = 0;
        G3_MultMtx33(arg);
        NNS_G3dGlbLightVector(2, p->unk_08, p->unk_0C, p->unk_10);
        NNS_G3dGlbLightColor(2, p->unk_04);
    } else {
        NNS_G3dGlbLightColor(2, 0);
    }
}
