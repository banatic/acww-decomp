/* func_02076434 @ 0x02076434, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1264(int, int);

void func_02076434(void)
{
    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a1264(func_020a132c(), 1);
        }
    }
}
