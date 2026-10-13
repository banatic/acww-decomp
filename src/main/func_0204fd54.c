/* func_0204fd54 @ 0x0204fd54, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cb788[];

unsigned short func_0204fd54(unsigned int index)
{
    if (index >= 56) {
        return 10;
    }
    return *(unsigned short *) (data_020cb788 + index * 6);
}
