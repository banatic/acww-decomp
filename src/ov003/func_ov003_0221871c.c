/* func_ov003_0221871c @ 0x0221871c, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221871c {
    int unk_00;
    int unk_04;
    short unk_08;
    char unk_0A;
};

void func_ov003_0221871c(struct UnkStruct_0221871c *out, char fA, int f0, int f4, short f8)
{
    out->unk_0A = fA;
    out->unk_00 = f0;
    out->unk_04 = f4;
    out->unk_08 = f8;
}
