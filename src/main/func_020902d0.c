/* func_020902d0 @ 0x020902d0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020902d0(int *arr, int v1, int v2)
{
    int i, found;
    found = 0;
    i = found;
    while (i < 10) {
        if (*arr == ~found) {
            *arr = v1;
            arr[1] = v2;
            found = 1;
            break;
        }
        arr += 2;
        i++;
    }
    return found;
}
