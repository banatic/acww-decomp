/* func_020b3eb8 @ 0x020b3eb8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f08(char *);
extern int func_020b3ed4(int);

int func_020b3eb8(int param)
{
    int a;
    int b;
    int result;

    a = func_020b3f08((char *) param);
    b = func_020b3ed4(param);
    result = a + b;
    return result;
}
