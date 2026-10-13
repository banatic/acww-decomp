/* func_020966fc @ 0x020966fc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int data_020d1864[];
extern int func_020738bc(int, int);

int func_020966fc(int param)
{
    return func_020738bc(data_020ccf94, data_020d1864[param]);
}
