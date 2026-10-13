/* func_020a0fac @ 0x020a0fac, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6ed0(void *p);
extern int func_02073dd4(int *p, int v);
extern void func_020a2444(void *p, int a, int b);
extern int func_020644cc(int n);
extern int *data_020ccf94;

void func_020a0fac(void *p)
{
    int x;
    int count;
    int i;
    int *ptr;
    int arr[4];
    int v;

    x = func_020a6ed0(p);
    count = 0;
    i = 3;
    ptr = data_020ccf94;
    while (i >= 0) {
        if (i != x && func_02073dd4(ptr, i)) {
            arr[count] = i;
            count++;
        }
        i--;
    }

    i = 3;
    while (i >= 0) {
        if (func_02073dd4(ptr, i)) {
            func_020a2444(p, i, i);
        } else {
            func_020a2444(p, i, 4);
        }
        i--;
    }

    v = arr[func_020644cc(count)];
    func_020a2444(p, v, x);
    func_020a2444(p, x, v);
}
