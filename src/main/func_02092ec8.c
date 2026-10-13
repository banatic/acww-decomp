/* func_02092ec8 @ 0x02092ec8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ba4e4(int);
extern int func_02094b58(int, int, int, int, int, void *);
extern int data_020e28d4[];

int func_02092ec8(int a, int b, int c, int d)
{
    if (func_020ba4e4(a) == 1) {
        return func_02094b58(0x74, a, b, c, d, data_020e28d4);
    }
    return 3;
}
