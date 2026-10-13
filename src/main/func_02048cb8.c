/* func_02048cb8 @ 0x02048cb8, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern int func_02048db8(void *, void *, void *, void *, int, int);
extern int func_02048d2c(void *, void *, int, Pair *, unsigned short, int);

int func_02048cb8(void *a0, void *a1, void *a2, int a3, unsigned short a4, int a5, int a6)
{
    Pair arr[0x100];
    Pair *p = arr;
    int flag = 0;
    int x;

    do {
        p->a = 0;
        p->b = 0;
        p++;
    } while (p != arr + 0x100);

    x = func_02048db8(a0, arr, a1, a2, a3, a5);
    if (func_02048d2c(a0, a1, x, arr, a4, a6) >= 0) {
        flag = 1;
    }
    return flag;
}
