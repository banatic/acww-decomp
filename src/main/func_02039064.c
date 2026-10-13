/* func_02039064 @ 0x02039064, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c6730;
extern void func_02038eec(int arg);

void func_02039064(int arg)
{
    if (data_021c6730 > 0) {
        data_021c6730--;
    }
    func_02038eec(arg);
}
