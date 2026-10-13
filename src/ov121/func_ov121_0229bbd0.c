/* func_ov121_0229bbd0 @ 0x0229bbd0, 0x38 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bbd0 {
    char pad_00[0x94];
    int unk_94;
};

extern int func_ov002_02207f48(struct UnkStruct_0229bbd0 *s, int x);
extern void func_ov002_022080a0(struct UnkStruct_0229bbd0 *s, int x);
extern void func_ov121_0229afb8(struct UnkStruct_0229bbd0 *s);
extern void func_ov002_02207e80(struct UnkStruct_0229bbd0 *s, int a, int b, int c);
extern int func_ov002_02207f60(struct UnkStruct_0229bbd0 *s);

void func_ov121_0229bbd0(struct UnkStruct_0229bbd0 *s)
{
    if (func_ov002_02207f48(s, 0) != 0) {
        func_ov002_022080a0(s, 2);
        func_ov121_0229afb8(s);
    }
    func_ov002_02207e80(s, 6, 0, 0);
    s->unk_94 = func_ov002_02207f60(s);
}
