/* func_0203e55c @ 0x0203e55c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203e55c {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
};

extern struct UnkStruct_0203e55c *data_021c72b8;
extern int (*data_020daaa0[])(struct UnkStruct_0203e55c *);
extern void func_0203df6c(void);

void func_0203e55c(void)
{
    if (data_021c72b8->unk_14 == 4) {
        if (data_020daaa0[data_021c72b8->unk_15](data_021c72b8) != 0) {
            func_0203df6c();
        }
    }
}
