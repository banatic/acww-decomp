/* func_0201c014 @ 0x0201c014, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c040(int a, int *b, int *c);

int func_0201c014(int param)
{
    int arr[3];
    arr[0] = 4;
    arr[1] = 4;
    if (func_0201c040(param, &arr[0], &arr[1]) != 0) {
        if (arr[1] < 4) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
