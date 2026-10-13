/* func_ov054_02260484 @ 0x02260484, 0x14 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02260484;

extern UnkStruct_02260484 *data_020ccf94;
extern void func_02073dd4(UnkStruct_02260484 *p, int val);

void func_ov054_02260484(void)
{
    func_02073dd4(data_020ccf94, data_020ccf94->unk_64);
}
