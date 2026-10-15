/* func_02075380 @ 0x02075380, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1200(int, int, int);

void func_02075380(unsigned char *payload, unsigned int length, int player)
{
    int r4 = player;
    int result;

    result = func_020b65c4();
    if (result == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a1200(func_020a132c(), r4, 1);
        }
    }
}
