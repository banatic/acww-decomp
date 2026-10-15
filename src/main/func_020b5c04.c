/* func_020b5c04 @ 0x020b5c04, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6ea0(void);
extern void func_020a6eb0(int);
extern void func_020b5be4(int);

void func_020b5c04(int param)
{
    if (func_020a6ea0() == 0xb) {
        func_020a6eb0(0xc);
        func_020b5be4(param);
    }
}
