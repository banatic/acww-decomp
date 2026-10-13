/* func_02044540 @ 0x02044540, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02044540 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_02044540_2 {
    char pad_00[0x1c];
    unsigned char flag;
};

extern struct UnkStruct_02044540 *data_020ccf94;
extern struct UnkStruct_02044540_2 data_021c779c;

extern int func_02073dd4(struct UnkStruct_02044540 *ptr, int arg);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);

int func_02044540(void)
{
    int ret = 0;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto end;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        goto end;
    }
    if (data_021c779c.flag != 0) {
        goto end;
    }
    ret = 1;
end:
    return ret;
}
