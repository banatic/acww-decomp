/* func_0206eae4 @ 0x0206eae4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cfc0c;

int func_0206eae4(int r0)
{
    int r1;
    int r2;
    int result;

    r1 = data_021cfc0c;
    r2 = r0 & r1;
    if (r0 == r2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
