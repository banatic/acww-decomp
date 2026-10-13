/* func_02015d44 @ 0x02015d44, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void func_020a13d0(void);
extern void func_020952ec(void);

void func_02015d44(void)
{
    if (func_020b65c4() == 0x2f) {
        func_020a13d0();
    } else {
        func_020952ec();
    }
}
