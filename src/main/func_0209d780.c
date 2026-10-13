/* func_0209d780 @ 0x0209d780, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b5e10(int);
extern int func_020b6140(int, int, void *, void *, void *, void *, void *, void *, int, int);
extern int func_0209d7c8(int);
int func_0209d780(int param1)
{
    unsigned char arr[4];
    int localC;
    int localB;
    long long localA;
    if (func_020b6140(func_020b5e10(param1), param1, arr, &localA, &localB, &localC, &arr[2], &arr[1], 0, 0)) {
        return func_0209d7c8(arr[0]);
    }
    return 0;
}
