/* func_020a86e4 @ 0x020a86e4, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020a87c8(unsigned int, int);

struct UnkStruct_020a86e4 {
    unsigned char pad_00[0xC];
    unsigned int unk_0C;
};

void func_020a86e4(struct UnkStruct_020a86e4 *s, unsigned char *out0, unsigned char *out1, unsigned char *out2)
{
    *out0 = func_020a87c8(s->unk_0C, 0);
    *out1 = func_020a87c8(s->unk_0C, 1);
    *out2 = func_020a87c8(s->unk_0C, 2);
}
