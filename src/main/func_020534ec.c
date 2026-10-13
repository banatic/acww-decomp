/* func_020534ec @ 0x020534ec, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0204bc50(unsigned int a, unsigned int b);
extern unsigned int func_02053c88(unsigned int a);

unsigned char func_020534ec(unsigned int param)
{
    unsigned char count = 0;
    unsigned int i;
    for (i = 0; i < 0x6e9; i++) {
        volatile unsigned short tmp;
        tmp = func_0204bc50(i, 0);
        if (param == func_02053c88(i)) {
            count++;
        }
    }
    return count;
}
