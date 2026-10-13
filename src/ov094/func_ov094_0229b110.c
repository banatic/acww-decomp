/* func_ov094_0229b110 @ 0x0229b110, 0x24 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

int func_ov094_0229b110(int *bits, int n)
{
    int result = 1;
    int mask = result << (n & 31);
    if (!(mask & bits[n >> 5])) {
        result = 0;
    }
    return result;
}
