/* func_02092758 @ 0x02092758, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e27a8;
extern void func_02034270(void *, int, int, int);
extern int func_020b6598(int);
extern int func_02094cf8(int, int, int, int, int, int *);
extern void func_0203423c(void *);

int func_02092758(int a0, int a1, int a2, int a3)
{
    int arr[17];
    int v;
    int result;

    func_02034270(arr, a1, 0, 0);
    v = arr[13];
    result = -1;
    if (func_020b6598(0) != 0 && v == 3) {
        result = 0x8a;
    } else if (v == 0x13) {
        result = 0x89;
    }
    if (result != -1) {
        result = func_02094cf8(result, a0, a1, a2, a3, &data_020e27a8);
        func_0203423c(arr);
        return result;
    } else {
        func_0203423c(arr);
        return 3;
    }
}
