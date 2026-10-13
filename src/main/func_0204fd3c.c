/* func_0204fd3c @ 0x0204fd3c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_020cb784[];

int func_0204fd3c(unsigned int index)
{
    if (index >= 0x3b) {
        return 3;
    }
    return data_020cb784[index * 6];
}
