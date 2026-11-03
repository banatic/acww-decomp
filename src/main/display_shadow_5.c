/* display_shadow_5: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001d1c @ 0x02001d1c, 0xc bytes, Thumb
 * func_02001d0c @ 0x02001d0c, 0x10 bytes, Thumb
 * func_02001d00 @ 0x02001d00, 0xc bytes, Thumb
 * func_02001cf4 @ 0x02001cf4, 0xc bytes, Thumb
 * func_02001ce8 @ 0x02001ce8, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char value;
} unk_struct;

extern unsigned char data_0213fe74[];

void func_02001d1c(unsigned char arg)
{
    data_0213fe74[0x1a] = arg;
}

void func_02001d0c(unsigned char mask)
{
    data_0213fe74[0x1a] &= ~mask;
}

void func_02001d00(unsigned char param)
{
    (*(unk_struct *) data_0213fe74).value = param;
}

void func_02001cf4(unsigned char value)
{
    data_0213fe74[0x1c] = value;
}

void func_02001ce8(unsigned char value)
{
    data_0213fe74[0x1d] = value;
}
