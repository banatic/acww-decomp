/* func_02036714 @ 0x02036714, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(void);
extern int func_02036754(int);

int func_02036714(void)
{
    int r4;
    int r5;
    int r0;

    r4 = func_020b65c4();
    func_020b5e10();
    r5 = func_020b5e84();
    r4 = func_02036754(r4);
    r0 = func_02036754(r5);
    if (r4 == r0) {
        if (r4 != 0xffff) {
            return 1;
        }
    }
    return 0;
}
