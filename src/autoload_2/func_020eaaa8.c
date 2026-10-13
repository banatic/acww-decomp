/* func_020eaaa8 @ 0x020eaaa8, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaaa8(void *p, int shift);

void func_020eaaa8(void *p, int shift)
{
    int *arr = (int *) p;
    arr[0] = arr[0] >> shift;
    arr[1] = arr[1] >> shift;
    arr[2] = arr[2] >> shift;
}
