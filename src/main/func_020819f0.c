/* func_020819f0 @ 0x020819f0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020819f0(void *ptr)
{
    unsigned short v = *(unsigned short *) ((char *) ptr + 0x7c);
    if (((unsigned int) v << 27) >> 31) {
        return 1;
    } else {
        return 0;
    }
}
