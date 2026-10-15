/* func_020796e4 @ 0x020796e4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_020797bc(int, int);

void func_020796e4(int arg0)
{
    int ret = func_02073d90(data_020ccf94);
    if (ret != 0) {
        return;
    }
    func_020797bc(5, arg0);
}
