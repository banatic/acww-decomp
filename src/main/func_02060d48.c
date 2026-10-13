/* func_02060d48 @ 0x02060d48, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02060d48(unsigned char *data, int param)
{
    if (param >= 7) {
        int temp = data[0x15a3] + (param - 6);
        if (temp > 10) {
            temp = 10;
        }
        data[0x15a3] = (unsigned char) temp;
    }
}
