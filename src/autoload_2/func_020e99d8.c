/* func_020e99d8 @ 0x020e99d8, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void *func_020ea0e0(int argument0, void *argument1);
extern void func_020e99ac(void);
extern int func_020e9a08(void *);

void *func_020e99d8(int argument0, void *argument1)
{
    void *p = func_020ea0e0(argument0, argument1);
    if (p == 0) {
        return 0;
    }
    func_020e99ac();
    func_020e9a08(p);
    return p;
}
