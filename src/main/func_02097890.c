/* func_02097890 @ 0x02097890, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(char *p);

int func_02097890(char *base, int n)
{
    int i;
    int count;
    count = 0;
    i = count;
    while (i < n) {
        if (func_02065ec0(base + (i << 8)) != 0) {
            count++;
        }
        i++;
    }
    return count;
}
