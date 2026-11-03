/* creature_table_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204fd54 @ 0x0204fd54, 0x18 bytes, Thumb
 * func_0204fd3c @ 0x0204fd3c, 0x18 bytes, Thumb
 */

extern unsigned char data_020cb788[];
extern const unsigned char data_020cb784[];

unsigned short func_0204fd54(unsigned int index)
{
    if (index >= 56) {
        return 10;
    }
    return *(unsigned short *) (data_020cb788 + index * 6);
}

int func_0204fd3c(unsigned int index)
{
    if (index >= 0x3b) {
        return 3;
    }
    return data_020cb784[index * 6];
}
