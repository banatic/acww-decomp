/* func_ov112_022a168c @ 0x022a168c, 0x34 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a168c {
    char pad_00[0xA8];
    int unk_A8;
};

extern void func_ov112_0229f058(struct UnkStruct_022a168c *obj);
extern void func_ov002_02207f04(struct UnkStruct_022a168c *obj, int a, int b, int c, int d);
extern void func_ov002_02208090(struct UnkStruct_022a168c *obj, int a);
extern int func_ov002_02207f60(struct UnkStruct_022a168c *obj);

void func_ov112_022a168c(struct UnkStruct_022a168c *obj)
{
    func_ov112_0229f058(obj);
    func_ov002_02207f04(obj, 0, 0, 0, 0x30);
    func_ov002_02208090(obj, 7);
    obj->unk_A8 = func_ov002_02207f60(obj);
}
