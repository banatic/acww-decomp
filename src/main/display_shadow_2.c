/* display_shadow_2: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001b6c @ 0x02001b6c, 0x10 bytes, Thumb
 * func_02001b60 @ 0x02001b60, 0xc bytes, Thumb
 * func_02001b54 @ 0x02001b54, 0xc bytes, Thumb
 * func_02001b44 @ 0x02001b44, 0x10 bytes, Thumb
 * func_02001b34 @ 0x02001b34, 0x10 bytes, Thumb
 * func_02001b28 @ 0x02001b28, 0xc bytes, Thumb
 * func_02001b1c @ 0x02001b1c, 0xc bytes, Thumb
 * func_02001b0c @ 0x02001b0c, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned char value;
} Global;

struct UnkStruct_0213FE74 {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
};

typedef struct {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
} UnkStruct_02001b1c;

extern unsigned char data_0213fe74[];

void func_02001b6c(unsigned char r0)
{
    data_0213fe74[0x19] &= ~r0;
}

unsigned char func_02001b60(void)
{
    return data_0213fe74[0x14];
}

void func_02001b54(unsigned char arg)
{
    (*(Global *) data_0213fe74).value = arg;
}

void func_02001b44(unsigned char param)
{
    data_0213fe74[0x14] |= param;
}

void func_02001b34(unsigned char mask)
{
    data_0213fe74[0x14] &= ~mask;
}

unsigned char func_02001b28(void)
{
    return (*(struct UnkStruct_0213FE74 *) data_0213fe74).unk_15;
}

void func_02001b1c(unsigned char value)
{
    (*(UnkStruct_02001b1c *) data_0213fe74).unk_15 = value;
}

void func_02001b0c(int arg)
{
    data_0213fe74[0x15] |= arg;
}
