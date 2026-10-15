/* func_0205d978 @ 0x0205d978, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205dad0(void);

int func_0205d978(int *arr, int idx, int flag)
{
    if (flag == 1) {
        int v = arr[idx];
        return v + func_0205dad0();
    } else {
        return arr[idx];
    }
}
