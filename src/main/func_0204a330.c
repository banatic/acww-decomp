/* func_0204a330 @ 0x0204a330, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_ov003_02224140(int, int, int, int);
extern void func_ov004_02233ad4(int, int, int, int);

void func_0204a330(int a, int b, int c, int d)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        func_ov003_02224140(a, b, c, d);
    } else {
        func_ov004_02233ad4(a, b, c, 0);
    }
}
