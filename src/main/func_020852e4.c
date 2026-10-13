/* func_020852e4 @ 0x020852e4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020738bc(int a, int b);
extern int data_020ccf94;

int func_020852e4(unsigned short *arg)
{
    unsigned int masked = ((unsigned int) *arg) & 0x0fff;
    int result;
    if (masked < 8) {
        result = func_020738bc(data_020ccf94, masked + 12);
    } else {
        result = 0;
    }
    return result;
}
