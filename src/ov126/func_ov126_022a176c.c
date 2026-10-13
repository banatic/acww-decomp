/* func_ov126_022a176c @ 0x022a176c, 0x50 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a176c {
    char pad_00[0x3dc4];
    char member;
};

extern int func_ov002_02207f3c(struct UnkStruct_022a176c *p, int val);
extern void func_ov002_02207eb4(struct UnkStruct_022a176c *p, int a, int b);
extern int func_ov126_0229f7c8(struct UnkStruct_022a176c *p, int val);
extern void func_ov002_0220a9e4(char *s, int val);
extern void func_ov002_02208090(struct UnkStruct_022a176c *p, int val);

void func_ov126_022a176c(struct UnkStruct_022a176c *p)
{
    if (func_ov002_02207f3c(p, -1) == 0) {
        return;
    }

    func_ov002_02207eb4(p, 0, 0);
    if (func_ov126_0229f7c8(p, 0x40) != 0) {
        func_ov002_0220a9e4(&p->member, 0x87);
    } else {
        func_ov002_0220a9e4(&p->member, 0x22);
    }
    func_ov002_02208090(p, 8);
}
