/* func_ov129_0229c520 @ 0x0229c520, 0x26 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xae];
    unsigned char flag;
} UnkStruct_0229c520;

extern int func_ov129_0229b7ec(UnkStruct_0229c520 *arg, int value);

int func_ov129_0229c520(UnkStruct_0229c520 *arg)
{
    if (func_ov129_0229b7ec(arg, 2) != 0) {
        return 0;
    }
    if (arg->flag == 4) {
        return 1;
    }
    return 0;
}
