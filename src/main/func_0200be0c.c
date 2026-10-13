/* func_0200be0c @ 0x0200be0c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_0200be0c;

void func_0200be0c(UnkStruct_0200be0c *out, const unsigned int *src, unsigned int val)
{
    out->unk_04 = (unsigned char) src[0];
    out->unk_05 = (unsigned char) src[1];
    out->unk_00 = val;
}
