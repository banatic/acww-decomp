/* func_02073cf0 @ 0x02073cf0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

void func_02073cf0(int arg0, int arg1, int arg2)
{
    int i;
    int *ptr;
    int result;

    i = arg1;
    result = func_02077b58(i);
    ptr = (int *) (arg0 + 0xc);
    ptr[result] += arg2;
}
