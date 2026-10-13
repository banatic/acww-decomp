/* func_020804e8 @ 0x020804e8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080500(void);
extern int func_020807c0(int a, int b);

int func_020804e8(int a)
{
    int b;
    int c;

    b = a;
    c = func_02080500();
    return func_020807c0(b, c);
}
