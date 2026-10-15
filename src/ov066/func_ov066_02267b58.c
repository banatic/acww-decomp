/* func_ov066_02267b58 @ 0x02267b58, 0x88 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02267b58;
struct UnkStruct_02267b58_2;
struct UnkStruct_02267b58_3;
struct UnkStruct_02267b58_4;

struct UnkStruct_02267b58 {
    unsigned char pad_00[0x8e];
    unsigned char unk_8E;
    unsigned char pad_8F[0x95 - 0x8e - 1];
    unsigned char unk_95;
};

struct UnkStruct_02267b58_2 {
    struct UnkStruct_02267b58_4 *first;
    unsigned int second;
};

struct UnkStruct_02267b58_3 {
    unsigned char pad_00[0x22];
    unsigned short unk_22;
};

struct UnkStruct_02267b58_4 {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
};

extern struct UnkStruct_02267b58 *data_ov066_0226bdf4;
extern struct UnkStruct_02267b58_2 *data_ov066_0226bdf0;
extern struct UnkStruct_02267b58_3 *data_ov066_0226bdec;

extern unsigned char func_ov066_02267db4(unsigned char);

void func_ov066_02267b58(void)
{
    struct UnkStruct_02267b58_4 *out = data_ov066_0226bdf0->first;
    data_ov066_0226bdf4->unk_8E = func_ov066_02267db4(data_ov066_0226bdf4->unk_95);
    out->unk_00 = data_ov066_0226bdf0->second;
    out->unk_04 = data_ov066_0226bdf4->unk_8E;
    out->unk_06 = data_ov066_0226bdec->unk_22;
    out->unk_08 = 0xff;
    out->unk_09 = 0xff;
    out->unk_0A = 0xff;
    out->unk_0B = 0xff;
    out->unk_0C = 0xff;
    out->unk_0D = 0xff;
}
