/* func_020a186c @ 0x020a186c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a186c {
    unsigned char pad_00[0x50];
    int unk_50;
};
extern struct UnkStruct_020a186c *data_021f3c3c;

int func_020a186c(void)
{
    if (data_021f3c3c != 0 && data_021f3c3c->unk_50 == 0) {
        return 1;
    }
    return 0;
}
