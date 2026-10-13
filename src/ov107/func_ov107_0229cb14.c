/* func_ov107_0229cb14 @ 0x0229cb14, 0x28 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *addr, int val);
extern void func_ov002_02208098(void *addr, int val);
extern void RtcSendPxiCommand(unsigned int cmd);

void func_ov107_0229cb14(void *param)
{
    func_ov002_0220a720((char *) param + 0x2828, 9);
    func_ov002_02208098(param, 15);
    RtcSendPxiCommand(0x28);
}
