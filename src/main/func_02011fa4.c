/* func_02011fa4 @ 0x02011fa4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011e48(void *ptr, int val);
extern void func_02039800(void);

extern unsigned char data_021c1284[];

void func_02011fa4(void)
{
    func_02011e48((void *) data_021c1284, 0);
    func_02039800();
}
