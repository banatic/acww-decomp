/* func_0201abd0 @ 0x0201abd0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201ac10(void);
extern int func_0201abac(int a, int b);

int func_0201abd0(int a)
{
    int r4 = a;
    int r1 = func_0201ac10();
    return func_0201abac(r4, r1);
}
