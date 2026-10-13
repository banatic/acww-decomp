/* func_020770a0 @ 0x020770a0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, int *, int);
extern int func_02052b20(int *);

int func_020770a0(int arg)
{
    int local;
    func_020736bc(data_020ccf94, &local, arg);
    return func_02052b20(&local);
}
