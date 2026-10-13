/* func_0206e3f4 @ 0x0206e3f4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e438(int, int);
extern void func_0206e6c4(int, void *);
extern void OS_DisableInterrupts(void);
extern void OS_Halt(void);
extern unsigned char data_021cfb64;

extern unsigned char OSi_LauncherThread[];

void func_0206e3f4(int arg)
{
    OS_DisableInterrupts();
    func_0206e438(1, 1);
    if (data_021cfb64 == 0) {
        data_021cfb64 = 1;
        func_0206e6c4(arg, (void *) OSi_LauncherThread);
    }
    while (data_021cfb64 != 0) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
