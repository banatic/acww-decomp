/* func_020019cc @ 0x020019cc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020019cc {
    unsigned char unk_00[0x12];
    unsigned char unk_12;
};

extern struct UnkStruct_020019cc data_0213fe94;

void func_020019cc(void)
{
    data_0213fe94.unk_12 |= 0x20;
}
