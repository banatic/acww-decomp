/* func_020ed68c @ 0x020ed68c, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_021fbffa[];
extern void func_020ed950(void *);

void func_020ed68c(int a, int b)
{
    data_021fbffa[b * 4] = 0;
    func_020ed950((void *) a);
}
