/* func_020950f8 @ 0x020950f8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020950d4(void);
extern int func_02095128(int, int, int);

int func_020950f8(int a, int b)
{
    int r;
    r = func_020950d4();
    while (r == 0 || func_02095128(r, a, b) == 1) {
        r = func_020950d4();
    }
    return r;
}
