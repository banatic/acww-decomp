/* func_020931a4 @ 0x020931a4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020932b4(int a, int b, int c, int d, int e, void *f);
extern int data_020e2790;
extern int data_020e27b8;

int func_020931a4(int a, int b, int c, int d)
{
    if (func_020932b4(a, b, c, d, 0x57, &data_020e2790) == 1) {
        return func_020932b4(a, b, c, d, 0x57, &data_020e27b8);
    }
    return 3;
}
