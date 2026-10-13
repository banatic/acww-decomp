/* func_020b0074 @ 0x020b0074, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b00a8(unsigned int, unsigned int, unsigned char *);

int func_020b0074(unsigned int a, unsigned int b, unsigned char *arr)
{
    if (a < b && func_020b00a8(a, b, arr) == 0) {
        arr[a >> 3] |= (1 << (a & 7));
        return 1;
    }
    return 0;
}
