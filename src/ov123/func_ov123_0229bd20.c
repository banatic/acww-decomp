/* func_ov123_0229bd20 @ 0x0229bd20, 0x7c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov002_02208054(void *ptr, int n);
extern int func_ov002_0220a784(void *ptr, int n);
extern void func_ov123_0229b620(void *ptr);
extern void func_ov123_0229ae84(void *ptr);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov123_0229bd20(void *param)
{
    int cond;

    if (func_ov002_02208054(param, 1) != 0) {
        func_ov123_0229b620(param);
    } else {
        cond = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
        if (cond != 0) {
            if (func_ov002_0220a784((char *) param + 0x5030, 3) != 0) {
                *(unsigned char *) ((char *) param + 0xa5) = 0x1f;
                func_ov123_0229ae84(param);
            } else if (func_ov002_0220a784((char *) param + 0x5030, 4) != 0) {
                *(unsigned char *) ((char *) param + 0xa5) = 0x20;
                func_ov123_0229ae84(param);
            }
        }
    }
}
