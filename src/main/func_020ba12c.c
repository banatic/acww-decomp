/* func_020ba12c @ 0x020ba12c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020ba12c(void *arg0);

unsigned char func_020ba12c(void *arg0)
{
    unsigned char val;
    unsigned int val2;

    val2 = *(unsigned int *) ((unsigned char *) arg0 + 8);
    val2 = val2 >> 0xb;
    val = (unsigned char) (val2 & 0xff);
    val = (unsigned char) (val + 1);
    return val;
}
