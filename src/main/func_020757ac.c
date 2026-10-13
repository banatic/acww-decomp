/* func_020757ac @ 0x020757ac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020757ac {
    char pad_00[0x68];
    void *unk_68;
} *data_020ccf94;

extern int func_02096284(void *arg);
extern int func_0209847c(int arg);
extern int func_02075ff8(void *a, int b, int c, int d, int e);

int func_020757ac(void *param)
{
    int x;
    x = func_0209847c(func_02096284(data_020ccf94->unk_68));
    return func_02075ff8(param, x, 0x249c, 0x15, 1);
}
