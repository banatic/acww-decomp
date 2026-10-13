/* func_020b74f0 @ 0x020b74f0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c38;
extern unsigned char data_021f6c34;
extern int func_020b7524(int, int, int);

int func_020b74f0(int a, int b, int c)
{
    int flag;
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return func_020b7524(a, b, c);
    }
    return 0;
}
