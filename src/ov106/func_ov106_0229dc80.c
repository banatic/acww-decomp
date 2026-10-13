/* func_ov106_0229dc80 @ 0x0229dc80, 0x2e bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229dc80 {
    unsigned char pad_00[0xa0];
    int unk_A0;
};

extern int func_ov002_02207f48(struct UnkStruct_0229dc80 *p, int flag);
extern int func_ov002_02207f60(struct UnkStruct_0229dc80 *p);
extern void func_ov106_0229d6a4(struct UnkStruct_0229dc80 *p);

void func_ov106_0229dc80(struct UnkStruct_0229dc80 *self)
{
    int result1;
    int result2;
    result1 = func_ov002_02207f48(self, -1);
    result2 = func_ov002_02207f60(self);
    self->unk_A0 = result2;
    if (result1 != 0) {
        func_ov106_0229d6a4(self);
    }
}
