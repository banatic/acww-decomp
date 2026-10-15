/* func_02043e88 @ 0x02043e88, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pair;
extern int data_021c7c48;
extern int func_0204482c(int);
extern int func_02042f20(int *, int, int, Pair *, int, int, int, int, int, int);

int func_02043e88(int a0, unsigned short *a1, int *a2, int a3)
{
    Pair tmp;
    int ret;
    unsigned short v;

    ret = -1;
    if (func_0204482c(a0) != 0) {
        v = *a1;
        tmp.x = a2[0];
        tmp.y = a2[1];
        ret = func_02042f20(&data_021c7c48, a0, 0xf, &tmp, v, v, 0, 0, a3, -1);
    }
    return ret;
}
