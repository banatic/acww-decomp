/* func_ov123_0229b600 @ 0x0229b600, 0x20 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov123_0229b644(void *);
extern void func_ov123_0229b620(void *);

void func_ov123_0229b600(void *param)
{
    if (func_0206fe60() != 0) {
        func_ov123_0229b644(param);
    } else {
        func_ov123_0229b620(param);
    }
}
