/* func_ov003_0221c8ac @ 0x0221c8ac, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221c724(void *param);
extern void *func_02055e00(int *ptr);
extern int func_ov009_02264cf8(void *param, int zero);
extern void func_02056440(int *dst, void *src, int val, int flag, int param1, unsigned char param2);

typedef struct {
    char pad_00[0x13c];
    int unk_13C;
    char pad_140[373];
    unsigned char unk_2B5;
    char pad_2B6[2];
    int unk_2B8;
} UnkStruct_0221c8ac;

int func_ov003_0221c8ac(UnkStruct_0221c8ac *param)
{
    void *ptr;
    int val;
    func_ov003_0221c724(param);
    ptr = func_02055e00(&param->unk_13C);
    val = func_ov009_02264cf8(param, 0);
    func_02056440(&param->unk_2B8, ptr, val, 1, 0x1000, param->unk_2B5);
    return 1;
}
