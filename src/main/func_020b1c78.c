/* func_020b1c78 @ 0x020b1c78, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_SetIrqFunction(int, void (*)(void));
extern void func_01ffcc60(void);
extern int data_021cfb90[];
extern int data_021cfb98[];
extern unsigned char data_021cfb68;

void func_020b1c78(void)
{
    int *p0;
    int *p1;
    int i;

    p0 = data_021cfb90;
    p1 = data_021cfb98;

    p0[1] = 0;
    p0[0] = 0;
    p1[1] = 0;
    p1[0] = 0;

    OS_SetIrqFunction(1, func_01ffcc60);

    data_021cfb68 = 1;
}
