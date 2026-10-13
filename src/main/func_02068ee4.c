/* func_02068ee4 @ 0x02068ee4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_020cce90[];

// O: inline (*pp + row*32)[col]
void func_02068ee4(unsigned short **pp, int index)
{
    int row = 15;
    int col;
    const unsigned char *p = data_020cce90 + index;

    for (; row <= 24; row++) {
        for (col = 1; col <= 30; col++) {
            unsigned short v = (*pp + row * 32)[col] & 0xffff0fff;
            (*pp + row * 32)[col] = v | ((unsigned) (p[0] << 28) >> 16);
        }
    }
}
