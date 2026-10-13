/* func_02076f4c @ 0x02076f4c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, int *, int, int);
extern void func_020b25e0(int *, int);

void func_02076f4c(int param0, int param1, int param2, int param3)
{
    int local[2];
    func_020736bc(data_020ccf94, local, param0, param3);
    func_020b25e0(local, param3);
}
