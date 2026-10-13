/* func_020c3760 @ 0x020c3760, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(int);

int func_020c3760(int r0)
{
    int result;

    result = func_02014868(r0 + 0x618);
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}
