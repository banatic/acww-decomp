/* func_ov123_0229b5cc @ 0x0229b5cc, 0x34 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov123_02299630(void *, int);
extern void func_ov123_0229b56c(void *, int, int);

void func_ov123_0229b5cc(void *r0)
{
    void *r4 = r0;
    RtcSendPxiCommand(0x29);
    func_ov123_02299630(r4, 8);
    if (((unsigned char *) r4)[0xac] == 2) {
        ((unsigned char *) r4)[0xac] = 0;
    }
    func_ov123_0229b56c(r4, 6, 9);
}
