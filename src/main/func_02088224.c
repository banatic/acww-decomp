/* func_02088224 @ 0x02088224, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088220(int);
extern void func_02072d58(int, int);
extern int func_02072d4c(int);
extern void func_02072f54(int, int);

void func_02088224(int param)
{
    func_02072d58(func_02088220(param), 0xf);
    func_02072f54(func_02072d4c(func_02088220(param)), 0);
}
