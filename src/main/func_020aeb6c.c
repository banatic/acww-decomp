/* func_020aeb6c @ 0x020aeb6c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef28(void);
extern void func_020b00fc(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);

void func_020aeb6c(char *arg0, int *arg1)
{
    int ret_val;
    ret_val = func_020aef28();
    func_020b00fc(arg0 + 4, arg1, 0x155e, 1, ret_val, 0x25, 0);
}
