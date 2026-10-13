/* func_ov144_0229a6c8 @ 0x0229a6c8, 0x54 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void func_ov004_0223c310(void);
extern void func_ov144_02299694(void *p, short s);
extern void func_ov144_02299670(void *p, int n);
extern void func_ov144_02299b7c(void *p);
extern void func_ov144_0229a7c8(void *p);
extern void RtcSendPxiCommand(int cmd);

void func_ov144_0229a6c8(void *p)
{
    int flag;
    short *field;

    flag = data_020e54a8 ? 0 : 1;
    if (flag == 0) {
        func_ov004_0223c310();
    }
    func_ov144_02299694(p, *(short *) ((char *) p + 0xbc));
    field = (short *) ((char *) p + 0xbc);
    *field = -1;
    func_ov144_02299670(p, 8);
    func_ov144_02299b7c(p);
    func_ov144_0229a7c8(p);
    RtcSendPxiCommand(0x56);
}
