/* func_02095a28 @ 0x02095a28, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200a254(int, int, int);

int func_02095a28(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_0200a254(r, 6, -1);
    }
    return 0;
}
