/* func_020a536c @ 0x020a536c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e3c7c;
extern unsigned short data_020e3c80;
extern void *data_021dc740;

extern void func_02116a1c(int);
extern int func_0202f134(int, void *, int, int);

int func_020a536c(void)
{
    if (data_020e3c7c != 0 || data_020e3c80 == 0xd8) {
        return 0;
    }

    if (data_020e3c80 == 2) {
        func_02116a1c(1);
    }

    {
        int result = func_0202f134(data_020e3c80, data_021dc740, 0, 2);
        if (result != 0) {
            data_020e3c80 = 0xd8;
            data_020e3c7c = 1;
            return result;
        }
        return 0;
    }
}
