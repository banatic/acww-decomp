/* func_020824d0 @ 0x020824d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cd550[];

unsigned char *func_020824d0(unsigned short *p)
{
    int index;
    int type;
    unsigned char *result = 0;

    index = *p & 0x0fff;
    type = (*p & 0xf000) >> 12;
    if (type == 0xd && index < 38) {
        result = data_020cd550 + index * 3;
    }
    return result;
}
