/* func_02038d50 @ 0x02038d50, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020732c0(void *p);
extern void func_020732cc(void *p, int x);
extern void *data_020ccf94;

void func_02038d50(void)
{
    void *p = data_020ccf94;
    int arg = func_020732c0(p) | 0x20;
    func_020732cc(p, arg);
}
