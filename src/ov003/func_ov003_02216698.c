/* func_ov003_02216698 @ 0x02216698, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_022166e8(void *, int, int, int *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_02216698(void *arg1, int arg2, int arg3, int *arg4, int arg5, short arg6)
{
    int arg3_copy;
    int arr[2];
    char buf1[12];
    char buf2[20];
    int result;

    arg3_copy = arg3;
    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x4a, arg5, (int) arg6);
    arr[0] = arg4[0];
    arr[1] = arg4[1];
    func_ov003_022166e8(buf2, arg2, arg3_copy, arr);
    result = func_0200e894(arg1, buf1);
    func_0200e91c(buf1);
    return result;
}
