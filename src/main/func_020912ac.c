/* func_020912ac @ 0x020912ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d52d8;
extern void func_02091358(int *arg1, int arg2, int arg3, int arg4, short *arg5, int arg6);

void func_020912ac(int p0, short p1, int p2, int p3)
{
    short local = p1;
    func_02091358(&data_021d52d8, p0, p2, p3, &local, -1);
}
