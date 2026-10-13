/* func_ov107_0229caa8 @ 0x0229caa8, 0x6c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
} UnkStruct_0229caa8;

extern int func_0206f6a4(UnkStruct_0229caa8 *p);
extern void func_02061e2c(unsigned short *dst, unsigned short *src);
extern int func_0209a19c(void);
extern void func_020984e8(void);
extern int func_020996ac(void);
extern void OSi_DoUnlockByWord__main_0203cd2c(int a, void *b, int c, int d);
extern void func_ov107_0229d0f0(UnkStruct_0229caa8 *p, unsigned char b);
extern void func_0206f698(void);
extern void func_ov107_0229d2d8(UnkStruct_0229caa8 *p, unsigned char b, int c, int d);

void func_ov107_0229caa8(UnkStruct_0229caa8 *param)
{
    unsigned short local[2];
    int val;
    int flag;
    int res;

    local[0] = (unsigned short) func_0206f6a4(param);
    func_02061e2c(&local[1], local);
    val = local[1];
    flag = 0;
    if (val == 0x156b) {
        val = func_0209a19c();
        flag = 1;
    }
    func_020984e8();
    res = func_020996ac();
    OSi_DoUnlockByWord__main_0203cd2c(res, &local[1], 0, 1);

    func_ov107_0229d0f0(param, param->unk_B9);
    func_0206f698();
    func_ov107_0229d2d8(param, param->unk_B9, val, flag);
}
