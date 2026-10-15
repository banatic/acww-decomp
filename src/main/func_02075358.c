/* func_02075358 @ 0x02075358, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a11f8(int a, int b, int c);

void func_02075358(unsigned char *payload, unsigned int length, int player)
{
    int ret1;
    int ret2;
    int ret3;

    ret1 = func_020b65c4();
    if (ret1 == 0x2e) {
        ret2 = func_020a132c();
        if (ret2 != 0) {
            ret3 = func_020a132c();
            func_020a11f8(ret3, player, 1);
        }
    }
}
