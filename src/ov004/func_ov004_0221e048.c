/* func_ov004_0221e048 @ 0x0221e048, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0221e048;

extern int func_020984e8(void);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);

void func_ov004_0221e048(UnkStruct_0221e048 *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8();
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
