/* func_02076f2c @ 0x02076f2c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *arg1, int *arg2, int arg3);
extern int func_0209d3a8(int *arg);

void func_02076f2c(int arg, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc(data_020ccf94, &local, arg);
    func_0209d3a8(&local);
}
