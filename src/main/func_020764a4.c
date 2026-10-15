/* func_020764a4 @ 0x020764a4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1248(int, int, int);

void func_020764a4(int a1, int a2, int a3, int a4)
{
    if (func_020b65c4() == 0x2E) {
        if (func_020a132c() != 0) {
            func_020a1248(func_020a132c(), a4, 1);
        }
    }
}
