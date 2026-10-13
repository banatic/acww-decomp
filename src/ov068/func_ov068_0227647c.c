/* func_ov068_0227647c @ 0x0227647c, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0227647c;

extern int func_020984e8(UnkStruct_0227647c *param);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);

void func_ov068_0227647c(UnkStruct_0227647c *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8(param);
    if (a == 0) {
        return;
    }
    if (param->unk_830 == 0) {
        return;
    }
    b = func_02099870(a);
    c = func_020804b8(param->unk_830, b);
    func_02081e14(c, 0, 0, 0);
}
