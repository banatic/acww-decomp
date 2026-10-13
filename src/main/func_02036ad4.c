/* func_02036ad4 @ 0x02036ad4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(unsigned short value);

struct unknown {
    char pad_00[12];
    unsigned short unk_0C;
};

void func_02036ad4(struct unknown *data)
{
    if (data->unk_0C != 0xFFFF) {
        func_02035638(data->unk_0C);
        data->unk_0C = 0xFFFF;
    }
}
