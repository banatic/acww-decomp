/* func_020a82f8 @ 0x020a82f8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d1d70[];

int func_020a82f8(int r0)
{
    return (int) (data_020d1d70 + r0 * 10);
}
