/* func_02079774 @ 0x02079774, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *arg);
extern int func_020797bc(int arg0, void *arg1);

int func_02079774(void *param)
{
    int result;

    result = func_02073d90(data_020ccf94);
    if (result == 0) {
        result = func_020797bc(0, param);
    }
    return result;
}
