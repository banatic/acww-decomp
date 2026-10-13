/* func_0203ad58 @ 0x0203ad58, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *data_021c67a4;

void func_0203ad58(void)
{
    unsigned int *ptr;
    unsigned int *addr;

    ptr = data_021c67a4;
    addr = (unsigned int *) ((unsigned char *) ptr + 0xc8);
    *addr = 0;
}
