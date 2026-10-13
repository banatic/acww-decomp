/* func_0203e37c @ 0x0203e37c, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e31c(void);
extern int func_0203e2f8(void);
extern int func_020961a8(int);
extern void func_0203e2a8(int);
extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);

int func_0203e37c(void)
{
    int r4;

    if (func_0203e31c() != 0 || func_0203e2f8() != 0) {
        return 0;
    }
    r4 = func_020961a8(4);
    if (r4 == 0) {
        return 0;
    }
    func_0203e2a8(6);
    return func_0203e478(0, func_0203efbc(r4), 0xb, 1, 0);
}
