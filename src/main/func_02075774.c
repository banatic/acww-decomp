/* func_02075774 @ 0x02075774, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02075774 {
    char pad_00[0x68];
    void *unk_68;
} *data_020ccf94;

extern unsigned char func_02096284(void *a);
extern int func_0209847c(int index);
extern int func_020989e0(int object);
extern int func_02075ff8(int a, int b, int c, int d, int e);

int func_02075774(int param1)
{
    int ret;

    ret = func_020989e0(func_0209847c((int) func_02096284(data_020ccf94->unk_68)));
    return func_02075ff8(param1, ret, 0x3200, 0x16, 1);
}
