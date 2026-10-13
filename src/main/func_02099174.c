/* func_02099174 @ 0x02099174, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_02099174(unsigned char *base, unsigned int index)
{
    if (index < 8) {
        return (base + index)[0x2454];
    }
    return 0xff;
}
