/* func_0209de24 @ 0x0209de24, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1aec[];
extern unsigned char data_020d1af8[];

unsigned char func_0209de24(unsigned int a, unsigned int index)
{
    if ((a & 3) == 0) {
        return data_020d1aec[index - 1];
    } else {
        return data_020d1af8[index - 1];
    }
}
