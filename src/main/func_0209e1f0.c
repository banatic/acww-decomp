/* func_0209e1f0 @ 0x0209e1f0, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0209e1f0(unsigned char *ptr, int val)
{
    int diff;
    diff = ptr[5] - val;
    if (diff < 0) {
        diff += 100;
    }
    ptr[5] = (unsigned char) diff;
}
