/* func_02038d30 @ 0x02038d30, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(int p);
extern void func_020a8c1c(int p);
extern int data_020da530;

int func_02038d30(int param)
{
    func_020a8cac(param);
    *(int *) param = (int) &data_020da530;
    func_020a8c1c(param);
    return param;
}
