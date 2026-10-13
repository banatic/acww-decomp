/* func_020e99d8 @ 0x020e99d8, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void *func_020ea0e0(void);
extern void func_020e99ac(void *);
extern void func_020e9a08(void *);

void *func_020e99d8(void)
{
    void *p = func_020ea0e0();
    if (p == 0) {
        return 0;
    }
    func_020e99ac(p);
    func_020e9a08(p);
    return p;
}
