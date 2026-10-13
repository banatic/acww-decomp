/* func_0205e138 @ 0x0205e138, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c9f5c[];
extern int func_0205e508(unsigned char *data, unsigned char byte, int flag);

int func_0205e138(const unsigned char *src, int flag)
{
    return func_0205e508(data_021c9f5c, *src, flag);
}
