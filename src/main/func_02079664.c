/* func_02079664 @ 0x02079664, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_02079690(int);
extern void func_020797bc(int, int);

void func_02079664(int param)
{
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_02079690(param) != 0) {
            func_020797bc(6, param);
        }
    }
}
