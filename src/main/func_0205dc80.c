/* func_0205dc80 @ 0x0205dc80, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned long func_0205dce0(void *ptr, unsigned char byte);

extern unsigned char data_021c9e24[];

unsigned long func_0205dc80(unsigned char *data)
{
    return func_0205dce0((void *) data_021c9e24, *data);
}
