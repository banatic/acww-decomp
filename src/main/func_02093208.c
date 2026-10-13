/* func_02093208 @ 0x02093208, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020932b4(int a, int b, int c, int d, int e, int f);

extern unsigned char data_020e2780[];
extern unsigned char data_020e27ac[];

int func_02093208(int a, int b, int c, int d)
{
    if (func_020932b4(a, b, c, d, 0x57, (unsigned int) data_020e27ac) == 1) {
        return func_020932b4(a, b, c, d, 0x57, (unsigned int) data_020e2780);
    } else {
        return 3;
    }
}
