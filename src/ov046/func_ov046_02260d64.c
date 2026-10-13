/* func_ov046_02260d64 @ 0x02260d64, 0x32 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260d64;

struct UnkStruct_02260d64 {
    char pad_00[0xdc];
    int unk_DC;
};

extern int func_020644cc(int);
extern int func_ov046_022610fc(struct UnkStruct_02260d64 *);

void func_ov046_02260d64(struct UnkStruct_02260d64 *param)
{
    int r = func_020644cc(0x65);
    if (r < 0x46) {
        param->unk_DC = func_ov046_022610fc(param);
    } else if (r < 0x55) {
        param->unk_DC = 0x32;
    } else {
        param->unk_DC = 0x33;
    }
}
