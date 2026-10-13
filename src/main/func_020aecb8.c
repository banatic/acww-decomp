/* func_020aecb8 @ 0x020aecb8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aefa4(int *a, int b);
extern int func_020b00fc(int *a, int b, int c, int d, int e, int f, int g);

int func_020aecb8(int *arg0, int arg1)
{
    int tmp;

    tmp = func_020aefa4(arg0, arg1);
    return func_020b00fc(arg0 + 1, arg1, 0x151d, 2, tmp, 0x25, 0);
}
