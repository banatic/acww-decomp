/* func_02044910 @ 0x02044910, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_0204f5e0(int, int, int, int, int, int);
extern void func_02044958(int, int *, int);

void func_02044910(int *a, int b)
{
    int c = func_0204e414();

    if (c != 0) {
        int a0 = a[0];
        int a1 = a[1];
        int hx = a0 >> 4;
        int hy = a1 >> 4;
        int low1 = a1 - (hy << 4);
        int low0 = a0 - (hx << 4);
        int res = func_0204f5e0(c, hx, hy, low0, low1, 0);

        if (res != 0) {
            int arr[2];

            arr[0] = a[0];
            arr[1] = a[1];
            func_02044958(res, arr, b);
        }
    }
}
