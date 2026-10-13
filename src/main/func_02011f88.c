/* func_02011f88 @ 0x02011f88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011e48(unsigned int, int);
extern void func_02039800(void);

extern unsigned char data_021c1284[];

void func_02011f88(void)
{
    unsigned int *addr = (unsigned int *) data_021c1284;
    func_02011e48((unsigned int) addr, 2);
    func_02039800();
}
