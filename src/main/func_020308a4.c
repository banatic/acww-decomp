/* func_020308a4 @ 0x020308a4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);

struct UnkStruct_020308a4 {
    unsigned char pad_00[300];
    int unk_12C;
};

extern struct UnkStruct_020308a4 *data_020da1a8;

int func_020308a4(int argument0, int argument1)
{
    int r;
    r = func_01ffcb2c((int) argument0, (int) argument1);
    if (r >= 104 && r <= 110) {
        r -= 104;
    } else {
        r = -1;
    }
    if (r < 0 || r == data_020da1a8->unk_12C) {
        r = -1;
    }
    return r;
}
