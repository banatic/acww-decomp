/* func_02081b54 @ 0x02081b54, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02081b54(void *arg)
{
    unsigned short h = *(unsigned short *) ((char *) arg + 0x7c);
    if ((((unsigned int) h << 28) >> 31) == 1) {
        return 1;
    } else {
        return 0;
    }
}
