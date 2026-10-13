/* func_02076f9c @ 0x02076f9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int a, int *b, int c);
extern void func_020b2734(int *a);

void func_02076f9c(int param)
{
    int var;
    func_020736bc(data_020ccf94, &var, param);
    func_020b2734(&var);
}
