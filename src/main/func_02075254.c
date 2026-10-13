/* func_02075254 @ 0x02075254, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a11b8(int, int);

void func_02075254(void)
{
    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a11b8(func_020a132c(), 1);
        }
    }
}
