/* func_02050bf8 @ 0x02050bf8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02050bf8 {
    int unk_00;
    int unk_04;
} data_020cba34[];

struct UnkStruct_02050bf8 *func_02050bf8(int index)
{
    return &data_020cba34[index];
}
