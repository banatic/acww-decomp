/* func_0204fa68 @ 0x0204fa68, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204fa68(int r0);

int func_0204fa68(int r0)
{
    if (r0 < 0 || r0 >= 0x38) {
        return 0;
    }
    if (r0 >= 0x23) {
        return 3;
    }
    if (r0 >= 9 && r0 <= 0xb) {
        return 2;
    }
    return 1;
}
