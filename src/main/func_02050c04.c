/* func_02050c04 @ 0x02050c04, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02050c04 {
    int unk_00;
    int unk_04;
} data_020cb9bc[];

struct UnkStruct_02050c04 *func_02050c04(int index)
{
    return &data_020cb9bc[index];
}
