/* func_02057a60 @ 0x02057a60, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02057a60(void *arg0);

unsigned int func_02057a60(void *arg0)
{
    unsigned int val;
    unsigned short val2;
    unsigned int val3;

    val3 = *(unsigned int *) ((int) arg0 + 0x14) & 0x1c000000;
    if ((val3 >> 0x1a) == 2) {
        val2 = *(unsigned short *) ((int) arg0 + 0x1c);
        val = (unsigned int) val2 << 3;
    } else {
        val2 = *(unsigned short *) ((int) arg0 + 0x1c);
        val = (unsigned int) val2 << 4;
    }
    return val;
}
