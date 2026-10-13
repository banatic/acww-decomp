/* func_ov003_02221228 @ 0x02221228, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0223cfe4;
extern int func_0204e414(int param1, int param2);
extern void func_0204f818(int *outX, int *outY, int param3);
extern int func_0204eda8(int obj, int x, int y);
extern int func_ov003_0222139c(char *obj, int a, void *pair, int *arr, int c1, int c2, int c3, int c4);

struct Pair {
    int x;
    int y;
};

int func_ov003_02221228(int a, int b)
{
    int r6;         // returned from func_0204e414
    int x, y;       // coordinates
    int status;     // result from func_0204eda8
    int code;       // 0xFC or 0xFD
    struct Pair pr; // pair to pass
    int arr[3];     // zeroed array

    r6 = func_0204e414(a, b);
    if (r6 == 0) {
        return 0;
    }

    x = 0;
    y = 0;
    func_0204f818(&x, &y, b);

    status = func_0204eda8(r6, x, y);
    code = (status == 0) ? 0xFC : 0xFD;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;

    pr.x = x;
    pr.y = y;

    return func_ov003_0222139c(&data_ov003_0223cfe4, a, &pr, arr, 2, code, 0, 0);
}
