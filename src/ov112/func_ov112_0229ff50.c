/* func_ov112_0229ff50 @ 0x0229ff50, 0xc bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);

void func_ov112_0229ff50(void *receiver)
{
    RtcSendPxiCommand(0x34);
}
