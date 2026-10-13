/* func_0202feec @ 0x0202feec, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da18c[];

struct UnkStruct_0202feec {
    unsigned char *unk_00;
    char pad_04[0x24];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
};

void func_0202feec(struct UnkStruct_0202feec *param)
{
    param->unk_00 = data_020da18c;
    param->unk_28 = 0;
    param->unk_2C = 0;
    param->unk_30 = 0;
    param->unk_34 = 0;
}
