/* func_ov111_022a0ba0 @ 0x022a0ba0, 0x2a bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_022a0a5c(int arg);
extern void func_ov111_022a0b58(int arg);
extern void func_ov111_022a0bcc(int arg);
extern void func_ov111_022a0b20(int arg);

int func_ov111_022a0ba0(int arg)
{
    if (func_ov111_022a0a5c(arg) != 0) {
        return 1;
    }
    func_ov111_022a0b58(arg);
    func_ov111_022a0bcc(arg);
    func_ov111_022a0b20(arg);
    return 1;
}
