/* func_0206f5e4 @ 0x0206f5e4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cfc60;
extern unsigned char data_021cfc90[];

unsigned char func_0206f5e4(unsigned char input)
{
    if (input == 0xFF) {
        input = data_021cfc60;
    }
    return data_021cfc90[input];
}
