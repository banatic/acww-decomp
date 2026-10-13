/* func_0206ed2c @ 0x0206ed2c, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfc28;
extern unsigned short data_021cfc20;
extern unsigned char data_020e54a8;
extern int data_021cfc24;

int FX_MulFunc(int a, int b);
void func_0206fd54(int x);
void func_020ba518(void);
void func_02001c30(int x);

int func_0206ed2c(void)
{
    int val;
    unsigned int flag;
    int ret;

    val = data_021cfc28;
    if (val == 0) {
        data_021cfc20 = 6;
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag > 0) {
            func_020ba518();
        }
        func_02001c30(0);
        return 1;
    } else {
        if (val > data_021cfc24) {
            data_021cfc28 = val - data_021cfc24;
        } else {
            data_021cfc28 = 0;
        }
        ret = FX_MulFunc(data_021cfc28, data_021cfc28);
        func_0206fd54(0x1000 - ret);
        return 1;
    }
}
