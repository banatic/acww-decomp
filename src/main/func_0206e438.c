/* func_0206e438 @ 0x0206e438, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int PXI_SendWordByFifo(int a, int b, int c);
extern void WaitByLoop(int a);

void func_0206e438(int param1, int param2)
{
    while (PXI_SendWordByFifo(0xe, param1, 0) != 0) {
        WaitByLoop(param2);
    }
}
