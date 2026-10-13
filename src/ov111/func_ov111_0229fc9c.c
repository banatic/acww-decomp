/* func_ov111_0229fc9c @ 0x0229fc9c, 0x14 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_020398d4(unsigned int);
struct UnkStruct_0229fc9c {
    char unk_00[0x64];
    unsigned int unk_64;
};
extern struct UnkStruct_0229fc9c *data_020ccf94;

int func_ov111_0229fc9c(void)
{
    return func_020398d4(data_020ccf94->unk_64);
}
