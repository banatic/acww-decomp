/* func_0209a088 @ 0x0209a088, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(unsigned short *, int, int);
extern int func_02098f70(int);
extern int func_020996ac(int);
extern int func_02099734(int);
extern void func_02098f0c(int, unsigned short *, int, int);
extern void OSi_DoUnlockByWord__main_0203cd2c(int, void *, int, int);

void func_0209a088(unsigned short *p, int flag, int arg2)
{
    int h;
    int ret;
    int ok;
    unsigned short local;

    h = func_020984e8(p, flag, arg2);
    if (func_02098f70(arg2) == 0) {
        return;
    }
    if (*p != 0xfff1 && flag == 0) {
        ret = func_020996ac(h);
        OSi_DoUnlockByWord__main_0203cd2c(ret, p, 0, 1);
    }
    if (flag == 0) {
        ok = 0;
        if (*p >= 0x151f && *p <= 0x151f) {
            ok = 1;
        }
        if (ok != 0) {
            local = 0x1033;
            ret = func_020996ac(h);
            OSi_DoUnlockByWord__main_0203cd2c(ret, &local, 0, 1);
        }
    }
    ret = func_02099734(h);
    func_02098f0c(ret, p, arg2, flag);
}
