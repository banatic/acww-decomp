/* func_ov142_0229a05c @ 0x0229a05c, 0x1e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a05c {
    char pad_00[0xa4];
    void *unk_A4;
} UnkStruct_0229a05c;

extern void func_ov142_02299f8c(UnkStruct_0229a05c *p);
extern void func_ov142_0229a09c(UnkStruct_0229a05c *p);

void func_ov142_0229a05c(UnkStruct_0229a05c *p)
{
    if (p->unk_A4 == 0) {
        func_ov142_02299f8c(p);
    } else {
        func_ov142_0229a09c(p);
    }
}
