/* func_ov121_0229b09c @ 0x0229b09c, 0x1e bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_02299aac(void *p, unsigned char b);
extern void func_ov121_0229afb8(void *p);

struct UnkStruct_0229b09c {
    char pad_00[0xb7];
    unsigned char unk_B7;
};

void func_ov121_0229b09c(struct UnkStruct_0229b09c *p)
{
    if (func_ov121_02299aac(p, p->unk_B7) != 0) {
        func_ov121_0229afb8(p);
    }
}
