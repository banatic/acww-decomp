/* func_ov068_0226eca8 @ 0x0226eca8, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226eca8 {
    char pad_00[0x26c];
    int unk_26C;
    int unk_270;
    char pad_274[0x94];
    int unk_308;
    char pad_30C[0x4];
    int unk_310;
    char pad_314[0x82];
    short unk_396;
    unsigned char unk_398;
} UnkStruct_0226eca8;

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int, int);
extern void func_ov068_0226fcbc(UnkStruct_0226eca8 *);
extern void func_020ee470(UnkStruct_0226eca8 *);

void func_ov068_0226eca8(UnkStruct_0226eca8 *obj)
{
    short val;
    obj->unk_270 = obj->unk_26C;
    val = FX_SinCosTable_[((unsigned short) obj->unk_396 >> 4) * 2 + 1];
    obj->unk_308 = -FX_MulFunc(0x100, val);
    obj->unk_310 = FX_MulFunc(0x100, val);
    obj->unk_396 += 0x3800;
    if (obj->unk_398 != 0) {
        obj->unk_398--;
    }
    if (obj->unk_398 == 0) {
        func_ov068_0226fcbc(obj);
        func_020ee470(obj);
    }
}
