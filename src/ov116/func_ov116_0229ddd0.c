/* func_ov116_0229ddd0 @ 0x0229ddd0, 0x28 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *obj, int n);

struct UnkStruct_0229ddd0 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x94 - 0x8e];
    unsigned char unk_94;
    char pad_95[0x142c - 0x95];
    unsigned char unk_142C;
};

void func_ov116_0229ddd0(struct UnkStruct_0229ddd0 *obj)
{
    func_ov002_0220a164(&obj->unk_94);
    obj->unk_142C = obj->unk_8D;
    func_ov002_02208098(obj, 5);
}
