/* func_020aeb6c @ 0x020aeb6c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef28(int a, int b);
extern int func_020b00fc(int a, int b, int c, int d, int e, int f, int g);

int func_020aeb6c(int arg0, int arg1)
{
    int ret_val;
    ret_val = func_020aef28(arg0, arg1);
    return func_020b00fc(arg0 + 4, arg1, 0x155e, 1, ret_val, 0x25, 0);
}
