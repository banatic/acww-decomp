/* func_020902f8 @ 0x020902f8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020902f8(int *p, int key)
{
    int i, result;
    result = 0;
    i = result;
    while (i < 10) {
        if (key == p[0]) {
            result = p[1];
            break;
        }
        p += 2;
        i++;
    }
    return result;
}
