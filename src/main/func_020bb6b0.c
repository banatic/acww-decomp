/* func_020bb6b0 @ 0x020bb6b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_021f3b28[];
extern int func_020bb6a0(int a, int b, int c);

int func_020bb6b0(int a, int b)
{
    int rem = (b + data_021f3b28[4]) % 24;
    return func_020bb6a0(a, (unsigned char) data_021f3b28[2], rem);
}
