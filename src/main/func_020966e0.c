/* func_020966e0 @ 0x020966e0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern unsigned int data_020d1874[];
extern int func_020738bc(unsigned int, unsigned int);

int func_020966e0(int param)
{
    return func_020738bc(data_020ccf94, data_020d1874[param]);
}
