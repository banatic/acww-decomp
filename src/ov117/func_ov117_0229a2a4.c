/* func_ov117_0229a2a4 @ 0x0229a2a4, 0x24 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct entry {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
};

void func_ov117_0229a2a4(struct entry *arr, int idx, unsigned short v0, unsigned short v2, unsigned char v4)
{
    if (idx < 0x11) {
        arr[idx].unk_00 = v0;
        arr[idx].unk_02 = v2;
        arr[idx].unk_04 = v4;
    }
}
