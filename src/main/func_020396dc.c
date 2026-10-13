/* func_020396dc @ 0x020396dc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020396dc {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_020396dc *data_020ccf94;

int func_020396dc(int unused, int value)
{
    return (value - data_020ccf94->unk_64 + 4) % 4;
}
