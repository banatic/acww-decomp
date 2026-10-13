/* func_02075548 @ 0x02075548, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6f74(int a, int b, int c);
extern int func_020a6f54(unsigned short v);

int func_02075548(unsigned char *param)
{
    unsigned char b = *param;
    func_020a6f74(3, b & 7, 7);
    return func_020a6f54((unsigned short) ((b >> 4) & 0xF));
}
