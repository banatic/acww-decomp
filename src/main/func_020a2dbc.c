/* func_020a2dbc @ 0x020a2dbc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a259c(int a, int b);
extern void func_020a01b4(int a);
extern int func_020a4e94(int a, int b);

int func_020a2dbc(int param)
{
    int result;

    result = func_020a259c(param, 1);
    if (result == 0) {
        return result;
    }
    func_020a01b4(result);
    return func_020a4e94(param, 0x1d);
}
