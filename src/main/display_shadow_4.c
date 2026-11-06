/* display_shadow_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001c58 @ 0x02001c58, 0x24 bytes, Thumb
 * func_02001c30 @ 0x02001c30, 0x28 bytes, Thumb
 * func_02001c08 @ 0x02001c08, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xd];
    unsigned char d;
    unsigned char e;
    unsigned char unk_0F;
    unsigned char g;
} UnkStruct_02001c58;

typedef struct {
    unsigned char pad_00[0x12];
    unsigned short h;
} UnkStruct_02001c58_2;

struct UnkStruct_02001c08 {
    unsigned char pad_00[16];
    unsigned char unk_10;
    unsigned char pad_11[6];
    unsigned char unk_17;
};

extern UnkStruct_02001c58 data_0213fe94;
extern UnkStruct_02001c58_2 data_0213fe74;

void func_02001c58(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    data_0213fe94.d = a;
    data_0213fe94.e = b;
    data_0213fe94.unk_0F = c;
    data_0213fe94.g = d;
    data_0213fe74.h |= 0x80;
}

void func_02001c30(unsigned char param)
{
    (*(struct {
        char pad0[16];
        unsigned char field_10;
        char pad1[5];
        unsigned char field_16;
    } *) &data_0213fe74)
        .field_16 = param;
    (*(struct {
        char pad0[16];
        unsigned char field_10;
        char pad1[5];
        unsigned char field_16;
    } *) &data_0213fe74)
        .field_10 = ((*(struct {
                         char pad0[16];
                         unsigned char field_10;
                         char pad1[5];
                         unsigned char field_16;
                     } *) &data_0213fe74)
                         .field_10 &
                     ~3) |
                    ((0xf78u >> (param * 2)) & 3);
}

void func_02001c08(unsigned char param)
{
    (*(struct UnkStruct_02001c08 *) &data_0213fe74).unk_17 = param;
    (*(struct UnkStruct_02001c08 *) &data_0213fe74).unk_10 =
        ((*(struct UnkStruct_02001c08 *) &data_0213fe74).unk_10 & ~0x0C) | ((0x3de0u >> (param << 1)) & 0x0C);
}
