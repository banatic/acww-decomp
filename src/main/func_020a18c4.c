/* func_020a18c4 @ 0x020a18c4, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c38[];

void func_020a18c4(void)
{
    unsigned int *ptr;
    unsigned int value;

    value = 0x18;
    ptr = (unsigned int *) data_021f3c38;
    *ptr = value;
}
