/* func_02034aa8 @ 0x02034aa8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_02232054(int);
extern int func_02034b80(int, int, int, int);

int func_02034aa8(int arg0)
{
    int flag;

    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        func_02034b80(func_ov004_02232054(flag), 0, 0, arg0);
        return 1;
    }
    return 0;
}
