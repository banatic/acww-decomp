/* func_020e9974 @ 0x020e9974, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9a08(unsigned int);

typedef struct UnkStruct_020e9974 {
    char pad_00[0x6c];
    unsigned int unk_6C;
} UnkStruct_020e9974;

typedef struct UnkStruct_020e9974_2 {
    int unk_00;
    UnkStruct_020e9974 *unk_04;
} UnkStruct_020e9974_2;

extern UnkStruct_020e9974_2 OSi_ThreadInfo;
extern unsigned int data_021fbe9c[];

void func_020e9974(void)
{
    unsigned int idx = OSi_ThreadInfo.unk_04->unk_6C;
    func_020e9a08(data_021fbe9c[idx]);
    data_021fbe9c[idx] = 0;
}
