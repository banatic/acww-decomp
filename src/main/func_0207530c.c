/* func_0207530c @ 0x0207530c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1208(int a0, int a1, int a2);

void func_0207530c(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0x2e && func_020a132c()) {
        func_020a1208(func_020a132c(), player, 1);
    }
}
