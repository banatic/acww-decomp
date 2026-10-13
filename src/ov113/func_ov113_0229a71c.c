/* func_ov113_0229a71c @ 0x0229a71c, 0x30 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a71c {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned char pad_98[2];
    unsigned char unk_9A;
};

extern void func_ov002_02208090(struct UnkStruct_0229a71c *p, int x);
extern int func_ov002_02207f60(struct UnkStruct_0229a71c *p);
extern void func_ov113_02299df4(struct UnkStruct_0229a71c *p, int x);
extern void func_ov113_02299d94(struct UnkStruct_0229a71c *p, int x);

void func_ov113_0229a71c(struct UnkStruct_0229a71c *p)
{
    func_ov002_02208090(p, 2);
    func_ov113_02299df4(p, p->unk_9A);
    p->unk_94 = func_ov002_02207f60(p);
    func_ov113_02299d94(p, 8);
}
