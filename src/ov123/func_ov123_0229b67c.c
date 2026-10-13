/* func_ov123_0229b67c @ 0x0229b67c, 0x52 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b67c {
    unsigned char pad_00[0xac];
    unsigned char unk_AC;
    unsigned char pad_AD[2];
    unsigned char unk_AF;
};

extern void func_ov123_02299d00(struct UnkStruct_0229b67c *);
extern void func_ov123_02299d44(struct UnkStruct_0229b67c *);
extern int func_ov123_0229ae7c(struct UnkStruct_0229b67c *, unsigned char);
extern void func_020041bc(int);
extern void func_ov002_02207fb0(struct UnkStruct_0229b67c *, int, int, int);
extern void func_ov002_02208098(struct UnkStruct_0229b67c *, int);
extern void func_ov002_02207fc0(struct UnkStruct_0229b67c *);

void func_ov123_0229b67c(struct UnkStruct_0229b67c *param)
{
    if (param->unk_AC == 2) {
        func_ov123_02299d00(param);
        func_ov002_02207fb0(param, 5, 0, 5);
        func_ov002_02208098(param, 4);
        func_020041bc((unsigned char) func_ov123_0229ae7c(param, param->unk_AF));
    } else {
        func_ov123_02299d44(param);
        func_ov002_02207fc0(param);
        func_ov002_02208098(param, 3);
    }
}
