/* func_ov003_02216ab8 @ 0x02216ab8, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(char *);
extern void func_0200e90c(char *, int, int, short);
extern void func_ov003_02216b08(char *, int, int, int *);
extern int func_0200e894(int, char *);
extern void func_0200e91c(char *);

int func_ov003_02216ab8(int arg1, int arg2, int arg3, int *arg4, int arg5, short arg6)
{
    int pair[2];
    char buf1[12];
    char buf2[20];
    int result;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x49, arg5, arg6);
    pair[0] = arg4[0];
    pair[1] = arg4[1];
    func_ov003_02216b08(buf2, arg2, arg3, pair);
    result = func_0200e894(arg1, buf1);
    func_0200e91c(buf1);
    return result;
}
