/* func_0201ab94 @ 0x0201ab94, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201abe8(void);
extern int func_0201ab70(int a, int b);

int func_0201ab94(int a)
{
    int r4;
    int r0;
    int r1;

    r4 = a;
    r0 = func_0201abe8();
    r1 = r0;
    r0 = r4;
    func_0201ab70(r0, r1);
    return;
}
