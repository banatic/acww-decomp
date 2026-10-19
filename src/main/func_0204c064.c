/* func_0204c064 @ 0x0204c064, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c078(int value);

int func_0204c064(int a, int b)
{
    return func_0204c078(((a & 3) << 3) + (b & 7));
}
