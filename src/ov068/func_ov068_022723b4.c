/* func_ov068_022723b4 @ 0x022723b4, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220174(int);
extern int func_ov009_02262ff8(int, int, int);

typedef struct {
    char pad_00[0x2db];
    unsigned char unk_2DB;
} UnkStruct_022723b4;

int func_ov068_022723b4(UnkStruct_022723b4 *param)
{
    int result = func_ov003_02220174(0x5000);
    if (result != 0) {
        param->unk_2DB = 0x10;
        return func_ov009_02262ff8(result, 0x2db, 0x10);
    }
    return 1;
}
