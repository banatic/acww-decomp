/* func_020764cc @ 0x020764cc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1210(int);

void func_020764cc(int length, int sequence, unsigned char category, unsigned int player)
{
    int temp;

    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            temp = func_020a132c();
            func_020a1210(1);
        }
    }
}
