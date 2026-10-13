/* func_0206faf8 @ 0x0206faf8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfd08[];

void func_0206faf8(unsigned short *src)
{
    int i;
    for (i = 0; i < 15; i++) {
        data_021cfd08[i] = src[i];
    }
}
