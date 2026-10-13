/* func_0203e5c0 @ 0x0203e5c0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0203e5c0 {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
} *data_021c72b8;
extern int (*data_020daa64[])(struct UnkStruct_0203e5c0 *);

void func_0203e5c0(void)
{
    if (data_021c72b8->unk_14 == 2) {
        if (data_020daa64[data_021c72b8->unk_15](data_021c72b8) != 0) {
            data_021c72b8->unk_14 = 3;
        }
    }
}
