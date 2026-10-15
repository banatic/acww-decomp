/* func_02019eb0 @ 0x02019eb0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02019eb0 {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x04];
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned char pad_24[0x2a];
    unsigned short unk_4E;
    unsigned char pad_50[0x32];
    unsigned short unk_82;
    unsigned char pad_84[0x15];
    unsigned char unk_99;
    unsigned char pad_9A[0x02];
    unsigned int unk_9C;
    unsigned short unk_A0;
    unsigned char pad_A2[0x02];
    unsigned int unk_A4;
    unsigned char unk_A8;
    unsigned char unk_A9;
    unsigned char pad_AA[0x02];
    unsigned int unk_AC;
    unsigned int unk_B0;
} UnkStruct_02019eb0;

extern void func_02019d78(UnkStruct_02019eb0 *param);
extern void func_02019af0(UnkStruct_02019eb0 *param, int arg);

UnkStruct_02019eb0 *func_02019eb0(UnkStruct_02019eb0 *param)
{
    param->unk_4E = 0xfff1;
    param->unk_82 = 0xfff1;
    param->unk_1C = 0x16;
    param->unk_20 = 0;
    param->unk_14 = 0;
    func_02019d78(param);
    func_02019af0(param, 1);
    param->unk_99 = 0;
    param->unk_9C = 0;
    param->unk_A0 = 0;
    param->unk_A4 = 0;
    param->unk_A8 = 1;
    param->unk_A9 = 0;
    param->unk_B0 = 5;
    param->unk_AC = -1;
    return param;
}
