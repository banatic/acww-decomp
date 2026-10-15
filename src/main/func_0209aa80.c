/* func_0209aa80 @ 0x0209aa80, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099640(int object);
extern void func_0209aa9c(int);

void func_0209aa80(void)
{
    int forwarded_value;

    if ((forwarded_value = (int) func_020984e8()) != 0) {
        func_0209aa9c((int) func_02099640((int) forwarded_value));
    }
}
