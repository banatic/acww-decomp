/* func_ov123_02299630 @ 0x02299630, 0xe bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

void func_ov123_02299630(void *param0, unsigned int param1)
{
    unsigned int *p;
    unsigned int val;

    p = (unsigned int *) ((char *) param0 + 0x9c);
    val = *p & ~param1;
    *p = val;
}
