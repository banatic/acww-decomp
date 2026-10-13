/* func_ov096_0229cbbc @ 0x0229cbbc, 0x24 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *arg0, int arg1);

typedef struct UnkStruct_0229cbbc {
    char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_0229cbbc;

extern UnkStruct_0229cbbc *data_020ccf94;

unsigned char func_ov096_0229cbbc(void)
{
    unsigned int field = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, field) != 0) {
        return (unsigned char) field;
    }
    return 0;
}
