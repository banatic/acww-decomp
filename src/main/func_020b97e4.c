/* func_020b97e4 @ 0x020b97e4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9808(int, int, void *);
extern void OS_VSNPrintf(void *, int);

void func_020b97e4(int arg0, int arg1)
{
    char local_84[0x81];

    OS_VSNPrintf(local_84, 0x81);
    func_020b9808(arg0, arg1, local_84);
}
