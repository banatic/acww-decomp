/* func_02001c30 @ 0x02001c30, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    char pad0[16];
    unsigned char field_10;
    char pad1[5];
    unsigned char field_16;
} data_0213fe74;

void func_02001c30(unsigned char param)
{
    data_0213fe74.field_16 = param;
    data_0213fe74.field_10 = (data_0213fe74.field_10 & ~3) | ((0xf78u >> (param * 2)) & 3);
}
