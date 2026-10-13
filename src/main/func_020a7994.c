/* func_020a7994 @ 0x020a7994, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a7994;

void func_020a7994(UnkStruct_020a7994 *obj, char *str)
{
    int i = 0;
    obj->unk_04 = 0;
    while (str[i] != 0 || str[i + 1] != 0) {
        int val = ((str[i + 1] << 8) & 0x0000ff00) | (str[i] & 0xff);
        if (val >= 0x0000ac00 && val <= 0x0000d7a3) {
            obj->unk_04 = val;
        }
        i += 2;
    }
}
