/* func_02035800 @ 0x02035800, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern int func_020356fc(void);

void func_02035800(int param)
{
    if (func_020b6660() || func_020b6640()) {
        asm { add r0, param, #0 }
        func_020356fc();
    }
}
