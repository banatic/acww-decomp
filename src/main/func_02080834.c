/* func_02080834 @ 0x02080834, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207dd10(int a);
extern unsigned char *func_02080864(int a, int b);
extern int func_0209b6c0(int a, unsigned char b, unsigned char c);

int func_02080834(int a, int b)
{
    int tmp;
    unsigned char *p;

    tmp = func_0207dd10(a);
    p = func_02080864(a, tmp);
    if (p != 0) {
        return func_0209b6c0(b, p[0], p[1]);
    }
    return 0;
}
