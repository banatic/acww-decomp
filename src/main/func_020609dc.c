/* func_020609dc @ 0x020609dc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02060a14(int a, int b);

extern unsigned char data_021ed268[];

void func_020609dc(unsigned int param0)
{
    if (param0 >= 0x1323 && param0 <= 0x1368) {
        int delta;
        if (param0 >= 0x1323 && param0 <= 0x1368) {
            delta = param0 - 0x1323;
        } else {
            delta = -1;
        }
        func_02060a14((unsigned int) data_021ed268, delta);
    }
}
