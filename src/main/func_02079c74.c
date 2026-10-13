/* func_02079c74 @ 0x02079c74, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02079c74(int p0, int p1, int p2)
{
    int sum = 0;
    int low = p1;
    int high = p2;
    int i;
    if (p1 > p2) {
        low = p2;
        high = p1;
    }
    for (i = 0; i < low; i++) {
        sum += 7 - i;
    }
    sum += high - low - 1;
    return sum;
}
