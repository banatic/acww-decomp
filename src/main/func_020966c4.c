/* func_020966c4 @ 0x020966c4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int data_020d1884[];
extern int func_020738bc(int a, int b);

int func_020966c4(int param)
{
    return func_020738bc(data_020ccf94, data_020d1884[param]);
}
