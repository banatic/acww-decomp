/* func_020a6878 @ 0x020a6878, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7704(int *, int *, int *);

int func_020a6878(int *p)
{
    int arr[3];
    func_020a7704(p + 3, &arr[1], &arr[0]);
    return arr[1];
}
