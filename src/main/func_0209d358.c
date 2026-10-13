/* func_0209d358 @ 0x0209d358, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc5c0[][2]; // 0x021dc5c0

unsigned short *func_0209d358(unsigned short param0, unsigned short param1)
{
    unsigned char *base;
    unsigned short *result;

    base = (unsigned char *) data_021dc5c0;
    base += (param0 << 8);
    result = (unsigned short *) (base + (param1 << 1));
    return result;
}
