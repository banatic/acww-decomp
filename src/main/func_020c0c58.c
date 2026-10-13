/* func_020c0c58 @ 0x020c0c58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Global2 {
    char pad_00[0x24];
    int unk_24;
} data_021f8ab0;

void func_020c0c58(int *param)
{
    int v;
    if (data_021f8ab0.unk_24 != 3 && data_021f8ab0.unk_24 != 4) {
        v = 0x1000;
    } else {
        v = 0;
    }
    param[0x1b] = v;
}
