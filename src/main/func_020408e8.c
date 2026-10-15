/* func_020408e8 @ 0x020408e8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7a8[];
extern void *func_020409c8(void *arg, int _x);
extern int func_020984d4(void);

int func_020408e8(int param, unsigned char flag)
{
    if (param == 0x45) {
        return 0;
    }
    {
        char *base;
        int result;
        unsigned char *p;
        int shift;

        base = data_021dc7a8;
        result = 0;
        if (param == 0x60) {
            param = 0x40;
        }
        p = func_020409c8(base + 0x17218, flag);
        if (p != 0) {
            if (param != p[2]) {
                result = 1;
            } else {
                shift = func_020984d4();
                flag = (unsigned char) ((p[5] >> shift) & 1);
                if (flag != 0) {
                    result = 1;
                }
            }
        }
        return result;
    }
}