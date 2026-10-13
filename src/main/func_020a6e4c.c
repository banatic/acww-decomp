/* func_020a6e4c @ 0x020a6e4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7738(unsigned char *p, int a, int b, int c);
extern unsigned char data_021f4320[][3];

void func_020a6e4c(int index, int a, int b, int c)
{
    if (index < 4) {
        func_020a7738(data_021f4320[index], a, b, c);
    }
}
