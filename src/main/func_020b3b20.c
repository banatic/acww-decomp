/* func_020b3b20 @ 0x020b3b20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f4b2c;

int func_020b3b20(void)
{
    if (data_021f4b2c) {
        data_021f4b2c = 0;
        return 1;
    }
    return 0;
}
