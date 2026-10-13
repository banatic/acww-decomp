/* func_0204fed0 @ 0x0204fed0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020dce11[];

unsigned char func_0204fed0(unsigned int x)
{
    if (x >= 4) {
        return 0xFF;
    }
    return data_020dce11[x * 12];
}
