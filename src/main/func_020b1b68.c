/* func_020b1b68 @ 0x020b1b68, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(int a, int b);
extern unsigned char data_021f4b10;

void func_020b1b68(int a, int b)
{
    if (b != 0) {
        OS_Terminate(a, b);
    }
    data_021f4b10 = 1;
}
