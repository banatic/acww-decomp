/* func_02073cb8 @ 0x02073cb8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

void func_02073cb8(int *arr, int n)
{
    int idx = func_02077b58(n);
    *(arr + idx + 3) = 3;
}
