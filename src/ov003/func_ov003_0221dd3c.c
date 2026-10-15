/* func_ov003_0221dd3c @ 0x0221dd3c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221dc7c(int);
extern void func_ov003_0221dc38(int);
extern int func_ov009_0226321c(int, int *, int *);
extern int func_02003348(int, int, int *, int, int);

int func_ov003_0221dd3c(int arg)
{
    int arr[4];

    func_ov003_0221dc7c(arg);
    func_ov003_0221dc38(arg);

    if (func_ov009_0226321c(arg, &arr[1], &arr[0])) {
        arr[1] -= 0x2000;
        arr[3] += 0x1000;
        func_02003348(0x24, 0x501d, &arr[1], 0, 0);
    }

    return 1;
}
