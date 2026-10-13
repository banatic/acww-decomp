/* func_0200ee0c @ 0x0200ee0c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0200ee0c {
    char pad_00[0x64];
    int unk_64;
} *data_020ccf94;

struct UnkStruct_0200ee0c_2 {
    char pad_00[0x800];
    int unk_800;
};

extern int func_02073dd4(struct UnkStruct_0200ee0c *a, int b);

int func_0200ee0c(struct UnkStruct_0200ee0c_2 *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        return 0;
    }
    if (param->unk_800 == 0) {
        return 0;
    }
    return 1;
}
