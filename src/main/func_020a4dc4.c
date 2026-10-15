/* func_020a4dc4 @ 0x020a4dc4, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_020b65c4(void);
extern void func_020a4e94(int, int);
extern unsigned char data_021c75b8;
extern int data_021f3c38;

void func_020a4dc4(int param)
{
    int v;
    unsigned int flag;

    v = func_020b65c4();
    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        if (v == 9) {
            if (data_021f3c38 == 0x12 || data_021f3c38 == 0x1f) {
                func_020a4e94(param, data_021f3c38);
                data_021f3c38 = 0;
            }
        } else if (v == 11) {
            if (data_021f3c38 == 0x13) {
                func_020a4e94(param, data_021f3c38);
                data_021f3c38 = 0;
            }
        } else if (v == 6) {
            if ((unsigned) (data_021f3c38 - 3) <= 1) {
                func_020a4e94(param, data_021f3c38);
                data_021f3c38 = 0;
            }
        } else if (v == 46) {
            func_020a4e94(param, data_021f3c38);
            data_021f3c38 = 0;
        }

        if (v == 12 && data_021f3c38 == 0x14) {
            func_020a4e94(param, data_021f3c38);
            data_021f3c38 = 0;
        }

        if (v == 47 || v == 13) {
            func_020a4e94(param, data_021f3c38);
            data_021f3c38 = 0;
        }
    }
}
