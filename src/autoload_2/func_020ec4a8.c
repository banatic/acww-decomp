/* func_020ec4a8 @ 0x020ec4a8, 0xa0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_020ec848(void);
extern int func_020ec5ac(void);
extern void func_020edb14(void);
extern int func_020ec548(void);

int func_020ec4a8(void)
{
    unsigned char v = data_021fbef8;
    if ((unsigned char) (v + 0xff) <= 1) {
        return func_020ec848();
    }
    if (v == 3 || v == 4) {
        while (func_020ec5ac() == 0) {
            func_020edb14();
        }
        data_021fbef8 = 6;
        return 1;
    }
    if (v == 5) {
        return func_020ec548();
    }
    return 0;
}
