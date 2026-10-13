/* func_020ed68c @ 0x020ed68c, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_021fbffa[];
extern int func_020ed950(int, int, char *, int);

int func_020ed68c(int a, int b)
{
    data_021fbffa[b * 4] = 0;
    return func_020ed950(a, b, data_021fbffa, 0);
}
