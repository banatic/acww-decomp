/* func_ov003_02220db4 @ 0x02220db4, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern void func_0204f818(int *x, int *y, int z);
extern int func_0204eda8(void *p, int x, int y);
extern int func_ov003_0222139c(void *data, int a, int *pair, int *arr, int b, int c, int d, int e);
extern char data_ov003_0223cfe4[];

int func_ov003_02220db4(int p1, int p2)
{
    void *p;
    int L0, L1;
    int pair[2];
    int arr[3];
    int err;

    p = func_0204e414();
    if (p == 0) {
        return 0;
    }

    L0 = 0;
    L1 = 0;
    func_0204f818(&L0, &L1, p2);
    err = (func_0204eda8(p, L0, L1) == 0) ? 0xfc : 0xfd;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    pair[0] = L0;
    pair[1] = L1;

    return func_ov003_0222139c(data_ov003_0223cfe4, p1, pair, arr, 0xa, err, 0, 0);
}
