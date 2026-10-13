/* func_02075334 @ 0x02075334, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a126c(int, int);

void func_02075334(void)
{
    int x;
    int y;

    x = func_020b65c4();
    if (x == 0x2e) {
        y = func_020a132c();
        if (y != 0) {
            func_020a126c(func_020a132c(), 1);
        }
    }
}
