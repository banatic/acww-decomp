/* func_02034664 @ 0x02034664, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02034664(unsigned char *arr)
{
    int i = 0;
    unsigned char *p = arr + 1;
    while (p < arr + 5) {
        if (((arr[0] >> i) & 1) && (*p < 3)) {
            (*p)++;
        } else {
            *p = 0xff;
            arr[0] &= ~(1 << i);
        }
        i++;
        p++;
    }
}
