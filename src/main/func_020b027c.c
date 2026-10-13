/* func_020b027c @ 0x020b027c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4acc[];

int func_020b027c(unsigned char arg_0)
{
    unsigned char temp;
    unsigned char *ptr;

    ptr = (unsigned char *) data_021f4acc;
    temp = *ptr;
    temp &= arg_0;
    if (temp != 0) {
        return 1;
    }
    return 0;
}
