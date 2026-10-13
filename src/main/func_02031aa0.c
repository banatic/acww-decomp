/* func_02031aa0 @ 0x02031aa0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int param);

typedef struct {
    short value;
    char pad_02[28];
} Entry_020c9082;

extern Entry_020c9082 data_020c9082[];

int func_02031aa0(int param)
{
    int idx;
    short s;
    int result;

    idx = func_01ffcb2c(param);
    if (idx < 0x7c) {
        s = data_020c9082[idx].value;
        if (s > 0) {
            result = 1;
        } else {
            result = s;
        }
    } else {
        result = -1;
    }
    return result;
}
