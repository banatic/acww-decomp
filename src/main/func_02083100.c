/* func_02083100 @ 0x02083100, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1a2c;

struct UnkStruct_02083100 {
    void *unk_00;
    char unk_04;
};

void func_02083100(struct UnkStruct_02083100 *param)
{
    param->unk_00 = &data_020e1a2c;
    param->unk_04 = -1;
}
