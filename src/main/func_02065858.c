/* func_02065858 @ 0x02065858, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02065858 {
    char pad_00[0x168];
    short unk_168;
};
extern struct UnkStruct_02065858 *data_021cd864;
short func_02065858(void)
{
    return data_021cd864->unk_168;
}
