/* func_0209dd9c @ 0x0209dd9c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209dd9c(const unsigned char *a, const unsigned char *b)
{
    int result = 1;
    if (a[2] < b[2]) {
        result = 0;
    } else if (a[2] != b[2]) {
        // do nothing
    } else {
        if (a[1] < b[1]) {
            result = 0;
        } else if (a[1] != b[1]) {
            // do nothing
        } else {
            if (a[0] < b[0]) {
                result = 0;
            }
        }
    }
    return result;
}
