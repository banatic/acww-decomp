/* func_020682e0 @ 0x020682e0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cda88;

int func_020682e0(int a0)
{
    int result = 0;
    if (data_021cda88 != 0) {
        result = data_021cda88 + a0 * 0x1e9c;
    }
    return result;
}
