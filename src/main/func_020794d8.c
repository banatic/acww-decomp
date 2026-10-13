/* func_020794d8 @ 0x020794d8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020794d8 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_020794d8_2 {
    char unk_00;
    unsigned char unk_01;
};

extern struct UnkStruct_020794d8 *data_020ccf94;
extern int func_02073dd4(struct UnkStruct_020794d8 *, int);

int func_020794d8(struct UnkStruct_020794d8_2 *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && param->unk_01 == 0) {
        return 1;
    } else {
        return param->unk_01;
    }
}
