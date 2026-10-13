/* func_0209c310 @ 0x0209c310, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned func_0209c310(unsigned r0)
{
    unsigned result = 3;
    if (r0 < 5) {
        result = 0;
    } else {
        if (r0 < 8) {
            result = 1;
        } else {
            if (r0 < 12) {
                result = 2;
            }
        }
    }
    return result;
}
