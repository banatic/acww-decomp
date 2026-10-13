/* func_020a7dac @ 0x020a7dac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43f0;
extern unsigned char data_021f43f4;

int func_020a7dac(void)
{
    if (data_021f43f0 != 0 && data_021f43f4 != 0) {
        return 1;
    }
    return 0;
}
