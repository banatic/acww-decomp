/* func_ov066_02269748 @ 0x02269748, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_02269748;

typedef struct {
    unsigned char pad_00[0x96];
    unsigned char unk_96;
} UnkStruct_02269748_2;

extern UnkStruct_02269748 *data_ov066_0226bdec;
extern UnkStruct_02269748_2 *data_ov066_0226bdf4;

extern void func_ov066_0226978c(int a);
extern void func_ov066_02268c4c(void);

void func_ov066_02269748(int a)
{
    data_ov066_0226bdec->unk_04 = 6;
    data_ov066_0226bdf4->unk_96 = 0;
    func_ov066_0226978c(a);
    func_ov066_02268c4c();
}
