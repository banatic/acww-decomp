/* func_ov123_0229b384 @ 0x0229b384, 0x40 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02088220(int arg);
extern void *func_ov123_02299d9c(void *arg);
extern void func_02072d84(void *a, void *b);
extern void *func_02072d4c(void *a);
extern void func_02072f38(void *a);
extern void func_02072f54(void *a, unsigned char b);

extern unsigned char data_021f3278[];

void func_ov123_0229b384(void *param)
{
    void *r4;
    r4 = func_02088220((unsigned int) data_021f3278);
    func_02072d84(r4, func_ov123_02299d9c(param));
    func_02072f38(func_02072d4c(r4));
    func_02072f54(func_02072d4c(r4), ((unsigned char *) param)[0xa1]);
}
