/* func_02050920 @ 0x02050920, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_02050920(unsigned short *data, int length)
{
    unsigned short sum = 0;

    if (length & 1) {
        goto done;
    }

    while (length != 0) {
        sum = (unsigned short) (sum + *data);
        data++;
        length -= 2;
    }

done:
    return sum;
}
