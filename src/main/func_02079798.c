/* func_02079798 @ 0x02079798, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int arg);
extern void func_020797bc(int a, int b);
extern int data_020ccf94;

void func_02079798(int param)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_020797bc(1, param);
    }
}
