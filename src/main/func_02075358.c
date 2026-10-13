/* func_02075358 @ 0x02075358, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int a, int b, int c);
extern int func_020a132c(int a);
extern void func_020a11f8(int a, int b, int c);

void func_02075358(int p1, int p2, int p3)
{
    int ret1;
    int ret2;
    int ret3;

    ret1 = func_020b65c4(p1, p2, p3);
    if (ret1 == 0x2e) {
        ret2 = func_020a132c(ret1);
        if (ret2 != 0) {
            ret3 = func_020a132c(ret2);
            func_020a11f8(ret3, p3, 1);
        }
    }
}
