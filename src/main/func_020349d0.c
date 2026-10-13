/* func_020349d0 @ 0x020349d0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c5204[];

int func_020349d0(unsigned int idx, unsigned short *src)
{
    if (idx < 0x33) {
        data_021c5204[idx] = *src;
        return 1;
    }
    return 0;
}
