/* func_ov066_02267c0c @ 0x02267c0c, 0x68 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02267c0c *data_ov066_0226bdec;
extern struct UnkStruct_02267c0c_2 *data_ov066_0226bdf4;
extern void func_ov066_02267b58(void);
extern void func_ov066_02267740(void);

struct UnkStruct_02267c0c {
    int unk_00;
    int unk_04;
    char pad_08;
    unsigned char unk_09;
};

struct UnkStruct_02267c0c_2 {
    char pad_00[0x95];
    unsigned char unk_95;
};

void func_ov066_02267c0c(void)
{
    data_ov066_0226bdec->unk_04 = 7;
    func_ov066_02267b58();
    func_ov066_02267740();
    data_ov066_0226bdf4->unk_95 = data_ov066_0226bdf4->unk_95 + 1;
    if (data_ov066_0226bdf4->unk_95 >= data_ov066_0226bdec->unk_09) {
        data_ov066_0226bdf4->unk_95 = 0;
    }
}
