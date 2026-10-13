/* func_0203f504 @ 0x0203f504, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203f504 {
    unsigned char data[0x1c];
};

extern struct UnkStruct_0203f504 data_021c72e8[15];

struct UnkStruct_0203f504 *func_0203f504(void)
{
    int i;
    unsigned int found;

    for (i = 0; i < 15; i++) {
        found = (data_021c72e8[i].data[0x14] == 0) ? 1 : 0;
        if (found > 0) {
            return &data_021c72e8[i];
        }
    }
    return 0;
}
