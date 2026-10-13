/* func_0202fa9c @ 0x0202fa9c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(void *dst, const void *src, int size);
extern int FX_MulFunc(int a, int b);

typedef struct {
    int pad_00;
    int arr0[3];
    int arr1[3];
    int arr2[3];
} SrcStruct;

int func_0202fa9c(const SrcStruct *src, int size)
{
    int X[3], Y[3], Z[3];
    int d1, d2, d3;

    func_020eaca0(X, &src->arr0[0], size);
    func_020eaca0(Y, &src->arr1[0], size);
    func_020eaca0(Z, &src->arr2[0], size);

    d1 = FX_MulFunc(X[0], Y[1]) - FX_MulFunc(X[1], Y[0]);
    d2 = FX_MulFunc(Y[0], Z[1]) - FX_MulFunc(Y[1], Z[0]);
    d3 = FX_MulFunc(Z[0], X[1]) - FX_MulFunc(Z[1], X[0]);

    if ((d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0)) {
        return 1;
    } else {
        return 0;
    }
}
