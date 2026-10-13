/* func_0207a244 @ 0x0207a244, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207a244(char *arr, unsigned int index, char value)
{
    if (index < 4) {
        (arr + index)[8] = value;
        return 1;
    } else {
        return 0;
    }
}
