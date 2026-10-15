/* func_020b0300 @ 0x020b0300, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b027c(int);
extern void func_020b026c(int);
extern unsigned int PM_GetBackLight(int, int);
extern int func_0211dc78(int, int);

extern unsigned char data_021f4ad4[];
extern unsigned char data_021f4ad8[];

void func_020b0300(void)
{
    int r0;
    int r1;

    r0 = func_020b027c(1);
    if (r0 == 0) {
        PM_GetBackLight((unsigned int) data_021f4ad8, (unsigned int) data_021f4ad4);
        func_0211dc78(2, 0);
        func_020b026c(1);
    }
}
