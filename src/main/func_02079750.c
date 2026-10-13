/* func_02079750 @ 0x02079750, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_020797bc(int, int);
extern int data_020ccf94;

int func_02079750(int param)
{
    int ret;

    ret = func_02073d90(data_020ccf94);
    if (ret != 0) {
        return ret;
    }
    return func_020797bc(2, param);
}
