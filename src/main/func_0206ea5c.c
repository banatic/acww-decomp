/* func_0206ea5c @ 0x0206ea5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02136b98(unsigned int a, unsigned int b, int c);

struct UnkStruct_0206ea5c {
    unsigned int unk_00;
    unsigned int unk_04;
};

void func_0206ea5c(struct UnkStruct_0206ea5c *s, unsigned char *out)
{
    int i;
    for (i = 0; i < 16; i++) {
        out[i] = (unsigned char) (func_02136b98(s->unk_00, s->unk_04, i * 4) & 0xF);
    }
}
