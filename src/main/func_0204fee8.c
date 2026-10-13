/* func_0204fee8 @ 0x0204fee8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020dce10[];

int func_0204fee8(unsigned int index)
{
    if (index >= 4) {
        return 9;
    } else {
        return data_020dce10[index * 12];
    }
}
