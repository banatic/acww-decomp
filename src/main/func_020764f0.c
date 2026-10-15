/* func_020764f0 @ 0x020764f0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1240(int x, int y, int z);

void func_020764f0(int length, int sequence, unsigned char category, unsigned int player)
{
    int result = func_020b65c4();
    if (result != 46) {
        return;
    }
    result = func_020a132c();
    if (result != 0) {
        func_020a1240(func_020a132c(), player, 1);
    }
    return;
}
