/* func_02054240 @ 0x02054240, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056e60(void *a, int b);
extern unsigned short func_020550b8(int a, int b);
extern void func_02056fcc(void *a, int b, int c, int d, int e);
extern void NNS_G3dAnmObjInit(int a, int b, int c, int d);

struct UnkStruct_02054240 {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[0x56];
    int unk_5C;
    char pad_60[0xf4];
    int unk_154;
    void *unk_158;
    char pad_15C[0x14];
    void *unk_170;
};

void func_02054240(struct UnkStruct_02054240 *obj, int p2, int p3, int p4, int p5, unsigned short p6, unsigned short p7,
                   int p8)
{
    func_02056e60(&obj->unk_170, p3);
    if (p7 == 0) {
        p7 = func_020550b8(p4, p2);
    }
    func_02056fcc(&obj->unk_158, p7, p4, p5, p6);
    NNS_G3dAnmObjInit(obj->unk_154, p2, obj->unk_5C, 0);
    if (p8 != 0) {
        obj->unk_04 |= 0x8000;
    } else {
        obj->unk_04 &= ~0x8000;
    }
}
