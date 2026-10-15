/* func_ov066_0226a00c @ 0x0226a00c, 0x68 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0226a00c;
extern struct UnkStruct_0226a00c_2;

struct UnkStruct_0226a00c {
    int pad_00;
    int unk_04;
};

struct UnkStruct_0226a00c_2 {
    char pad_00[0x8d];
    char unk_8D;
};

extern struct UnkStruct_0226a00c *data_ov066_0226bdec;   // 0x0226bdec
extern struct UnkStruct_0226a00c_2 *data_ov066_0226bdf4; // 0x0226bdf4
extern char data_ov066_0226bdfc;                         // 0x0226bdfc
extern short data_ov066_0226be00;                        // 0x0226be00
extern short data_ov066_0226be04;                        // 0x0226be04

int func_ov066_02269f6c(int);

void func_ov066_0226a00c(void)
{
    struct UnkStruct_0226a00c_2 *p;
    data_ov066_0226bdec->unk_04 = 5;
    data_ov066_0226bdfc = 0;
    data_ov066_0226be00 = 0;
    data_ov066_0226be04 = 0x65;
    p = data_ov066_0226bdf4;
    p->unk_8D = 0;
    func_ov066_02269f6c(0);
}
