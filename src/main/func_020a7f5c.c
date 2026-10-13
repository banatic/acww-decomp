/* func_020a7f5c @ 0x020a7f5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dcc(void);

struct UnkStruct_020a7f5c {
    unsigned char pad_00[2];
    unsigned short unk_02;
};
extern struct UnkStruct_020a7f5c data_021fbe40;

int func_020a7f5c(void)
{
    int ret = 0;
    if (!func_020a7dcc()) {
        if (data_021fbe40.unk_02 & 0x80) {
            ret = 1;
        }
    }
    return ret;
}
