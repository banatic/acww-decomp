/* func_ov104_0229e09c @ 0x0229e09c, 0x30 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *ptr);
extern void func_ov002_02208098(void *ptr, int value);
extern void func_ov104_0229dbd8(void *p, unsigned char c);

struct UnkStruct_0229e09c {
    char pad_00[0xb8];
    unsigned char unk_B8;
};

void func_ov104_0229e09c(struct UnkStruct_0229e09c *p)
{
    if (func_ov002_02209f9c((char *) p + 0x24a0)) {
        func_ov104_0229dbd8(p, p->unk_B8);
        func_ov002_02208098(p, 0x11);
    }
}
