/* func_020984d4 @ 0x020984d4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096284(int);
struct UnkStruct_020984d4 {
    unsigned char pad_00[0x68];
    int unk_68;
};
extern struct UnkStruct_020984d4 *data_020ccf94;
int func_020984d4(void)
{
    return func_02096284(data_020ccf94->unk_68);
}
