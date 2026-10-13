/* func_0209abd0 @ 0x0209abd0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209ad9c(void *arg, int flag);
extern void func_0209b56c(void);
extern void func_0209b4d8(void *param1, int param2, int param3, int param4);
extern void func_0209ac30(void *arg);
extern void func_0209abc0(void *arg);

void func_0209abd0(void *arg)
{
    void *ret_val;
    ret_val = func_0209ad9c(arg, 0);
    func_0209b56c();
    func_0209b4d8(ret_val, 0xb, 0, 0);
    func_0209ac30(arg);
    func_0209abc0(arg);
}
