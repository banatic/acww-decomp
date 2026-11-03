/* game_variables: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d368 @ 0x0209d368, 0x4 bytes, Thumb
 * func_0209d358 @ 0x0209d358, 0x10 bytes, Thumb
 */

extern unsigned char data_021dc5c0[][2]; // 0x021dc5c0

int func_0209d368(int id, int index)
{
    return 0;
}

unsigned short *func_0209d358(unsigned short param0, unsigned short param1)
{
    unsigned char *base;
    unsigned short *result;

    base = (unsigned char *) data_021dc5c0;
    base += (param0 << 8);
    result = (unsigned short *) (base + (param1 << 1));
    return result;
}
