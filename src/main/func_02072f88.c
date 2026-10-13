/* func_02072f88 @ 0x02072f88, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072614(int);
extern int func_02072f74(int);
extern int func_0207261c(int, int);

int func_02072f88(int arg0)
{
    int local_0;
    int r4;
    int r5;
    int result;

    r5 = arg0;
    r4 = func_02072614(r5);
    result = func_02072f74(r5);
    result = func_0207261c(r4, result);
    return result;
}
