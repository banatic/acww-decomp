/* func_020754e8 @ 0x020754e8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a125c(int, int);

void func_020754e8(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
        if (func_020a132c() != 0) {
            func_020a125c(func_020a132c(), 1);
        }
    }
}
