/* func_02076f2c @ 0x02076f2c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_020736bc(void *arg1, int *arg2, int arg3);
extern int func_0209d3a8(int *arg);

int func_02076f2c(int arg)
{
    int local;
    func_020736bc(data_020ccf94, &local, arg);
    return func_0209d3a8(&local);
}
