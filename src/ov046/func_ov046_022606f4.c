/* func_ov046_022606f4 @ 0x022606f4, 0x2c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);

struct Func_ov046_022606f4_Struct {
    char pad_00[0xdc];
    int unk_DC;
};

void func_ov046_022606f4(struct Func_ov046_022606f4_Struct *param, int cond)
{
    if (cond == 0) {
        if (func_020b1558() < 0x10) {
            param->unk_DC = 0x35;
        } else {
            param->unk_DC = 0x30;
        }
    } else {
        param->unk_DC = 0x2;
    }
}
