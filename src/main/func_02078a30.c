/* func_02078a30 @ 0x02078a30, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02078b64(const void *addr, int val);
extern void func_020e9b9c(int param);
extern char data_021d12a4;

void func_02078a30(int *param0, int param1)
{
    func_020e9b9c(func_02078b64(&data_021d12a4, param1));
    *param0 = param1;
}
