/* func_020984e8 @ 0x020984e8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020984e8 {
    char pad_00[0x68];
    void *unk_68;
};

extern struct UnkStruct_020984e8 *data_020ccf94;
extern int func_020984fc(void *p);

int func_020984e8(void)
{
    return func_020984fc(data_020ccf94->unk_68);
}
