/* func_0209ffb0 @ 0x0209ffb0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec1e8(void);
extern int func_020749c4(void);
extern int func_020984e8(void);
extern int func_0209985c(void);
extern void func_0209fd54(void);
extern void func_0209fcd8(void);
extern void func_0209fc60(void);
extern void func_020a01f8(void);
extern int func_020a1518(void);
extern int func_020682e0(int);
extern void func_02068358(void);
extern void func_02068434(int);
extern void func_0206844c(int, unsigned char *, unsigned char *);
extern unsigned char data_020e3c2c[];

int func_0209ffb0(void)
{
    int flag = 0;
    int ret;
    unsigned char byte;

    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        flag = 1;
    }

    ret = func_020749c4();

    if (flag) {
        if (func_020984e8()) {
            int idx = func_0209985c();
            if (idx >= 0 && idx < 4) {
                func_0209fd54();
                func_0209fcd8();
                func_0209fc60();
                func_020a01f8();
                if (func_020a1518()) {
                    int handle = func_020682e0(0);
                    func_02068358();
                    func_02068434(handle);
                    byte = 2;
                    func_0206844c(handle, &byte, data_020e3c2c);
                }
            }
        }
    }

    return ret;
}
