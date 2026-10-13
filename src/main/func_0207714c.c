/* func_0207714c @ 0x0207714c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_020736bc(int, int *, int);
extern int func_020714a0(int *);

int func_0207714c(int a)
{
    int local;
    func_020736bc(data_020ccf94, &local, a);
    return func_020714a0(&local);
}
