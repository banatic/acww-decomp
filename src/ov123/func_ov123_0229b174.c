/* func_ov123_0229b174 @ 0x0229b174, 0x2c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072614(void);
extern int func_0207261c(int a, unsigned char b);
extern int func_020b9b6c(void *a, int b, int c, int d);

int func_ov123_0229b174(void *param)
{
    return func_020b9b6c((char *) param + 0x124, func_0207261c(func_02072614(), ((unsigned char *) param)[0xa1]), 6, 0xe);
}
