/* func_0203d4d8 @ 0x0203d4d8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Struct0203d4d8 {
    char pad_00[0x24];
    int unk_24;
};
extern int data_020ca4ac[];
int func_0203d4d8(struct Struct0203d4d8 *arg0)
{
    return data_020ca4ac[arg0->unk_24];
}
