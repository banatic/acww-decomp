/* func_020b2300 @ 0x020b2300, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned char func_020b65c4(int flag);
extern int func_020b232c(int param);

int func_020b2300(void)
{
    int flag = (data_020e54a8 == 1);
    if (flag) {
        return func_020b232c(func_020b65c4(flag));
    }
    return 0;
}
