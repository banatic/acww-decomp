/* func_ov004_0222be7c @ 0x0222be7c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0222be7c; // unused

struct UnkStruct_0222be7c {
    unsigned char pad_00[0x7f0];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
};

extern struct UnkStruct_0222be7c *func_02096718(int arg);
extern unsigned int func_02008258(struct UnkStruct_0222be7c *ptr, unsigned int val);
extern int func_ov004_0222acf0(struct UnkStruct_0222be7c *ptr, int a, int b);

int func_ov004_0222be7c(void)
{
    struct UnkStruct_0222be7c *p = func_02096718(4);
    if (p != 0) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        return func_ov004_0222acf0(p, 5, -1);
    } else {
        return 0;
    }
}
