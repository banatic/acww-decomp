/* func_ov107_0229c354 @ 0x0229c354, 0x24 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0229c354;

extern UnkStruct_0229c354 *data_020ccf94;
extern int func_02073dd4(UnkStruct_0229c354 *obj, int val);

int func_ov107_0229c354(void)
{
    int field;
    field = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, field) != 0) {
        return (unsigned char) field;
    } else {
        return 0;
    }
}
