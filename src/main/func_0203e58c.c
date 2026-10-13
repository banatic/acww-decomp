/* func_0203e58c @ 0x0203e58c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0203e58c {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
} *data_021c72b8;
extern int (*data_020da9ec[])(struct UnkStruct_0203e58c *);

void func_0203e58c(void)
{
    if (data_021c72b8->unk_14 == 3) {
        if (data_020da9ec[data_021c72b8->unk_15](data_021c72b8) != 0) {
            data_021c72b8->unk_14 = 4;
        }
    }
}
