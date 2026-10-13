/* func_ov108_0229ce00 @ 0x0229ce00, 0x68 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ce00 {
    int pad_00;
} UnkStruct_0229ce00;

typedef struct UnkStruct_0229ce00_2 {
    unsigned char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    unsigned char pad_AC[0x203];
    unsigned char unk_2AF;
    unsigned char pad_2B0[0x21d0];
    UnkStruct_0229ce00 sub2480;
} UnkStruct_0229ce00_2;

extern void func_ov002_02209d68(UnkStruct_0229ce00 *sub, int v1, int v2);
extern int func_ov108_0229cc20(UnkStruct_0229ce00_2 *obj, int value);
extern int func_ov108_0229cbe4(UnkStruct_0229ce00_2 *obj, int value);
extern void func_ov002_02209d38(UnkStruct_0229ce00 *sub, int v1, int v2, int v3);
extern void func_ov002_02209d8c(UnkStruct_0229ce00 *sub);
extern void func_ov108_0229c918(UnkStruct_0229ce00_2 *obj);
extern void func_ov002_02208098(UnkStruct_0229ce00_2 *obj, int value);

void func_ov108_0229ce00(UnkStruct_0229ce00_2 *obj, int arg1, int arg2)
{
    int retA, retB;

    obj->unk_2AF = arg1;
    func_ov002_02209d68(&obj->sub2480, obj->unk_A4, obj->unk_A8);
    retA = func_ov108_0229cc20(obj, arg1);
    retB = func_ov108_0229cbe4(obj, arg1);
    func_ov002_02209d38(&obj->sub2480, retA, retB, arg2);
    func_ov002_02209d8c(&obj->sub2480);
    func_ov108_0229c918(obj);
    func_ov002_02208098(obj, 18);
}
