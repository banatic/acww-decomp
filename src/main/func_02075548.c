/* func_02075548 @ 0x02075548, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a6f74(int a, int b);
extern void func_020a6f54(unsigned short v);

void func_02075548(unsigned char *payload, unsigned int length, int player)
{
    unsigned char b = *payload;
    func_020a6f74(3, b & 7);
    func_020a6f54((unsigned short) ((b >> 4) & 0xF));
}
