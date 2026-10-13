/* func_02035800 @ 0x02035800, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_020356fc(int param);

void func_02035800(int param)
{
    if (func_020b6660() || func_020b6640()) {
        func_020356fc(param);
    }
}
