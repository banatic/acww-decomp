/* func_02075484 @ 0x02075484, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1274(int, int);

void func_02075484(void)
{
    int temp;
    int result;

    temp = func_020b65c4();
    if (temp == 0xd || func_020b65c4() == 0x2f) {
        result = func_020a132c();
        if (result != 0) {
            result = func_020a132c();
            func_020a1274(result, 1);
        }
    }
}
