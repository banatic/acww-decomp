/* func_ov100_0229e62c @ 0x0229e62c, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229e62c {
    unsigned char pad_00[0x28c8];
    int unk_28C8;
} UnkStruct_0229e62c;

extern int func_ov002_02207f48(UnkStruct_0229e62c *p, int arg);
extern int func_ov002_022080a0(UnkStruct_0229e62c *p, int arg);
extern void func_ov100_0229d8b0(UnkStruct_0229e62c *p);
extern int func_ov002_02207e80(UnkStruct_0229e62c *p, int arg1, int arg2, int arg3);
extern int func_ov002_02207f60(UnkStruct_0229e62c *p);

void func_ov100_0229e62c(UnkStruct_0229e62c *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov100_0229d8b0(p);
    }
    func_ov002_02207e80(p, 4, 0, 0);
    p->unk_28C8 = func_ov002_02207f60(p);
}
