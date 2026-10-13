/* func_02034f78 @ 0x02034f78, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02034f78(unsigned char *ptr, int *value)
{
    int i = -1;
    int n = *(int *) (ptr + 0x1c0);
    if (n < 16) {
        for (i = 0; i < n; i++) {
            if (*(int *) (ptr + i * 28) > *value) {
                break;
            }
        }
    }
    return i;
}
