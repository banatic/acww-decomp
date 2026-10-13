/* func_ov120_0229bfe8 @ 0x0229bfe8, 0x28 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bfe8 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
};

extern int func_020ee45c(struct UnkStruct_0229bfe8 *obj);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_022080a0(struct UnkStruct_0229bfe8 *obj, int a);

int func_ov120_0229bfe8(struct UnkStruct_0229bfe8 *obj)
{
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    obj->unk_8C = 5;
    func_ov002_022080a0(obj, 1);
    return 1;
}
