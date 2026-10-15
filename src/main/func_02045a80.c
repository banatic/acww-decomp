/* func_02045a80 @ 0x02045a80, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x68];
    void *unk_68;
} UnkStruct_02045a80;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02045a80_2;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02045a80_3;

extern UnkStruct_02045a80 *data_020ccf94;
extern int func_02045ac4(void *arg0, void *arg1);

int func_02045a80(UnkStruct_02045a80_2 *param)
{
    void *arg2;
    UnkStruct_02045a80_3 local;

    arg2 = data_020ccf94->unk_68;
    local.unk_00 = param->unk_00;
    local.unk_04 = param->unk_04;
    return func_02045ac4(&local, arg2);
}
