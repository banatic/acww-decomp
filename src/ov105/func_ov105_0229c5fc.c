/* func_ov105_0229c5fc @ 0x0229c5fc, 0x30 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov105_0229c5fc(void *param)
{
    void *r4;
    r4 = param;
    RtcSendPxiCommand(0x2a);
    func_ov002_0220a720((char *) r4 + 0x5fb8, 4);
    *(char *) ((char *) r4 + 0x8c) = 0x12;
    func_ov002_02208098(r4, 0x1b);
}
