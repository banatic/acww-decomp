/* func_0201aa10 @ 0x0201aa10, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096190(int);
extern int func_020954c0(int *arr, int c);
extern void func_0201aa94(int a, int b, int c, int *arr, int d, unsigned char e);

void func_0201aa10(int a, int b, int c, int d, unsigned char e)
{
    int tmp1;
    int arr1[3];
    int arr2[3];

    tmp1 = func_02096190(c);
    if (tmp1 != 0) {
        if (func_020954c0(arr1, c) != 0) {
            arr2[0] = arr1[0];
            arr2[1] = arr1[1];
            arr2[2] = arr1[2];
            func_0201aa94(a, b, tmp1, arr2, d, e);
        }
    }
}
