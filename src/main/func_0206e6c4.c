/* func_0206e6c4 @ 0x0206e6c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020012ec(void);
extern void OS_SetUserExceptionHandler(int param1, int param2);

extern int data_0213fde0;

void func_0206e6c4(int param1)
{
    OS_SetUserExceptionHandler(0, 0);
    data_0213fde0 = param1;
    func_020012ec();
}
