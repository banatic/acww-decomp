/* func_020bb608 @ 0x020bb608, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_020e5e0c[];
extern void *data_021fbe94;
extern int func_02064b2c(int, void *, int, void *);
extern int func_02064af4(int, int, int);

typedef struct {
    char pad_00[0x1570];
    int unk_1570;
} UnkStruct_020bb608;

int func_020bb608(UnkStruct_020bb608 *param0, int *param1, int *param2, int param3, int param4)
{
    int result = 0;
    int idx;
    int val;
    if (param3 == 0) {
        int t = param4 * 2;
        idx = t + param0->unk_1570;
    } else {
        idx = param4;
    }
    val = data_020e5e0c[param3][idx];
    if (*param1 == 0) {
        *param1 = func_02064b2c(val, data_021fbe94, -4, param2);
        if (*param1 != 0) {
            result = 1;
        }
    } else {
        if (func_02064af4(val, *param1, *param2) != 0) {
            result = 1;
        }
    }
    return result;
}
