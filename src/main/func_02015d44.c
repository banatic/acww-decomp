/* func_02015d44 @ 0x02015d44, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern unsigned char func_020a13d0(void);
extern int func_020952ec(void);

int func_02015d44(void)
{
    if (func_020b65c4() == 0x2f) {
        return func_020a13d0();
    } else {
        return func_020952ec();
    }
}
