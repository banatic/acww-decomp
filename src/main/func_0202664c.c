/* func_0202664c @ 0x0202664c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202cbdc(void *dst, int a, int b, int c, int d);

struct UnkStruct_0202664c {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
};

void func_0202664c(unsigned short *out, struct UnkStruct_0202664c *in)
{
    *out = 0xfff1;
    if (func_0202cbdc(out, 1, 2, in->unk_04, in->unk_03) != 0) {
        return;
    }
    if (func_0202cbdc(out, 0, 0, in->unk_04, in->unk_03) != 0) {
        return;
    }
    func_0202cbdc(out, 3, 4, in->unk_04, in->unk_03);
}
