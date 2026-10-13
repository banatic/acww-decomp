/* func_02076458 @ 0x02076458, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int a1, int a2, int a3, int a4);
extern int func_020a132c(void);
extern void func_020a1208(int a, int b, int c);

void func_02076458(int a1, int a2, int a3, int a4)
{
    if (func_020b65c4(a1, a2, a3, a4) == 0x2e) {
        if (func_020a132c()) {
            func_020a1208(func_020a132c(), a4, 1);
        }
    }
}
