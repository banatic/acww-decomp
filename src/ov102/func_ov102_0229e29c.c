/* func_ov102_0229e29c @ 0x0229e29c, 0x6c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e29c {
    char pad_00[0x24d4];
    int unk_24D4;
};

extern int func_ov002_02207f3c(struct UnkStruct_0229e29c *p, int a);
extern void func_020027f0(int size);
extern void func_ov102_0229c288(struct UnkStruct_0229e29c *p, int a);
extern void func_ov002_02207f04(struct UnkStruct_0229e29c *p, int a, int b, int c, int d);
extern void func_ov002_02207e80(struct UnkStruct_0229e29c *p, int a, int b, int c);
extern void func_ov002_02208090(struct UnkStruct_0229e29c *p, int a);
extern void func_ov102_0229e24c(struct UnkStruct_0229e29c *p);
extern int func_ov002_02207f60(struct UnkStruct_0229e29c *p);

void func_ov102_0229e29c(struct UnkStruct_0229e29c *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        func_ov102_0229c288(param, 0x80);
        func_ov002_02207f04(param, 8, 0, 0, 0x30);
        func_ov002_02207e80(param, 6, 0, 0);
        func_ov002_02208090(param, 6);
        func_ov102_0229e24c(param);
    } else {
        func_ov002_02207e80(param, 4, 0, 0);
        param->unk_24D4 = func_ov002_02207f60(param);
    }
}
