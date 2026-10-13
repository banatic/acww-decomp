/* func_02060cf4 @ 0x02060cf4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060d3c(int param);
extern unsigned int func_02060e78(int param);
extern void func_02060d24(int a, int b, int c);
extern int data_020cc9d0[];

void func_02060cf4(int arg)
{
    unsigned int index;

    if (func_02060d3c(arg) != 0) {
        return;
    }
    index = func_02060e78(arg);
    if (index >= 7) {
        return;
    }
    func_02060d24(arg, data_020cc9d0[index], index << 2);
}
